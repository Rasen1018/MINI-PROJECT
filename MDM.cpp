#include "MDM.h"
#include "PDM.h"
#include "purchase.h"
#include <fstream>
#include <sstream>
#include <Windows.h>

PurchaseManagement::PurchaseManagement(ClientManagement& cm, ProductManagement& pm) : cm_(cm), pm_(pm)
//�� ���� ����Ʈ�� ��ǰ ���� ����Ʈ�� �����ͼ� �ȿ� �ִ� ������ ��� ���۷����� �޾Ƽ� ���
{
	ifstream file;
	file.open("shoppinglist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');	//vector�� ���� ������ ������ ','�� ����
			if (row.size()) {
				int id = atoi(row[0].c_str());			//�޸��忡 ����Ǿ��ִ� ���ڸ� integer�� �ٲ㼭 id�� ����
				int clientID = atoi(row[1].c_str());
				int productID = atoi(row[2].c_str());
				int sellAmount = atoi(row[3].c_str());
				Purchase* m = new Purchase(id, clientID, productID, sellAmount, row[4]);
										//id, ��ID, ��ǰID, �ֹ�����, �ֹ����� ��
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
	cout << "******���� ����Ʈ ���� �Ϸ�******" << endl;
	file.close();
}

vector<string> PurchaseManagement::parseCSV(istream& file, char delimiter)
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

// ���� ����Ʈ ID ����
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

// Ư�� ID�� ���� ���� ����Ʈ ��������
Purchase* PurchaseManagement::mmChooseID(int id) {
	auto it = purchaseList_.find(id);
	return (it != purchaseList_.end()) ? purchaseList_[id] : nullptr;
}

// ���� ���� �Է�
void PurchaseManagement::mmInput()
{
	int flag = 0;
	int ID, clientID, productID, sellAmount;
	string sellTime;

	cout << endl << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;

	cm_.showList(); // �Է��ϱ� �� �� ���� �����ֱ�

	while (flag != 1) { 
		cout << "������ ID: "; Primary::integerInput(clientID, flag);		// �� ID �Է�
		if (clientID < 10001) {												// �ùٸ� ID�� ���� ������ while�� �ݺ�
			cout << "(ID:10001���� �����Դϴ�)" << endl;
			flag = 0;
		}
	}
	flag = 0; 
	while (flag != 1) {
		cout << "������ ��ǰ ID: "; Primary::integerInput(productID, flag);	// ��ǰ ID �Է�
		if (productID < 30001) {											// �ùٸ� ID�� ���� ������ while�� �ݺ�
			cout << "(ID:30001���� �����Դϴ�)" << endl;
			flag = 0;
		}
	}
	flag = 0;
	Product* p = pm_.pdchooseID(productID);			// ��ǰ����Ʈ �޾ƿ���
	int stock = p->getStock();						// ��ǰ����Ʈ ��� �޾ƿ���
	while (flag != 1) {
		cout << "���� ����: "; Primary::integerInput(sellAmount, flag);
		if (stock < sellAmount)		// ���� �������� ��� ���ٸ� �����޼��� ���
		{
			cout << endl << "!!��� �����Դϴ�!!" << endl;
			cout << "���� ���: " << stock << endl << endl;
			flag = 0;
		}
	} p->setStock(stock - sellAmount);		// ��� ���� ���� �ݿ�

	cout << "���� ��¥: "; cin >> sellTime;
	ID = makeID();

	Purchase* m = new Purchase(ID, clientID, productID, sellAmount, sellTime);
	purchaseList_[makeID()] = m;

	cout << endl << "���������� �Է��߽��ϴ�." << endl << "����� ���θ޴��� ���ư��ϴ�." << endl;
	Sleep(1000); Sleep(1000);
	system("cls");

}

// ���� ���� ��ȸ
void PurchaseManagement::mmOutput(ClientManagement& cm, ProductManagement& pm)
{
	cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
	for_each(purchaseList_.begin(), purchaseList_.end(), [&](auto mm)
		{Purchase* m = mm.second;			// ���� ���� map�� value�� ���� -> value�� Purchase* ����
	if (m != nullptr) {
		Client* c = cm.cmChooseID(m->CID());	// �� ����Ʈ�� ��ǰ ����Ʈ �޾ƿ��� 
		Product* p = pm.pdchooseID(m->PID());
		cout << "[" << m->id() << "] ���̸�: " << c->getName()
			<< " ����: " << c->getGender() << " ����: " << c->getAge() << endl;
		cout << setw(17) << setfill(' ') << " ��ǰ��: " << p->getName() << endl;
		cout << setw(19) << setfill(' ') <<" �ֹ�����: " << m->getAmount() 
			<<" �ֹ��ݾ�: " << (m->getAmount()) * (p->getPrice())
			<< " �ֹ�����: " << m->getTime() << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
	}
		}
	); 
}
// �� �̸����� �˻��ϱ�
void PurchaseManagement::mmSearchCID()
{
	int found = 0;
	char one;
	string name;
	string cmp_name;
	cout << "�� �̸��� �Է��ϼ���: "; cin >> name;
	cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;

	for (auto i = purchaseList_.begin(); i != purchaseList_.end(); i++) {
		if (i->second != nullptr) {
			Client* c = cm_.cmChooseID(i->second->CID());
			Product* p = pm_.pdchooseID(i->second->PID());
			Purchase* m = i->second;
			cmp_name = c->getName();

			if (name == cmp_name) {
				found = 1;
				cout << "[" << m->id() << "] ���̸�: " << c->getName()
					<< " ����: " << c->getGender() << " ����: " << c->getAge()
					<< endl << "        " << " ��ǰ��: " << p->getName()
					<< " �ֹ�����: " << m->getAmount() << " �ֹ�����: " << m->getTime()
					<< " �ֹ��ݾ�: " << (m->getAmount()) * (p->getPrice()) << endl;
				cout << "--------------------------------------------------------------------------" << endl;
			}
		}
		cmp_name = "";
	}

	if (found == 0) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!���� ������ �����ϴ�!!" << endl;
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
void PurchaseManagement::mmSearchPID()
{
	char one;
	int found = 0;
	string category;
	string cmp_catg;
	cout << "��ǰ �̸��� �Է��ϼ���: "; cin >> category;
	cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;

	for (auto i = purchaseList_.begin(); i != purchaseList_.end(); i++) {
		if (i->second != nullptr) {
			Client* c = cm_.cmChooseID(i->second->CID());
			Product* p = pm_.pdchooseID(i->second->PID());
			Purchase* m = i->second;
			cmp_catg = p->category();

			if (category == cmp_catg) {
				found = 1;
				cout << "[" << m->id() << "] ���̸�: " << c->getName() 
					<< " ����: " << c->getGender() << " ����: " << c->getAge() 
					<< endl << "        " << " ��ǰ��: " << p->getName()
					<< " �ֹ�����: " << m->getAmount() << " �ֹ�����(YY-MM-DD): " << m->getTime() 
					<< " �ֹ��ݾ�: " << (m->getAmount()) * (p->getPrice()) << endl;
				cout << "-----------------------------------------------------------------------------" << endl;
			}
		}
		cmp_catg = "";
	}

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
void PurchaseManagement::deleteReceipt(int id)
{
	if (purchaseList_.find(id)==purchaseList_.end()) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!�ֹ� ������ �����ϴ�!!" << endl;
		cout << "\t\t" << "!!����Ŀ� ���� �޴��� ���ư��ϴ�!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}
	else {
		purchaseList_.erase(id);
		cout << endl << "\t\t" << "������������������������������������������������������������������������" << endl;
		cout << "\t\t" << "!!���������� ���� �Ǿ����ϴ�!!" << endl;
		cout << "\t\t" << "!!����Ŀ� ���� �޴��� ���ư��ϴ�!!" << endl;
		cout << endl << "\t\t" << "������������������������������������������������������������������������" << endl;
		Sleep(1000); Sleep(1000);
	}
	getchar();
}

void PurchaseManagement::mmRevise(int id) // �ٹٲ㵵 ��
{
	map<int, Purchase*> ::iterator it;
	it = purchaseList_.find(id);
	// ã�� ID�� ������ ���
	if (it == purchaseList_.end()) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!�ֹ� ������ �����ϴ�!!" << endl;
		cout << "\t\t" << "!!����Ŀ� ���� �޴��� ���ư��ϴ�!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}
	else {
		Purchase* m = purchaseList_[id];
		Client* c = cm_.cmChooseID(m->CID());
		Product* p = pm_.pdchooseID(m->PID());
		cout << "[" << m->id() << "] ���̸�: " << c->getName()
			<< " ����: " << c->getGender() << " ����: " << c->getAge()
			<< endl << "        " << " ��ǰ��: " << p->getName()
			<< " �ֹ�����: " << m->getAmount() << " �ֹ�����: " << m->getTime()
			<< " �ֹ��ݾ�: " << (m->getAmount()) * (p->getPrice()) << endl;

		int num, clientID, productID, sellAmount; char one;
		string sellTime;
		cout << endl << "                  �ٲٰ� ���� ������ �Է��ϼ���.                  " << endl;
		cout << "1: ������   |   2: ��ǰ����   |   3: �ֹ���   |   4: �ֹ�����" << endl;
		Primary::switchInput(num, one); cout << endl;

		switch (num) {
		case 1:
			cout << "(���� ���� ������ [�� ���� ����]���� �ٲ� �� �ֽ��ϴ�.) "
				<< endl << "����Ǿ� ����� �� ID�� �Է��ϼ��� : ";
			cin >> clientID; m->setClient(clientID);      // ���� �ѹ��̶� �ֹ��ߴ��� Ȯ��
			break;
		case 2:
			cout << "(��ǰ�� ���� ������ [��ǰ ���� ����]���� �ٲ� �� �ֽ��ϴ�.) "
				<< endl << "����Ǿ� ����� ��ǰ ID�� �Է��ϼ��� : ";
			cin >> productID; m->setProduct(productID);      // ��ǰ�� �ѹ��̶� ���ŵȰ��� Ȯ��      
			break;
		case 3:
			cout << "�ֹ��� : "; cin >> sellAmount;
			m->setAmount(sellAmount);
			break;
		case 4:
			cout << "�ֹ���¥ : "; cin >> sellTime;
			m->setTime(sellTime);
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
