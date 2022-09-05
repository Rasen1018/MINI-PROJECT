#include "MDM.h"
#include "PDM.h"
#include "purchase.h"
#include <fstream>
#include <sstream>

PurchaseManagement::PurchaseManagement(ClientManagement& cm, ProductManagement& pm) : cm_(cm), pm_(pm)
//堅偌 薑爾 葬蝶お諦 薯ヶ 薑爾 葬蝶お蒂 陛螳諦憮 寰縑 氈朝 薑爾蒂 賅舒 溯ぷ楛蝶煎 嫡嬴憮 餌辨
{
	ifstream file;
	file.open("shoppinglist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');	//vector曖 牖憮 釭援朝 晦遽擊 ','煎 撲薑
			if (row.size()) {
				int id = atoi(row[0].c_str());			//詭賅濰縑 盪濰腎橫氈朝 僥濠蒂 integer煎 夥脯憮 id縑 渠殮
				int clientID = atoi(row[1].c_str());
				int productID = atoi(row[2].c_str());
				int sellAmount = atoi(row[3].c_str());
				Purchase* m = new Purchase(id, clientID, productID, sellAmount, row[4]);
										//id, 堅偌ID, 鼻ヶID, 輿僥熱榆, 輿僥橾濠 牖
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
	cout << "******澗ё 葬蝶お 盪濰 諫猿******" << endl;
	file.close();
}

vector<string> PurchaseManagement::parseCSV(istream& file, char delimiter)
{
	stringstream ss;
	vector<string> row;
	string t = " \n\r\t";

	//stringstream擊 檜辨ж罹 欽橫 釭援晦
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

// 澗ё 葬蝶お ID 儅撩
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

// か薑 ID縑 渠и 澗ё 葬蝶お 陛螳螃晦
Purchase* PurchaseManagement::mmChooseID(int id) {
	return purchaseList_[id];
}

// 澗ё 薑爾 殮溘
void PurchaseManagement::mmInput()
{
	int flag = 0;
	int ID, clientID, productID, sellAmount;
	string sellTime;

	cout << endl << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;

	cm_.showList(); // 殮溘ж晦 瞪 堅偌 薑爾 爾罹輿晦

	while (flag != 1) { 
		cout << "掘衙濠 ID: "; Primary::integerInput(clientID, flag);		// 堅偌 ID 殮溘
		if (clientID < 10001) {												// 螢夥艇 ID陛 菟橫螢 陽梱雖 while僥 奩犒
			cout << "(ID:10001睡攪 衛濛殮棲棻)" << endl;
			flag = 0;
		}
	}
	flag = 0; 
	while (flag != 1) {
		cout << "掘衙и 鼻ヶ ID: "; Primary::integerInput(productID, flag);	// 鼻ヶ ID 殮溘
		if (productID < 30001) {											// 螢夥艇 ID陛 菟橫螢 陽梱雖 while僥 奩犒
			cout << "(ID:30001睡攪 衛濛殮棲棻)" << endl;
			flag = 0;
		}
	}
	flag = 0;
	Product* p = pm_.pdchooseID(productID);			// 鼻ヶ葬蝶お 嫡嬴螃晦
	int stock = p->getStock();						// 鼻ヶ葬蝶お 營堅 嫡嬴螃晦
	while (flag != 1) {
		cout << "掘衙 偃熱: "; Primary::integerInput(sellAmount, flag);
		if (stock < sellAmount)		// 掘衙 偃熱爾棻 營堅陛 瞳棻賊 螃盟詭撮雖 轎溘
		{
			cout << endl << "!!營堅 睡褶殮棲棻!!" << endl;
			cout << "陴擎 營堅: " << stock << endl << endl;
			flag = 0;
		}
	} p->setStock(stock - sellAmount);		// 營堅縑 掘衙 熱榆 奩艙

	cout << "掘衙 陳瞼: "; cin >> sellTime;
	ID = makeID();

	Purchase* m = new Purchase(ID, clientID, productID, sellAmount, sellTime);
	purchaseList_[makeID()] = m;

}

// 澗ё 薑爾 褻��
void PurchaseManagement::mmOutput(ClientManagement& cm, ProductManagement& pm)
{
	cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
	for_each(purchaseList_.begin(), purchaseList_.end(), [&](auto mm)
		{Purchase* m = mm.second;			// 澗ё 薑爾 map曖 value縑 蕾斬 -> value陛 Purchase* ⑽鷓
	if (m != nullptr) {
		Client* c = cm.cmChooseID(m->CID());	// 堅偌 葬蝶お諦 鼻ヶ 葬蝶お 嫡嬴螃晦 
		Product* p = pm.pdchooseID(m->PID());
		cout << "[" << m->id() << "] 堅偌檜葷: " << c->getName()
			<< " 撩滌: " << c->getGender() << " 釭檜: " << c->getAge() << endl;
		cout << setw(17) << setfill(' ') << " 薯ヶ貲: " << p->getName() << endl;
		cout << setw(19) << setfill(' ') <<" 輿僥熱榆: " << m->getAmount() 
			<<" 輿僥旎擋: " << (m->getAmount()) * (p->getPrice())
			<< " 輿僥橾濠: " << m->getTime() << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
	}
		}
	); 
}
// 堅偌 檜葷戲煎 匐儀ж晦
void PurchaseManagement::mmSearchCID()
{
	int found = 0;
	string name;
	string cmp_name;
	cout << "堅偌 檜葷擊 殮溘ж撮蹂: "; cin >> name;
	cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;

	for (auto i = purchaseList_.begin(); i != purchaseList_.end(); i++) {
		if (i->second != nullptr) {
			Client* c = cm_.cmChooseID(i->second->CID());
			Product* p = pm_.pdchooseID(i->second->PID());
			Purchase* m = i->second;
			cmp_name = c->getName();

			if (name == cmp_name) {
				found = 1;
				cout << "[" << m->id() << "] 堅偌檜葷: " << c->getName()
					<< " 撩滌: " << c->getGender() << " 釭檜: " << c->getAge()
					<< endl << "        " << " 薯ヶ貲: " << p->getName()
					<< " 輿僥熱榆: " << m->getAmount() << " 輿僥橾濠: " << m->getTime()
					<< " 輿僥旎擋: " << (m->getAmount()) * (p->getPrice()) << endl;
				cout << "--------------------------------------------------------------------------" << endl;
			}
		}
		cmp_name = "";
	}

	if (found == 0) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "!!輿僥 頂羲檜 橈蝗棲棻!!" << endl;
		cout << "*************************" << endl;
	}
}
void PurchaseManagement::mmSearchPID()
{
	int found = 0;
	string name;
	string cmp_name;
	cout << "薯ヶ 檜葷擊 殮溘ж撮蹂: "; cin >> name;
	cout << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;

	for (auto i = purchaseList_.begin(); i != purchaseList_.end(); i++) {
		if (i->second != nullptr) {
			Client* c = cm_.cmChooseID(i->second->CID());
			Product* p = pm_.pdchooseID(i->second->PID());
			Purchase* m = i->second;
			cmp_name = p->getName();

			if (name == cmp_name) {
				found = 1;
				cout << "[" << m->id() << "] 堅偌檜葷: " << c->getName() 
					<< " 撩滌: " << c->getGender() << " 釭檜: " << c->getAge() 
					<< endl << "        " << " 薯ヶ貲: " << p->getName()
					<< " 輿僥熱榆: " << m->getAmount() << " 輿僥橾濠: " << m->getTime() 
					<< " 輿僥旎擋: " << (m->getAmount()) * (p->getPrice()) << endl;
				cout << "-----------------------------------------------------------------------------" << endl;
			}
		}
		cmp_name = "";
	}

	if (found == 0) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "!!輿僥 頂羲檜 橈蝗棲棻!!" << endl;
		cout << "*************************" << endl;
	}
}
void PurchaseManagement::deleteReceipt(int id)
{
	if (!(purchaseList_[id])) {
		cout << endl;
		cout << "**************************" << endl;
		cout << "!!輿僥 頂羲檜 橈蝗棲棻!!" << endl;
		cout << "**************************" << endl;
	}
	else {
		purchaseList_.erase(id);
		cout << endl << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
		cout << "!!撩奢瞳戲煎 薯剪 腎歷蝗棲棻!!" << endl;
		cout << endl << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
	}
}
void PurchaseManagement::mmRevise(int id) // 棻夥脯紫 脾
{
	Purchase* m = purchaseList_[id];


	if (!(purchaseList_[id])) {         // 瓊朝 嬴檜蛤陛 橈戲賊 轎溘
		cout << endl;
		cout << "****************************" << endl;
		cout << "!!襄營ж雖 彊朝 堅偌殮棲棻!!" << endl;
		cout << "****************************" << endl;
	}

	else {
		Client* c = cm_.cmChooseID(m->CID());
		Product* p = pm_.pdchooseID(m->PID());
		cout << "[" << m->id() << "] 堅偌檜葷: " << c->getName()
			<< " 撩滌: " << c->getGender() << " 釭檜: " << c->getAge()
			<< endl << "        " << " 薯ヶ貲: " << p->getName()
			<< " 輿僥熱榆: " << m->getAmount() << " 輿僥橾濠: " << m->getTime()
			<< " 輿僥旎擋: " << (m->getAmount()) * (p->getPrice()) << endl;

		int num, clientID, productID, sellAmount; char one;
		string sellTime;
		cout << endl << "                  夥紱堅 談擎 薑爾蒂 殮溘ж撮蹂.                  " << endl;
		cout << "1: 堅偌薑爾   |   2: 鼻ヶ薑爾   |   3: 輿僥榆   |   4: 輿僥橾濠" << endl;
		Primary::switchInput(num, one); cout << endl;

		switch (num) {
		case 1:
			cout << "(堅偌曖 撮睡 薑爾朝 [堅偌 薑爾 婦葬]縑憮 夥羚 熱 氈蝗棲棻.) "
				<< endl << "滲唳腎橫 盪濰腆 堅偌 ID蒂 殮溘ж撮蹂 : ";
			cin >> clientID; m->setClient(clientID);      // 堅偌檜 и廓檜塭紫 輿僥ц朝雖 �挫�
			break;
		case 2:
			cout << "(鼻ヶ曖 撮睡 薑爾朝 [鼻ヶ 薑爾 婦葬]縑憮 夥羚 熱 氈蝗棲棻.) "
				<< endl << "滲唳腎橫 盪濰腆 薯ヶ ID蒂 殮溘ж撮蹂 : ";
			cin >> productID; m->setProduct(productID);      // 薯ヶ檜 и廓檜塭紫 掘衙脹勒雖 �挫�      
			break;
		case 3:
			cout << "輿僥榆 : "; cin >> sellAmount;
			m->setAmount(sellAmount);
			break;
		case 4:
			cout << "輿僥陳瞼 : "; cin >> sellTime;
			m->setTime(sellTime);
			break;
		}
		if (0 < num && num < 5) {
			cout << endl << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
			cout << "  !!撩奢瞳戲煎 滲唳 腎歷蝗棲棻!!  " << endl;
			cout << endl << "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
		}
	}
}
