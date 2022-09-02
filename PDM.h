#ifndef __PDM_H__
#define __PDM_H__
#include "product.h"
#include "primary.h"

class ProductManagement{
public:
	ProductManagement();
	void pdInput();
	void pdOutput();
	Product* pdchooseID(int);
	void pdSearchID(int);
	void pdSearchCategory();
	int makeID();
	void deleteProduct(int);
	void pdRevise(int);

private:
	map<int, Product*> productList_;
};

#endif // !__PDM_H__
