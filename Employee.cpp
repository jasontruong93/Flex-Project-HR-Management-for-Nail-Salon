//Implementation file of Employee.h
#include "Employee.h"
#include "SpaManagement.h"
#include "Utility.h"

//constructor
Employee::Employee(const std::string& id, const std::string& name, const std::string& ssn, const Date& date, const EMPLOYEE_TYPE& type)
	:id(id), name(name), dateOfBirth(date), SSN(ssn), type(type) {
	setSalary(0);
	setTip(0);
}

//getters and setters
std::string Employee::getID() const {
	return id;
}
std::string Employee::getSSN() const {
	return SSN;
}
std::string Employee::getName() const {
	return name;
}
double Employee::getSalary() const {
	return salary;
}
void Employee::setSalary(double salary) {
	this->salary = salary;
}
void Employee::setTip(double tip) {
	this->tip = tip;
}
Date Employee::getDateOfBirth() const {
	return dateOfBirth;
}

//get all information of an employee
void Employee::getEmployeeInfo() {
	std::string idTemp;
	SpaManagement spa;

	//check id existed or not
	while (true) {
		idTemp = SpaManagement::inputEmployeeId();
		if (spa.isContainEmployee(idTemp)) {
			std::cout << "The ID Has Been Used, Try Again!\n";
			continue;
		}
		else
			break;
	}
	id = idTemp;
	//name
	inputName();
	//address
	inputSSN();
	//date of birth
	inputDateOfBirth();
}


std::string Employee::convertEmployeeTypeToString() const {
	if (this->type == EMPLOYEE_TYPE::MANAGER) {
		return "Manager";
	}
	else if (this->type == EMPLOYEE_TYPE::NAIL_TECHNICIAN) {
		return "Nail Technician";
	}
	else {
		return "Unkown";
	}
}


//Ask user input employee name
void Employee::inputName() {
	std::string name;
	std::cout << "Enter Name (First Last): ";
	//prompt user to input name

	std::cin.clear();
	std::cin.ignore(1000, '\n');
	getline(std::cin, name);

	//trim leading and trailing space out of the text
	name = Utility::trim(name);

	//store employee name as member varibale
	this->name = name;
}

//Ask user to input employee address
void Employee::inputSSN() {
	std::cout << "Enter SSN (xxx-xx-xxxx): ";
	std::string sSN;

	std::cin >> sSN;
	std::cin.clear();
	std::cin.ignore(1000, '\n');	

	//store employee address as member variable
	this->SSN = sSN;
}

//Ask user to input employee birthday
void Employee::inputDateOfBirth() {
	std::string dateStr;	
	
	while (true) {

		std::cout << "Enter Date of Birth (mm/dd/yyyy): ";
		std::cin >> dateStr;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		Date date(dateStr);

		//check valid date input
		//for age
		if (date.get_year() > 2005 || date.get_year() < 1956) {
			std::cout << "NOT the AGE To Work!!! Try Again\n";
			continue;
		}
		if (date.get_month() > 12 || date.get_month() <= 0) {			
			std::cout << "Month Has to Be LESS Than 13 and GREATER Than 0!!! Try Again\n";
			continue;
		}
		if (date.get_day() > 31 || date.get_day() <= 0) {
			std::cout << "Invalid Day Input!!! Try Again\n";
			continue;			
		}
		//these months only have 30 days
		else if (date.get_day() > 30 && (date.get_month() == 4 
			|| date.get_month() == 6 || date.get_month() == 9 || date.get_month() == 11)) {
			std::cout << "Invalid Day Input (The Month Only Have 30 Days)!!! Try Again\n";
				continue;
		}
		//leap year
		else if (date.get_day() > 28 && date.get_month() == 2) {

			if (date.get_day() == 29 && Utility::isLeapYear(date.get_year()) == false){
				std::cout << "Invalid Day Input (NOT LEAp Year)!!! Try Again\n";
				continue;
			}
			if (date.get_day() >= 30) {
				std::cout << "Invalid Day Input (February Days Less Than 30)!!! Try Again\n";
				continue;
			}
		}

		dateOfBirth = date;
		break;
	}	
}

std::string Employee::convertInfoToString() const {
	std::string str = id + "|" + name + "|" + SSN + "|" + convertDateToString(dateOfBirth) + "|" + std::to_string(static_cast<int>(this->type));
	return str;
}

//overload <<
std::ostream& operator << (std::ostream& out, const Employee& employee) {
	out << std::left << std::setw(WIDTH_COLUMN_ID) << employee.getID()
		<< std::setw(WIDTH_COLUMN_NAME) << employee.getName()
		<< std::setw(WIDTH_COLUMN_SSN) << employee.getSSN()
		<< std::setw(WIDTH_COLUMN_TYPE) << employee.convertEmployeeTypeToString()
		<< employee.getDateOfBirth();
		
	out << std::endl;
	return out;
}

double Employee::getTips() const {
	return 0;
}
