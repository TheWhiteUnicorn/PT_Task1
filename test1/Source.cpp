#include <iostream>
#include "CFileProcessor.h"

#define IF_INVITATION "������� ��� ����� �����: "
#define OF_INVITATION "������� ��� ����� ������: "

using namespace std;

int main() {
	setlocale(0, "Russian");
	string strIFName, strOFName;
	CFileProcessor fpProcessor;
	cout << IF_INVITATION;
	cin >> strIFName;
	cout << OF_INVITATION;
	cin >> strOFName;

	try {
		fpProcessor.Process(strIFName, strOFName);
	}
	catch (exception* e) {
		cout << e->what() << endl;
		delete e;
	}
	system("pause");
	return 0;
}