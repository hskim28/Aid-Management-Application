/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#pragma once
#ifndef ama_Utilities_h
#define ama_Utilities_h
#include "Product.h"

using namespace std;
namespace ama
{
	double& operator+=(double& total, const iProduct& prod);
	ostream& operator<<(ostream& out, const iProduct& prod);
	istream& operator>>(istream& in, iProduct& prod);
	iProduct* createInstance(char tag);
}

#endif




