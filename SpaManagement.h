#ifndef SPAMANAGEMENT_H
#define SPAMANAGEMENT_H

#include <map>

#include "Employee.h"

class SpaManagement {
private:
	std::map<std::string, Employee*> employeeList; //key: employee ID
	double totalSalary;
	std::string employeeFileName;
	std::string payRollFileName;

public:
	//constructor
	SpaManagement();
	//display menu
	void displayMainMenu();
	void displayPayrollInfoMenu();
	void displayCalculateSalaryMenu();
	void displayEmployeeManagementMenu();
	void updatePayrollForEmployee();

	//add, update, remove employee functions
	void addNewEmployee();
	void updateEmployeeInfo(); //update by id
	void deleteEmployee();
	void displayAllEmployeeInfo();

	//checking the system contain employee id as input
	bool isContainEmployee(const std::string& id);

	//input employee id
	static std::string inputEmployeeId();
	
	void loadEmployeeFromFile();
	void updatePayrollInfoToFileByDate(const Date& date);
	
	double calculateTotalSalary(const Date& startDate, const Date& endDate);

	//destructor
	~SpaManagement();
};

#endif // !


