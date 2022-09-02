#include "client.h"

/*
	1. �� ����
		- ������ ID�� �����ϴ� ���(�ֹε�Ϲ�ȣ, ��ȭ��ȣ, E-mail)
		- �ʼ� ���� :
		- �ΰ� ���� :
	2. ��ǰ ����
		- �ʼ� ���� : ���� ID, ��ǰ��, ����, ....
		- �ΰ� ���� :
	3. ���� ���� : ���� ��ǰ�� ��� ���������� �Է�
		- �ʼ� ���� : ��������, �� ����(PK ����), ��ǰ����(PK ����), ���� ����
		- �ΰ� ���� : ��������

		��ǰ ���� ���α׷�
		1. �� ���� ����
		2. ��ǰ ���� ����
		3. ���� ���� ����

		����� �Է��Ͻðڽ��ϱ�?

	1 -> �Է�/��ȸ/����/����
	2 -> �Է�/��ȸ/����/����
	3 -> �ֹ�/���/��ȸ

*/

Client::Client(int id, string name, char gender, int age, string phoneNumber, string adress) : //������ �ʱ�ȭ
	id_(id), name_(name), gender_(gender), age_(age), phoneNumber_(phoneNumber), adress_(adress) {}

string Client::getName() const
{
	return name_;
}
void  Client::setName(string& name) //�޸𸮵� ���� ���� �ӵ��� ������ �ϱ� ���� & ���
{
	name_ = name;
}

char  Client::getGender() const
{
	return gender_;
}
void  Client::setGender(char gender)
{
	gender_ = gender;
}

int  Client::getAge()
{
	return age_;
}
void  Client::setAge(int age)
{
	age_ = age;
}

string  Client::getPhoneNumber() const
{
	return phoneNumber_;
}
void  Client::setPhoneNumber(string& phoneNumber)
{
	phoneNumber_ = phoneNumber;
}

string  Client::getAdress() const
{
	return adress_;
}
void  Client::setAdress(string& adress)
{
	adress_ = adress;
}

int Client::id() const {
	return id_;
}
