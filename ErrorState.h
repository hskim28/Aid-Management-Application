/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#pragma once
#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H
#include <iostream>

using namespace std;

namespace ama
{

	class ErrorState {

	private:
		char* msg;

	public:
		explicit ErrorState(const char* = nullptr);
		ErrorState(const ErrorState& other) = delete;
		ErrorState& operator=(const ErrorState& other) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char* pText);
		void message(const char* pText);
		const char* message() const;
	};
	ostream& operator<<(ostream&, const ErrorState&); // helper function
}


#endif




