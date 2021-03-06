// Lista4.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "CValue.h"

int main()
{
	CValue c_value_0, c_value_1, c_value_2, c_value_3;

	int i_int_value = 21;
	int* pi_int_value = new int(21);
	bool b_bool_value = false;

	c_value_0.vSetValue(&i_int_value, false);
	c_value_1.vSetValue(pi_int_value, true);
	c_value_2.vSetValue(pi_int_value, false);
	c_value_3.vSetValue(&b_bool_value, false);

	std::cout << c_value_0.bEquals(&c_value_1) << std::endl;
	std::cout << c_value_0.bEquals(&c_value_3) << std::endl;
	std::cout << c_value_1.bEquals(&c_value_2) << std::endl;

	CValue c_value_4(c_value_1);
	CValue c_value_5(c_value_0);

	std::cout << c_value_4.bEquals(&c_value_1) << std::endl;
	std::cout << c_value_5.bEquals(&c_value_0) << std::endl;
}