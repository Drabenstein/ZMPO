#include "pch.h"
#include "CSubject.h"
#include <sstream>
#define PARENTHESES_OPEN "("
#define PARENTHESES_CLOSE ")"
#define DATA_SEPARATOR ", "

std::string CSubject::sToString()
{
	std::stringstream c_result;
	c_result << PARENTHESES_OPEN << d_value << DATA_SEPARATOR << d_size << PARENTHESES_CLOSE;
	return c_result.str();
} // std::string CSubject::sToString()
