#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "primary.h"

class Client {
public:
	Client(int id = 0, string = "", char = ' ', int = 0, string = "", string = ""); //디폴트 매개변수

	// 고객 이름 입력,출력
	string getName() const;
	void setName(string&); 

	// 고객 성별 입력,출력
	char getGender() const;
	void setGender(char);

	//고객 나이 입력,출력
	int getAge();
	void setAge(int);

	//고객 전화번호 입력, 출력
	string getPhoneNumber() const;
	void setPhoneNumber(string&);

	//고객 주소 입력, 출력
	string getAdress() const;
	void setAdress(string&);

	int id() const; //고객 ID 가져오기

private:
	int id_;
	string name_;
	char gender_;
	int age_;
	string phoneNumber_;
	string adress_;

};


#endif

