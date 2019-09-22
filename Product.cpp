#define _CRT_SECURE_NO_WARNINGS
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

using namespace std;

namespace ama
{
	void Product::message(const char* p_Text)
	{
		errorstate.message(p_Text);
	}

	bool Product::isClear() const
	{
		if (errorstate.message() == nullptr) {
			return true;
		}
		else
		{
			return false;
		}
	}

	Product::Product(char type_src) : m_type(type_src) {

		m_sku[0] = '\0';
		m_unit[0] = '\0';
		m_name = nullptr;
		m_cqty = 0;
		m_nqty = 0;
		m_price = 0.0;
		m_status = false;
	}

	Product::Product(const char* sku_src, const char* name_src, const char* unit_src, double price_src, int nqty_src, int cqty_src, bool status_src) : m_type('N') {

		m_price = price_src;
		m_nqty = nqty_src;
		m_cqty = cqty_src;
		m_status = status_src;

		strncpy(m_sku, sku_src, max_length_sku);
		m_sku[max_length_sku] = '\0';

		strncpy(m_unit, unit_src, max_length_unit);
		m_unit[max_length_unit] = '\0';

		if (name_src != nullptr)
		{
			m_name = new char[max_length_name + 1];
			strncpy(m_name, name_src, max_length_name);
			m_name[max_length_name] = '\0';
		}

		else {
			m_sku[0] = '\0';
			m_unit[0] = '\0';
			m_name = nullptr;
			m_cqty = 0;
			m_nqty = 0;
			m_price = 0.0;
			m_status = false;
		}
	}

	//copy constructor
	Product::Product(const Product & other) : m_type(other.m_type) {

		m_cqty = other.m_cqty;
		m_nqty = other.m_nqty;
		m_price = other.m_price;
		m_status = other.m_status;

		strncpy(m_sku, other.m_sku, max_length_sku);
		m_sku[max_length_sku] = '\0';

		strncpy(m_unit, other.m_unit, max_length_unit);
		m_unit[max_length_unit] = '\0';

		if (other.m_name != nullptr) {
			m_name = nullptr;
			m_name = new char[max_length_name + 1];
			strncpy(m_name, other.m_name, max_length_name);
			m_name[max_length_name] = '\0';
		}

		else {
			m_name = nullptr;
		}
	}

	//destructor
	Product::~Product() {
		delete[] m_name;
	}

	//copy assignment operator
	Product &Product::operator=(const Product &other) {
		if (this != &other) {

			m_cqty = other.m_cqty;
			m_nqty = other.m_nqty;
			m_price = other.m_price;
			m_status = other.m_status;

			strncpy(m_sku, other.m_sku, max_length_sku);
			m_sku[max_length_sku] = '\0';
			strncpy(m_unit, other.m_unit, max_length_unit);
			m_unit[max_length_unit] = '\0';

			if (other.m_name != nullptr) {
				delete[] m_name;
				m_name = new char[max_length_name + 1];
				strncpy(m_name, other.m_name, max_length_name);
				m_name[max_length_name] = '\0';
			}

			else {
				m_name = nullptr;
			}
		}

		return *this;
	}

	int Product::operator+=(int cnt) {
		if (cnt > 0) {
			m_cqty += cnt;
			return m_cqty;
		}

		else
		{
			return m_cqty;
		}
	}

	bool Product::operator==(const char* psku) const {
		if (strcmp(this->m_sku, psku) == 0) {
			return true;
		}
		else {
			return false;
		}

	}

	bool Product::operator>(const char* psku) const {
		if (strcmp(this->m_sku, psku) > 0)
		{
			return true;
		}
		else {
			return false;
		}
	}

	bool Product::operator>(const iProduct& other) const {
		if (strcmp(this->m_name, other.name()) > 0)
		{
			return true;
		}
		else {
			return false;
		}
	}

	int Product::qtyAvailable() const {
		return m_cqty;
	}

	int Product::qtyNeeded() const {
		return m_nqty;
	}

	const char* Product::name() const {
		return m_name;
	}

	double Product::total_cost() const {
		if (m_status == true)
		{
			return (m_price + (m_price * tax_rate)) * m_cqty;
		}

		else
		{
			return m_price * m_cqty;
		}
	}

	bool Product::isEmpty() const {
		if (m_name == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	istream& Product::read(istream& in, bool interractive) {
		char is_sku[max_length_sku];
		char *is_name = new char[max_length_name + 1];
		char is_unit[max_length_unit];
		int is_cqty;
		int is_nqty;
		double is_price;
		char is_tax;
		bool is_status;

		if (interractive == true) {

			cout << setw(max_length_label) << right << "Sku: ";
			in >> is_sku;
			cout << setw(max_length_label) << right << " Name (no spaces): ";
			in >> is_name;
			cout << setw(max_length_label) << right << " Unit: ";
			in >> is_unit;
			cout << setw(max_length_label) << right << " Taxed? (y/n): ";
			in >> is_tax;
			if (is_tax == 'Y' || is_tax == 'y')
			{
				is_status = true;
			}
			else if (is_tax == 'N' || is_tax == 'n') {
				is_status = false;
			}
			else {
				errorstate.message("Only (Y)es or (N)o are acceptable!");
				in.setstate(ios::failbit);
			}
			if (!in.fail()) {
				cout << setw(max_length_label) << right << "Price: ";
				in >> is_price;
				if (in.fail()) {
					errorstate.message("Invalid Price Entry!");
					in.setstate(ios::failbit);
				}
			}
			if (!in.fail()) {
				cout << setw(max_length_label) << right << "Quantity on hand: ";
				in >> is_cqty;
				if (in.fail()) {
					errorstate.message("Invalid Quantity Available Entry!");
					in.setstate(ios::failbit);
				}
			}
			if (!in.fail()) {
				cout << setw(max_length_label) << right << "Quantity needed: ";
				in >> is_nqty;

				if (in.fail()) {
					errorstate.message("Invalid Quantity Needed Entry!");
					in.setstate(ios::failbit);
				}
			}

			if (!in.fail()) {
				Product temp = Product(is_sku, is_name, is_unit, is_price, is_nqty, is_cqty, is_status);
				*this = temp;
			}
		}

		else
		{
			char divider = ',';
			//cin.getline
			in.getline(is_sku, max_length_sku, ',');
			in.getline(is_name, max_length_name, ',');
			in.getline(is_unit, max_length_unit, ',');
			in >> is_price >> divider >> is_status >> divider >> is_cqty >> divider >> is_nqty;

			Product temp = Product(is_sku, is_name, is_unit, is_price, is_nqty, is_cqty, is_status);
			*this = temp;
		}

		delete[] is_name;
		return in;
	}

	ostream& Product::write(ostream& out, int writemode) const {
		if (isClear() == false) {
			out << errorstate.message();
		}
		if (isEmpty() == false && isClear() == true) {
			if ((writemode == write_condensed)) {
				char divider = ',';
				out << m_type << divider << m_sku << divider << m_name << divider << m_unit
					<< divider << m_price << divider << m_status
					<< divider << m_cqty << divider << m_nqty;
			}
			else if (writemode == write_table) {
				const char *decision = "yes";
				out << " ";
				out << setw(max_length_sku) << right << m_sku;
				out << " " << '|';
				out << " ";
				if (strlen(m_name) > 16) {
					for (int i = 0; i < 13; i++)
					{
						out << m_name[i];
					}
					out << "...";
				}

				else {
					out << setw(16) << left << m_name;
				}
				out << " " << '|';
				out << " ";
				out << setw(10) << left << m_unit;
				out << " " << '|';
				out << " ";
				out << setw(7) << right << setprecision(2) << m_price;
				out << " " << '|';
				if (m_status == 1) {
					out << " ";
					out << setw(3) << right << decision;
					out << " " << '|';
				}
				else {
					decision = "no";
					out << " ";
					out << setw(3) << right << decision;
					out << " " << '|';
				}

				out << " ";
				out << setw(6) << right << m_cqty;
				out << " " << '|';
				out << " ";
				out << setw(6) << right << m_nqty;
				out << " " << '|';

			}
			else if (writemode == write_human) {
				out << setw(max_length_label) << right << "Sku: " << m_sku << endl;
				out << setw(max_length_label) << right << "Name: " << m_name << endl;
				out << setw(max_length_label) << right << fixed << setprecision(2) << "Price: " << m_price << endl;
				if (m_status == true)
				{
					out << setw(max_length_label) << right << fixed << setprecision(2) << "Price after Tax: " << m_price + m_price * tax_rate << endl;
				}
				else
				{
					out << setw(max_length_label) << right << fixed << setprecision(2) << "Price after Tax: " << m_price << endl;
				}

				out << setw(max_length_label) << right << "Quantity Available: " << m_cqty << " " << m_unit << endl;
				out << setw(max_length_label) << right << "Quantity Needed: " << m_nqty << " " << m_unit << endl;
			}
		}
		return out;
	}
}