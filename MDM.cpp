#include "MDM.h"
#include "PDM.h"
#include "purchase.h"

PurchaseManagement::PurchaseManagement(ClientManagement& cm, ProductManagement& pm) :
cm_(cm), pm_(pm) {}		//고객 정보 리스트와 제품 정보 리스트를 가져와서 안에 있는 정보를 모두 레퍼런스로 받아서 사용

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
	return purchaseList_[id];
}

// 쇼핑 정보 입력
void PurchaseManagement::mmInput()
{
	int flag = 0;
	int ID, clientID, productID, sellAmount;
	string sellTime;

	while (flag != 1) { 
		cout << "구매자 ID: "; Primary::integerInput(clientID, flag);
		if (clientID < 10001) {
			cout << "(ID:10001부터 시작입니다)" << endl;
			flag = 0;
		}
	}
	flag = 0; 
	while (flag != 1) {
		cout << "구매한 제품 ID: "; Primary::integerInput(productID, flag);
		if (productID < 30001) {
			cout << "(ID:30001부터 시작입니다)" << endl;
			flag = 0;
		}
	}
	flag = 0; while (flag != 1) { cout << "구매 개수: "; Primary::integerInput(sellAmount, flag); }
	cout << "구매 날짜: "; cin >> sellTime;

	ID = makeID();
	Purchase* m = new Purchase(ID, clientID, productID, sellAmount, sellTime);
	purchaseList_[makeID()] = m;

}

// 쇼핑 정보 조회
void PurchaseManagement::mmOutput(ClientManagement& cm, ProductManagement& pm)
{
	cout << "─────────────────────────────────────────────────────────" << endl;
	for_each(purchaseList_.begin(), purchaseList_.end(), [&](auto mm)
		{Purchase* m = mm.second;			// 쇼핑 정보 map의 value에 접근 -> value가 Purchase* 형태
	if (m != nullptr) {
		Client* c = cm.cmChooseID(m->CID());	// 
		Product* p = pm.pdchooseID(m->PID());
		cout << m->id() << " : " << c->getName() << " : "
			<< c->getGender() << " : " << c->getAge() << " : "
			<< p->getName() << " : " << m->getAmount() << " : "
			<< m->getTime() << " : " << (m->getAmount()) * (p->getPrice()) << endl;
		cout << "---------------------------------------------------------" << endl;
	}
		}
	); 
}
// 고객 이름으로 검색하기
void PurchaseManagement::mmSearchCID()
{
	int found = 0;
	string name;
	string cmp_name;
	cout << "고객 이름을 입력하세요: "; cin >> name;
	cout << "─────────────────────────────────────────────────────────" << endl;

	for (auto i = purchaseList_.begin(); i != purchaseList_.end(); i++) {
		if (i->second != nullptr) {
			Client* c = cm_.cmChooseID(i->second->CID());
			Product* p = pm_.pdchooseID(i->second->PID());
			Purchase* m = i->second;
			cmp_name = c->getName();

			if (name == cmp_name) {
				found = 1;
				cout << m->id() << " : " << c->getName() << " : "
					<< c->getGender() << " : " << c->getAge() << " : "
					<< p->getName() << " : " << m->getAmount() << " : "
					<< m->getTime() << " : " << (m->getAmount()) * (p->getPrice()) << endl;
				cout << "---------------------------------------------------------" << endl;
			}
		}
		cmp_name = "";
	}

	if (found == 0) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "!!주문 내역이 없습니다!!" << endl;
		cout << "*************************" << endl;
	}
}
void PurchaseManagement::mmSearchPID()
{
	int found = 0;
	string name;
	string cmp_name;
	cout << "제품 이름을 입력하세요: "; cin >> name;
	cout << "─────────────────────────────────────────────────────────" << endl;

	for (auto i = purchaseList_.begin(); i != purchaseList_.end(); i++) {
		if (i->second != nullptr) {
			Client* c = cm_.cmChooseID(i->second->CID());
			Product* p = pm_.pdchooseID(i->second->PID());
			Purchase* m = i->second;
			cmp_name = p->getName();

			if (name == cmp_name) {
				found = 1;
				cout << m->id() << " : " << c->getName() << " : "
					<< c->getGender() << " : " << c->getAge() << " : "
					<< p->getName() << " : " << m->getAmount() << " : "
					<< m->getTime() << " : " << (m->getAmount()) * (p->getPrice()) << endl;
				cout << "---------------------------------------------------------" << endl;
			}
		}
		cmp_name = "";
	}

	if (found == 0) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "!!주문 내역이 없습니다!!" << endl;
		cout << "*************************" << endl;
	}
}
void PurchaseManagement::deleteReceipt(int id)
{
	if (!(purchaseList_[id])) {
		cout << endl;
		cout << "**************************" << endl;
		cout << "!!주문 내역이 없습니다!!" << endl;
		cout << "**************************" << endl;
	}
	else {
		purchaseList_.erase(id);
		cout << endl << "────────────────────────────────" << endl;
		cout << "!!성공적으로 제거 되었습니다!!" << endl;
		cout << endl << "────────────────────────────────" << endl;
	}
}
void PurchaseManagement::mmRevise(int id) // 다바꿔도 됨
{
	Purchase* m = purchaseList_[id];
	Client* c = cm_.cmChooseID(m->CID());
	Product* p = pm_.pdchooseID(m->PID());

	if (!(purchaseList_[id])) {			// 찾는 아이디가 없으면 출력
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!존재하지 않는 고객입니다!!" << endl;
		cout << "****************************" << endl;
	}

	else {
		cout << m->id() << " 이름: " << c->getName() << " 성별: "
			<< c->getGender() << " 나이: " << c->getAge() << endl << " 제품명: "
			<< p->getName() << " 주문량: " << m->getAmount() << " 주문날짜: "
			<< m->getTime() << " 주문금액: " << (m->getAmount()) * (p->getPrice()) << endl;

		int num, clientID, productID, sellAmount; char one;
		string sellTime;
		cout << endl << "                  바꾸고 싶은 정보를 입력하세요.                  " << endl;
		cout << "1: 고객정보   |   2: 제품정보   |   3: 주문량   |   4: 주문날짜" << endl;
		Primary::switchInput(num, one); cout << endl;

		switch (num) {
		case 1:
			cout << "고객 ID : "; cin >> clientID;		// 고객이 한번이라도 주문했는지 확인
			m->setClient(clientID);
			break;
		case 2:
			cout << "제품 ID : "; cin >> productID;		// 제품이 한번이라도 구매된건지 확인
			m->setProduct(productID);
			break;
		case 3:
			cout << "주문량 : "; cin >> sellAmount;
			m->setAmount(sellAmount);
			break;
		case 4:
			cout << "주문날짜 : "; cin >> sellTime;
			m->setTime(sellTime);
			break;
		}
		if (0 < num && num < 5) {
			cout << endl << "────────────────────────────────" << endl;
			cout << "  !!성공적으로 변경 되었습니다!!  " << endl;
			cout << endl << "────────────────────────────────" << endl;
		}
	}
}
