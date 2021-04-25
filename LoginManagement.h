#ifndef LOGINMANAGEMENT_H
#define LOGINMANAGEMENT_H

#include <iostream>
#include <string>
#include <fstream>

class LoginManagement {
private:
	std::string user_name;
	std::string user_name_temp;
	std::string password;	
	std::string password_temp;
	std::string file_name;
public:	
	//constructor
	LoginManagement();
	void setUserName(std::string user_name);
	void setPassword(std::string password);
	std::string getUserName() const;
	std::string getPassword() const;

	void loadFileLogin();
	void passwordChange();
	void login();
};

#endif // !LOGINMANAGEMENT_H
