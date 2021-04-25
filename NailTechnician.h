#ifndef NAILTECHNICIAN_H
#define NAILTECHNICIAN_H

#include "Employee.h"

class NailTechnician : public Employee {

public:
	NailTechnician(const std::string& id = "", const std::string& name = "", const std::string& ssn = "", const Date& date = Date());
	
	//Virtual function
	double getTips() const override;
	void getEmployeeInfo() override; //input employee information
	std::string convertInfoToString() const override;

	//Overriding pure virtual functions
	double calculatePayRoll() override; // calculate as 60% salary + 100% tip
	void inputPayRollInfo(bool isReset) override;
};

#endif // !NAILTECHNICIAN_H


