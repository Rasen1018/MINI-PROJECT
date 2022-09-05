#include "MDM.h"
#include "PDM.h"
#include "purchase.h"
#include <fstream>
#include <sstream>
#include <Windows.h>

PurchaseManagement::PurchaseManagement(ClientManagement& cm, ProductManagement& pm) : cm_(cm), pm_(pm)
//고객 정보 리스트와 제품 정보 리스트를 가져와서 안에 있는 정보를 모두 레퍼런스로 받아서 사용
{
	ifstream file;
	file.open("shoppinglist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');	//vector의 순서 나누는 기준을 ','로 설정
			if (row.size()) {
				int id = atoi(row[0].c_str());			//메모장에 저장되어있는 문자를 integer로 바꿔서 id에 대입
				int clientID = atoi(row[1].c_str());
				int productID = atoi(row[2].c_str());
				int sellAmount = atoi(row[3].c_str());
				Purchase* m = new Purchase(id, clientID, productID, sellAmount, row[4]);
										//id, 고객ID, 상품ID, 주문수량, 주문일자 순
				purchaseList_.insert({ id, m });
			}
		}
	}
	file.close();
}

PurchaseManagement::~PurchaseManagement()
{
	ofstream file;
	file.open("shoppinglist.txt");
	if (!file.fail()) {
		for (const auto& v : purchaseList_) {
			Purchase* m = v.second;
			if (m != nullptr) {
				file << m->id() << ',' << m->CID() << ","
					<< m->PID() << ',' << m->getAmount() << ','
					<< m->getTime() << endl;
			}
		}
	}
	cout << "******쇼핑 리스트 저장 완료******" << endl;
	file.close();
}

vector<string> PurchaseManagement::parseCSV(istream& file, char delimiter)
{
	stringstream ss;
	vector<string> row;
	string t = " \n\r\t";

	//stringstream을 이용하여 단어 나누기
	while (!file.eof()) {
		char c = file.get();
		if (c == delimiter || c == '\r' || c == '\n') {
			if (file.peek() == '\n') file.get();
			string s = ss.str();
			s.erase(0, s.find_first_not_of(t));
			s.erase(s.find_last_not_of(t) + 1);
			row.push_back(s);
			ss.str("");
			if (c != delimiter) break;
		}
		else {
			ss << c;
		}
	}
	return row;
}

// 쇼핑 리스트 ID 생성
int PurchaseManagement::makeID()
{
	auto key = purchaseList_.end();
	if (purchaseList_.size() == 0) {
		return 110001;
	}
	else {
		int id = (--key)->first;
		return ++id;
	}
}

// 특정 ID에 대한 쇼핑 리스트 가져오기
Purchase* PurchaseManagement::mmChooseID(int id) {
	auto it = purchaseList_.find(id);
	return (it != purchaseList_.end()) ? purchaseList_[id] : nullptr;
}

// 쇼핑 정보 입력
void PurchaseManagement::mmInput()
{
	int flag = 0;
	int ID, clientID, productID, sellAmount;
	string sellTime;

	cout << endl << "────────────────────────────────────────────────────────────────────────────" << endl;

	cm_.showList(); // 입력하기 전 고객 정보 보여주기

	while (flag != 1) { 
		cout << "구매자 ID: "; Primary::integerInput(clientID, flag);		// 고객 ID 입력
		if (clientID < 10001) {												// 올바른 ID가 들어올 때까지 while문 반복
			cout << "(ID:10001부터 시작입니다)" << endl;
			flag = 0;
		}
	}
	flag = 0; 
	while (flag != 1) {
		cout << "구매한 상품 ID: "; Primary::integerInput(productID, flag);	// 상품 ID 입력
		if (productID < 30001) {											// 올바른 ID가 들어올 때까지 while문 반복
			cout << "(ID:30001부터 시작입니다)" << endl;
			flag = 0;
		}
	}
	flag = 0;
	Product* p = pm_.pdchooseID(productID);			// 상품리스트 받아오기
	int stock = p->getStock();						// 상품리스트 재고 받아오기
	while (flag != 1) {
		cout << "구매 개수: "; Primary::integerInput(sellAmount, flag);
		if (stock < sellAmount)		// 구매 개수보다 재고가 적다면 오류메세지 출력
		{
			cout << endl << "!!재고 부족입니다!!" << endl;
			cout << "남은 재고: " << stock << endl << endl;
			flag = 0;
		}
	} p->setStock(stock - sellAmount);		// 재고에 구매 수량 반영

	cout << "구매 날짜: "; cin >> sellTime;
	ID = makeID();

	Purchase* m = new Purchase(ID, clientID, productID, sellAmount, sellTime);
	purchaseList_[makeID()] = m;

	cout << endl << "성공적으로 입력했습니다." << endl << "잠시후 메인메뉴로 돌아갑니다." << endl;
	Sleep(1000); Sleep(1000);
	system("cls");

}

// 쇼핑 정보 조회
void PurchaseManagement::mmOutput(ClientManagement& cm, ProductManagement& pm)
{
	cout << "────────────────────────────────────────────────────────────────────────────" << endl;
	for_each(purchaseList_.begin(), purchaseList_.end(), [&](auto mm)
		{Purchase* m = mm.second;			// 쇼핑 정보 map의 value에 접근 -> value가 Purchase* 형태
	if (m != nullptr) {
		Client* c = cm.cmChooseID(m->CID());	// 고객 리스트와 상품 리스트 받아오기 
		Product* p = pm.pdchooseID(m->PID());
		cout << "[" << m->id() << "] 고객이름: " << c->getName()
			<< " 성별: " << c->getGender() << " 나이: " << c->getAge() << endl;
		cout << setw(17) << setfill(' ') << " 제품명: " << p->getName() << endl;
		cout << setw(19) << setfill(' ') <<" 주문수량: " << m->getAmount() 
			<<" 주문금액: " << (m->getAmount()) * (p->getPrice())
			<< " 주문일자: " << m->getTime() << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
	}
		}
	); 
}
// 고객 이름으로 검색하기
void PurchaseManagement::mmSearchCID()
{
	int found = 0;
	char one;
	string name;
	string cmp_name;
	cout << "고객 이름을 입력하세요: "; cin >> name;
	cout << "────────────────────────────────────────────────────────────────────────────" << endl;

	for (auto i = purchaseList_.begin(); i != purchaseList_.end(); i++) {
		if (i->second != nullptr) {
			Client* c = cm_.cmChooseID(i->second->CID());
			Product* p = pm_.pdchooseID(i->second->PID());
			Purchase* m = i->second;
			cmp_name = c->getName();

			if (name == cmp_name) {
				found = 1;
				cout << "[" << m->id() << "] 고객이름: " << c->getName()
					<< " 성별: " << c->getGender() << " 나이: " << c->getAge()
					<< endl << "        " << " 제품명: " << p->getName()
					<< " 주문수량: " << m->getAmount() << " 주문일자: " << m->getTime()
					<< " 주문금액: " << (m->getAmount()) * (p->getPrice()) << endl;
				cout << "--------------------------------------------------------------------------" << endl;
			}
		}
		cmp_name = "";
	}

	if (found == 0) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!구매 내역이 없습니다!!" << endl;
		cout << "\t\t" << "!!잠시후에 메인 메뉴로 돌아갑니다!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
		system("cls");
	}
	else {
		cout << endl << endl << "\t" << "아무키나 입력하면 메인화면으로 돌아갑니다." << endl;
		one = _getch();
		system("cls");
		cin.ignore();
	}
}
void PurchaseManagement::mmSearchPID()
{
	char one;
	int found = 0;
	string category;
	string cmp_catg;
	cout << "제품 이름을 입력하세요: "; cin >> category;
	cout << "────────────────────────────────────────────────────────────────────────────" << endl;

	for (auto i = purchaseList_.begin(); i != purchaseList_.end(); i++) {
		if (i->second != nullptr) {
			Client* c = cm_.cmChooseID(i->second->CID());
			Product* p = pm_.pdchooseID(i->second->PID());
			Purchase* m = i->second;
			cmp_catg = p->category();

			if (category == cmp_catg) {
				found = 1;
				cout << "[" << m->id() << "] 고객이름: " << c->getName() 
					<< " 성별: " << c->getGender() << " 나이: " << c->getAge() 
					<< endl << "        " << " 제품명: " << p->getName()
					<< " 주문수량: " << m->getAmount() << " 주문일자(YY-MM-DD): " << m->getTime() 
					<< " 주문금액: " << (m->getAmount()) * (p->getPrice()) << endl;
				cout << "-----------------------------------------------------------------------------" << endl;
			}
		}
		cmp_catg = "";
	}

	if (found == 0) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!찾는 품목이 없습니다!!" << endl;
		cout << "\t\t" << "!!잠시후에 메인 메뉴로 돌아갑니다!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
		system("cls");
	}
	else {
		cout << endl << endl << "\t" << "아무키나 입력하면 메인화면으로 돌아갑니다." << endl;
		one = _getch();
		system("cls");
		cin.ignore();
	}
}
void PurchaseManagement::deleteReceipt(int id)
{
	if (purchaseList_.find(id)==purchaseList_.end()) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!주문 내역이 없습니다!!" << endl;
		cout << "\t\t" << "!!잠시후에 메인 메뉴로 돌아갑니다!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}
	else {
		purchaseList_.erase(id);
		cout << endl << "\t\t" << "────────────────────────────────────" << endl;
		cout << "\t\t" << "!!성공적으로 제거 되었습니다!!" << endl;
		cout << "\t\t" << "!!잠시후에 메인 메뉴로 돌아갑니다!!" << endl;
		cout << endl << "\t\t" << "────────────────────────────────────" << endl;
		Sleep(1000); Sleep(1000);
	}
	getchar();
}

void PurchaseManagement::mmRevise(int id) // 다바꿔도 됨
{
	map<int, Purchase*> ::iterator it;
	it = purchaseList_.find(id);
	// 찾는 ID가 없으면 출력
	if (it == purchaseList_.end()) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!주문 내역이 없습니다!!" << endl;
		cout << "\t\t" << "!!잠시후에 메인 메뉴로 돌아갑니다!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}
	else {
		Purchase* m = purchaseList_[id];
		Client* c = cm_.cmChooseID(m->CID());
		Product* p = pm_.pdchooseID(m->PID());
		cout << "[" << m->id() << "] 고객이름: " << c->getName()
			<< " 성별: " << c->getGender() << " 나이: " << c->getAge()
			<< endl << "        " << " 제품명: " << p->getName()
			<< " 주문수량: " << m->getAmount() << " 주문일자: " << m->getTime()
			<< " 주문금액: " << (m->getAmount()) * (p->getPrice()) << endl;

		int num, clientID, productID, sellAmount; char one;
		string sellTime;
		cout << endl << "                  바꾸고 싶은 정보를 입력하세요.                  " << endl;
		cout << "1: 고객정보   |   2: 상품정보   |   3: 주문량   |   4: 주문일자" << endl;
		Primary::switchInput(num, one); cout << endl;

		switch (num) {
		case 1:
			cout << "(고객의 세부 정보는 [고객 정보 관리]에서 바꿀 수 있습니다.) "
				<< endl << "변경되어 저장될 고객 ID를 입력하세요 : ";
			cin >> clientID; m->setClient(clientID);      // 고객이 한번이라도 주문했는지 확인
			break;
		case 2:
			cout << "(상품의 세부 정보는 [상품 정보 관리]에서 바꿀 수 있습니다.) "
				<< endl << "변경되어 저장될 제품 ID를 입력하세요 : ";
			cin >> productID; m->setProduct(productID);      // 제품이 한번이라도 구매된건지 확인      
			break;
		case 3:
			cout << "주문량 : "; cin >> sellAmount;
			m->setAmount(sellAmount);
			break;
		case 4:
			cout << "주문날짜 : "; cin >> sellTime;
			m->setTime(sellTime);
			break;
		default:
			getchar();
			system("cls");
			break;
		}
		if (0 < num && num < 5) {
			cout << endl << "\t\t" << "────────────────────────────────────" << endl;
			cout << "\t\t" << "!!성공적으로 변경 되었습니다!!" << endl;
			cout << "\t\t" << "!!잠시후에 메인 메뉴로 돌아갑니다!!" << endl;
			cout << endl << "\t\t" << "────────────────────────────────────" << endl;
			Sleep(1000); Sleep(1000); system("cls");
		}
	}
}
