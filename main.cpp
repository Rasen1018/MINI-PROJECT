#include "primary.h"
#include "CRM.h"
#include "PDM.h"
#include "MDM.h"

/*getchar�� �̿��ؼ� �ѱ��ڸ� �ް�(���ڷ�) ASCII�ڵ�� �� -> ���ڰ� �ƴϸ� �ٽ��Է� printf("%d\b", num) ����*/
void title(char& one, int& num);
void clientInterface(ClientManagement&);
void productInterface(ProductManagement&);
void purchaseInterface(PurchaseManagement& mm, ClientManagement& cm, ProductManagement& pm);

int main()
{
	int num;
	char one;
	ClientManagement cm;	//�� Ŭ���� ����
	ProductManagement pm;	//��ǰ Ŭ���� ����
	PurchaseManagement mm(cm, pm);  //���� Ŭ���� ����

	while (1) {				//������ ������ ��� �ݺ�

	title(one, num);				//Ÿ��Ʋ ȭ��
		switch (num) {
		case 1:
			clientInterface(cm);	// 1�� ������ �� ���� ����
			break;
		case 2:
			productInterface(pm);	// 2�� ������ ��ǰ ���� ����
			break;
		case 3:
			purchaseInterface(mm, cm, pm);	 // 3�� ������ ���� ���� ����
			break;
		case 4:
			return 0;
			break;
		default:
			cout << "!!�ٽ� �Է��ϼ���!!";
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
	cout << "                     ��ǰ ���� ���α׷�                         " << endl;
	cout << endl;
	cout << "                      1. �� ���� ����                        " << endl;
	cout << "                      2. ��ǰ ���� ����                        " << endl;
	cout << "                      3. ���� ���� ����                        " << endl;
	cout << "                      4. ����                        " << endl;
	cout << endl;
	cout << "                  ����� �Է��Ͻðڽ��ϱ�? ";
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

void clientInterface(ClientManagement& cm) // �� ���� �������̽�
{
	int num, id; char one;
	cout << "1��: �Է�" << " | " << "2��: ��ȸ " << " | "
		<< "3��: ID �˻�" << " | " << "4��: �̸� �˻�" << " | " << "0��: ���" << endl;
	Primary::switchInput(num, one);

	switch (num) {
	case 1:
		cm.cmInput();  // �Է�
		break;
	case 2: {
		cm.cmOutput();  // ��ȸ
		cout << endl << "    �� ������ ����/���� �Ͻðڽ��ϱ�?    " << endl;
		cout << "1: ����   |   2: ����   |   0: ���   |" << endl;
		Primary::switchInput(num, one);

		if (num == 1) {
			cout << "�����Ϸ��� �� ID�� �Է��ϼ���. "; cin >> id;
			system("cls");
			cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
			cm.cmRevise(id);  // ����
		}
		else if (num == 2) {
			cout << "�����Ϸ��� �� ID�� �Է��ϼ���. "; cin >> id;
			cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
			cm.deleteClient(id);  // ����
		}
		system("cls");
		break;
	}
	case 3:
		cout << "�˻��� ID�� �Է��ϼ���. "; cin >> id;
		cm.cmSearchID(id);	// ID�� �˻�
		break;
	case 4:
		cm.cmSearchName();	// �̸����� �˻�
		break;
	}
}

void productInterface(ProductManagement& pm)	// ��ǰ ���� �������̽�
{
	int num, id; char one;
	cout << "1��: �Է�" << " | " << "2��: ��ȸ " << " | "
		<< "3��: ID �˻�" << " | " << "4��: ǰ�� �˻�" << " | " << "0��: ���" << endl;
	Primary::switchInput(num, one);

	switch (num) {
	case 1:
		pm.pdInput();	// �Է�
		break;
	case 2: {
		pm.pdOutput();	// ��ȸ
		cout << endl << "    ��ǰ ������ ����/���� �Ͻðڽ��ϱ�?    " << endl;
		cout << "1: ����   |   2: ����   |   0: ���   |" << endl;
		Primary::switchInput(num, one);

		if (num == 1) {
			cout << "�����Ϸ��� ��ǰ ID�� �Է��ϼ���. "; cin >> id;
			system("cls");
			cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
			pm.pdRevise(id);	// ����
		}
		else if (num == 2) {
			cout << "�����Ϸ��� ��ǰ ID�� �Է��ϼ���. "; cin >> id;
			cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
			pm.deleteProduct(id);	// ����
		}
		system("cls");
		break;
	}
	case 3:
		cout << "�˻��� ID�� �Է��ϼ���. "; cin >> id;
		pm.pdSearchID(id);		// ID�� �˻�
		break;
	case 4:
		pm.pdSearchCategory();		// ǰ������ �˻�
		break;
	}
}

void purchaseInterface(PurchaseManagement& mm, ClientManagement& cm, ProductManagement& pm)
// ���Ÿ�� �������̽�
{
	int num, id; char one;
	cout << "1��: �Է�" << " | " << "2��: ��ȸ " << " | "
		<< "3��: �� �˻�" << " | " << "4��: ǰ�� �˻�" << " | " << "0��: ���" << endl;
	Primary::switchInput(num, one);

	switch (num) {
	case 1:
		mm.mmInput();	// �Է�
		break;
	case 2: {
		mm.mmOutput(cm, pm);	// ��ȸ
		cout << endl << "    �ֹ� ������ ����/���� �Ͻðڽ��ϱ�?    " << endl;
		cout << "1: ����   |   2: ����   |   0: ���   |" << endl;
		Primary::switchInput(num, one);

		if (num == 1) {
			cout << "�����Ϸ��� ���� ��� ID�� �Է��ϼ���. "; cin >> id;
			system("cls");
			cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
			mm.mmRevise(id);	// ����
		}
		else if (num == 2) {
			cout << "�����Ϸ��� ���� ����� ID�� �Է��ϼ���. "; cin >> id;
			cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
			mm.deleteReceipt(id);	// ����
		}
		system("cls");
		break;
	}
	case 3:
		mm.mmSearchCID();	// �� ������ �˻�
		break;
	case 4:
		mm.mmSearchPID();	// ��ǰ ������ �˻�
		break;
	}
}

// 	while (1) { one = _getch(); if (one >= '0' && one <= '9') break; printf("\b "); }
//num = one - '0';
