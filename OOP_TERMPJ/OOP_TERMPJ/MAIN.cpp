#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "BookType.h"
#include "LoginManager.h"

#define BOOK_DB_PATH "C:\\Users\\mrkim\\바탕 화면\\OOP_Library\\BOOK_DATA.txt"
#define USER_DB_PATH "C:\\Users\\mrkim\\바탕 화면\\OOP_Library\\USER_DATA.txt"

using namespace std;

class BookManager {
	
public:
	BookManager() {	}
	/* ini 는 반드시 대문자 알파벳이여야 함. */
	void add_book(char ini = 'A', string title="none", string writer="none") {
		std::ifstream infile(BOOK_DB_PATH);
		std::vector<std::string> lines;
		std::string line;

		// 파일의 내용을 벡터에 저장
		for (int i = 0; std::getline(infile, line);i++) {
			if (line[0] >= ini) {
				// ini로 시작하는 섹션을 찾은 경우
				lines.push_back((title + " " + writer));
				lines.push_back(line);
				break;
			}
			// ini 로 시작파는 책 이름을 발견하지 못했다면
			lines.push_back(line);
		}
		// 나머지 내용들을 복사한다.
		while (getline(infile, line)) lines.push_back(line);

		// 만약, 모든 책의 제목보다 높은 제목이라면
		if(ini > line[0]) lines.push_back((title + " " + writer));

		infile.close();

		for (string& s : lines) {
			cout << s << endl;
		}
		// 파일에 수정된 내용을 쓰기
		std::ofstream outfile(BOOK_DB_PATH);
		for (const auto& updatedLine : lines) {
			outfile << updatedLine << std::endl;
		}
		outfile.close();

		std::cout << "도서 추가 완료" << std::endl;
	}
	void remove_book_i(int i) {
		ifstream infile(BOOK_DB_PATH);
		vector<std::string> lines; // 파일 내용을 저장할 벡터
		string line;

		// 파일의 내용을 벡터에 저장 (i번째 줄 제외)
		int lineNumber = 1;
		while (std::getline(infile, line)) {
			if (lineNumber != i) {
				lines.push_back(line);
			}
			lineNumber++;
		}

		infile.close(); // 입력 파일 스트림을 닫음

		// 파일을 쓰기 모드로 열어서 벡터의 내용을 파일에 씀 (기존 파일 내용 덮어씀)
		ofstream outfile(BOOK_DB_PATH);
		for (const auto& updatedLine : lines) {
			outfile << updatedLine << std::endl;
		}

		std::cout << "제거 완료" << std::endl;
		outfile.close(); // 출력 파일 스트림을 닫음
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
		if (item.empty()) cout << "검색된 책이 없습니당" << endl;
		else for (string& s : item) cout<<s<<endl;
		return item;
	}
	void read_all_books() {
		ifstream infile(BOOK_DB_PATH);
		string line;
		while (getline(infile, line)) {
			cout<<line<<endl;
		}

		if (infile.eof()) cout << "검색된 책이 없습니당" << endl;
		infile.close();
	}
};



int main(void) {
	LoginManager* lm = new LoginManager(USER_DB_PATH);
	BookManager* bm = new BookManager();
	if (!bm)return 1;
	cout << "파일 오픈 성공!" << endl;

	int flag = 0;
	do {
		cout << "파일 관리 시스템: \n파일 읽기[1]\n파일 쓰기[2]\n파일 초기화하기[3]\n로그인하기[4]\n회원가입하기[5]\n종료하기[other]\n:";
		cin >> flag;
		cin.ignore();

		switch (flag)
		{
		case 1: {
			cout << "알파벳 하나 입력 >>";
			string c;
			cin >> c;
			cin.ignore();
			bm->read_books_startwith(c);
			break;
		}
		case 2: {
			string title, writer;
			cout << "책 이름과, 책 저자 입력 >>";
			cin >> title >> writer;
			cin.ignore();
			bm->add_book(title[0], title, writer);
			break;
		}
		case 3: {
			int i;
			cout << "삭제할 책 번호를 입력하세요>>";
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
			cout << "아이디, 비밀번호, 이름, 직급을 입력하세요! >>";
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
