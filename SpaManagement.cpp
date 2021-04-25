//Implementation file of SpaManagement.h
#include "SpaManagement.h"
#include "NailTechnician.h"
#include "LoginManagement.h"
#include "Manager.h"
#include "BusinessIO.h"
#include "Utility.h"

//constructor
SpaManagement::SpaManagement() {
	this->employeeFileName = "employeeInfomation.txt";
	this->payRollFileName = "payRoll.txt";
	this->totalSalary = 0;

	loadEmployeeFromFile();	
}

//load employee from the file
void SpaManagement::loadEmployeeFromFile() {
	//First, make sure the vector is empty before adding items to it
	employeeList.clear();

	//read all employee records from text file
	BusinessIO ioFile(employeeFileName);
	std::vector<std::string> allRecord;
	ioFile.readAll(allRecord);

	//For each employee, get all of its data
	for (std::string record : allRecord) {
		Employee* employee = nullptr;
		std::vector<std::string> listInfo;
		Utility::parse(record, '|', listInfo);

		std::string id = listInfo.at(0);
		std::string name = listInfo.at(1);
		std::string sSN = listInfo.at(2);
		std::string dateStr = listInfo.at(3);
		std::string type = listInfo.at(4);
		int employeeTypeInt = stoi(type);

		std::vector<int> dateInfoList;
		Date date(dateStr);

		//depend on what employee Type, create a corresponding object for polymophism
		switch (employeeTypeInt) {
		case static_cast<int>(EMPLOYEE_TYPE::NAIL_TECHNICIAN):
			employee = new NailTechnician(id, name, sSN, date);
			break;

		case static_cast<int>(EMPLOYEE_TYPE::MANAGER): {
			int salaryPerH = 0;
			salaryPerH = stoi(listInfo.at(5));
			employee = new Manager(id, name, sSN, date, salaryPerH);
			break;
		}			
		default:
			break;
		}
		//store to member variable
		if (employee != nullptr) {
			employeeList[id] = employee;
		}
	}
}

//add new employee
void SpaManagement::addNewEmployee() {

	int employeeTypeInt = 0;
	Employee* newEmployee = nullptr;
	std::cout << "Enter Employee's Information: \n";
	std::cout << "Enter Employee Type (0:Nail Technician | 1:Manager): ";
	std::cin >> employeeTypeInt;

	//depending on which employee type, we create a corresponding object of that employee type	
	switch (employeeTypeInt) {
	case static_cast<int>(EMPLOYEE_TYPE::NAIL_TECHNICIAN):
		newEmployee = new NailTechnician();
		break;
	case static_cast<int>(EMPLOYEE_TYPE::MANAGER):
		newEmployee = new Manager();
		break;
	default:
		std::cout << "\t[ERROR]Invalid Employee Type\n";
		return;
	}
	//If not default above case, get employee info and this new employee to the list of employees
	if (newEmployee != nullptr) {
		//Depend on which type of employee, corresponding overrided method will be called
		newEmployee->getEmployeeInfo();
		
		employeeList[newEmployee->getID()] = newEmployee;
	}

	//Add the new employee to file
	BusinessIO ioFile(employeeFileName);
	std::vector<std::string> newRecord;
	newRecord.push_back(newEmployee->convertInfoToString() + "\n");
	
	//Alway remove the ID before adding (avoid any problems with the ID in the file)	
	ioFile.removeRecord(newEmployee->getID());
	ioFile.addRecord(newRecord);	
}

//Update employee information
void SpaManagement::updateEmployeeInfo() {
	std::string id = SpaManagement::inputEmployeeId();
	if (!isContainEmployee(id)) {
		std::cout << "System Does NOT Contain This Employee ID!\n";
	}
	else {
		Employee* employee = employeeList[id];
		

		int choice = 0;
		bool isUpdated = false;
		while (true) {
			//call function from utility file
			bool exit = false;
			Utility::updateEmployeeMenu();
			std::cout << "Enter your choice: ";
			std::cin >> choice;
			switch (choice) {
			case 1:
				employee->inputName();
				isUpdated = true;
				break;
			case 2:
				employee->inputSSN();
				isUpdated = true;
				break;
			case 3:
				employee->inputDateOfBirth();
				isUpdated = true;
				break;
			// special case: if no choice is input or input is 0, exit the function
			case 0:
				exit = true;
				break;
			//if no choice, retry
			default:
				break;
			}
			if (exit) {
				break;
			}
		}
		if (isUpdated) {
			//update employee info to the file
			BusinessIO ioFile(employeeFileName);
			ioFile.updateRecord(employee->getID(), employee->convertInfoToString());
		}
	}	
}

//delete employee
void SpaManagement::deleteEmployee() {
	//Ask user to input employee ID
	std::string id = SpaManagement::inputEmployeeId();

	//if employee ID doesnot exist, print error log
	if (!isContainEmployee(id)) {
		std::cout << "System Does NOT Contain This Employee ID!\n";
	}
	//otherwise, remove it
	else {
		//First, remove it from the global list
		Employee* employee = employeeList[id];
		//Call 'erase' function of vector to remove specific item at the specific index
		employeeList.erase(id);
		delete employee;
		employee = nullptr;

		//Then remove employee from the file
		BusinessIO ioFile(employeeFileName);
		ioFile.removeRecord(id);
	}
}

//Check if an employee exists in the list
bool SpaManagement::isContainEmployee(const std::string& id) {
	if (employeeList.count(id) != 0) {
		return true;
	}
	else
		return false;
}
//Prompt user to input employee ID
std::string SpaManagement::inputEmployeeId() {
	std::string idStr;
	std::cout << "Enter Employee's ID: ";

	while (true) {
		std::cin >> idStr;

		//make sure there is no leading and trailing space arround the input
		idStr = Utility::trim(idStr);

		//if ID is invalid format(not a number), ask to enter again
		if (!Utility::isInteger(idStr)) {
			std::cout << "\t[ERROR] Invalid choice!\nEnter Employee's ID Again: ";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			continue;			
		}
		//otherwise, stop the loop to return ID
		else {
			int id = stoi(idStr);
			if (id <= 0) {
				std::cout << "\t[ERROR] ID Must Be Greater Than 0!\n Enter Again: ";
				std::cin.clear();
				std::cin.ignore(100, '\n');
				continue;				
			}
			break;
		}
	}
	return idStr;
}

//function to work on MainMenu
void SpaManagement::displayMainMenu() {
	
	int idKey1 = 0;

	while (true) {
		//call main menu from utility
		Utility::mainMenu();

		std::cout << "Enter your choice: ";
		std::cin >> idKey1;

		switch (idKey1)
		{
		case 1:
			displayEmployeeManagementMenu();
			break;
		case 2:
			displayPayrollInfoMenu();
			break;
		case 0:
			//special case, input is 0, exit function
			return;
		default:
			break;
		}
	}
}

void SpaManagement::displayAllEmployeeInfo() {
	//print the title
	std::cout << std::left << std::setw(WIDTH_COLUMN_ID) <<"ID"
		<< std::setw(WIDTH_COLUMN_NAME) << "NAME"
		<< std::setw(WIDTH_COLUMN_SSN) << "SSN"		
		<< std::setw(WIDTH_COLUMN_TYPE) << "TYPE"
		<< std::setw(WIDTH_COLUMN_DATE) << "DATE OF BIRTH";
	std::cout << std::endl;

	//print each employee info
	for (std::map<std::string, Employee*>::iterator it = employeeList.begin(); it != employeeList.end(); ++it) {
		Employee* employee = it->second;
		if (employee)
			std::cout << *employee;
	}

	//print total number of employees
	std::cout << "Number of Employee: " << employeeList.size() << std::endl;
}

//display the payroll menu
void SpaManagement::displayPayrollInfoMenu() {
	int idKey = 0;
	while (true) {
		//call menu from utility
		Utility::payRollMenu();
		std::cout << "Enter your choice: ";
		std::cin >> idKey;

		switch (idKey)
		{
		case 1:
			updatePayrollForEmployee();
			break;
		case 2:
			displayCalculateSalaryMenu();
			break;
		case 0:
			return;
		default:
			break;
		}
	}
}
//display employee management menu
void SpaManagement::displayEmployeeManagementMenu() {
	int idKey = -1;
	while (true) {
		//call menu from utility
		Utility::employeeManagementMenu();
		std::cout << "Enter your Choice: ";
		std::cin >> idKey;
		switch (idKey)
		{
		case 1:
			displayAllEmployeeInfo();
			break;
		case 2:
			addNewEmployee();
			break;
		case 3:
			deleteEmployee();
			break;
		case 4:
			updateEmployeeInfo();
			break;
		case 0:
			return;
		default:
			break;
		}
		
	}
}

//display calculateSalary Menu
void SpaManagement::displayCalculateSalaryMenu() {
	std::string startDateStr;
	std::string endDateStr;

	std::cout << "Enter Start Date (Format: mm/dd/yyyy): ";
	std::cin >> startDateStr;
	Date startDate(startDateStr);

	std::cout << "Enter End Date (Format: mm/dd/yyyy): ";
	std::cin >> endDateStr;
	Date endDate(endDateStr);

	calculateTotalSalary(startDate, endDate);
}

double SpaManagement::calculateTotalSalary(const Date& startDate, const Date& endDate) {
	BusinessIO ioFile(payRollFileName);
	std::vector<std::string> allRecords;

	//Total salary of all employee during a duration of days
	double totalIncome = 0;
	std::map<std::string, double> salaryEmployeeList;

	//read all records from payroll file
	//record format: date|<employeeID_1>= <salaryOfEmployee_1>|<EmployeeID_2> = <salaryOfEmployee_2>| ... |TotalSalary
	//Ex: 4/14/2021|1=70.0|2=100|3=0
	ioFile.readAll(allRecords);

	//for each record
	for (std::string record : allRecords) {
		std::vector<std::string> items;
		Utility::parse(record, '|', items);
		
		//Get date(index of 0)
		std::string dateItem = items.at(0);
		Date date(dateItem);

		//only sum up income dor dates which are between out expected start and end date
		//using overload >= <=
		if (date >= startDate && date <= endDate) {
			//item.size() - 1 because item income is at the last index
			totalIncome += stod(items.at(items.size() - 1));
		}
		else {
			continue;
		}		


		//Get salary for each employee
		//Why choose index from 1 to size -1?
		//Because salary of each employee is from the 2nd index to the near-last index
		for (unsigned int i = 1; i < items.size() - 1; ++i) {
			std::string employeeSalaryInfo = items.at(i);
			std::vector<std::string> listDateSalaryInfo;

			//parse salary from string for each employee
			//format: <employeeId>=<salaryOfEmployee>
			Utility::parse(employeeSalaryInfo, '=', listDateSalaryInfo);
			
			if (listDateSalaryInfo.size() > 0) {
				std::string employeeId = listDateSalaryInfo.at(0);
				double employeeSalary = stod(listDateSalaryInfo.at(1));
				
				//if this is the first nail section of the employee on this day
				//the total salary is also the latest salary
				if (salaryEmployeeList.count(employeeId) == 0) {
					salaryEmployeeList[employeeId] = employeeSalary;
				}
				//if this is NOT the first on this day
				//change the total salary by summing with the latest salary
				else {
					double newSalary = salaryEmployeeList[employeeId] + employeeSalary;
					salaryEmployeeList[employeeId] = newSalary;
				}
			}

		}
	}
	std::cout << "\nTotal Income: $" << totalIncome << std::endl;
	std::cout << "Salary for Each Employee..." << std::endl;

	double totalSalary = 0;
	for (std::map<std::string, double>::iterator it = salaryEmployeeList.begin(); it != salaryEmployeeList.end(); ++it) {
		std::string employeeId = it->first;
		double salary = it->second;
		totalSalary += salary;
		std::cout << "Employee ID " << employeeId << ": $" << salary << std::endl;
	}
	double profit = totalIncome - totalSalary;
	std::cout << "Profit of the Business: $" << profit << std::endl;

	return totalSalary;
}

//Update payroll to text file
void SpaManagement::updatePayrollInfoToFileByDate(const Date& date) {
	//start save to file
	std::string resultStr; //string to write to the text file
	std::map<std::string, Employee*>::iterator it; //iterator for std::map

	std::string dateStr = convertDateToString(date);

	//1. Append date to the string
	resultStr += dateStr;
	double totalIncomeOfSpa = 0;

	//update payroll for all employees on the day
	for (it = employeeList.begin(); it != employeeList.end(); ++it) {
		Employee* employee = it->second;
		
		//get salary
		double salary = employee->calculatePayRoll();

		//2. append "|<employeeID>=<employeeSalary>" to the string
		resultStr += "|" + employee->getID() + "=" + std::to_string(salary);

		//calculate the total income of spa
		totalIncomeOfSpa += employee->getSalary() + employee->getTips();
	}

	//3. append total income to the string
	resultStr += "|" + std::to_string(totalIncomeOfSpa);

	//4. dont forget to append a new line to the string
	resultStr += "\n";

	//Write the string to text file
	BusinessIO ioFile(payRollFileName);
	ioFile.updateRecord(dateStr, resultStr, true);
}

//function to update payroll for employee
void SpaManagement::updatePayrollForEmployee() {
	std::string dateStr;
	std::string idStr;

	//prompt user to input date
	std::cout << "Enter Date (Format:mm/dd/yyyy): ";
	std::cin >> dateStr;
	Date date(dateStr);

	//Check if date exists in employeeinformation.txt
	//if not, change reset flag to true( prepare to reset salary and tip of employee)
	bool isReset = false;
	int i = 0;

	BusinessIO payRollIO(payRollFileName);
	std::vector<std::string> payRollRecords;
	payRollIO.readAll(payRollRecords);

	if (payRollIO.isExistRecord(dateStr, payRollRecords, i) == false) {
		isReset = true;
	}

	while (true) {
		std::cout << "\nEnter employee ID (or 0 to exit): ";
		std::cin >> idStr;

		//make sure there is no leading and trailing space around the input
		idStr = Utility::trim(idStr);

		//if ID is invalid format (ex: not in form of a number), ask to enter again
		if (!Utility::isInteger(idStr)) {
			std::cout << "\t[ERROR] Invalid Input!\nEnter Again: ";
			continue;
		}

		//if input is 0, exit
		if (idStr == "0") {
			break;
		}
		//Check if the input ID exists
		//If not, output error log
		if (!isContainEmployee(idStr)) {
			std::cout << "System Does NOT contain this Employee ID\nEnter Again: ";
			continue;
		}
		//if ID exist, prompt user to input payroll info
		else {
			//If reset flag is true, reset salary and tip of all employees
			//except the employee with inputted ID
			if (isReset) {
				std::map<std::string, Employee*>::iterator it;
				for (it = employeeList.begin(); it != employeeList.end(); ++it) {
					if (it->first != idStr) {
						(it->second)->setSalary(0);
						(it->second)->setTip(0);
					}
				}
			}
			Employee* employee = employeeList[idStr];
			employeeList[idStr]->inputPayRollInfo(isReset);
		}
		isReset = false;
	}
	//Update new payroll info to file
	updatePayrollInfoToFileByDate(date);
}

//destructor to deallocate
SpaManagement::~SpaManagement() {
	for (auto it = employeeList.begin(); it != employeeList.end(); ++it) {
		delete it->second;
		//std::cout << "Im here "  << std::endl;
	}
}