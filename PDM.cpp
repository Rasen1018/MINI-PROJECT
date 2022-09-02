#include "PDM.h"

ProductManagement::ProductManagement() {}

//제품 정보 입력
void ProductManagement::pdInput()
{
	int flag = 0;
	int id, stock, price;
	string productName, category;
	
	cout << "제품명 : "; cin >> productName;
	while (flag != 1) { cout << "가격(단위:천원) : "; Primary::integerInput(price, flag); }
	flag = 0; while (flag != 1) { cout << "재고 수량 : "; Primary::integerInput(stock, flag); }
	cout << "품목 : "; cin >> category;

	id=makeID();
	Product* p = new Product(id, productName, price, stock, category);
	productList_[makeID()] = p;
}

//제품 정보 조회
void ProductManagement::pdOutput() {

	cout << "─────────────────────────────────────────────────────────" << endl;
	for_each(productList_.begin(), productList_.end(), 
		[](auto pm) {Product* p = pm.second;
	if (p != nullptr) {
		cout << p->getID() << " : "
			<< p->getName() << " : "
			<< p->getPrice() << " : "
			<< p->getStock() << " : "
			<< p->category() << endl;
		cout << "---------------------------------------------------------" << endl;
	}
		}
	);
}

Product* ProductManagement::pdchooseID(int id) {
	return productList_[id];
}

//제품 ID로 검색
void ProductManagement::pdSearchID(int id) {

	Product* p = productList_[id];

	//ID가 없을 때
	if (!(productList_[id]))
	{
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!존재하지 않는 제품입니다!!" << endl;
		cout << "****************************" << endl;
	}

	//ID가 있을 때
	else {
		cout << "──────────────────────────────" << endl
			<< id << " 제품 정보" << endl
			<< "──────────────────────────────" << endl;
	cout << p->getName() << " : "
		<< p->getPrice() << " : "
		<< p->getStock() << " : "
		<< p->category() << endl;
	}
}

//제품 품목으로 검색
void ProductManagement::pdSearchCategory() {

	int found = 0;
	string catg;
	string cmp_catg;

	cout << "검색할 품목을 입력하세요. "; cin >> catg;
	cout << "─────────────────────────────────────────────────────────" << endl;



	for (auto i = productList_.begin(); i != productList_.end(); i++) {
		if (i->second != nullptr)
			cmp_catg = i->second->category();

		//맞는 품목이 있다면 정보 출력
		if (cmp_catg == catg) {
			found = 1;
			cout << i->second->getName() << " : "
				<< i->second->getPrice() << " : "
				<< i->second->getStock() << " : "
				<< i->second->category() << endl;
		}
		cmp_catg = "";
	}

	//맞는 품목이 없다면
	if (found == 0) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "!!찾는 품목이 없습니다!!" << endl;
		cout << "*************************" << endl;
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

	if(!(productList_[id])) {
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!존재하지 않는 제품입니다!!" << endl;
		cout << "****************************" << endl;
	}
	else {
		productList_.erase(id);
		cout << endl << "────────────────────────────────" << endl;
		cout << "!!성공적으로 제거 되었습니다!!" << endl;
		cout << endl << "────────────────────────────────" << endl;
	}
}

//해당 제품 변경
void ProductManagement::pdRevise(int id) {

	Product* p = productList_[id];

	if (!(productList_[id])) {
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!존재하지 않는 제품입니다!!" << endl;
		cout << "****************************" << endl;
	}

	else {
		cout << p->getName() << " : "
			<< p->getPrice() << " : "
			<< p->getStock() << " : "
			<< p->category() << endl << endl;

		int num, stock, price; char one;
		string name, category;
		cout << "─────────────────────────────────────────────────────────" << endl;
		cout << "              바꾸고 싶은 정보를 입력하세요.              " << endl;
		cout << "1: 제품명   |   2: 가격   |   3: 재고 수량   |   4: 품목   |   0: 취소" << endl;
		Primary::switchInput(num, one); cout << endl;

		switch (num) {
		case 1:
			cout << "제품명 : "; cin >> name;
			p->setName(name);
			break;
		case 2:
			cout << "가격 : "; cin >> price;
			p->setPrice(price);
			break;
		case 3:
			cout << "재고 수량 : "; cin >> stock;
			p->setStock(stock);
			break;
		case 4:
			cout << "품목 : "; cin >> category;
			p->setcatg(category);
			break;
		default:
			break;
		}
		if (0 < num && num < 5) {
			cout << endl << "────────────────────────────────" << endl;
			cout << "!!성공적으로 변경 되었습니다!!" << endl;
			cout << endl << "────────────────────────────────" << endl;
		}
	}
}