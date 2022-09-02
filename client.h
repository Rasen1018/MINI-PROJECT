#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "primary.h"

class Client {
public:
	Client(int id = 0, string = "", char = ' ', int = 0, string = "", string = ""); //����Ʈ �Ű�����

	// �� �̸� �Է�,���
	string getName() const;
	void setName(string&); 

	// �� ���� �Է�,���
	char getGender() const;
	void setGender(char);

	//�� ���� �Է�,���
	int getAge();
	void setAge(int);

	//�� ��ȭ��ȣ �Է�, ���
	string getPhoneNumber() const;
	void setPhoneNumber(string&);

	//�� �ּ� �Է�, ���
	string getAdress() const;
	void setAdress(string&);

	int id() const; //�� ID ��������

private:
	int id_;
	string name_;
	char gender_;
	int age_;
	string phoneNumber_;
	string adress_;

};


#endif

