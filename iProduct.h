/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#ifndef ama_IPRODUCT_H
#define ama_IPRODUCT_H
#include <iostream>

using namespace std;
namespace ama
{
	const int max_length_label = 30;
	const int max_length_sku = 7;
	const int max_length_name = 75;
	const int max_length_unit = 10;
	const int write_condensed = 0;
	const int write_table = 1;
	const int write_human = 2;
	const double tax_rate = 0.13;

	class iProduct
	{
	public:
		virtual ~iProduct() {};
		virtual ostream& write(ostream& os, int writeMode) const = 0;
		virtual istream& read(istream& is, bool interractive) = 0;
		virtual bool operator==(const char* sku) const = 0;
		virtual double total_cost() const = 0;
		virtual int qtyNeeded() const = 0;
		virtual int qtyAvailable() const = 0;
		virtual const char* name() const = 0;
		virtual int operator+=(int qty) = 0;
		virtual bool operator>(const iProduct& others) const = 0;

	};


}

#endif




