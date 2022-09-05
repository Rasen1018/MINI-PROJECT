#ifndef __MDM_H__
#define __MDM_H__
#include "CRM.h"

// �Ű������� �ʿ��� Ŭ���� ���� ��������
class ProductManagement;
class Purchase;
class Primary;

class PurchaseManagement {
public:
	PurchaseManagement(ClientManagement&, ProductManagement&);
	~PurchaseManagement();
	int makeID();
	Purchase* mmChooseID(int id);
	void mmInput();
	void mmOutput(ClientManagement&, ProductManagement&);
	void mmSearchCID();
	void mmSearchPID();
	void deleteReceipt(int id);
	void mmRevise(int id);

	vector<string> parseCSV(istream&, char);

private:
	map<int, Purchase*> purchaseList_;
	ClientManagement& cm_;
	ProductManagement& pm_;

};

#endif // !__MDM_H__

