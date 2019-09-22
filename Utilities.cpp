/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#include <iostream>
#include <string.h>
#include <iomanip>
#include "Product.h"
#include "Perishable.h"
#include "Utilities.h"
using namespace std;

namespace ama
{
	double& operator+=(double& total, const iProduct& prod) {
		total += prod.total_cost();
		return total;
	}

	ostream& operator<<(ostream& out, const iProduct& prod) {
		return prod.write(out, write_human);
	}

	istream& operator>>(istream& in, iProduct& prod) {
		prod.read(in, true);
		return in;
	}

	iProduct* createInstance(char tag) {
		if (tag == 'N' || tag == 'n') {
			return new Product();
		}

		else if (tag == 'P' || tag == 'p') {
			return new Perishable();
		}

		else
		{
			return nullptr;
		}
	}
}