#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "BookType.h"
#include "LoginManager.h"

// "C:\\Users\\mrkim\\���� ȭ��\\OOP_Library\\BOOK_DATA.txt"
using namespace std;

class BookManager {
	const char* BOOK_DATA_LINK;
	const char* BOOK_DATA_LINK_BU;
	ifstream* bin;
	ifstream* bout;
	int n;
public:
	BookManager(const char* src1, const char* src2) {
		BOOK_DATA_LINK = src1;
		BOOK_DATA_LINK_BU = src2;
		bin = new ifstream(src1, ios::in);
		
		cout << n << "���� �ܾ �ֽ��ϴ�." << endl;
	}
	void write(char* s, int i = 0) {
		(*data).seekp(i * sizeof(string), ios::beg);
		(*data) << s << endl;
		(*data).flush();
		read_all();
	}
	void read_all() {
		int temp = data->tellg();
		ifstream i(BOOK_DATA_LINK);
		string buffer;
		while (i) {
			i >> buffer;
			if (i.eof()) break;
			cout << buffer << endl;;
		}
		cout << endl;
		i.close();
		(*data).seekg(temp, ios::beg);
	}
	void clear() {
		ifstream from(BOOK_DATA_LINK);
		ofstream to(BOOK_DATA_LINK_BU);
		
		string line;
		while (getline(from, line)) {
			to << line << endl;
		}

		from.close();
		to.flush();
		to.close();
	}
	bool is_open() {
		return data->is_open();
	}
	bool is_eof() {
		return data->eof();
	}
};



int main(void) {
	LoginManager* lm = new LoginManager("C:\\Users\\mrkim\\���� ȭ��\\OOP_Library\\USER_DATA.txt");
	BookManager* bm = new BookManager("C:\\Users\\mrkim\\���� ȭ��\\OOP_Library\\BOOK_DATA.txt", "C:\\Users\\mrkim\\���� ȭ��\\OOP_Library\\BOOK_DATA_BACKUP.txt");
	if (!bm->is_open())return 1;
	cout << "���� ���� ����!" << endl;

	int flag = 0;
	do {
		cout << "���� ���� �ý���: \n���� �б�[1]\n���� ����[2]\n���� �ʱ�ȭ�ϱ�[3]\n�α����ϱ�[4]\nȸ�������ϱ�[5]\n�����ϱ�[other]\n:";
		cin >> flag;
		cin.ignore();

		switch (flag)
		{
		case 1: {
			bm->read_all();
			break;
		}
		case 2: {
			char buffer[40];
			cout << "�Է��� ������ ������. : ";
			cin.getline(buffer, 39, '\n');
			cout << buffer << "�Էµ�." << endl;
			bm->write(buffer, 3);
			break;
		}
		case 3: {
			bm->clear();
			break;
		}
		case 4: {
			string id, pw;
			cin >> id >> pw;
			lm->login(id, pw);
			break;
		}
		case 5: {
			string id, pw, name, level;
			cout << "���̵�, ��й�ȣ, �̸�, ������ �Է��ϼ���! >>";
			cin >> id >> pw >> name >> level;
			lm->sign_up(id, pw, name, level);
			break;
		}
		default: {
			flag = 0;
			break;
		}
		}
	} while (flag);

	

	delete bm;
	delete lm;
	return 0;
}