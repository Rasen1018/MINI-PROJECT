#ifndef __PURCHASE_H__
#define __PURCHASE_H__
#include "client.h"

class PurchaseManagement;
class ProductManagement;

class Purchase {
public:
	Purchase(int = 0, int = 0, int = 0, int=0, string = "");

	int CID() const;
	int PID() const;
	void setClient(int);
	void setProduct(int);
	int getAmount();
	string getTime();
	int id();

	void setAmount(int);
	void setTime(string&);
private:
	int purchaseID_;
	int clientID_;
	int productID_;
	int sellAmount_;
	string sellTime_;
};




//string getChannel();
//void setChannel(string&);
//string getOption();
//void setOption(string&);

#endif

