#ifndef __PRODUCT_H__
#define __PRODUCT_H__
#include "client.h"

class Product {
public:
	Product(int = 0, string = "", int = 0, int = 0, string = "");

	int getID() const;
	string getName();
	int getPrice();
	int getStock();
	string category();

	void setName(string&);
	void setPrice(int);
	void setStock(int);
	void setcatg(string&);

private:
	int productID_;
	string productName_;
	int price_;
	int stock_;
	string category_;
};


#endif 

