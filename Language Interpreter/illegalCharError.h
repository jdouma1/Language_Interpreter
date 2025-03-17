// illegalCharError.h : This file subclasses "error.h" to create specific error messages regarding illegal character usage

#include "error.h"
#pragma once

class IllegalCharError: Error {
public:
	IllegalCharError(std::string details = "Undefined illegal character details") : Error("Illegal Character", details) {}
	std::string toString() {
		return(Error::toString());
	}
private:
};

