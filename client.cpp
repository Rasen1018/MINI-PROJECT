#include "client.h"

/*
	1. 고객 정보
		- 고유한 ID를 구현하는 방법(주민등록번호, 전화번호, E-mail)
		- 필수 정보 :
		- 부가 정보 :
	2. 상품 정보
		- 필수 정보 : 유저 ID, 상품명, 가격, ....
		- 부가 정보 :
	3. 관리 정보 : 고객이 상품을 사면 관리정보로 입력
		- 필수 정보 : 구매일자, 고객 정보(PK 연결), 상품정보(PK 연결), 구매 수량
		- 부가 정보 : 할인정보

		상품 관리 프로그램
		1. 고객 정보 관리
		2. 상품 정보 관리
		3. 쇼핑 정보 관리

		몇번을 입력하시겠습니까?

	1 -> 입력/조회/삭제/변경
	2 -> 입력/조회/삭제/변경
	3 -> 주문/취소/조회

*/

Client::Client(int id, string name, char gender, int age, string phoneNumber, string adress) : //열거형 초기화
	id_(id), name_(name), gender_(gender), age_(age), phoneNumber_(phoneNumber), adress_(adress) {}

string Client::getName() const
{
	return name_;
}
void  Client::setName(string& name) //메모리도 적게 쓰고 속도도 빠르게 하기 위해 & 사용
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
