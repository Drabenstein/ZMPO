#include "pch.h"
#include "CMenuManager.h"
#include <iostream>
#include "MessageConstants.h"

CMenuManager::CMenuManager()
{
	pc_root_menu = new CMenu();
} // CMenuManager::CMenuManager()

CMenuManager::~CMenuManager()
{
	delete pc_root_menu;
} // CMenuManager::~CMenuManager()

bool CMenuManager::bRun()
{
	std::cout << MessageConstants::MSG_INPUT_DESERIALIZE_TEXT << std::endl;
	std::string s_deserialize_input;
	std::getline(std::cin, s_deserialize_input);
	std::string s_error_msg;
	int i_deserialize_result = pc_root_menu->iDeserialize(s_deserialize_input, 0, s_error_msg);
	
	if(i_deserialize_result != std::string::npos)
	{
		std::cout << std::endl << pc_root_menu->sGetHelp() << std::endl;
		pc_root_menu->bRun();
	}
	else
	{
		std::cout << std::endl << s_error_msg << std::endl << std::endl;
		return false;
	}

	return true;
} // bool CMenuManager::bRun()
