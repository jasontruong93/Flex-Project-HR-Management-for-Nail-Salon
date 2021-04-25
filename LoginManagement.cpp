//Implementation file of LoginManagement.h

#include "LoginManagement.h"
#include "BusinessIO.h"
#include "SpaManagement.h"
#include "Utility.h"

//constructor
LoginManagement::LoginManagement() {
	file_name = "login.txt";
	setUserName("admin");

	loadFileLogin();	
}

//set the username
void LoginManagement::setUserName(std::string user_name) {
	this->user_name = user_name;
}
//set password
void LoginManagement::setPassword(std::string password) {
	this->password = password;
}
//get username
std::string LoginManagement::getUserName() const {
	return user_name;
}
//get password
std::string LoginManagement::getPassword() const {
	return password;
}
//change the password
void LoginManagement::passwordChange() {

	std::cout << "Enter Current Password: ";

	std::cin >> password_temp;

	if (password_temp == getPassword()) {
		std::string newPassword1, newPassword2;

		do {
			std::cout << "Enter New Password: ";
			std::cin >> newPassword1;
			//check the newPassword temp
			if (newPassword1.size() <= 0) {
				std::cout << "The Password Must NOT Empty! Try again!\n\n";
				continue;
			}
			std::cout << "Enter New Password Again: ";
			std::cin >> newPassword2;
			//check for matching
			if (newPassword1 == newPassword2) {
				//set the new password
				this->password = newPassword1;
				break;
			}
			else {
				std::cout << "The Password Does NOT Match! Try Again!\n\n";
			}
		} while (true);

		//save to vector then file
		std::vector<std::string> records;
		records.push_back(password);
		BusinessIO fileIO(file_name);
		std::string newRecord = "password|" + password;
		fileIO.updateRecord("password", newRecord);
		std::cout << "Password Changed Successfully!\n\n";
	}
	else {
		std::cout << "Incorrect Password!!!\n\n";
		passwordChange();
	}
}

//funtcion to login
void LoginManagement::login() {
	std::cout << "Enter Username: ";
	std::cin >> user_name_temp;
	std::cin.clear();
	std::cin.ignore(1000, '\n');

	if (user_name_temp == getUserName()) {

		std::cout << "Enter Password: ";
		std::cin >> password_temp;
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		if (password_temp == getPassword()) {
			std::cout << "Login Successfully!\n";
			//create object of SpaManagement
			SpaManagement management;
			management.displayMainMenu();
		}
		else {
			std::cout << "Incorrect Password! Try Again!\n\n";
			login();
		}

	}
	else {
		std::cout << "Incorrect UserName! Try Again!\n\n";
		
		login();
	}
}

void LoginManagement::loadFileLogin() {
	//read login.txt to get the password
	//the data will be stored as global variable which are used across the program
	BusinessIO fileIO(file_name);

	//create login.txt and add default data if the file doesnot exist
	if (!fileIO.isOpen(file_name)) {
		std::cout << "THE FIRST LOGIN! Creating the Default Account!\n"
			<< "Hint:\nDefault ID: admin\nDefault Password: 123\n\n";
		std::string defaultPassword = "password|123";
		std::vector<std::string> newRecord;
		newRecord.push_back(defaultPassword);
		fileIO.addRecord(newRecord);
	}

	//first, read password from the account file
	std::vector<std::string> allRecords;
	fileIO.readAll(allRecords);

	for (std::string line : allRecords) {
		std::vector<std::string> listInfo;
		//separate the string and store in the vector by parse function
		Utility::parse(line, '|', listInfo);
		//if found the password
		if (listInfo.size() >= 2) {
			//get value of key password
			std::string key = listInfo.at(0);
			if (key == "password") {
				//store password as member variable
				this->password = listInfo.at(1);
			}
		}
	}
}