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
	std::istream* uin;
	std::ostream* uout;
public:
	LoginManager(const char* UserDataLink) {

		uin = new std::ifstream(UserDataLink, std::ios::in);
		uout = new std::ofstream(UserDataLink, std::ios::app);
			std::string s;
		while (uin->eof()) {
			*uin >> s;
			std::cout << s;
			uin->seekg(sizeof(std::string), std::ios::cur);
		}
	}
	void skip_n(int n) {
		std::string s;
		for (int i = 0; i < n && *uin; i++) *uin >> s;
	}
	bool login(std::string& id, std::string& pw) {
    uin->seekg(0, std::ios::beg);
    std::cout << "파일 오픈 성공!";
    std::string i, p;
    bool found = false;
    
    while (*uin >> i >> p) {
        if (i == id && p == pw) {
            std::string name, level;
            *uin >> name >> level;
            std::cout << "id : " << i << " pw : " << p << " " << name << " " << level << std::endl;
            found = true;
            break;
        } else {
            // 실패한 로그인 정보를 건너뛰기
            std::string dummy;
            std::getline(*uin, dummy);
        }
    }

    return found;
}

	/* 유저 데이터 파일에 씀 */
	bool sign_up(std::string id, std::string pw, std::string name, std::string level) {
		id = id.substr(0, 10);
		int pos;
		while ((pos = id.find('k')) != std::string::npos)
			id.replace(pos, 1, "u");
		std::cout << "id 는 " << id << "가 되었습니다." << std::endl;
		*uout << id << ' ' << pw << ' ' << name << ' ' << level << '\n';
		uout->flush();
		return true;
	}
};