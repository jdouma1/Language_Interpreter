#include <string>
#pragma once
class Error {
public:
	Error(std::string errorName = "Undefined", std::string details = "Undefined") {
		this->errorName = errorName;
		this->details = details;
	}
	std::string toString() {
		return(errorName + ": " + details);
	}
private:
	std::string errorName;
	std::string details;
};

