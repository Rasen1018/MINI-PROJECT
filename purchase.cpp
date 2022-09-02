#include "purchase.h"
#include "PDM.h"
#include "MDM.h"

Purchase::Purchase(int purchaseID, int clientID, int productID, int sellAmount, string sellTime) :
	purchaseID_(purchaseID), clientID_(clientID), productID_(productID), sellAmount_(sellAmount), sellTime_(sellTime) {}

int Purchase::CID() const {
	return clientID_;
}
int Purchase::PID() const {
	return productID_;
}

void Purchase::setClient(int clientID) {
	clientID_ = clientID;
}

void Purchase::setProduct(int productID) {
	productID_ = productID;
}

int Purchase::getAmount()
{
	return sellAmount_;
}
void Purchase::setAmount(int sellamount)
{
	sellAmount_ = sellamount;
}

string Purchase::getTime() {
	return sellTime_;
}
void Purchase::setTime(string& sellTime) {
	sellTime_ = sellTime;
}

int Purchase::id() {
	return purchaseID_; 
}

//void Purchase::calcCount()
//{
//	cout << "개별 가격 : " << salesMoney_ / sellAmount_ << "만원" << endl;
//}








//string Purchase::getChannel() {
//	return channel_;
//}
//void Purchase::setChannel(string& channel) {
//	channel_ = channel;
//}
//
//string Purchase::getOption() {
//	return option_;
//}              
//void Purchase::setOption(string& option) {
//	option_ = option;
//}