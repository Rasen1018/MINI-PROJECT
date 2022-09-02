#ifndef __CRM_H__
#define __CRM_H__
#include "client.h"

class Primary;

class ClientManagement {
public:
	ClientManagement();
	int makeID(); 
	void cmInput();
	void cmOutput();
	Client* cmChooseID(int);
	void cmSearchID(int);
	void cmSearchName();
	void deleteClient(int);
	void cmRevise(int);

private:
	map<int, Client*> clientList_; //고객 데이터를 map에 저장
};


#endif // !__CRM_H__

