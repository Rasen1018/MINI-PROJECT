#include "CRM.h"
#include <string>

ClientManagement::ClientManagement() {}

int ClientManagement::makeID() {	//고객 ID 생성(map은 자동정렬, 중복 X 기능이 있기 때문에 
									//primary key를 만들기에 좋다.
	auto key = clientList_.end();	//key에 end()를 대입
	if (clientList_.size() == 0) {	
		return 10001;				//만약 고객 정보가 없다면 10001을 반환
	}
	else 
	{
		int id = (--key)->first;	//있다면 다음 순서부터 id를 1씩 증가
		return ++id;
	}
}

void ClientManagement::cmInput()
{
	string name, phoneNumber, adress;
	char gender;
	int age = 1, flag = 0;

	//고객 정보 입력
	cout << "이름 : "; cin >> name;
	do { 
		if (flag == 1) 
		{ cout << endl << "!!성별을 다시 입력하세요!!" << endl << endl; }					// flag ==1이면 출력
		cout << "성별(M/W) : ";  cin >> gender; gender = toupper(gender); flag = 1; }	
	while (gender != 'M' && gender != 'W');												// 성별을 제대로 받을 때까지 반복
	flag = 0;
	while (flag!=1) { cout << "나이 : "; Primary::integerInput(age, flag); }				// 정수가 아니면 계속 반복
	cout << "전화번호 : "; cin >> phoneNumber;
	cout << "주소 : "; cin.ignore(); getline(cin, adress, '\n');
	
	int id = makeID();	//아이디는 자동 생성
	
	//고객 객체 동적 메모리 할당(힙에 생성)
	Client* c = new Client(id, name, gender, age, phoneNumber, adress);

	clientList_[makeID()] = c; //map에 key -> makeID() , value -> c 대입
							   //clientList_.insert({makeID(), c});
	
	/*Client* client1 = new Client("TaeHun", 'M', 30, "010-5557-9957", "AnSan");
	clientList_[1] = client1;*/
}

void ClientManagement::cmOutput()
{			// map의 처음부터 끝까지 하나씩 출력
	cout << "─────────────────────────────────────────────────────────" << endl;
	for_each(clientList_.begin(), clientList_.end(),
		[](auto cm) {Client* c = cm.second;	//객체 정보(c)는 map의 value 정보(second)
		if (c != nullptr) {
			cout << c->id() << " : "
				<< c->getName() << " : "			//검색한 ID 정보 출력
				<< c->getAge() << " : "
				<< c->getPhoneNumber() << " : "
				<< c->getAdress() << endl;			// 객체의 멤버 함수에 접근
			cout << "---------------------------------------------------------" << endl;
			}
		}
	);													

	//for (auto i = clientList_.begin(); i != clientList_.end(); i++) {
	//	cout << i->first << " " << i->second->getName() << endl;
	//}
}

Client* ClientManagement::cmChooseID(int id) //id값 반환
{
	return clientList_[id];
}

void ClientManagement::cmSearchID(int id) //ID로 검색
{
	Client* c = clientList_[id];				//검색할 ID 입력

	if (!(clientList_[id]))						//ID가 없으면 출력
	{
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!존재하지 않는 고객입니다!!" << endl;
		cout << "****************************" << endl;
	}

	else {
		cout << "──────────────────────────────" << endl
			<< id << " 고객 정보" << endl
			<< "──────────────────────────────" << endl;
		cout << c->getName() << " : "			//검색한 ID 정보 출력
			<< c->getAge() << " : "
			<< c->getPhoneNumber() << " : "
			<< c->getAdress() << endl;
	}
}

void ClientManagement::cmSearchName() //이름으로 검색
{
	int found=0;		//나중에 이름이 존재하는지 확인하기 위해 사용
	string name;		//검색할 이름
	string cmp_name;	//객체에서 확인할 이름

	cout << "검색할 이름을 입력하세요. "; cin >> name;
	cout << "─────────────────────────────────────────────────────────" << endl;

	//map의 처음부터 끝까지 검색
	for (auto i = clientList_.begin(); i != clientList_.end(); i++) {
		if(i->second != nullptr)
			cmp_name = i->second->getName();
		if((cmp_name == name)) {		//검색한 이름의 고객이 있다면 중복해서 모두 검색
			found = 1;
			cout << i->second->getName() << " : "
				<< i->second->getAge() << " : "
				<< i->second->getPhoneNumber() << " : "
				<< i->second->getAdress() << endl;
			cout << "---------------------------------------------------------" << endl;
		}
		cmp_name = ""; //string 초기화
	}

	if (found == 0) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "!!찾는 이름이 없습니다!!" << endl;
		cout << "*************************" << endl;
	}
}

//정보 삭제
void ClientManagement::deleteClient(int id) {

	if(!(clientList_[id])) {			// 찾는 아이디가 없으면 출력
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!존재하지 않는 고객입니다!!" << endl;
		cout << "****************************" << endl;
	}
	else {
		clientList_.erase(id);			// erease로 key 삭제
		cout << endl << "────────────────────────────────" << endl;
		cout << "!!성공적으로 제거 되었습니다!!" << endl;
		cout << endl << "────────────────────────────────" << endl;
	}
}

//정보 변경
void ClientManagement::cmRevise(int id) {

	Client* c = clientList_[id];

	if (!(clientList_[id])) {			// 찾는 아이디가 없으면 출력
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!존재하지 않는 고객입니다!!" << endl;
		cout << "****************************" << endl;
	}

	else {
		cout << c->getName() << " : "				//먼저 바꾸고 싶은 고객 정보 출력
			<< c->getAge() << " : "
			<< c->getPhoneNumber() << " : "
			<< c->getAdress() << endl << endl;

		int num, age; char one;
		string name, phoneNumber, adress;
		cout << "─────────────────────────────────────────────────────────" << endl;
		cout << "            바꾸고 싶은 정보를 입력하세요.            " << endl;
		cout << "1: 이름   |   2: 나이   |   3: 전화번호   |   4: 주소   |   0: 취소" << endl;
		Primary::switchInput(num, one); cout << endl;

		//바꾸고 싶은 정보에 따라 switch 문 실행
		switch (num) {
		case 1:		//이름 변경
			cout << "이름 : "; cin >> name;
			c->setName(name);
			break;
		case 2:		//나이 변경
			cout << "나이 : "; cin >> age;
			c->setAge(age);
			break;
		case 3:		//전화번호 변경
			cout << "전화번호 : "; cin >> phoneNumber;
			c->setPhoneNumber(phoneNumber);
			break;
		case 4:		//주소 변경
			cout << "주소 : "; cin.ignore(); getline(cin, adress, '\n');
			c->setAdress(adress);
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