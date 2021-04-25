/*
* Author: Nghia Truong - U#: 97367726
* Flex Project
* Topic:
*	HR management for Nails Spa Salons 
*/

#include "LoginManagement.h"
#include "Utility.h"

using namespace std;

void loginMenu();

int main() {
	cout << "WELCOME TO NGHIA TRUONG'S SPA!!! \n\n";
	int choice = 0;
	//create object
	LoginManagement loginManager;

	while (true) {
		loginMenu();
		cin >> choice;
		switch (choice)
		{
		case 1: {
			//login
			cout << "\n===============LOGIN SECTION===============\n";
			loginManager.login();
			break;
		}
		case 2: {
			//change password
			cout << "\n===============PASSWORD CHANGE SECTION===============\n";
			loginManager.passwordChange();
			break;
		}
		case 0:
			cout << "\nBYE!! Thank You For Using NGHIA TRUONG's Service" << endl;
			return 0;
		}
	}
		
	return 0;
}

void loginMenu() {
	std::cout << "MENU:\n"
		<< "[1]\t: Login.\n"
		<< "[2]\t: Change Password.\n"
		<< "[0]\t: Exit\n"
		<< "Your Choice: ";
}