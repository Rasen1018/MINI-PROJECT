#include "CRM.h"
#include <string>
#include <fstream>
#include <sstream>

ClientManagement::ClientManagement()
{
//	std::vector<Client*> vecList;
	ifstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');	//vector의 순서 나누는 기준을 ','로 설정
			if (row.size()) {
				int id = atoi(row[0].c_str());		//메모장에 저장되어있는 문자를 integer로 바꿔서 id에 대입
				char gender = row[2][0];			//2번째 줄에 첫번째 글자를 gender에 대입
				int age = atoi(row[3].c_str());
				Client* c = new Client(id, row[1], gender, age, row[4], row[5]);	
									//id, name, gender, age, phonenumber, adress 순
				clientList_.insert({ id, c });
//				vecList.push_back(c);
			}
		}
	}
	file.close();

/*	vector로 검색
	int id = 2;
	string name = "Yuna";
	auto it = find_if(vecList.begin(), vecList.end(),
		[=](Client* p) { return *p == name; });
	if (it != vecList.end()) {
		Client* c = *it;
		c->displayInfo();
	}
*/
}

ClientManagement::~ClientManagement()
{
	ofstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		for (const auto& v : clientList_) {
			Client* c = v.second;
			file << c->id() << ','		// 고객 정보 순서대로 저장
				<< c->getName() << ','
				<< c->getGender() << ','
				<< c->getAge() << ','
				<< c->getPhoneNumber() << ','
				<< c->getAdress() << endl;
		}
	}
	cout << "******고객 리스트 저장 완료******" << endl;
	file.close();
}

vector<string> ClientManagement::parseCSV(istream& file, char delimiter)
{
	stringstream ss;
	vector<string> row;
	string t = " \n\r\t";

	//stringstream을 이용하여 단어 나누기
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
	cout << "이름 : "; getline(cin, name, '\n');
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
	cout << "────────────────────────────────────────────────────────────────────────────" << endl;
	for_each(clientList_.begin(), clientList_.end(),
		[](auto cm) {Client* c = cm.second;	//객체 정보(c)는 map의 value 정보(second)
		if (c != nullptr) {
			cout << "[" << c->id() << "] 이름: " << c->getName()		//ID 순서대로 고객 정보 출력
				<< " 성별: " << c->getGender() << " 나이: " << c->getAge()  
				<< " 전화번호: " << c->getPhoneNumber() << " 주소: " << c->getAdress() << endl;
				// 객체의 멤버 함수에 접근
			cout << "-----------------------------------------------------------------------------" << endl;
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
		cout << "이름: " << c->getName() << " 나이: "			//검색한 ID 정보 출력
			<< c->getAge() << " 전화번호: "
			<< c->getPhoneNumber() << " 주소: "
			<< c->getAdress() << endl;
	}
}

void ClientManagement::cmSearchName() //이름으로 검색
{
	int found=0;		//나중에 이름이 존재하는지 확인하기 위해 사용
	string name;		//검색할 이름
	string cmp_name;	//객체에서 확인할 이름

	cout << "검색할 이름을 입력하세요. "; cin >> name;
	cout << "────────────────────────────────────────────────────────────────────────────" << endl;

	//map의 처음부터 끝까지 검색
	for (auto i = clientList_.begin(); i != clientList_.end(); i++) {
		if(i->second != nullptr)
			cmp_name = i->second->getName();
		if((cmp_name == name)) {		//검색한 이름의 고객이 있다면 중복해서 모두 검색
			found = 1;
			cout << "이름: " << i->second->getName() << " 나이: "
				<< i->second->getAge() << " 전화번호: "
				<< i->second->getPhoneNumber() << " 주소: "
				<< i->second->getAdress() << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
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
		cout << "이름: " << c->getName() << " 나이 : "		//찾는 ID에 대한 정보 출력
			<< c->getAge() << " 전화번호: "
			<< c->getPhoneNumber() << " 주소: "
			<< c->getAdress() << endl << endl;

		int num, age; char one;
		string name, phoneNumber, adress;
		cout << "────────────────────────────────────────────────────────────────────────────" << endl;
		cout << "            바꾸고 싶은 정보를 입력하세요.            " << endl;
		cout << "1: 이름   |   2: 나이   |   3: 전화번호   |   4: 주소   |   0: 취소" << endl;
		Primary::switchInput(num, one); cout << endl;

		//바꾸고 싶은 정보에 따라 switch 문 실행
		switch (num) {
		case 1:		//이름 변경
			cout << "이름 : "; cin.ignore(); getline(cin, name, '\n');
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

void ClientManagement::showList() {
	for (auto cm : clientList_) {
		Client* c = cm.second;
		if (c != nullptr) {
			cout << "[" << c->id() << "] 이름: " << c->getName()		//검색한 ID 정보 출력
				<< " 성별: " << c->getGender() << " 나이: " << c->getAge()
				<< " 전화번호: " << c->getPhoneNumber() << " 주소: " << c->getAdress() << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
		}
	}
}