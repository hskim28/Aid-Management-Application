/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#pragma once
#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H
#include "Product.h"
#include "Date.h"

using namespace std;
namespace ama
{
	class Perishable : public Product {
	private:
		Date m_date;

	public:
		Perishable();
		ostream& write(ostream& os, int writemode) const;
		istream& read(istream& is, bool interactive);

	};
}

#endif // AMA_PERISHABLE_H




