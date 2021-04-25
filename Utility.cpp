#include "Utility.h"

//slipt string with delimiter
//parse string into intems based on a delimeter
//Ex:if the string is "abc:xyz" and delimeter is ":",
//	then after parsing, we'll have 2 items "abc" and "xyz" (both stored in a vector)
//NOTE: all items in the vector must be STRING
void Utility::parse(std::string str, char delim, std::vector<std::string>& vec) {
	
	std::stringstream ss(str);
	std::string value; //each item

	//First clear the vector to make sure we will add item to a completely empty vector
	//instead of a vector holding other existing items
	vec.clear();
	
	//For each item, push it to the vector
	while (getline(ss, value, delim)) {
		vec.push_back(value);
	}
}
//split string with delimiter but different type
//the body is different so I dont use template
//Parse string into items based on a delimeter
//All items in the vector must be INTEGER
void Utility::parse(std::string str, char delim, std::vector<int>& vec) {
	//clear vector
	vec.clear();

	std::stringstream ss(str);
	std::string value; //each item

	//for each item, push it to the vector
	while (getline(ss, value, delim)) {
		if (!value.empty()) {
			//convert value to integer
			try {
				//before push the item into vector, convert to integer
				//I use try-catch here to avoid case where string is not a number
				//Ex: We can convert "123" to integer, but cannot convert "12c" to integer
				//in this case, try-catch will help our program from crashing
				vec.push_back(stoi(value));
			}
			catch (...) {

			}
		}
	}
}

//Parse string into items based on a delimeter
//Note: All items in the vector must be Double
void Utility::parse(std::string str, char delim, std::vector<double>& vec) {
	vec.clear();
	std::stringstream ss(str);
	std::string value;
	while (getline(ss, value, delim)) {
		if (!value.empty()) {
			try {
				vec.push_back(stod(value));
			}
			catch (...) {

			}
		}
	}
}

//Trim leading and trailing space out of the text
//Ex: "   abc  " after triming becomes "abc"
std::string Utility::trim(const std::string& input) {
	//use iterator
	auto wsfront = find_if_not(input.begin(), input.end(), [](int c) {return isspace(c); });
	auto wsback = find_if_not(input.rbegin(), input.rend(), [](int c) {return isspace(c); }).base();
	return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

//check if a string is in form of an integer
bool Utility::isInteger(const std::string& input) {
	for (int i = 0; i < input.size(); ++i) {
		//if not digit, but letter (a,b,c,...) => the string is NOT in form of an integer
		if (isdigit(input[i]) == 0) {
			return false;
		}
	}
	return true;
}
//check the leap year
bool Utility::isLeapYear(int year) {
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
		return true;
	}
	else
		return false;
}

void Utility::mainMenu() {
	std::cout << "\n********************MAIN MENU********************\n"
		<< "[1]\t: Go To Employee Information Section\n"
		<< "[2]\t: Go to Payroll Section\n"
		<< "[0]\t: Go Back to Login Section\n";
}

void Utility::employeeManagementMenu() {
	std::cout << "\n********************EMPLOYEE MANAGEMENT********************\n"
		<< "[1]\t: Print All Employee's Information\n"
		<< "[2]\t: Add New Employee\n"
		<< "[3]\t: Remove An Employee\n"
		<< "[4]\t: Update Information of Employee by ID\n"
		<< "[0]\t: Go Back\n";
}

void Utility::updateEmployeeMenu() {
	std::cout << "\n********************MENU********************\n"
		<< "[1]\t: Update Employee Name\n"
		<< "[2]\t: Update Employee SSN\n"
		<< "[3]\t: Update Employee Date of Birth\n"
		<< "[0]\t: Go Back\n";
}

void Utility::payRollMenu() {
	std::cout << "\n********************PAYROLL MENU********************\n"
		<< "[1]\t: Update Payroll for Employee\n"
		<< "[2]\t: Calculate Salary and Profit\n"
		<< "[0]\t: Go Back\n";
}

