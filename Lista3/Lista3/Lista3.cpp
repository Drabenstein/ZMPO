// Lista3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "CMenu.h"
#include "CMenuCommand.h"
#include "CSerializeCommand.h"

int main()
{
	/*CMenu menu;
	std::cout << "Wczytaj string to deserializacji: ";
	std::string s_input;
	std::getline(std::cin, s_input);
	std::string s_error_msg;
	int res = menu.iDeserialize(s_input, 0, s_error_msg);
	std::cout << res << std::endl;

	if(res == -1)
	{
		std::cout << s_error_msg << std::endl;
	}
	else
	{
		menu.bRun();
	}*/

	CMenuCommand menu;
	std::cout << "Wczytaj string to deserializacji: ";
	std::string s_input;
	std::getline(std::cin, s_input);
	std::string s_error_msg;
	int res = menu.iDeserialize(s_input, 0, s_error_msg);
	std::cout << res << std::endl;

	if (res == std::string::npos)
	{
		std::cout << s_error_msg << std::endl;
	}
	else
	{
		std::cout << menu.sToString() << menu.sGetHelp() <<std::endl ;
	}
}
