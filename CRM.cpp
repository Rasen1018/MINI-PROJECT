#include "CRM.h"
#include <string>

ClientManagement::ClientManagement() {}

int ClientManagement::makeID() {	//�� ID ����(map�� �ڵ�����, �ߺ� X ����� �ֱ� ������ 
									//primary key�� ����⿡ ����.
	auto key = clientList_.end();	//key�� end()�� ����
	if (clientList_.size() == 0) {	
		return 10001;				//���� �� ������ ���ٸ� 10001�� ��ȯ
	}
	else 
	{
		int id = (--key)->first;	//�ִٸ� ���� �������� id�� 1�� ����
		return ++id;
	}
}

void ClientManagement::cmInput()
{
	string name, phoneNumber, adress;
	char gender;
	int age = 1, flag = 0;

	//�� ���� �Է�
	cout << "�̸� : "; cin >> name;
	do { 
		if (flag == 1) 
		{ cout << endl << "!!������ �ٽ� �Է��ϼ���!!" << endl << endl; }					// flag ==1�̸� ���
		cout << "����(M/W) : ";  cin >> gender; gender = toupper(gender); flag = 1; }	
	while (gender != 'M' && gender != 'W');												// ������ ����� ���� ������ �ݺ�
	flag = 0;
	while (flag!=1) { cout << "���� : "; Primary::integerInput(age, flag); }				// ������ �ƴϸ� ��� �ݺ�
	cout << "��ȭ��ȣ : "; cin >> phoneNumber;
	cout << "�ּ� : "; cin.ignore(); getline(cin, adress, '\n');
	
	int id = makeID();	//���̵�� �ڵ� ����
	
	//�� ��ü ���� �޸� �Ҵ�(���� ����)
	Client* c = new Client(id, name, gender, age, phoneNumber, adress);

	clientList_[makeID()] = c; //map�� key -> makeID() , value -> c ����
							   //clientList_.insert({makeID(), c});
	
	/*Client* client1 = new Client("TaeHun", 'M', 30, "010-5557-9957", "AnSan");
	clientList_[1] = client1;*/
}

void ClientManagement::cmOutput()
{			// map�� ó������ ������ �ϳ��� ���
	cout << "������������������������������������������������������������������������������������������������������������������" << endl;
	for_each(clientList_.begin(), clientList_.end(),
		[](auto cm) {Client* c = cm.second;	//��ü ����(c)�� map�� value ����(second)
		if (c != nullptr) {
			cout << c->id() << " : "
				<< c->getName() << " : "			//�˻��� ID ���� ���
				<< c->getAge() << " : "
				<< c->getPhoneNumber() << " : "
				<< c->getAdress() << endl;			// ��ü�� ��� �Լ��� ����
			cout << "---------------------------------------------------------" << endl;
			}
		}
	);													

	//for (auto i = clientList_.begin(); i != clientList_.end(); i++) {
	//	cout << i->first << " " << i->second->getName() << endl;
	//}
}

Client* ClientManagement::cmChooseID(int id) //id�� ��ȯ
{
	return clientList_[id];
}

void ClientManagement::cmSearchID(int id) //ID�� �˻�
{
	Client* c = clientList_[id];				//�˻��� ID �Է�

	if (!(clientList_[id]))						//ID�� ������ ���
	{
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!�������� �ʴ� ���Դϴ�!!" << endl;
		cout << "****************************" << endl;
	}

	else {
		cout << "������������������������������������������������������������" << endl
			<< id << " �� ����" << endl
			<< "������������������������������������������������������������" << endl;
		cout << c->getName() << " : "			//�˻��� ID ���� ���
			<< c->getAge() << " : "
			<< c->getPhoneNumber() << " : "
			<< c->getAdress() << endl;
	}
}

void ClientManagement::cmSearchName() //�̸����� �˻�
{
	int found=0;		//���߿� �̸��� �����ϴ��� Ȯ���ϱ� ���� ���
	string name;		//�˻��� �̸�
	string cmp_name;	//��ü���� Ȯ���� �̸�

	cout << "�˻��� �̸��� �Է��ϼ���. "; cin >> name;
	cout << "������������������������������������������������������������������������������������������������������������������" << endl;

	//map�� ó������ ������ �˻�
	for (auto i = clientList_.begin(); i != clientList_.end(); i++) {
		if(i->second != nullptr)
			cmp_name = i->second->getName();
		if((cmp_name == name)) {		//�˻��� �̸��� ���� �ִٸ� �ߺ��ؼ� ��� �˻�
			found = 1;
			cout << i->second->getName() << " : "
				<< i->second->getAge() << " : "
				<< i->second->getPhoneNumber() << " : "
				<< i->second->getAdress() << endl;
			cout << "---------------------------------------------------------" << endl;
		}
		cmp_name = ""; //string �ʱ�ȭ
	}

	if (found == 0) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "!!ã�� �̸��� �����ϴ�!!" << endl;
		cout << "*************************" << endl;
	}
}

//���� ����
void ClientManagement::deleteClient(int id) {

	if(!(clientList_[id])) {			// ã�� ���̵� ������ ���
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!�������� �ʴ� ���Դϴ�!!" << endl;
		cout << "****************************" << endl;
	}
	else {
		clientList_.erase(id);			// erease�� key ����
		cout << endl << "����������������������������������������������������������������" << endl;
		cout << "!!���������� ���� �Ǿ����ϴ�!!" << endl;
		cout << endl << "����������������������������������������������������������������" << endl;
	}
}

//���� ����
void ClientManagement::cmRevise(int id) {

	Client* c = clientList_[id];

	if (!(clientList_[id])) {			// ã�� ���̵� ������ ���
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!�������� �ʴ� ���Դϴ�!!" << endl;
		cout << "****************************" << endl;
	}

	else {
		cout << c->getName() << " : "				//���� �ٲٰ� ���� �� ���� ���
			<< c->getAge() << " : "
			<< c->getPhoneNumber() << " : "
			<< c->getAdress() << endl << endl;

		int num, age; char one;
		string name, phoneNumber, adress;
		cout << "������������������������������������������������������������������������������������������������������������������" << endl;
		cout << "            �ٲٰ� ���� ������ �Է��ϼ���.            " << endl;
		cout << "1: �̸�   |   2: ����   |   3: ��ȭ��ȣ   |   4: �ּ�   |   0: ���" << endl;
		Primary::switchInput(num, one); cout << endl;

		//�ٲٰ� ���� ������ ���� switch �� ����
		switch (num) {
		case 1:		//�̸� ����
			cout << "�̸� : "; cin >> name;
			c->setName(name);
			break;
		case 2:		//���� ����
			cout << "���� : "; cin >> age;
			c->setAge(age);
			break;
		case 3:		//��ȭ��ȣ ����
			cout << "��ȭ��ȣ : "; cin >> phoneNumber;
			c->setPhoneNumber(phoneNumber);
			break;
		case 4:		//�ּ� ����
			cout << "�ּ� : "; cin.ignore(); getline(cin, adress, '\n');
			c->setAdress(adress);
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