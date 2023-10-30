#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "BookType.h"
#include "LoginManager.h"

#define BOOK_DB_PATH "C:\\Users\\mrkim\\���� ȭ��\\OOP_Library\\BOOK_DATA.txt"
#define USER_DB_PATH "C:\\Users\\mrkim\\���� ȭ��\\OOP_Library\\USER_DATA.txt"

using namespace std;

class BookManager {
	
public:
	BookManager() {	}
	/* ini �� �ݵ�� �빮�� ���ĺ��̿��� ��. */
	void add_book(char ini = 'A', string title="none", string writer="none") {
		std::ifstream infile(BOOK_DB_PATH);
		std::vector<std::string> lines;
		std::string line;

		// ������ ������ ���Ϳ� ����
		for (int i = 0; std::getline(infile, line);i++) {
			if (line[0] >= ini) {
				// ini�� �����ϴ� ������ ã�� ���
				lines.push_back((title + " " + writer));
				lines.push_back(line);
				break;
			}
			// ini �� �����Ĵ� å �̸��� �߰����� ���ߴٸ�
			lines.push_back(line);
		}
		// ������ ������� �����Ѵ�.
		while (getline(infile, line)) lines.push_back(line);

		// ����, ��� å�� ���񺸴� ���� �����̶��
		if(ini > line[0]) lines.push_back((title + " " + writer));

		infile.close();

		for (string& s : lines) {
			cout << s << endl;
		}
		// ���Ͽ� ������ ������ ����
		std::ofstream outfile(BOOK_DB_PATH);
		for (const auto& updatedLine : lines) {
			outfile << updatedLine << std::endl;
		}
		outfile.close();

		std::cout << "���� �߰� �Ϸ�" << std::endl;
	}
	void remove_book_i(int i) {
		ifstream infile(BOOK_DB_PATH);
		vector<std::string> lines; // ���� ������ ������ ����
		string line;

		// ������ ������ ���Ϳ� ���� (i��° �� ����)
		int lineNumber = 1;
		while (std::getline(infile, line)) {
			if (lineNumber != i) {
				lines.push_back(line);
			}
			lineNumber++;
		}

		infile.close(); // �Է� ���� ��Ʈ���� ����

		// ������ ���� ���� ��� ������ ������ ���Ͽ� �� (���� ���� ���� ���)
		ofstream outfile(BOOK_DB_PATH);
		for (const auto& updatedLine : lines) {
			outfile << updatedLine << std::endl;
		}

		std::cout << "���� �Ϸ�" << std::endl;
		outfile.close(); // ��� ���� ��Ʈ���� ����
	}
	
	vector<string> read_books_startwith(string initial = " ") {
		ifstream infile (BOOK_DB_PATH);
		string buff;
		vector<string> item;
		if (initial == "all") {
			while (getline(infile, buff)) {
				item.push_back(buff);
			}
		}
		else {
			while (getline(infile, buff)) {
				if (buff.at(0) == initial.at(0)) item.push_back(buff);
			}
		}
		
		infile.close();
		if (item.empty()) cout << "�˻��� å�� �����ϴ�" << endl;
		else for (string& s : item) cout<<s<<endl;
		return item;
	}
	void read_all_books() {
		ifstream infile(BOOK_DB_PATH);
		string line;
		while (getline(infile, line)) {
			cout<<line<<endl;
		}

		if (infile.eof()) cout << "�˻��� å�� �����ϴ�" << endl;
		infile.close();
	}
};



int main(void) {
	LoginManager* lm = new LoginManager(USER_DB_PATH);
	BookManager* bm = new BookManager();
	if (!bm)return 1;
	cout << "���� ���� ����!" << endl;

	int flag = 0;
	do {
		cout << "���� ���� �ý���: \n���� �б�[1]\n���� ����[2]\n���� �ʱ�ȭ�ϱ�[3]\n�α����ϱ�[4]\nȸ�������ϱ�[5]\n�����ϱ�[other]\n:";
		cin >> flag;
		cin.ignore();

		switch (flag)
		{
		case 1: {
			cout << "���ĺ� �ϳ� �Է� >>";
			string c;
			cin >> c;
			cin.ignore();
			bm->read_books_startwith(c);
			break;
		}
		case 2: {
			string title, writer;
			cout << "å �̸���, å ���� �Է� >>";
			cin >> title >> writer;
			cin.ignore();
			bm->add_book(title[0], title, writer);
			break;
		}
		case 3: {
			int i;
			cout << "������ å ��ȣ�� �Է��ϼ���>>";
			cin >> i;
			cin.ignore();
			bm->remove_book_i(i);
			break;
		}
		case 4: {
			string id, pw;
			cin >> id >> pw;
			cin.ignore();
			lm->login(id, pw);
			break;
		}
		case 5: {
			string id, pw, name, level;
			cout << "���̵�, ��й�ȣ, �̸�, ������ �Է��ϼ���! >>";
			cin >> id >> pw >> name >> level;
			cin.ignore();
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
