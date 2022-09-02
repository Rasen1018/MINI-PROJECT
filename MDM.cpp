#include "MDM.h"
#include "PDM.h"
#include "purchase.h"

PurchaseManagement::PurchaseManagement(ClientManagement& cm, ProductManagement& pm) :
cm_(cm), pm_(pm) {}		//�� ���� ����Ʈ�� ��ǰ ���� ����Ʈ�� �����ͼ� �ȿ� �ִ� ������ ��� ���۷����� �޾Ƽ� ���

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
	return purchaseList_[id];
}

// ���� ���� �Է�
void PurchaseManagement::mmInput()
{
	int flag = 0;
	int ID, clientID, productID, sellAmount;
	string sellTime;

	while (flag != 1) { 
		cout << "������ ID: "; Primary::integerInput(clientID, flag);
		if (clientID < 10001) {
			cout << "(ID:10001���� �����Դϴ�)" << endl;
			flag = 0;
		}
	}
	flag = 0; 
	while (flag != 1) {
		cout << "������ ��ǰ ID: "; Primary::integerInput(productID, flag);
		if (productID < 30001) {
			cout << "(ID:30001���� �����Դϴ�)" << endl;
			flag = 0;
		}
	}
	flag = 0; while (flag != 1) { cout << "���� ����: "; Primary::integerInput(sellAmount, flag); }
	cout << "���� ��¥: "; cin >> sellTime;

	ID = makeID();
	Purchase* m = new Purchase(ID, clientID, productID, sellAmount, sellTime);
	purchaseList_[makeID()] = m;

}

// ���� ���� ��ȸ
void PurchaseManagement::mmOutput(ClientManagement& cm, ProductManagement& pm)
{
	cout << "������������������������������������������������������������������������������������������������������������������" << endl;
	for_each(purchaseList_.begin(), purchaseList_.end(), [&](auto mm)
		{Purchase* m = mm.second;			// ���� ���� map�� value�� ���� -> value�� Purchase* ����
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
// �� �̸����� �˻��ϱ�
void PurchaseManagement::mmSearchCID()
{
	int found = 0;
	string name;
	string cmp_name;
	cout << "�� �̸��� �Է��ϼ���: "; cin >> name;
	cout << "������������������������������������������������������������������������������������������������������������������" << endl;

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
		cout << "!!�ֹ� ������ �����ϴ�!!" << endl;
		cout << "*************************" << endl;
	}
}
void PurchaseManagement::mmSearchPID()
{
	int found = 0;
	string name;
	string cmp_name;
	cout << "��ǰ �̸��� �Է��ϼ���: "; cin >> name;
	cout << "������������������������������������������������������������������������������������������������������������������" << endl;

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
		cout << "!!�ֹ� ������ �����ϴ�!!" << endl;
		cout << "*************************" << endl;
	}
}
void PurchaseManagement::deleteReceipt(int id)
{
	if (!(purchaseList_[id])) {
		cout << endl;
		cout << "**************************" << endl;
		cout << "!!�ֹ� ������ �����ϴ�!!" << endl;
		cout << "**************************" << endl;
	}
	else {
		purchaseList_.erase(id);
		cout << endl << "����������������������������������������������������������������" << endl;
		cout << "!!���������� ���� �Ǿ����ϴ�!!" << endl;
		cout << endl << "����������������������������������������������������������������" << endl;
	}
}
void PurchaseManagement::mmRevise(int id) // �ٹٲ㵵 ��
{
	Purchase* m = purchaseList_[id];
	Client* c = cm_.cmChooseID(m->CID());
	Product* p = pm_.pdchooseID(m->PID());

	if (!(purchaseList_[id])) {			// ã�� ���̵� ������ ���
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!�������� �ʴ� ���Դϴ�!!" << endl;
		cout << "****************************" << endl;
	}

	else {
		cout << m->id() << " �̸�: " << c->getName() << " ����: "
			<< c->getGender() << " ����: " << c->getAge() << endl << " ��ǰ��: "
			<< p->getName() << " �ֹ���: " << m->getAmount() << " �ֹ���¥: "
			<< m->getTime() << " �ֹ��ݾ�: " << (m->getAmount()) * (p->getPrice()) << endl;

		int num, clientID, productID, sellAmount; char one;
		string sellTime;
		cout << endl << "                  �ٲٰ� ���� ������ �Է��ϼ���.                  " << endl;
		cout << "1: ������   |   2: ��ǰ����   |   3: �ֹ���   |   4: �ֹ���¥" << endl;
		Primary::switchInput(num, one); cout << endl;

		switch (num) {
		case 1:
			cout << "�� ID : "; cin >> clientID;		// ���� �ѹ��̶� �ֹ��ߴ��� Ȯ��
			m->setClient(clientID);
			break;
		case 2:
			cout << "��ǰ ID : "; cin >> productID;		// ��ǰ�� �ѹ��̶� ���ŵȰ��� Ȯ��
			m->setProduct(productID);
			break;
		case 3:
			cout << "�ֹ��� : "; cin >> sellAmount;
			m->setAmount(sellAmount);
			break;
		case 4:
			cout << "�ֹ���¥ : "; cin >> sellTime;
			m->setTime(sellTime);
			break;
		}
		if (0 < num && num < 5) {
			cout << endl << "����������������������������������������������������������������" << endl;
			cout << "  !!���������� ���� �Ǿ����ϴ�!!  " << endl;
			cout << endl << "����������������������������������������������������������������" << endl;
		}
	}
}
