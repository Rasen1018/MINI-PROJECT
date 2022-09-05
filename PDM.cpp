#include "PDM.h"
#include <sstream>
#include <fstream>
#include <Windows.h>

ProductManagement::ProductManagement()
{
	ifstream file;
	file.open("productlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');	//vector의 순서 나누는 기준을 ','로 설정
			if (row.size()) {
				int id = atoi(row[0].c_str());		//메모장에 저장되어있는 문자를 integer로 바꿔서 id에 대입
				int price = atoi(row[2].c_str());
				int stock = atoi(row[3].c_str());
				Product* p = new Product(id, row[1], price, stock, row[4]);
										//id, name, price, stock, category 순
				productList_.insert({ id, p });
			}
		}
	}
	file.close();
}

ProductManagement::~ProductManagement()
{
	ofstream file;
	file.open("productlist.txt");
	if (!file.fail()) {
		for (const auto& v : productList_) {
			Product* p = v.second;
			if (p != nullptr) {
				file << p->getID() << ","		//ID 순서대로 제품 정보 저장
					<< p->getName() << ","
					<< (p->getPrice()) / 1000 << ","
					<< p->getStock() << ","
					<< p->category() << endl;
			}
		}
	}
	cout << "******상품 리스트 저장 완료******" << endl;
	file.close();
}

vector<string> ProductManagement::parseCSV(istream& file, char delimiter)
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

//제품 정보 입력
void ProductManagement::pdInput()
{
	int flag = 0;
	int id, stock, price;
	string productName, category;
	
	cout << "제품명 : "; getline(cin, productName, '\n');
	while (flag != 1) { cout << "가격(단위:천원) : "; Primary::integerInput(price, flag); }
	flag = 0; while (flag != 1) { cout << "재고 수량 : "; Primary::integerInput(stock, flag); }
	cout << "품목 : "; cin >> category;

	id=makeID();
	Product* p = new Product(id, productName, price, stock, category);
	productList_[makeID()] = p;

	cout << endl << "성공적으로 입력했습니다." << endl << "잠시후 메인메뉴로 돌아갑니다." << endl;
	Sleep(1000); Sleep(1000);
	system("cls");
}

//제품 정보 조회
void ProductManagement::pdOutput() {

	cout << "────────────────────────────────────────────────────────────────────────────" << endl;
	for_each(productList_.begin(), productList_.end(), 
		[](auto pm) {Product* p = pm.second;
	if (p != nullptr) {
		cout << "[" << p->getID() << "] 제품명: "
			<< p->getName() << " 가격: "
			<< p->getPrice() << " 재고수량: "
			<< p->getStock() << " 품목: "
			<< p->category() << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
	}
		}
	);
}

Product* ProductManagement::pdchooseID(int id) {
	auto it = productList_.find(id);
	return (it != productList_.end()) ? productList_[id] : nullptr;
}

//제품 ID로 검색
void ProductManagement::pdSearchID(int id) {

	char one;
	Product* p = productList_[id];

	//ID가 없을 때
	if (productList_.find(id)==productList_.end())
	{
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!존재하지 않는 제품입니다!!" << endl;
		cout << "\t\t" << "!!잠시후에 메인 메뉴로 돌아갑니다!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
		system("cls");
	}

	//ID가 있을 때
	else {
		cout << "────────────────────────────────────────────────────────────────────────────" << endl
			<< id << " 제품 정보" << endl
			<< "────────────────────────────────────────────────────────────────────────────" << endl;
	cout << "제품명: " << p->getName() << " 가격: "
		<< p->getPrice() << " 재고수량: "
		<< p->getStock() << " 품목: "
		<< p->category() << endl;

	cout << endl << endl << "\t" << "아무키나 입력하면 메인화면으로 돌아갑니다." << endl;
	one = _getch();
	system("cls");
	cin.ignore();
	}
}

//제품 품목으로 검색
void ProductManagement::pdSearchCategory() {

	int found = 0;
	char one;
	string catg;
	string cmp_catg;

	cout << "검색할 품목을 입력하세요. "; cin >> catg;
	cout << "────────────────────────────────────────────────────────────────────────────" << endl;


	for (auto i = productList_.begin(); i != productList_.end(); i++) {
		if (i->second != nullptr)
			cmp_catg = i->second->category();

		//맞는 품목이 있다면 정보 출력
		if (cmp_catg == catg) {
			found = 1;
			cout << "제품명: " << i->second->getName() << " 가격: "
				<< i->second->getPrice() << " 재고수량: "
				<< i->second->getStock() << " 품목: "
				<< i->second->category() << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
		}
		cmp_catg = "";
	}

	//맞는 품목이 없다면
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

//제품 ID 할당
int ProductManagement::makeID() {
	auto key = productList_.end();
	if (productList_.size() == 0) {
		return 30001;
	}
	else
	{
		int id = (--key)->first;
		return ++id;
	}
}

//해당 ID로 제품 삭제
void ProductManagement::deleteProduct(int id) {

	if(productList_.find(id)==productList_.end()) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!존재하지 않는 제품입니다!!" << endl;
		cout << "\t\t" << "!!잠시후에 메인 메뉴로 돌아갑니다!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}
	else {
		productList_.erase(id);
		cout << endl << "\t\t" << "────────────────────────────────────" << endl;
		cout << "\t\t" << "!!성공적으로 제거 되었습니다!!" << endl;
		cout << "\t\t" << "!!잠시후에 메인 메뉴로 돌아갑니다!!" << endl;
		cout << endl << "\t\t" << "────────────────────────────────────" << endl;
		Sleep(1000); Sleep(1000);
	}
	getchar();
}

//해당 제품 변경
void ProductManagement::pdRevise(int id) {

	Product* p = productList_[id];

	if (!(productList_[id])) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!존재하지 않는 제품입니다!!" << endl;
		cout << "\t\t" << "!!잠시후에 메인 메뉴로 돌아갑니다!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}

	else {
		cout << "제품명: " << p->getName() << " 가격: "
			<< p->getPrice() << " 재고수량: "
			<< p->getStock() << " 품목: "
			<< p->category() << endl << endl;

		int num, stock, price; char one;
		string name, category;
		cout << "────────────────────────────────────────────────────────────────────────────" << endl;
		cout << "              바꾸고 싶은 정보를 입력하세요.              " << endl;
		cout << "1: 제품명   |   2: 가격   |   3: 재고 수량   |   4: 품목   |   0: 취소" << endl;
		Primary::switchInput(num, one); cout << endl;

		//바꾸고 싶은 정보에 따라 switch 문 실행
		switch (num) {
		case 1:		//제품명 변경
			cout << "제품명 : "; cin.ignore(); getline(cin, name, '\n');
			p->setName(name);
			break;
		case 2:		//가격 변경
			cout << "가격 : "; cin >> price;
			p->setPrice(price);
			break;
		case 3:		//재고수량 변경
			cout << "재고 수량 : "; cin >> stock;
			p->setStock(stock);
			break;
		case 4:		//품목 변경
			cout << "품목 : "; cin >> category;
			p->setcatg(category);
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

void ProductManagement::showList() {
	for (auto pm : productList_) {
		Product* p = pm.second;
		if (p != nullptr) {
			cout << "[" << p->getID() << "] 제품명: "
				<< p->getName() << " 가격: "
				<< p->getPrice() << " 재고수량: "
				<< p->getStock() << " 품목: "
				<< p->category() << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
		}
	}
}