#include "pch.h"
#include "CMenu.h"
#include <iostream>
#include <sstream>
#include "MenuConstants.h"

CMenu::CMenu(std::string sName, std::string sCommand, CMenuItem* pcParentItem, bool * bSuccess) : CMenuItem(sName, sCommand, pcParentItem, bSuccess)
{
} // CMenu::CMenu(std::string sName, std::string sCommand, bool * bSuccess) : CMenuItem(sName, sCommand, bSuccess)

CMenu::~CMenu()
{
	for(int i = 0; i < v_menu_items.size(); i++)
	{
		delete v_menu_items.at(i);
	}

	v_menu_items.clear();
} // CMenu::~CMenu()

bool CMenu::bRun()
{
	bool b_back_requested = false;
	bool b_exit_not_requested = true;

	do
	{
		std::cout << MenuConstants::MSG_MENU_SEPARATOR << std::endl << 
			sGetMenuHeader() << std::endl << MenuConstants::MSG_MENU_SEPARATOR << std::endl;

		for (int i = 0; i < v_menu_items.size(); i++)
		{
			std::cout << i + 1 << MenuConstants::MSG_CMD_NUM_SEPARATOR << v_menu_items.at(i)->sToString() << std::endl;
		} // for(int i = 0; i < v_menu_items.size(); i++)

		std::cout << MenuConstants::MSG_MENU_SEPARATOR << std::endl << std::endl;

		std::string s_user_command;
		std::getline(std::cin, s_user_command);

		std::cout << std::endl;

		CMenuItem* pc_selected_item = nullptr;

		const std::string s_help_cmd_start = MenuConstants::CMD_HELP + MenuConstants::MSG_WHITE_SPACE;;
		bool b_is_help_cmd = s_user_command.substr(0, s_help_cmd_start.length()) == s_help_cmd_start;
			
		if(b_is_help_cmd)
		{
			s_user_command = s_user_command.substr(5);
		}

		for(int i = 0; i < v_menu_items.size(); i++)
		{
			if(s_user_command == v_menu_items.at(i)->sGetCommand())
			{
				pc_selected_item = v_menu_items.at(i);
			}
		} // for(int i = 0; i < v_menu_items.size(); i++)

		const std::string s_search_cmd_start = MenuConstants::CMD_SEARCH + MenuConstants::MSG_WHITE_SPACE;

		if(s_user_command.substr(0, s_search_cmd_start.length()) == s_search_cmd_start)
		{
			std::string s_cmd_to_find = s_user_command.substr(s_search_cmd_start.length());
			std::vector<CMenuItem*>* pv_found_items = pvInitSearch(s_cmd_to_find);

			for(int i = 0; i < pv_found_items->size(); i++)
			{
				std::cout << pv_found_items->at(i)->sGetPath() << std::endl;
			}

			std::cout << std::endl;

			if(pv_found_items->size() == 0)
			{
				std::cout << MenuConstants::ERR_MSG_CMD_DOES_NOT_EXIST << std::endl << std::endl;
			}
		}
		else if(s_user_command == MenuConstants::CMD_BACK)
		{
			b_back_requested = true;
		}
		else if(s_user_command == MenuConstants::CMD_EXIT)
		{
			b_exit_not_requested = false;
		}
		else if(b_is_help_cmd)
		{
			if(pc_selected_item != nullptr)
			{
				std::cout << pc_selected_item->sGetHelp() << std::endl << std::endl;
			}
			else
			{
				std::cout << MenuConstants::ERR_MSG_CMD_DOES_NOT_EXIST << std::endl << std::endl;
			}
		}
		else if(pc_selected_item != nullptr)
		{
			b_exit_not_requested = pc_selected_item->bRun();
		}
		else
		{
			std::cout << MenuConstants::ERR_MSG_INVALID_CMD << std::endl;
		}

	} while (!b_back_requested && b_exit_not_requested);

	return b_exit_not_requested;
} // void CMenu::bRun()

void CMenu::vSearch(std::vector<CMenuItem*>* pvFoundItems, const std::string & rsCmdToFind)
{
	if(sGetCommand() == rsCmdToFind)
	{
		pvFoundItems->push_back(this);
	}

	for(int i = 0; i < v_menu_items.size(); i++)
	{
		v_menu_items.at(i)->vSearch(pvFoundItems, rsCmdToFind);
	}
} // void CMenu::vSearch(std::vector<CMenuItem*>* pvFoundItems, const std::string & rsCmdToFind)

bool CMenu::bAddMenuItem(CMenuItem * pcMenuItem)
{
	bool b_is_succces = false;

	if(pcMenuItem != nullptr)
	{
		bool b_is_duplicate = b_check_duplicate(pcMenuItem);
		if (!b_is_duplicate)
		{
			pcMenuItem->bSetParentItem(this);
			v_menu_items.push_back(pcMenuItem);
			b_is_succces = true;
		}
	}

	return b_is_succces;
} // bool CMenu::bAddMenuItem(CMenuItem * pcMenuItem)

const std::vector<CMenuItem*>& CMenu::pvGetMenuItems()
{
	return v_menu_items;
} // const std::vector<CMenuItem*>& CMenu::pvGetMenuItems()

bool CMenu::bRemoveMenuItem(int iOffset)
{
	bool b_success = false;

	if(iOffset >= 0 && iOffset < v_menu_items.size())
	{
		delete v_menu_items.at(iOffset);
		v_menu_items.erase(v_menu_items.begin() + iOffset);
		b_success = true;
	}

	return b_success;
} // bool CMenu::bRemoveMenuItem(int iOffset)

std::string CMenu::sGetMenuHeader()
{
	return sGetName();
} // std::string CMenu::sGetMenuHeader()

bool CMenu::b_check_duplicate(CMenuItem * pcMenuItem)
{
	bool b_is_duplicate = false;

	for (int i = 0; i < v_menu_items.size() && !b_is_duplicate; i++)
	{
		CMenuItem* pc_current_item = v_menu_items.at(i);
		
		if (pcMenuItem->sGetName() == pc_current_item->sGetName() 
			|| pcMenuItem->sGetCommand() == pc_current_item->sGetCommand()
			|| pcMenuItem->sGetCommand() == MenuConstants::CMD_HELP + MenuConstants::MSG_WHITE_SPACE + pc_current_item->sGetCommand())
		{
			b_is_duplicate = true;
		}
	} // for(int i = 0; i < v_menu_items.size() && !b_check_duplicate; i++)

	return b_is_duplicate;
} // bool CMenu::b_check_duplicate(CMenuItem * pcMenuItem)
