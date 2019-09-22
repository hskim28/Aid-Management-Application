/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#include <iostream>
#include <iomanip>
#include "Perishable.h"

using namespace std;
namespace ama
{
	Perishable::Perishable() : Product('P') {}

	ostream& Perishable::write(ostream& os, int writemode) const
	{
		Product::write(os, writemode);
		if (m_date.status() == no_error) {
			if (m_date.status() == no_error) {
				if (writemode == write_human) {
					cout << setw(max_length_label) << right << "Expiry Date: ";
					os << m_date << endl;
				}
				if (writemode == write_table)
				{
					os << " " << m_date << " |";
				}
				if (writemode == write_condensed)
				{
					os << "," << m_date;
				}

			}
		}
		return os;
	}


	istream& Perishable::read(istream& is, bool interractive) {
		Product::read(is, interractive);

		if (interractive == true)
		{
			cout << setw(max_length_label) << right << "Expiry date (YYYY/MM/DD): ";
			is >> m_date;
			//is.setstate(ios::failbit);
			if (m_date.status() == error_year) {
				message("Invalid Year in Date Entry");
				is.setstate(ios::failbit);
			}

			if (m_date.status() == error_mon)
			{
				message("Invalid Month in Date Entry");
				is.setstate(ios::failbit);
			}

			if (m_date.status() == error_day)
			{
				message("Invalid Day in Date Entry");
				is.setstate(ios::failbit);
			}

			if (m_date.status() == error_input)
			{
				message("Invalid Date Entry");
				is.setstate(ios::failbit);
			}
		}
		else
		{
			is.ignore();
			m_date.read(is);
			//is.ignore();
		}
		return is;
	}

}



