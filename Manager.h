#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

class Manager : public Employee {
private:
	int salary_per_hour;
	int hour;
public:
	Manager(const std::string& id = "", const std::string& name = "", const std::string& ssn = "",
		const Date& date = Date(), const int& salaryPerHour = 0);

	//Overriding virtual functions
	void getEmployeeInfo() override;
	std::string convertInfoToString() const override;
	void inputPayRollInfo(bool isReset) override;

	//Overriding pure virtual functions
	double calculatePayRoll() override;

	void setSalaryPerHour();

};

#endif // !MANAGER_H



