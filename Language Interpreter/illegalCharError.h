#include "error.h"
#pragma once
class IllegalCharError: Error {
public:
	IllegalCharError(std::string details = "Undefined") {
		e = Error("Illegal Character", details);
	}
	std::string toString() {
		return(e.toString());
	}
private:
	Error e;
};

