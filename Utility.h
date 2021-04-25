#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#define WIDTH_COLUMN_ID			5
#define WIDTH_COLUMN_NAME		25
#define WIDTH_COLUMN_SSN		20
#define WIDTH_COLUMN_DATE		20
#define WIDTH_COLUMN_TYPE		25

class Utility {
public:
	static void parse(std::string str, char delim, std::vector<std::string>& vec);
	static void parse(std::string str, char delum, std::vector<int>& vec);
	static void parse(std::string str, char delum, std::vector<double>& vec);
	static std::string trim(const std::string& input);
	static bool isInteger(const std::string& input);
	static void updateEmployeeMenu();
	static void mainMenu();
	static void payRollMenu();
	static void employeeManagementMenu();
	static bool isLeapYear(int year);
};


#endif // !1
