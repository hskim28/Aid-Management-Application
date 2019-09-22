/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#include <iostream>
#include <ostream>
#include <iomanip>
#include "Date.h"

using namespace std;

namespace ama
{
	void Date::status(int newStatus)
	{
		if (newStatus >= 0 && newStatus <= 5) {
			status_code = newStatus;
		}
	}

	int Date::mdays(int year, int mon) const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::setEmpty()
	{
		year = 0000;
		month = 00;
		day = 00;
	}

	Date::Date() {
		setEmpty();
		status(no_error);
	}

	Date::Date(int dyear, int dmonth, int dday) {
		if (dyear < min_year || dyear > max_year) {
			this->status(error_year);
			setEmpty();
		}
		else if (dmonth < 1 || dmonth > 12) {
			this->status(error_mon);
			setEmpty();
		}
		else if (dday < 1 || dday > mdays(dyear, dmonth)) {
			this->status(error_day);
			setEmpty();
		}
		else {
			this->status(no_error);
			year = dyear;
			month = dmonth;
			day = dday;
		}

	}

	int Date::status() const
	{
		return status_code;
	}

	void Date::clearError()
	{
		status(no_error);
	}

	bool Date::isGood()
	{
		if (status() == no_error && year != 0 && month != 0 && day != 0) {
			return true;
		}
		else {
			return false;
		}
	}

	Date& Date::operator+=(int days) {
		if (isGood() == false) {
			status(error_invalid_operation);
		}
		else
		{
			this->day += days;
			if (this->day < 1 || this->day > mdays(this->year, this->month)) {
				day -= days;
				status(error_invalid_operation);
			}
		}
		return *this;
	}

	Date& Date::operator++() {
		if (isGood() == false) {
			status(error_invalid_operation);
		}
		else
		{
			this->day += 1;
			if (this->day < 1 || this->day > mdays(this->year, this->month)) {
				this->status(error_invalid_operation);
				this->day--;
			}
		}
		return *this;
	}

	Date Date::operator++(int day) {
		Date postfix = *this;
		if (isGood() == false) {
			status(error_invalid_operation);
		}
		else
		{
			++*this;
			if (postfix.day < 1 || postfix.day > mdays(postfix.year, postfix.month)) {
				postfix.status(error_invalid_operation);
			}
		}
		return postfix;
	}

	Date Date::operator+(int days) {
		Date plus = *this;
		if (this->isGood() == false) {
			plus.status(error_invalid_operation);
		}
		else {
			plus.day += days;
			if (plus.day < 1 || plus.day > mdays(plus.year, plus.month)) {
				plus.status(error_invalid_operation);
				plus.day -= days;
			}
		}
		return plus;
	}

	int Date::calculator() const {
		int cal = year * 372 + month * 12 + day;
		return cal;
	}

	bool Date::operator == (const Date& rhs) {
		if (this->calculator() == rhs.calculator()) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator != (const Date& rhs) {
		if (this->calculator() != rhs.calculator()) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator < (const Date& rhs) {
		if (this->calculator() < rhs.calculator()) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator > (const Date& rhs) {
		if (this->calculator() > rhs.calculator()) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator <= (const Date& rhs) {
		if (this->calculator() <= rhs.calculator()) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator >= (const Date& rhs) {
		if (this->calculator() >= rhs.calculator()) {
			return true;
		}
		else
		{
			return false;
		}
	}

	istream& Date::read(istream& is) {
		char character;
		is >> year >> character >> month >> character >> day;
		if (is.fail() == true) {
			this->status(error_input);
			this->setEmpty();
		}

		else if (year < min_year || year > max_year) {
			this->status(error_year);
			this->setEmpty();
		}

		else if (month < 1 || month > 12) {
			this->status(error_mon);
			this->setEmpty();
		}

		else if (day < 1 || day > mdays(this->year, this->month)) {
			this->status(error_day);
			this->setEmpty();
		}

		else {
			this->status(no_error);
		}

		return is;
	}

	ostream& Date::write(ostream& os) const {
		os.fill('0');
		os.width(4);
		os.setf(ios::right);
		os << year << "/";
		os.width(2);
		os << month << "/";
		os.width(2);
		os << day << setfill(' ');

		return os;
	}

	ostream& operator<<(ostream& ost, const Date& para) {
		return para.write(ost);
	}

	istream& operator>>(istream& ist, Date& para) {
		return para.read(ist);
	}

}
