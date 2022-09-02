#include "PDM.h"

ProductManagement::ProductManagement() {}

//��ǰ ���� �Է�
void ProductManagement::pdInput()
{
	int flag = 0;
	int id, stock, price;
	string productName, category;
	
	cout << "��ǰ�� : "; cin >> productName;
	while (flag != 1) { cout << "����(����:õ��) : "; Primary::integerInput(price, flag); }
	flag = 0; while (flag != 1) { cout << "��� ���� : "; Primary::integerInput(stock, flag); }
	cout << "ǰ�� : "; cin >> category;

	id=makeID();
	Product* p = new Product(id, productName, price, stock, category);
	productList_[makeID()] = p;
}

//��ǰ ���� ��ȸ
void ProductManagement::pdOutput() {

	cout << "������������������������������������������������������������������������������������������������������������������" << endl;
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

//��ǰ ID�� �˻�
void ProductManagement::pdSearchID(int id) {

	Product* p = productList_[id];

	//ID�� ���� ��
	if (!(productList_[id]))
	{
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!�������� �ʴ� ��ǰ�Դϴ�!!" << endl;
		cout << "****************************" << endl;
	}

	//ID�� ���� ��
	else {
		cout << "������������������������������������������������������������" << endl
			<< id << " ��ǰ ����" << endl
			<< "������������������������������������������������������������" << endl;
	cout << p->getName() << " : "
		<< p->getPrice() << " : "
		<< p->getStock() << " : "
		<< p->category() << endl;
	}
}

//��ǰ ǰ������ �˻�
void ProductManagement::pdSearchCategory() {

	int found = 0;
	string catg;
	string cmp_catg;

	cout << "�˻��� ǰ���� �Է��ϼ���. "; cin >> catg;
	cout << "������������������������������������������������������������������������������������������������������������������" << endl;



	for (auto i = productList_.begin(); i != productList_.end(); i++) {
		if (i->second != nullptr)
			cmp_catg = i->second->category();

		//�´� ǰ���� �ִٸ� ���� ���
		if (cmp_catg == catg) {
			found = 1;
			cout << i->second->getName() << " : "
				<< i->second->getPrice() << " : "
				<< i->second->getStock() << " : "
				<< i->second->category() << endl;
		}
		cmp_catg = "";
	}

	//�´� ǰ���� ���ٸ�
	if (found == 0) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "!!ã�� ǰ���� �����ϴ�!!" << endl;
		cout << "*************************" << endl;
	}
}

//��ǰ ID �Ҵ�
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

//�ش� ID�� ��ǰ ����
void ProductManagement::deleteProduct(int id) {

	if(!(productList_[id])) {
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!�������� �ʴ� ��ǰ�Դϴ�!!" << endl;
		cout << "****************************" << endl;
	}
	else {
		productList_.erase(id);
		cout << endl << "����������������������������������������������������������������" << endl;
		cout << "!!���������� ���� �Ǿ����ϴ�!!" << endl;
		cout << endl << "����������������������������������������������������������������" << endl;
	}
}

//�ش� ��ǰ ����
void ProductManagement::pdRevise(int id) {

	Product* p = productList_[id];

	if (!(productList_[id])) {
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!�������� �ʴ� ��ǰ�Դϴ�!!" << endl;
		cout << "****************************" << endl;
	}

	else {
		cout << p->getName() << " : "
			<< p->getPrice() << " : "
			<< p->getStock() << " : "
			<< p->category() << endl << endl;

		int num, stock, price; char one;
		string name, category;
		cout << "������������������������������������������������������������������������������������������������������������������" << endl;
		cout << "              �ٲٰ� ���� ������ �Է��ϼ���.              " << endl;
		cout << "1: ��ǰ��   |   2: ����   |   3: ��� ����   |   4: ǰ��   |   0: ���" << endl;
		Primary::switchInput(num, one); cout << endl;

		switch (num) {
		case 1:
			cout << "��ǰ�� : "; cin >> name;
			p->setName(name);
			break;
		case 2:
			cout << "���� : "; cin >> price;
			p->setPrice(price);
			break;
		case 3:
			cout << "��� ���� : "; cin >> stock;
			p->setStock(stock);
			break;
		case 4:
			cout << "ǰ�� : "; cin >> category;
			p->setcatg(category);
			break;
		default:
			break;
		}
		if (0 < num && num < 5) {
			cout << endl << "����������������������������������������������������������������" << endl;
			cout << "!!���������� ���� �Ǿ����ϴ�!!" << endl;
			cout << endl << "����������������������������������������������������������������" << endl;
		}
	}
}