#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
	int day;
	int month;
	int year;
public:
	//constructors
	Date(const int& day = 0, const int& month = 0, const int& year = 0);
	Date(const std::string& dateStr);
	
	//getter
	int get_day() const;
	int get_month() const;
	int get_year() const;

	//setter
	void set_day(int day);
	void set_month(int month);
	void set_year(int year);

	//convert to format: mm/dd/yyyy
	friend std::string convertDateToString(const Date& date);
	int convertDateToInt() const;

	//overload operator <<
	friend std::ostream& operator <<(std::ostream& out, const Date&);
	friend bool operator <= (const Date& d1, const Date& d2);
	friend bool operator >= (const Date& d1, const Date& d2);
};

#endif // !DATE_H

