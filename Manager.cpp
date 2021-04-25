//Implementation file of Manager.h

#include "Manager.h"
#include "Utility.h"

//constructor
Manager::Manager(const std::string& id, const std::string& name, const std::string& ssn,
	const Date& date, const int& salaryPerHour)
	: Employee(id, name, ssn, date, EMPLOYEE_TYPE::MANAGER) {

	this->salary_per_hour = salaryPerHour;
	this->hour = 0;
}

//Overrided function
//Get all information of an employee
void Manager::getEmployeeInfo() {
	std::cout << "Enter Manager Information as Following ...\n";

	//First, get basic info
	Employee::getEmployeeInfo();
	//Then, get special information for manager
	setSalaryPerHour();
}

//Set salary per hour for manager
void Manager::setSalaryPerHour() {
	//input the salary per hour
	std::cout << "Salary per hour: ";
	std::string salaryPerHour;

	while (true) {
		std::cin >> salaryPerHour;

		//make sure there is no leading and trailing space arround the input
		salaryPerHour = Utility::trim(salaryPerHour);
		
		//If salary is invalid format(ex: not in form of a number), ask to enter again
		if (!Utility::isInteger(salaryPerHour)) {
			std::cout << "\t[ERROR] Invalid Input!\nEnter Again: ";
			continue;
		}
		else
			break;
	}
	try {
		//convert string to integer
		this->salary_per_hour = stoi(salaryPerHour);
	}
	catch (std::exception&) {
		std::cout << "\t[ERROR] Invalid Input! Cannot Convert String to Int\n";
	}
}

//Overrided function
//Convert employee information to string
std::string Manager::convertInfoToString() const {
	//First, convert basic info
	std::string baseStr = Employee::convertInfoToString();

	//Then, convert special info for manager
	baseStr += "|" + std::to_string(this->salary_per_hour);

	return baseStr;
}

//Overrided function
//calculate Payroll
double Manager::calculatePayRoll() {
	//Because hour and salary_per_hour are both int, but the function return double
	//we have to cast them to double 
	return static_cast<double>(hour) * static_cast<double>(this->salary_per_hour);
}

//Overrided function
//Get Payroll Information
void Manager::inputPayRollInfo(bool isReset) {
	std::string hour;
	std::cout << "Enter hour/day: ";
	while (true) {
		std::cin >> hour;

		//make sure there is no leading and trailing space around the input
		hour = Utility::trim(hour);

		//If salary is invalid format(not a number), ask to enter again
		if (!Utility::isInteger(hour)) {
			std::cout << "\t[ERROR] Invalid Input! Enter Again: ";
			continue;
		}
		else {
			break;
		}
	}

	try {
		//Convert string to integer
		this->hour = stoi(hour);
	}
	catch (std::exception&) {
		std::cout << "\t[ERROR] Invalid Input! Cannot Convert String to Int\n";
	}
}