#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iomanip>

#include "Date.h"


enum class EMPLOYEE_TYPE
{
	NAIL_TECHNICIAN = 0, 
	MANAGER, 
	MAX_TYPE
};

class Employee {
protected:
	std::string id;
	std::string name;
	Date dateOfBirth;
	std::string SSN;
	EMPLOYEE_TYPE type;
	double salary; //the current salary of the employee from start of a week to now
	double tip;
public:	
	//constructor with default value
	Employee(const std::string& id,const std::string& name = "",const std::string& ssn = ""
		,const Date& date = Date(),const EMPLOYEE_TYPE& type = EMPLOYEE_TYPE::MAX_TYPE);

	std::string getID() const;
	std::string getName() const;
	std::string getSSN() const;
	Date getDateOfBirth() const;
	double getSalary() const;
	void setSalary(double salary);
	void setTip(double tip);
	
	virtual void getEmployeeInfo();
	virtual double getTips() const;
	//convert type to string: NAIL_TECHNICIAN -> "Nail Technician", MANAGER -> "Manager"
	std::string convertEmployeeTypeToString() const;

	//convert employee information to string format to save to file.
	//split by '|'
	virtual std::string convertInfoToString() const;

	//input functions
	//manager and nail technician have input payRoll difference
	//therefore, payRoll is virtual
	virtual void inputPayRollInfo(bool isReset) = 0;
	virtual double calculatePayRoll() = 0;
	//input employee information
	void inputName();
	void inputSSN();
	void inputDateOfBirth();

	//friend & overload operator
	friend std::ostream& operator <<(std::ostream& out,const Employee&);
};

#endif // !EMPLOYEE_H
