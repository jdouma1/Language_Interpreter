// error.h : This file contains methods which create and return the program's logical error messages

#include <string>
#pragma once
class Error {
public:
	Error(std::string errorName = "Undefined error", std::string details = "Undefined error details") {
		this->errorName = errorName;
		this->details = details;
	}
	std::string toString() {
		return("ERROR: " + errorName + ": " + details);
	}
private:
	std::string errorName;
	std::string details;
};

