#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
class User{
	std::string name;
	std::string id;
	std::string pw;
	std::string level;
	static int user_count;
public:
	User(std::string name = "anonymous", std::string id = "none", std::string pw = "none", std::string level="none") : name(name), id(id), pw(pw), level(level) {
		user_count++;
	}
	~User() {
		user_count--;
	}
	void set_name(std::string& s) { name = s; }
	void set_id(std::string& s) { id = s; }
	void set_pw(std::string& s) { pw = s; }
	void set_level(std::string& s) { level = s; }
	std::string get_name() { return name; }
	std::string get_id() { return id; }
	std::string get_pw() { return pw; }
	std::string get_level() { return level; }
	int static get_count_of_users() { return user_count; }
};
int User::user_count = 0;
class LoginManager {
	std::string userdb_path;
public:
	LoginManager(const char* UserDataLink) {
		userdb_path = UserDataLink;
	}
	bool login(std::string& id, std::string& pw) {
		bool found = false;
		std::ifstream ifile(userdb_path);
		if (!ifile) return found;
		std::cout << "파일 오픈 성공!";
		std::string i;
		std::string p;
		std::string dummy;

		while (!ifile.eof()) {
			ifile >> i >> p;
			if (i == id && p == pw) {
				std::string name, level;
				ifile >> name >> level;
				std::cout << "id : " << i << " pw : " << p << " name : " << name << " lavel : " << level << std::endl;
				found = true;
				return found;
			}
			else {
				// 실패한 로그인 정보를 건너뛰기
				std::getline(ifile, dummy);
			}
		}
		std::cout << "종료됨." << std::endl;
		ifile.close();
		if(found)
		return found;
	}

	/* 유저 데이터 파일에 씀 */
	bool sign_up(std::string id, std::string pw, std::string name, std::string level) {
		std::ofstream ofile(userdb_path, std::ios::app);
		id = id.substr(0, 10);
		int pos;
		std::cout << "id 는 " << id << "가 되었습니다." << std::endl;
		ofile << id << ' ' << pw << ' ' << name << ' ' << level << '\n';
		ofile.close();
		return true;
	}
};