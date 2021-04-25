//Implementation file of Date.h

#include "Date.h"
#include "Utility.h"

//constructors
Date::Date(const int& day, const int& month, const int& year) {
	set_day(day);
	set_month(month);
	set_year(year);
}
Date::Date(const std::string& dateStr) {
	std::vector<int> listValue;
	set_day(0);
	set_month(0);
	set_year(0);

	//Get year, month, day
	//split date by / delimiter
	Utility::parse(dateStr, '/', listValue);

	//form date: mm/dd/yyyy
	//save to member variables
	//make sure year is inputted; else, dont get year
	if (listValue.size() == 3) {
		this->month = listValue.at(0);
		this->day = listValue.at(1);
		this->year = listValue.at(2);
	}
}

//Getter and setters
int Date::get_day() const { return day; };
int Date::get_month() const { return month; };
int Date::get_year() const { return year; };

//setter
void Date::set_day(int day) { this->day = day; };
void Date::set_month(int month) { this->month = month; };
void Date::set_year(int year) { this->year = year; };

//Convert date to string
//this function is helpful when we want to quickly print the date in specific format that we want
//Ex1: always use format mm/dd/yyyy
std::string convertDateToString(const Date& date) {

	std::string strDate = std::to_string(date.get_month());
	
	//add string to the current mm/
	strDate += "/";
	
	strDate += std::to_string(date.get_day());
	
	//now the string is mm/dd
	strDate += "/";

	strDate += std::to_string(date.get_year());
	//after the process mm/dd/yyyy
	return strDate;
}

//Convert date to integer
//This function is helpful when we want to compare 2 dates (to which which one is newer)
//Ex: 4/4/2021 is newer than 4/1/2021
int Date::convertDateToInt() const {

	//convert date to int like mmddyyyy, ex: 4/4/2021 -> 442021
	std::string yearStr = std::to_string(get_year());
	std::string monthStr = std::to_string(get_month());
	std::string dayStr = std::to_string(get_day());
	
	std::string final = monthStr + dayStr + yearStr;

	//convert to int
	return stoi(final);
}

//Overload operator << to print the dat in mm/dd/yyyy format
std::ostream& operator << (std::ostream& out, const Date& date) {
	out << date.get_month() << "/" << date.get_day() << "/" << date.get_year();
	return out;
}

//Overload operator <=  to find which date is newer
bool operator <= (const Date& d1, const Date& d2) {
	int d1Value = d1.convertDateToInt();
	int d2Value = d2.convertDateToInt();
	if (d1Value <= d2Value) {
		return true;
	}
	else {
		return false;
	}
}

//Overload operator >= to find which date is newer
bool operator >= (const Date& d1, const Date& d2) {
	int d1Value = d1.convertDateToInt();
	int d2Value = d2.convertDateToInt();
	if (d1Value >= d2Value) {
		return true;
	}
	else {
		return false;
	}
}



