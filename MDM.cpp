#include "MDM.h"
#include "PDM.h"
#include "purchase.h"
#include <fstream>
#include <sstream>

PurchaseManagement::PurchaseManagement(ClientManagement& cm, ProductManagement& pm) : cm_(cm), pm_(pm)
//°í°´ Á¤º¸ ¸®½ºÆ®¿Í Á¦Ç° Á¤º¸ ¸®½ºÆ®¸¦ °¡Á®¿Í¼­ ¾È¿¡ ÀÖ´Â Á¤º¸¸¦ ¸ðµÎ ·¹ÆÛ·±½º·Î ¹Þ¾Æ¼­ »ç¿ë
{
	ifstream file;
	file.open("shoppinglist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');	//vectorÀÇ ¼ø¼­ ³ª´©´Â ±âÁØÀ» ','·Î ¼³Á¤
			if (row.size()) {
				int id = atoi(row[0].c_str());			//¸Þ¸ðÀå¿¡ ÀúÀåµÇ¾îÀÖ´Â ¹®ÀÚ¸¦ integer·Î ¹Ù²ã¼­ id¿¡ ´ëÀÔ
				int clientID = atoi(row[1].c_str());
				int productID = atoi(row[2].c_str());
				int sellAmount = atoi(row[3].c_str());
				Purchase* m = new Purchase(id, clientID, productID, sellAmount, row[4]);
										//id, °í°´ID, »óÇ°ID, ÁÖ¹®¼ö·®, ÁÖ¹®ÀÏÀÚ ¼ø
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
			file << m->id() << ',' << m->CID() << ","
				<< m->PID() << ',' << m->getAmount() << ','
				<< m->getTime() << endl;
		}
	}
	cout << "******¼îÇÎ ¸®½ºÆ® ÀúÀå ¿Ï·á******" << endl;
	file.close();
}

vector<string> PurchaseManagement::parseCSV(istream& file, char delimiter)
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

// ¼îÇÎ ¸®½ºÆ® ID »ý¼º
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

// Æ¯Á¤ ID¿¡ ´ëÇÑ ¼îÇÎ ¸®½ºÆ® °¡Á®¿À±â
Purchase* PurchaseManagement::mmChooseID(int id) {
	return purchaseList_[id];
}

// ¼îÇÎ Á¤º¸ ÀÔ·Â
void PurchaseManagement::mmInput()
{
	int flag = 0;
	int ID, clientID, productID, sellAmount;
	string sellTime;

	cout << endl << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;

	cm_.showList(); // ÀÔ·ÂÇÏ±â Àü °í°´ Á¤º¸ º¸¿©ÁÖ±â

	while (flag != 1) { 
		cout << "±¸¸ÅÀÚ ID: "; Primary::integerInput(clientID, flag);		// °í°´ ID ÀÔ·Â
		if (clientID < 10001) {												// ¿Ã¹Ù¸¥ ID°¡ µé¾î¿Ã ¶§±îÁö while¹® ¹Ýº¹
			cout << "(ID:10001ºÎÅÍ ½ÃÀÛÀÔ´Ï´Ù)" << endl;
			flag = 0;
		}
	}
	flag = 0; 
	while (flag != 1) {
		cout << "±¸¸ÅÇÑ »óÇ° ID: "; Primary::integerInput(productID, flag);	// »óÇ° ID ÀÔ·Â
		if (productID < 30001) {											// ¿Ã¹Ù¸¥ ID°¡ µé¾î¿Ã ¶§±îÁö while¹® ¹Ýº¹
			cout << "(ID:30001ºÎÅÍ ½ÃÀÛÀÔ´Ï´Ù)" << endl;
			flag = 0;
		}
	}
	flag = 0;
	Product* p = pm_.pdchooseID(productID);			// »óÇ°¸®½ºÆ® ¹Þ¾Æ¿À±â
	int stock = p->getStock();						// »óÇ°¸®½ºÆ® Àç°í ¹Þ¾Æ¿À±â
	while (flag != 1) {
		cout << "±¸¸Å °³¼ö: "; Primary::integerInput(sellAmount, flag);
		if (stock < sellAmount)		// ±¸¸Å °³¼öº¸´Ù Àç°í°¡ Àû´Ù¸é ¿À·ù¸Þ¼¼Áö Ãâ·Â
		{
			cout << endl << "!!Àç°í ºÎÁ·ÀÔ´Ï´Ù!!" << endl;
			cout << "³²Àº Àç°í: " << stock << endl << endl;
			flag = 0;
		}
	} p->setStock(stock - sellAmount);		// Àç°í¿¡ ±¸¸Å ¼ö·® ¹Ý¿µ

	cout << "±¸¸Å ³¯Â¥: "; cin >> sellTime;
	ID = makeID();

	Purchase* m = new Purchase(ID, clientID, productID, sellAmount, sellTime);
	purchaseList_[makeID()] = m;

}

// ¼îÇÎ Á¤º¸ Á¶È¸
void PurchaseManagement::mmOutput(ClientManagement& cm, ProductManagement& pm)
{
	cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
	for_each(purchaseList_.begin(), purchaseList_.end(), [&](auto mm)
		{Purchase* m = mm.second;			// ¼îÇÎ Á¤º¸ mapÀÇ value¿¡ Á¢±Ù -> value°¡ Purchase* ÇüÅÂ
	if (m != nullptr) {
		Client* c = cm.cmChooseID(m->CID());	// °í°´ ¸®½ºÆ®¿Í »óÇ° ¸®½ºÆ® ¹Þ¾Æ¿À±â 
		Product* p = pm.pdchooseID(m->PID());
		cout << "[" << m->id() << "] °í°´ÀÌ¸§: " << c->getName()
			<< " ¼ºº°: " << c->getGender() << " ³ªÀÌ: " << c->getAge() << endl;
		cout << setw(17) << setfill(' ') << " Á¦Ç°¸í: " << p->getName() << endl;
		cout << setw(19) << setfill(' ') <<" ÁÖ¹®¼ö·®: " << m->getAmount() 
			<<" ÁÖ¹®±Ý¾×: " << (m->getAmount()) * (p->getPrice())
			<< " ÁÖ¹®ÀÏÀÚ: " << m->getTime() << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
	}
		}
	); 
}
// °í°´ ÀÌ¸§À¸·Î °Ë»öÇÏ±â
void PurchaseManagement::mmSearchCID()
{
	int found = 0;
	string name;
	string cmp_name;
	cout << "°í°´ ÀÌ¸§À» ÀÔ·ÂÇÏ¼¼¿ä: "; cin >> name;
	cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;

	for (auto i = purchaseList_.begin(); i != purchaseList_.end(); i++) {
		if (i->second != nullptr) {
			Client* c = cm_.cmChooseID(i->second->CID());
			Product* p = pm_.pdchooseID(i->second->PID());
			Purchase* m = i->second;
			cmp_name = c->getName();

			if (name == cmp_name) {
				found = 1;
				cout << "[" << m->id() << "] °í°´ÀÌ¸§: " << c->getName()
					<< " ¼ºº°: " << c->getGender() << " ³ªÀÌ: " << c->getAge()
					<< endl << "        " << " Á¦Ç°¸í: " << p->getName()
					<< " ÁÖ¹®¼ö·®: " << m->getAmount() << " ÁÖ¹®ÀÏÀÚ: " << m->getTime()
					<< " ÁÖ¹®±Ý¾×: " << (m->getAmount()) * (p->getPrice()) << endl;
				cout << "--------------------------------------------------------------------------" << endl;
			}
		}
		cmp_name = "";
	}

	if (found == 0) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "!!ÁÖ¹® ³»¿ªÀÌ ¾ø½À´Ï´Ù!!" << endl;
		cout << "*************************" << endl;
	}
}
void PurchaseManagement::mmSearchPID()
{
	int found = 0;
	string name;
	string cmp_name;
	cout << "Á¦Ç° ÀÌ¸§À» ÀÔ·ÂÇÏ¼¼¿ä: "; cin >> name;
	cout << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;

	for (auto i = purchaseList_.begin(); i != purchaseList_.end(); i++) {
		if (i->second != nullptr) {
			Client* c = cm_.cmChooseID(i->second->CID());
			Product* p = pm_.pdchooseID(i->second->PID());
			Purchase* m = i->second;
			cmp_name = p->getName();

			if (name == cmp_name) {
				found = 1;
				cout << "[" << m->id() << "] °í°´ÀÌ¸§: " << c->getName() 
					<< " ¼ºº°: " << c->getGender() << " ³ªÀÌ: " << c->getAge() 
					<< endl << "        " << " Á¦Ç°¸í: " << p->getName()
					<< " ÁÖ¹®¼ö·®: " << m->getAmount() << " ÁÖ¹®ÀÏÀÚ: " << m->getTime() 
					<< " ÁÖ¹®±Ý¾×: " << (m->getAmount()) * (p->getPrice()) << endl;
				cout << "-----------------------------------------------------------------------------" << endl;
			}
		}
		cmp_name = "";
	}

	if (found == 0) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "!!ÁÖ¹® ³»¿ªÀÌ ¾ø½À´Ï´Ù!!" << endl;
		cout << "*************************" << endl;
	}
}
void PurchaseManagement::deleteReceipt(int id)
{
	if (!(purchaseList_[id])) {
		cout << endl;
		cout << "**************************" << endl;
		cout << "!!ÁÖ¹® ³»¿ªÀÌ ¾ø½À´Ï´Ù!!" << endl;
		cout << "**************************" << endl;
	}
	else {
		purchaseList_.erase(id);
		cout << endl << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
		cout << "!!¼º°øÀûÀ¸·Î Á¦°Å µÇ¾ú½À´Ï´Ù!!" << endl;
		cout << endl << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
	}
}
void PurchaseManagement::mmRevise(int id) // ´Ù¹Ù²ãµµ µÊ
{
	Purchase* m = purchaseList_[id];


	if (!(purchaseList_[id])) {         // Ã£´Â ¾ÆÀÌµð°¡ ¾øÀ¸¸é Ãâ·Â
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!Á¸ÀçÇÏÁö ¾Ê´Â °í°´ÀÔ´Ï´Ù!!" << endl;
		cout << "****************************" << endl;
	}

	else {
		Client* c = cm_.cmChooseID(m->CID());
		Product* p = pm_.pdchooseID(m->PID());
		cout << "[" << m->id() << "] °í°´ÀÌ¸§: " << c->getName()
			<< " ¼ºº°: " << c->getGender() << " ³ªÀÌ: " << c->getAge()
			<< endl << "        " << " Á¦Ç°¸í: " << p->getName()
			<< " ÁÖ¹®¼ö·®: " << m->getAmount() << " ÁÖ¹®ÀÏÀÚ: " << m->getTime()
			<< " ÁÖ¹®±Ý¾×: " << (m->getAmount()) * (p->getPrice()) << endl;

		int num, clientID, productID, sellAmount; char one;
		string sellTime;
		cout << endl << "                  ¹Ù²Ù°í ½ÍÀº Á¤º¸¸¦ ÀÔ·ÂÇÏ¼¼¿ä.                  " << endl;
		cout << "1: °í°´Á¤º¸   |   2: »óÇ°Á¤º¸   |   3: ÁÖ¹®·®   |   4: ÁÖ¹®ÀÏÀÚ" << endl;
		Primary::switchInput(num, one); cout << endl;

		switch (num) {
		case 1:
			cout << "(°í°´ÀÇ ¼¼ºÎ Á¤º¸´Â [°í°´ Á¤º¸ °ü¸®]¿¡¼­ ¹Ù²Ü ¼ö ÀÖ½À´Ï´Ù.) "
				<< endl << "º¯°æµÇ¾î ÀúÀåµÉ °í°´ ID¸¦ ÀÔ·ÂÇÏ¼¼¿ä : ";
			cin >> clientID; m->setClient(clientID);      // °í°´ÀÌ ÇÑ¹øÀÌ¶óµµ ÁÖ¹®Çß´ÂÁö È®ÀÎ
			break;
		case 2:
			cout << "(»óÇ°ÀÇ ¼¼ºÎ Á¤º¸´Â [»óÇ° Á¤º¸ °ü¸®]¿¡¼­ ¹Ù²Ü ¼ö ÀÖ½À´Ï´Ù.) "
				<< endl << "º¯°æµÇ¾î ÀúÀåµÉ Á¦Ç° ID¸¦ ÀÔ·ÂÇÏ¼¼¿ä : ";
			cin >> productID; m->setProduct(productID);      // Á¦Ç°ÀÌ ÇÑ¹øÀÌ¶óµµ ±¸¸ÅµÈ°ÇÁö È®ÀÎ      
			break;
		case 3:
			cout << "ÁÖ¹®·® : "; cin >> sellAmount;
			m->setAmount(sellAmount);
			break;
		case 4:
			cout << "ÁÖ¹®³¯Â¥ : "; cin >> sellTime;
			m->setTime(sellTime);
			break;
		}
		if (0 < num && num < 5) {
			cout << endl << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
			cout << "  !!¼º°øÀûÀ¸·Î º¯°æ µÇ¾ú½À´Ï´Ù!!  " << endl;
			cout << endl << "¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡" << endl;
		}
	}
}
