#include "primary.h"
#include "CRM.h"
#include "PDM.h"
#include "MDM.h"

/*getchar를 이용해서 한글자만 받고(문자로) ASCII코드로 비교 -> 숫자가 아니면 다시입력 printf("%d\b", num) 으로*/
void title(char& one, int& num);
void clientInterface(ClientManagement&);
void productInterface(ProductManagement&);
void purchaseInterface(PurchaseManagement& mm, ClientManagement& cm, ProductManagement& pm);

int main()
{
	int num;
	char one;
	ClientManagement cm;	//고객 클래스 관리
	ProductManagement pm;	//제품 클래스 관리
	PurchaseManagement mm(cm, pm);  //쇼핑 클래스 관리

	while (1) {				//끝내기 전까지 계속 반복

	title(one, num);				//타이틀 화면
		switch (num) {
		case 1:
			clientInterface(cm);	// 1번 누르면 고객 정보 관리
			break;
		case 2:
			productInterface(pm);	// 2번 누르면 제품 정보 관리
			break;
		case 3:
			purchaseInterface(mm, cm, pm);	 // 3번 누르면 쇼핑 정보 관리
			break;
		case 4:
			return 0;
			break;
		default:
			cout << "!!다시 입력하세요!!";
		}
		cin.clear();
	}

	return 0;
}


void title(char& one, int& num)
{
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "                     상품 관리 프로그램                         " << endl;
	cout << endl;
	cout << "                      1. 고객 정보 관리                        " << endl;
	cout << "                      2. 상품 정보 관리                        " << endl;
	cout << "                      3. 쇼핑 정보 관리                        " << endl;
	cout << "                      4. 종료                        " << endl;
	cout << endl;
	cout << "                  몇번을 입력하시겠습니까? ";
	Primary::switchInput(num, one);
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	system("cls");
}

void clientInterface(ClientManagement& cm) // 고객 정보 인터페이스
{
	int num, id; char one;
	cout << "1번: 입력" << " | " << "2번: 조회 " << " | "
		<< "3번: ID 검색" << " | " << "4번: 이름 검색" << " | " << "0번: 취소" << endl;
	Primary::switchInput(num, one);

	switch (num) {
	case 1:
		cm.cmInput();  // 입력
		break;
	case 2: {
		cm.cmOutput();  // 조회
		cout << endl << "    고객 정보를 변경/삭제 하시겠습니까?    " << endl;
		cout << "1: 변경   |   2: 삭제   |   0: 취소   |" << endl;
		Primary::switchInput(num, one);

		if (num == 1) {
			cout << "변경하려는 고객 ID를 입력하세요. "; cin >> id;
			system("cls");
			cout << "────────────────────────────────────────────────────────────────────────────" << endl;
			cm.cmRevise(id);  // 변경
		}
		else if (num == 2) {
			cout << "삭제하려는 고객 ID를 입력하세요. "; cin >> id;
			cout << "────────────────────────────────────────────────────────────────────────────" << endl;
			cm.deleteClient(id);  // 삭제
		}
		system("cls");
		break;
	}
	case 3:
		cout << "검색할 ID를 입력하세요. "; cin >> id;
		cm.cmSearchID(id);	// ID로 검색
		break;
	case 4:
		cm.cmSearchName();	// 이름으로 검색
		break;
	}
}

void productInterface(ProductManagement& pm)	// 제품 정보 인터페이스
{
	int num, id; char one;
	cout << "1번: 입력" << " | " << "2번: 조회 " << " | "
		<< "3번: ID 검색" << " | " << "4번: 품목 검색" << " | " << "0번: 취소" << endl;
	Primary::switchInput(num, one);

	switch (num) {
	case 1:
		pm.pdInput();	// 입력
		break;
	case 2: {
		pm.pdOutput();	// 조회
		cout << endl << "    제품 정보를 변경/삭제 하시겠습니까?    " << endl;
		cout << "1: 변경   |   2: 삭제   |   0: 취소   |" << endl;
		Primary::switchInput(num, one);

		if (num == 1) {
			cout << "변경하려는 제품 ID를 입력하세요. "; cin >> id;
			system("cls");
			cout << "────────────────────────────────────────────────────────────────────────────" << endl;
			pm.pdRevise(id);	// 변경
		}
		else if (num == 2) {
			cout << "삭제하려는 제품 ID를 입력하세요. "; cin >> id;
			cout << "────────────────────────────────────────────────────────────────────────────" << endl;
			pm.deleteProduct(id);	// 제거
		}
		system("cls");
		break;
	}
	case 3:
		cout << "검색할 ID를 입력하세요. "; cin >> id;
		pm.pdSearchID(id);		// ID로 검색
		break;
	case 4:
		pm.pdSearchCategory();		// 품목으로 검색
		break;
	}
}

void purchaseInterface(PurchaseManagement& mm, ClientManagement& cm, ProductManagement& pm)
// 구매목록 인터페이스
{
	int num, id; char one;
	cout << "1번: 입력" << " | " << "2번: 조회 " << " | "
		<< "3번: 고객 검색" << " | " << "4번: 품목 검색" << " | " << "0번: 취소" << endl;
	Primary::switchInput(num, one);

	switch (num) {
	case 1:
		mm.mmInput();	// 입력
		break;
	case 2: {
		mm.mmOutput(cm, pm);	// 조회
		cout << endl << "    주문 정보를 변경/삭제 하시겠습니까?    " << endl;
		cout << "1: 변경   |   2: 삭제   |   0: 취소   |" << endl;
		Primary::switchInput(num, one);

		if (num == 1) {
			cout << "변경하려는 구매 명단 ID를 입력하세요. "; cin >> id;
			system("cls");
			cout << "────────────────────────────────────────────────────────────────────────────" << endl;
			mm.mmRevise(id);	// 변경
		}
		else if (num == 2) {
			cout << "삭제하려는 구매 명단의 ID를 입력하세요. "; cin >> id;
			cout << "────────────────────────────────────────────────────────────────────────────" << endl;
			mm.deleteReceipt(id);	// 제거
		}
		system("cls");
		break;
	}
	case 3:
		mm.mmSearchCID();	// 고객 정보로 검색
		break;
	case 4:
		mm.mmSearchPID();	// 제품 정보로 검색
		break;
	}
}

// 	while (1) { one = _getch(); if (one >= '0' && one <= '9') break; printf("\b "); }
//num = one - '0';
