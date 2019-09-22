/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#pragma once
#ifndef ama_Product_h
#define ama_Product_h
#include "ErrorState.h"
#include "iProduct.h"

using namespace std;
namespace ama {

	class Product : public iProduct {

	public:
		Product(char type_src = 'N');
		Product(const char* sku_src, const char* name_src, const char* unit_src, double price_src = 0.0, int nqty_src = 0, int cqty_src = 0, bool status_src = true);
		Product(const Product& other);
		~Product();
		Product& operator=(const Product& other);
		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator>(const char* sku) const;
		bool operator>(const iProduct& other) const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		double total_cost() const;
		const char* name() const;
		bool isEmpty() const;
		istream& read(istream& in, bool interractive);
		ostream& write(ostream& out, int writeMode) const;

	private:
		const char m_type;
		char m_sku[max_length_sku + 1];
		char m_unit[max_length_unit + 1];
		char * m_name;
		int m_cqty;
		int m_nqty;
		double m_price;
		bool m_status;
		ErrorState errorstate;

	protected:
		void message(const char* pText);
		bool isClear() const;
	};
}

#endif




