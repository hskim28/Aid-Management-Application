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
#include <fstream>
#include <iomanip>
#include "AmaApp.h"
#include "Product.h"
#include "Utilities.h"

using namespace std;
namespace ama
{
	AmaApp::AmaApp(const char * filename)
	{
		strncpy(m_filename, filename, strlen(filename));
		//Set all the m_product elements to null
		m_filename[strlen(filename)] = '\0';
		m_noOfProducts = 0;

		for (int i = 0; i < m_noOfProducts; i++)
		{
			m_products[i] = NULL;
		}

		loadProductRecords();
	}

	AmaApp::~AmaApp() {
		for (int i = 0; i < m_noOfProducts; i++)
		{
			delete m_products[i];
		}
	}

	void AmaApp::pause() const {
		cout << "Press Enter to continue...";
		//cin.get();
		cin.ignore(1000, '\n');
		cout << endl;
	}

	int AmaApp::menu() const {
		int selection = 10;
		//cin.clear();

		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "--------------------------------------" << endl;
		cout << "1- List products" << endl;
		cout << "2- Search product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to product quantity" << endl;
		cout << "6- Delete product" << endl;
		cout << "7- Sort products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		cin >> selection;

		if (selection >= 0 || selection <= 5)
		{
			cin.ignore(1000, '\n');
			return selection;
		}
		else
		{
			cin.ignore(1000, '\n');
			return -1;
		}
	}

	void AmaApp::loadProductRecords() {
		for (int i = 0; i < m_noOfProducts; i++)
		{
			delete m_products[i];
		}
		int index = 0;
		char file;

		fstream read_file;

		read_file.open(m_filename, ios::in);

		if (read_file.is_open()) {
			while (!read_file.eof()) {
				read_file >> file;
				iProduct* load = createInstance(file);

				if (load != NULL) {
					m_products[index] = load;
					read_file.ignore(); // skip comma
					m_products[index]->read(read_file, false);
					//read product
					index++;
					//increament
				}

			}
			m_noOfProducts = index;
		}

		read_file.close();
	}

	void AmaApp::saveProductRecords() const {
		fstream write_file;
		write_file.open(m_filename, ios::out);
		for (int i = 0; i < m_noOfProducts; i++) {
			if (write_file.is_open())
			{
				m_products[i]->write(write_file, write_condensed) << endl;
			}
		}
		write_file.close();

	}

	void AmaApp::listProducts() const {
		double cost = 0.0;

		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl;
		cout << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;

		for (int i = 0; i < m_noOfProducts - 1; i++) {
			cout << "|";
			cout << setw(4) << right << i + 1;
			cout << " " << "|";
			cout << fixed;
			cout.precision(2);
			m_products[i]->write(cout, write_table) << endl;
			cost += m_products[i]->total_cost();
		}

		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                      Total cost of support ($): | ";
		cout << fixed;
		cout.precision(2);
		cout << setw(10) << right << cost;
		cout << " |" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << endl;

		pause();
	}

	iProduct* AmaApp::find(const char* sku) const {

		int match = 200;
		bool f_result = false;
		for (int i = 0; i < m_noOfProducts; i++) {

			f_result = (*m_products[i] == sku);
			if (f_result == true) {
				match = i;
			}
		}
		if (match <= 100) {
			return m_products[match];
		}
		else {
			return NULL;
		}
	}

	void AmaApp::addProduct(char tag) {
		iProduct* tp = createInstance(tag);

		if (tp != NULL)
		{
			m_products[m_noOfProducts - 1] = tp;
			cin >> *m_products[m_noOfProducts - 1];

			if (cin.fail()) {
				cin.clear();

				cout << endl;
				cout << *m_products[m_noOfProducts - 1] << endl;
				cout << endl;
			}

			else
			{
				saveProductRecords();
				cout << endl;
				cout << "Success!" << endl;
				cout << endl;
			}
		}
	}


	void AmaApp::addQty(iProduct* product) {
		int answer = 0;

		product->write(cout, write_human);
		cout << endl;
		cout << endl;
		cout << "Please enter the number of purchased items: ";
		cin >> answer;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid quantity value!" << endl;
			cout << endl;
		}
		else {

			if (answer <= (product->qtyNeeded() - product->qtyAvailable()))
			{
				*product += answer;
				cout << endl;
				cout << "Updated!" << endl;
				cout << endl;
			}

			else
			{
				cout << "Too many items; only " << product->qtyNeeded() - product->qtyAvailable() << " is needed. Please return the extra " << answer - (product->qtyNeeded() - product->qtyAvailable()) << " items." << endl;
				*product += product->qtyNeeded() - product->qtyAvailable();
				cout << endl;
				cout << "Updated!" << endl;
				cout << endl;
			}
		}
	}

	int AmaApp::run() {
		int selection = 10;
		char answer[100] = {};

		do
		{
			selection = menu();
			//cin.ignore(1000, '\n');

			if (selection == 1) {
				AmaApp::listProducts();
				//pause();
			}

			else if (selection == 2) {
				cout << "Please enter the product SKU: ";
				cin >> answer;
				cin.ignore(1000, '\n');
				cout << endl;
				find(answer);
				if (find(answer) != NULL) {
					find(answer)->write(cout, write_human);
					cout << endl;

				}
				else {
					cout << "No such product!" << endl;
				}
				pause();
			}

			else if (selection == 3) {
				addProduct('n');
				loadProductRecords();
				cin.ignore(1000, '\n');
			}

			else if (selection == 4) {
				addProduct('p');
				loadProductRecords();
				cin.ignore(1000, '\n');
			}


			else if (selection == 5)
			{
				char answer[100];
				cout << "Please enter the product SKU: ";
				cin >> answer;
				cin.ignore(1000, '\n');
				cout << endl;
				find(answer);

				if (find(answer) != NULL) {
					addQty(find(answer));
				}
				else
				{
					cout << "No such product!" << endl;
					cout << endl;
				}
			}

			else if (selection == 0) {
				cout << "Goodbye!" << endl;
			}

			else {
				cout << "~~~Invalid selection, try again!~~~" << endl;
				pause();
			}

		} while (selection != 0);

		return 0;

	}

}



