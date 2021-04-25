//Implementation file of NailTechnician.h
#include "NailTechnician.h"
#include "Utility.h"

NailTechnician::NailTechnician(const std::string& id, const std::string& name, const std::string& ssn, const Date& date)
	: Employee(id, name, ssn, date, EMPLOYEE_TYPE::NAIL_TECHNICIAN) {
	setTip(0);
}

double NailTechnician::getTips() const {
	return tip;
}

//overrided function
//get employee information
void NailTechnician::getEmployeeInfo() {
	std::cout << "------------------------\n" << "Enter the information of the Nail Technician: \n";
	//First, get the basic information
	Employee::getEmployeeInfo();
}


void NailTechnician::inputPayRollInfo(bool isReset) {
	std::string totalMoneyTemp;
	std::string tipTemp;

	if (isReset) {
		setSalary(0);
		setTip(0);
	}

	std::cout << "Enter the money Each Receipt (split by +), No Space between Words: ";
	std::cin.clear();
	std::cin.ignore(100,'\n');

	getline(std::cin, totalMoneyTemp);
	std::vector <double> listMoney;
	Utility::parse(totalMoneyTemp, '+', listMoney);

	//calculate total salary for a nail tachnician per date
	for (double i : listMoney) {
		this->salary += i;
	}

	std::cout << "Enter Tips Each Receipt (slipt by +): ";
	getline(std::cin, tipTemp);
	std::vector<double> listTip;
	Utility::parse(tipTemp, '+', listTip);

	//calculate total tip for a nail technician per date
	for (double i : listTip) {
		this->tip += i;
	}
}

//Overrided function
//Convert employee information to string
std::string NailTechnician::convertInfoToString() const {
	//first, convert basic info
	std::string baseStr = Employee::convertInfoToString();
	
	return baseStr;
}

//Overrided function 
//Calculate payroll for a nail tech
double NailTechnician::calculatePayRoll() {
	return 0.6 * salary + tip;
}