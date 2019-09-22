#define _CRT_SECURE_NO_WARNINGS
/* -------------------------------------------
Name: Hyun Soo Kim
Student number: 106283187
Email: hskim28@myseneca.ca
Section: SCC
Date: 04-07-19
-------------------------------------------*/
#include <iostream>
#include <ostream>
#include <iomanip>
#include <cstring>
#include "ErrorState.h"

using namespace std;

namespace ama
{
	ErrorState::ErrorState(const char* errorMessage) {
		if (errorMessage == nullptr) {
			msg = nullptr;
		}
		else if (errorMessage[0] == '\0') {
			msg = nullptr;
		}
		else
		{
			msg = new char[strlen(errorMessage) + 1];
			strcpy(msg, errorMessage);
		}
	}

	ErrorState::~ErrorState() {
		delete[] msg;
		msg = nullptr;
	}

	ErrorState::operator bool() const {
		if (msg != nullptr && msg[0] != '\0') {
			return true;
		}
		else
		{
			return false;
		}
	}

	ErrorState& ErrorState::operator=(const char* pText) {
		delete[] msg;

		if (pText == nullptr) {
			msg = nullptr;
		}
		else if (pText[0] == '\0') {
			msg = nullptr;
		}
		else
		{
			msg = new char[strlen(pText) + 1];
			strcpy(msg, pText);
		}
		return *this;
	}

	void ErrorState::message(const char* pText) {
		delete[] msg;

		if (pText == nullptr) {
			msg = nullptr;
		}
		else if (pText[0] == '\0') {
			msg = nullptr;
		}
		else
		{
			msg = new char[strlen(pText) + 1];
			strcpy(msg, pText);
		}
	}

	const char* ErrorState::message() const {
		if (msg != nullptr) {
			return msg;
		}
		else
		{
			return nullptr;
		}
	}

	ostream& operator<<(ostream& os, const ErrorState& es) {
		if (es.operator bool() == true) {
			os << es.message();
		}
		return os;
	}
}
