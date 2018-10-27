#include "pch.h"
#include "CConsoleInputHelper.h"
#include <iostream>
#include "CTableConstants.h"

const CConsoleInputHelper & CConsoleInputHelper::rcGetInstance()
{
	static CConsoleInputHelper instance;
	return instance;
}

bool CConsoleInputHelper::bReadTableIndex(int * piTableIndex) const
{
	std::cout << CTableConstants::MSG_INPUT_TABLE_INDEX << std::endl;
	return b_readTableIndex(piTableIndex) && piTableIndex >= NULL;
}

bool CConsoleInputHelper::bReadValueIndex(int * piValueIndex) const
{
	std::cout << CTableConstants::MSG_INPUT_VALUE_INDEX << std::endl;
	return b_readTableIndex(piValueIndex) && piValueIndex >= NULL;
}

bool CConsoleInputHelper::bReadTableLength(int * piTableLength) const
{
	std::cout << CTableConstants::MSG_INPUT_TABLE_LENGTH << std::endl;
	return b_readTableIndex(piTableLength) && piTableLength > NULL;
}

bool CConsoleInputHelper::bReadValue(int * piValue) const
{
	std::cout << CTableConstants::MSG_INPUT_VALUE << std::endl;
	return b_readTableIndex(piValue);
}

bool CConsoleInputHelper::b_readTableIndex(int * piIndex) const
{
	std::string s_input;
	std::getline(std::cin, s_input);
	int i_table_index = -1;
	bool b_is_success = true;

	if(s_input.length() > 0 && s_input[0] == '0')
	{
		i_table_index = 0;
	}
	else
	{
		i_table_index = strtol(s_input.c_str(), nullptr, 10);
		if(i_table_index == 0)
		{
			b_is_success = false;
		}
	}

	*piIndex = i_table_index;
	return b_is_success;
}
