/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#pragma once
#ifndef AMA_AMAAPP_H
#define AMA_AMAAPP_H
#include "iProduct.h"

namespace ama
{
	class AmaApp
	{
	private:
		char m_filename[256];
		iProduct* m_products[100];
		int m_noOfProducts;
		//Make sure the AmaApp cannot get copied or assigned to another AmaApp
		AmaApp(const AmaApp& other) = delete;
		AmaApp& operator=(const AmaApp& other) = delete;
		void pause() const;
		int menu() const;
		void loadProductRecords();
		void saveProductRecords() const;
		void listProducts() const;
		void deleteProductRecord(iProduct* product); // optional
		void sort(); // optional
		iProduct* find(const char* sku) const;
		void addQty(iProduct* product);
		void addProduct(char tag);

	public:
		AmaApp(const char* filename); //constructor
		~AmaApp(); //destructor
		int run();
	};

}

#endif // !AMA_AMAAPP_H
