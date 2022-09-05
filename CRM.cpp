#include "CRM.h"
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>

ClientManagement::ClientManagement()
{
//	std::vector<Client*> vecList;
	ifstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');	//vectorÀÇ ¼ø¼­ ³ª´©´Â ±âÁØÀ» ','·Î ¼³Á¤
			if (row.size()) {
				int id = atoi(row[0].c_str());		//¸Þ¸ðÀå¿¡ ÀúÀåµÇ¾îÀÖ´Â ¹®ÀÚ¸¦ integer·Î ¹Ù²ã¼­ id¿¡ ´ëÀÔ
				char gender = row[2][0];			//2¹øÂ° ÁÙ¿¡ Ã¹¹øÂ° ±ÛÀÚ¸¦ gender¿¡ ´ëÀÔ
				int age = atoi(row[3].c_str());
				Client* c = new Client(id, row[1], gender, age, row[4], row[5]);	
									//id, name, gender, age, phonenumber, adress ¼ø
				clientList_.insert({ id, c });
//				vecList.push_back(c);
			}
		}
	}
	file.close();

/*	vector·Î °Ë»ö
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
			if(c != nullptr) {
			file << c->id() << ','			// °í°´ Á¤º¸ ¼ø¼­´ë·Î ÀúÀå
				<< c->getName() << ','
				<< c->getGender() << ','
				<< c->getAge() << ','
				<< c->getPhoneNumber() << ','
				<< c->getAdress() << endl;
			}
		}
	}
	cout << "******°í°´ ¸®½ºÆ® ÀúÀå ¿Ï·á******" << endl;
	file.close();
}

vector<string> ClientManagement::parseCSV(istream& file, char delimiter)
{
	stringstream ss;
	vector<string> row;
	string t = " \n\r\t";

	//stringstreamÀ» ÀÌ¿ëÇÏ¿© ´Ü¾î ³ª´©±â
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

int ClientManagement::makeID() {	//°í°´ ID »ý¼º(mapÀº ÀÚµ¿Á¤·Ä, Áßº¹ X ±â´ÉÀÌ ÀÖ±â ¶§¹®¿¡ 
									//primary key¸¦ ¸¸µé±â¿¡ ÁÁ´Ù.
	auto key = clientList_.end();	//key¿¡ end()¸¦ ´ëÀÔ
	if (clientList_.size() == 0) {	
		return 10001;				//¸¸¾à °í°´ Á¤º¸°¡ ¾ø´Ù¸é 10001À» ¹ÝÈ¯
	}
	else 
	{
		int id = (--key)->first;	//ÀÖ´Ù¸é ´ÙÀ½ ¼ø¼­ºÎÅÍ id¸¦ 1¾¿ Áõ°¡
		return ++id;
	}
}

void ClientManagement::cmInput()
{
	string name, phoneNumber, adress;
	char gender;
	int age = 1, flag = 0;

	//°í°´ Á¤º¸ ÀÔ·Â
	cout << "ÀÌ¸§ : "; getline(cin, name, '\n');
	do { 
		if (flag == 1) 
		{ cout << endl << "!!¼ºº°À» ´Ù½Ã ÀÔ·ÂÇÏ¼¼¿ä!!" << endl << endl; }					// flag ==1ÀÌ¸é Ãâ·Â
		cout << "¼ºº°(M/W) : ";  cin >> gender; gender = toupper(gender); flag = 1; }	
	while (gender != 'M' && gender != 'W');												// ¼ºº°À» Á¦´ë·Î ¹ÞÀ» ¶§±îÁö ¹Ýº¹
	flag = 0;
	while (flag!=1) { cout << "³ªÀÌ : "; Primary::integerInput(age, flag); }				// Á¤¼ö°¡ ¾Æ´Ï¸é °è¼Ó ¹Ýº¹
	cout << "ÀüÈ­¹øÈ£ : "; cin >> phoneNumber;
	cout << "ÁÖ¼Ò : "; cin.ignore(); getline(cin, adress, '\n');
	
	int id = makeID();	//¾ÆÀÌµð´Â ÀÚµ¿ »ý¼º
	
	//°í°´ °´Ã¼ µ¿Àû ¸Þ¸ð¸® ÇÒ´ç(Èü¿¡ »ý¼º)
	Client* c = new Client(id, name, gender, age, phoneNumber, adress);

	clientList_[makeID()] = c; //map¿¡ key -> makeID() , value -> c ´ëÀÔ
							   //clientList_.insert({makeID(), c});
	
	cout << endl << "¼º°øÀûÀ¸·Î ÀÔ·ÂÇß½À´Ï´Ù." << endl << "Àá½ÃÈÄ ¸ÞÀÎ¸Þ´º·Î µ¹¾Æ°©´Ï´Ù." << endl;
	Sleep(1000); Sleep(1000);
	system("cls");
	/*Client* client1 = new Client("TaeHun", 'M', 30, "010-5557-9957", "AnSan");
	clientList_[1] = client1;*/
}

void ClientManagement::cmOutput()
{			// mapÀÇ Ã³À½ºÎÅÍ ³¡±îÁö ÇÏ³ª¾¿ Ãâ·Â
	cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
	for_each(clientList_.begin(), clientList_.end(),
		[](auto cm) {Client* c = cm.second;	//°´Ã¼ Á¤º¸(c)´Â mapÀÇ value Á¤º¸(second)
		if (c != nullptr) {
			cout << "[" << c->id() << "] ÀÌ¸§: " << c->getName()		//ID ¼ø¼­´ë·Î °í°´ Á¤º¸ Ãâ·Â
				<< " ¼ºº°: " << c->getGender() << " ³ªÀÌ: " << c->getAge()  
				<< " ÀüÈ­¹øÈ£: " << c->getPhoneNumber() << " ÁÖ¼Ò: " << c->getAdress() << endl;
				// °´Ã¼ÀÇ ¸â¹ö ÇÔ¼ö¿¡ Á¢±Ù
			cout << "-----------------------------------------------------------------------------" << endl;
			}
		}
	);													

	//for (auto i = clientList_.begin(); i != clientList_.end(); i++) {
	//	cout << i->first << " " << i->second->getName() << endl;
	//}
}

Client* ClientManagement::cmChooseID(int id) //id°ª ¹ÝÈ¯
{
	auto it = clientList_.find(id);
	return (it != clientList_.end())? clientList_[id] : nullptr;
}

void ClientManagement::cmSearchID(int id) //ID·Î °Ë»ö
{
	char one;
	Client* c = clientList_[id];				//°Ë»öÇÒ ID ÀÔ·Â

	if (clientList_.find(id)==clientList_.end())						//ID°¡ ¾øÀ¸¸é Ãâ·Â
	{
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!Á¸ÀçÇÏÁö ¾Ê´Â °í°´ÀÔ´Ï´Ù!!" << endl;
		cout << "\t\t" << "!!Àá½ÃÈÄ¿¡ ¸ÞÀÎ ¸Þ´º·Î µ¹¾Æ°©´Ï´Ù!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
		system("cls");
	}

	else {
		cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl
			<< id << " °í°´ Á¤º¸" << endl
			<< "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
		cout << "ÀÌ¸§: " << c->getName() << " ³ªÀÌ: "			//°Ë»öÇÑ ID Á¤º¸ Ãâ·Â
			<< c->getAge() << " ÀüÈ­¹øÈ£: "
			<< c->getPhoneNumber() << " ÁÖ¼Ò: "
			<< c->getAdress() << endl;

		cout << endl << endl << "\t" << "¾Æ¹«Å°³ª ÀÔ·ÂÇÏ¸é ¸ÞÀÎÈ­¸éÀ¸·Î µ¹¾Æ°©´Ï´Ù." << endl;
		one = _getch();
		system("cls");
		cin.ignore();
	}
}

void ClientManagement::cmSearchName() //ÀÌ¸§À¸·Î °Ë»ö
{
	int found=0;		//³ªÁß¿¡ ÀÌ¸§ÀÌ Á¸ÀçÇÏ´ÂÁö È®ÀÎÇÏ±â À§ÇØ »ç¿ë
	char one;
	string name;		//°Ë»öÇÒ ÀÌ¸§
	string cmp_name;	//°´Ã¼¿¡¼­ È®ÀÎÇÒ ÀÌ¸§

	cout << "°Ë»öÇÒ ÀÌ¸§À» ÀÔ·ÂÇÏ¼¼¿ä. "; cin >> name;
	cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;

	//mapÀÇ Ã³À½ºÎÅÍ ³¡±îÁö °Ë»ö
	for (auto i = clientList_.begin(); i != clientList_.end(); i++) {
		if(i->second != nullptr)
			cmp_name = i->second->getName();
		if((cmp_name == name)) {		//°Ë»öÇÑ ÀÌ¸§ÀÇ °í°´ÀÌ ÀÖ´Ù¸é Áßº¹ÇØ¼­ ¸ðµÎ °Ë»ö
			found = 1;
			cout << "ÀÌ¸§: " << i->second->getName() << " ³ªÀÌ: "
				<< i->second->getAge() << " ÀüÈ­¹øÈ£: "
				<< i->second->getPhoneNumber() << " ÁÖ¼Ò: "
				<< i->second->getAdress() << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
		}
		cmp_name = ""; //string ÃÊ±âÈ­
	} 

	if (found == 0) {
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!Ã£´Â ÀÌ¸§ÀÌ ¾ø½À´Ï´Ù!!" << endl;
		cout << "\t\t" << "!!Àá½ÃÈÄ¿¡ ¸ÞÀÎ ¸Þ´º·Î µ¹¾Æ°©´Ï´Ù!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
		system("cls");
	}
	else {
		cout << endl << endl << "\t" << "¾Æ¹«Å°³ª ÀÔ·ÂÇÏ¸é ¸ÞÀÎÈ­¸éÀ¸·Î µ¹¾Æ°©´Ï´Ù." << endl;
		one = _getch();
		system("cls");
		cin.ignore();
	}
}

//Á¤º¸ »èÁ¦
void ClientManagement::deleteClient(int id) {

	if(clientList_.find(id)==clientList_.end()) {			// Ã£´Â ¾ÆÀÌµð°¡ ¾øÀ¸¸é Ãâ·Â
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!Á¸ÀçÇÏÁö ¾Ê´Â °í°´ÀÔ´Ï´Ù!!" << endl;
		cout << "\t\t" << "!!Àá½ÃÈÄ¿¡ ¸ÞÀÎ ¸Þ´º·Î µ¹¾Æ°©´Ï´Ù!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}
	else {
		clientList_.erase(id);			// erease·Î key »èÁ¦
		cout << endl << "\t\t" << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
		cout << "\t\t" << "!!¼º°øÀûÀ¸·Î Á¦°Å µÇ¾ú½À´Ï´Ù!!" << endl;
		cout << "\t\t" << "!!Àá½ÃÈÄ¿¡ ¸ÞÀÎ ¸Þ´º·Î µ¹¾Æ°©´Ï´Ù!!" << endl;
		cout << endl << "\t\t" << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
		Sleep(1000); Sleep(1000);
	}
	getchar();
}

//Á¤º¸ º¯°æ
void ClientManagement::cmRevise(int id) {

	Client* c = clientList_[id];

	if (!(clientList_[id])) {			// Ã£´Â ¾ÆÀÌµð°¡ ¾øÀ¸¸é Ãâ·Â
		cout << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		cout << "\t\t" << "!!Á¸ÀçÇÏÁö ¾Ê´Â °í°´ÀÔ´Ï´Ù!!" << endl;
		cout << "\t\t" << "!!Àá½ÃÈÄ¿¡ ¸ÞÀÎ ¸Þ´º·Î µ¹¾Æ°©´Ï´Ù!!" << endl;
		cout << endl << "\t\t" << "************************************" << endl;
		Sleep(1000); Sleep(1000);
	}

	else {
		cout << "ÀÌ¸§: " << c->getName() << " ³ªÀÌ : "		//Ã£´Â ID¿¡ ´ëÇÑ Á¤º¸ Ãâ·Â
			<< c->getAge() << " ÀüÈ­¹øÈ£: "
			<< c->getPhoneNumber() << " ÁÖ¼Ò: "
			<< c->getAdress() << endl << endl;

		int num, age; char one;
		string name, phoneNumber, adress;
		cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
		cout << "            ¹Ù²Ù°í ½ÍÀº Á¤º¸¸¦ ÀÔ·ÂÇÏ¼¼¿ä.            " << endl;
		cout << "1: ÀÌ¸§   |   2: ³ªÀÌ   |   3: ÀüÈ­¹øÈ£   |   4: ÁÖ¼Ò   |   0: Ãë¼Ò" << endl;
		Primary::switchInput(num, one); cout << endl;

		//¹Ù²Ù°í ½ÍÀº Á¤º¸¿¡ µû¶ó switch ¹® ½ÇÇà
		switch (num) {
		case 1:		//ÀÌ¸§ º¯°æ
			cout << "ÀÌ¸§ : "; cin.ignore(); getline(cin, name, '\n');
			c->setName(name);
			break;
		case 2:		//³ªÀÌ º¯°æ
			cout << "³ªÀÌ : "; cin >> age;
			c->setAge(age);
			break;
		case 3:		//ÀüÈ­¹øÈ£ º¯°æ
			cout << "ÀüÈ­¹øÈ£ : "; cin >> phoneNumber;
			c->setPhoneNumber(phoneNumber);
			break;
		case 4:		//ÁÖ¼Ò º¯°æ
			cout << "ÁÖ¼Ò : "; cin.ignore(); getline(cin, adress, '\n');
			c->setAdress(adress);
			break;
		default:
			getchar();
			system("cls");
			break;
		}
		if (0 < num && num < 5) {
			cout << endl << "\t\t" << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
			cout << "\t\t" << "!!¼º°øÀûÀ¸·Î º¯°æ µÇ¾ú½À´Ï´Ù!!" << endl;
			cout << "\t\t" << "!!Àá½ÃÈÄ¿¡ ¸ÞÀÎ ¸Þ´º·Î µ¹¾Æ°©´Ï´Ù!!" << endl;
			cout << endl << "\t\t" << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
			Sleep(1000); Sleep(1000); system("cls");
		}
	}
}

void ClientManagement::showList() {
	for (auto cm : clientList_) {
		Client* c = cm.second;
		if (c != nullptr) {
			cout << "[" << c->id() << "] ÀÌ¸§: " << c->getName()		//°Ë»öÇÑ ID Á¤º¸ Ãâ·Â
				<< " ¼ºº°: " << c->getGender() << " ³ªÀÌ: " << c->getAge()
				<< " ÀüÈ­¹øÈ£: " << c->getPhoneNumber() << " ÁÖ¼Ò: " << c->getAdress() << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
		}
	}
}