#include "pch.h"
#include "CMenu.h"
#include <iostream>
#include <sstream>
#include "MenuConstants.h"
#include "CTable.h"

CMenu::CMenu(std::string sName, std::string sCommand, bool * bSuccess) : CMenuItem(sName, sCommand, bSuccess)
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

void CMenu::vRun()
{
	bool b_exit_requested = false;

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

		for(int i = 0; i < v_menu_items.size(); i++)
		{
			if(s_user_command == v_menu_items.at(i)->sGetCommand())
			{
				pc_selected_item = v_menu_items.at(i);
			}
		} // for(int i = 0; i < v_menu_items.size(); i++)

		if(s_user_command == MenuConstants::CMD_BACK)
		{
			b_exit_requested = true;
		}
		else if(pc_selected_item != nullptr)
		{
			pc_selected_item->vRun();
		}
		else
		{
			std::cout << MenuConstants::ERR_MSG_INVALID_CMD << std::endl;
		}

	} while (!b_exit_requested);

} // void CMenu::vRun()

std::string CMenu::sToString()
{
	std::ostringstream c_result;
	c_result << s_name << "(" << s_command << ")";
	return c_result.str();
} // std::string CMenu::sToString()

bool CMenu::bAddMenuItem(CMenuItem * pcMenuItem)
{
	bool b_is_succces = false;

	if(pcMenuItem != nullptr)
	{
		bool b_is_duplicate = false;

		for (int i = 0; i < v_menu_items.size() && !b_is_duplicate; i++)
		{
			CMenuItem* pc_current_item = v_menu_items.at(i);
			if (pcMenuItem->sGetCommand() == pc_current_item->sGetCommand())
			{
				b_is_duplicate = true;
			}
		} // for(int i = 0; i < v_menu_items.size() && !b_is_duplicate; i++)

		if (!b_is_duplicate)
		{
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
	return s_name;
} // std::string CMenu::sGetMenuHeader()

std::string CMenu::sGetCommand()
{
	return s_command;
} // std::string CMenu::sGetCommand()

std::string CMenu::sGetName()
{
	return s_name;
} // std::string CMenu::sGetName()

bool CMenu::bSetName(std::string sName)
{
	bool b_change_success = false;

	if(sName.length() > 0)
	{
		s_name = sName;
		b_change_success = true;
	}

	return b_change_success;
} // bool CMenu::bSetName(std::string sName)

bool CMenu::bSetCommand(std::string sCommand)
{
	bool b_change_success = false;

	if(sCommand.length() > 0)
	{
		s_command = sCommand;
		b_change_success = true;
	}

	return b_change_success;
} // bool CMenu::bSetCommand(std::string sCommand)