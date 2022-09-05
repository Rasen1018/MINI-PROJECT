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
			vector<string> row = parseCSV(file, ',');	//vector�� ���� ������ ������ ','�� ����
			if (row.size()) {
				int id = atoi(row[0].c_str());		//�޸��忡 ����Ǿ��ִ� ���ڸ� integer�� �ٲ㼭 id�� ����
				int price = atoi(row[2].c_str());
				int stock = atoi(row[3].c_str());
				Product* p = new Product(id, row[1], price, stock, row[4]);
										//id, name, price, stock, category ��
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
				file << p->getID() << ","		//ID ������� ��ǰ ���� ����
					<< p->getName() << ","
					<< (p->getPrice()) / 1000 << ","
					<< p->getStock() << ","
					<< p->category() << endl;
			}
		}
	}
	cout << "******��ǰ ����Ʈ ���� �Ϸ�******" << endl;
	file.close();
}

vector<string> ProductManagement::parseCSV(istream& file, char delimiter)
{
	stringstream ss;
	vector<string> row;
	string t = " \n\r\t";

	//stringstream�� �̿��Ͽ� �ܾ� ������
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

//��ǰ ���� �Է�
void ProductManagement::pdInput()
{
	int flag = 0;
	int id, stock, price;
	string productName, category;
	
	cout << "��ǰ�� : "; getline(cin, productName, '\n');
	while (flag != 1) { cout << "����(����:õ��) : "; Primary::integerInput(price, flag); }
	flag = 0; while (flag != 1) { cout << "��� ���� : "; Primary::integerInput(stock, flag); }
	cout << "ǰ�� : "; cin >> category;

	id=makeID();
	Product* p = new Product(id, productName, price, stock, category);
	productList_[makeID()] = p;

	cout << endl << "���������� �Է��߽��ϴ�." << endl << "����� ���θ޴��� ���ư��ϴ�." << endl;
	Sleep(1000); Sleep(1000);
	system("cls");
}

//��ǰ ���� ��ȸ
void ProductManagement::pdOutput() {

	cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
	for_each(productList_.begin(), productList_.end(), 
		[](auto pm) {Product* p = pm.second;
	if (p != nullptr) {
		cout << "[" << p->getID() << "] ��ǰ��: "
			<< p->getName() << " ����: "
			<< p->getPrice() << " ������: "
			<< p->getStock() << " ǰ��: "
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

//��ǰ ID�� �˻�
void ProductManagement::pdSearchID(int id) {

	char one;
	Product* p = productList_[id];

	//ID�� ���� ��
	if (productList_.find(id)==productList_.end())
	{
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!�������� �ʴ� ��ǰ�Դϴ�!!" << endl;
		cout << "\t\t" << "!!����Ŀ� ���� �޴��� ���ư��ϴ�!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
		system("cls");
	}

	//ID�� ���� ��
	else {
		cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl
			<< id << " ��ǰ ����" << endl
			<< "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
	cout << "��ǰ��: " << p->getName() << " ����: "
		<< p->getPrice() << " ������: "
		<< p->getStock() << " ǰ��: "
		<< p->category() << endl;

	cout << endl << endl << "\t" << "�ƹ�Ű�� �Է��ϸ� ����ȭ������ ���ư��ϴ�." << endl;
	one = _getch();
	system("cls");
	cin.ignore();
	}
}

//��ǰ ǰ������ �˻�
void ProductManagement::pdSearchCategory() {

	int found = 0;
	char one;
	string catg;
	string cmp_catg;

	cout << "�˻��� ǰ���� �Է��ϼ���. "; cin >> catg;
	cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;


	for (auto i = productList_.begin(); i != productList_.end(); i++) {
		if (i->second != nullptr)
			cmp_catg = i->second->category();

		//�´� ǰ���� �ִٸ� ���� ���
		if (cmp_catg == catg) {
			found = 1;
			cout << "��ǰ��: " << i->second->getName() << " ����: "
				<< i->second->getPrice() << " ������: "
				<< i->second->getStock() << " ǰ��: "
				<< i->second->category() << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
		}
		cmp_catg = "";
	}

	//�´� ǰ���� ���ٸ�
	if (found == 0) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!ã�� ǰ���� �����ϴ�!!" << endl;
		cout << "\t\t" << "!!����Ŀ� ���� �޴��� ���ư��ϴ�!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
		system("cls");
	}
	else {
		cout << endl << endl << "\t" << "�ƹ�Ű�� �Է��ϸ� ����ȭ������ ���ư��ϴ�." << endl;
		one = _getch();
		system("cls");
		cin.ignore();
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

	if(productList_.find(id)==productList_.end()) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!�������� �ʴ� ��ǰ�Դϴ�!!" << endl;
		cout << "\t\t" << "!!����Ŀ� ���� �޴��� ���ư��ϴ�!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}
	else {
		productList_.erase(id);
		cout << endl << "\t\t" << "������������������������������������������������������������������������" << endl;
		cout << "\t\t" << "!!���������� ���� �Ǿ����ϴ�!!" << endl;
		cout << "\t\t" << "!!����Ŀ� ���� �޴��� ���ư��ϴ�!!" << endl;
		cout << endl << "\t\t" << "������������������������������������������������������������������������" << endl;
		Sleep(1000); Sleep(1000);
	}
	getchar();
}

//�ش� ��ǰ ����
void ProductManagement::pdRevise(int id) {

	Product* p = productList_[id];

	if (!(productList_[id])) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!�������� �ʴ� ��ǰ�Դϴ�!!" << endl;
		cout << "\t\t" << "!!����Ŀ� ���� �޴��� ���ư��ϴ�!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}

	else {
		cout << "��ǰ��: " << p->getName() << " ����: "
			<< p->getPrice() << " ������: "
			<< p->getStock() << " ǰ��: "
			<< p->category() << endl << endl;

		int num, stock, price; char one;
		string name, category;
		cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
		cout << "              �ٲٰ� ���� ������ �Է��ϼ���.              " << endl;
		cout << "1: ��ǰ��   |   2: ����   |   3: ��� ����   |   4: ǰ��   |   0: ���" << endl;
		Primary::switchInput(num, one); cout << endl;

		//�ٲٰ� ���� ������ ���� switch �� ����
		switch (num) {
		case 1:		//��ǰ�� ����
			cout << "��ǰ�� : "; cin.ignore(); getline(cin, name, '\n');
			p->setName(name);
			break;
		case 2:		//���� ����
			cout << "���� : "; cin >> price;
			p->setPrice(price);
			break;
		case 3:		//������ ����
			cout << "��� ���� : "; cin >> stock;
			p->setStock(stock);
			break;
		case 4:		//ǰ�� ����
			cout << "ǰ�� : "; cin >> category;
			p->setcatg(category);
			break;
		default:
			getchar();
			system("cls");
			break;
		}
		if (0 < num && num < 5) {
			cout << endl << "\t\t" << "������������������������������������������������������������������������" << endl;
			cout << "\t\t" << "!!���������� ���� �Ǿ����ϴ�!!" << endl;
			cout << "\t\t" << "!!����Ŀ� ���� �޴��� ���ư��ϴ�!!" << endl;
			cout << endl << "\t\t" << "������������������������������������������������������������������������" << endl;
			Sleep(1000); Sleep(1000); system("cls");
		}
	}
}

void ProductManagement::showList() {
	for (auto pm : productList_) {
		Product* p = pm.second;
		if (p != nullptr) {
			cout << "[" << p->getID() << "] ��ǰ��: "
				<< p->getName() << " ����: "
				<< p->getPrice() << " ������: "
				<< p->getStock() << " ǰ��: "
				<< p->category() << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
		}
	}
}