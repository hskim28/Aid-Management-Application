/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#pragma once
#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>

using namespace std;

namespace ama
{
	const int min_year = 2019;
	const int max_year = 2028;
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	class Date {
	private:
		int year;
		int month;
		int day;
		int status_code;
		void status(int newStatus);
		int mdays(int year, int month) const;
		void setEmpty(); // added private member function
		int calculator() const; // added private member function

	public:
		Date();
		Date(int dyear, int dmonth, int dday);
		int status() const;
		void clearError();
		bool isGood();
		Date& operator+=(int days);
		Date& operator++();
		Date operator++(int);
		Date operator+(int days);
		bool operator==(const Date& rhs);
		bool operator!=(const Date& rhs);
		bool operator<(const Date& rhs);
		bool operator>(const Date& rhs);
		bool operator<=(const Date& rhs);
		bool operator>=(const Date& rhs);
		istream& read(istream& is);
		ostream& write(ostream& os) const;

	};
	istream& operator>>(istream&, Date&);
	ostream& operator<<(ostream&, const Date&);
}

#endif




