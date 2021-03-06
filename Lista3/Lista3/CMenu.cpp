#include "pch.h"
#include "CMenu.h"
#include <iostream>
#include <sstream>
#include "MenuConstants.h"
#include "CStringHelper.h"

const std::string CMenu::DEFAULT_NAME = "Default Menu";
const std::string CMenu::DEFAULT_CMD = "DefaultMenuCmd";
const std::string CMenu::DEFAULT_HELP_MSG = "Default help for menu";

namespace MC = MenuConstants;

CMenu::CMenu() : CMenuItem(DEFAULT_NAME, DEFAULT_CMD, DEFAULT_HELP_MSG, nullptr, nullptr)
{
} // CMenu::CMenu()

CMenu::CMenu(std::string sName, std::string sCommand, CMenuItem* pcParentItem, bool * pbSuccess) : CMenuItem(sName, sCommand, DEFAULT_HELP_MSG, pcParentItem, pbSuccess)
{
} // CMenu::CMenu(std::string sName, std::string sCommand, CMenuItem* pcParentItem, bool * pbSuccess) : CMenuItem(sName, sCommand, pcParentItem, pbSuccess) 

CMenu::~CMenu()
{
	for(int i = 0; i < v_menu_items.size(); i++)
	{
		delete v_menu_items.at(i);
	} // for(int i = 0; i < v_menu_items.size(); i++)

	v_menu_items.clear();
} // CMenu::~CMenu()

bool CMenu::bRun()
{
	bool b_back_requested = false;
	bool b_exit_not_requested = true;

	do
	{
		std::cout << MC::MSG_MENU_SEPARATOR << std::endl << 
			sGetMenuHeader() << std::endl << MC::MSG_MENU_SEPARATOR << std::endl;

		for (int i = 0; i < v_menu_items.size(); i++)
		{
			std::cout << i + 1 << MC::MSG_CMD_NUM_SEPARATOR << v_menu_items.at(i)->sToString() << std::endl;
		} // for(int i = 0; i < v_menu_items.size(); i++)

		std::cout << MC::MSG_MENU_SEPARATOR << std::endl << std::endl;

		std::string s_user_command;
		std::getline(std::cin, s_user_command);

		std::cout << std::endl;

		CMenuItem* pc_selected_item = nullptr;

		const std::string s_help_cmd_start = MC::CMD_HELP + MC::MSG_WHITE_SPACE;;
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

		const std::string s_search_cmd_start = MC::CMD_SEARCH + MC::MSG_WHITE_SPACE;

		if(s_user_command.substr(0, s_search_cmd_start.length()) == s_search_cmd_start)
		{
			std::string s_cmd_to_find = s_user_command.substr(s_search_cmd_start.length());
			std::vector<CMenuItem*> pv_found_items;
			pvInitSearch(pv_found_items, s_cmd_to_find);

			for(int i = 0; i < pv_found_items.size(); i++)
			{
				std::cout << pv_found_items.at(i)->sGetPath() << std::endl;
			}

			std::cout << std::endl;

			if(pv_found_items.size() == 0)
			{
				std::cout << MC::ERR_MSG_CMD_DOES_NOT_EXIST << std::endl << std::endl;
			}
		}
		else if(s_user_command == MC::CMD_SERIALIZE)
		{
			std::cout << sInitSerialize() << std::endl << std::endl;
		}
		else if(s_user_command == MC::CMD_BACK)
		{
			b_back_requested = true;
		}
		else if(s_user_command == MC::CMD_EXIT)
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
				std::cout << MC::ERR_MSG_CMD_DOES_NOT_EXIST << std::endl << std::endl;
			}
		}
		else if(pc_selected_item != nullptr)
		{
			b_exit_not_requested = pc_selected_item->bRun();
		}
		else
		{
			std::cout << MC::ERR_MSG_INVALID_CMD << std::endl;
		}

	} while (!b_back_requested && b_exit_not_requested);

	return b_exit_not_requested;
} // void CMenu::bRun()

std::string CMenu::sGetHiddenCmdHelp()
{
	std::stringstream c_help_msg;
	c_help_msg << MC::MSG_MENU_HIDDEN_CMD_HELP_MSG << std::endl;
	c_help_msg << MC::HELP_MSG_CMD_SEARCH << std::endl;
	c_help_msg << MC::HELP_MSG_CMD_HELP << std::endl;
	c_help_msg << MC::CMD_SERIALIZE << std::endl;
	c_help_msg << MC::CMD_BACK << std::endl;
	c_help_msg << MC::CMD_EXIT << std::endl;
	return c_help_msg.str();
} // std::string CMenu::sGetHiddenCmdHelp()

std::string CMenu::sSerialize()
{
	std::ostringstream c_result;
	c_result << MC::SYMBOL_MENU_OPEN_TAG;

	c_result << MC::SYMBOL_VALUE_OPEN_TAG;
	c_result << sGetName();
	c_result << MC::SYMBOL_VALUE_CLOSE_TAG;

	c_result << MC::SYMBOL_ATTRIBUTE_SEPARATOR;

	c_result << MC::SYMBOL_VALUE_OPEN_TAG;
	c_result << sGetCommand();
	c_result << MC::SYMBOL_VALUE_CLOSE_TAG;

	c_result << MC::SYMBOL_MENU_CHILD_LIST_START;

	if (v_menu_items.size() > 0)
	{
		for (int i = 0; i < v_menu_items.size() - 1; i++)
		{
			c_result << v_menu_items.at(i)->sSerialize();
			c_result << MC::SYMBOL_ATTRIBUTE_SEPARATOR;
		} // for(int i = 0; i + 1 < v_menu_items.size(); i++)

		c_result << v_menu_items.at(v_menu_items.size() - 1)->sSerialize();
	}

	c_result << MC::SYMBOL_MENU_CLOSE_TAG;

	return c_result.str();
} // std::string CMenu::sSerialize()

int CMenu::iDeserialize(std::string & rsInput, int iCurrentPosition, std::string & rsErrorMsg)
{
	CStringHelper c_string_helper;
	if(c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MC::SYMBOL_MENU_OPEN_TAG))
	{
		iCurrentPosition += MC::SYMBOL_MENU_OPEN_TAG.length();

		std::string s_name_read;
		if(!b_get_parse_value(rsInput, iCurrentPosition, s_name_read, rsErrorMsg))
		{
			return std::string::npos;
		}
		
		if(!c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MC::SYMBOL_ATTRIBUTE_SEPARATOR))
		{
			rsErrorMsg = s_construct_parse_error_msg(rsInput, MC::SYMBOL_ATTRIBUTE_SEPARATOR, iCurrentPosition);
			return std::string::npos;
		}

		iCurrentPosition += MC::SYMBOL_ATTRIBUTE_SEPARATOR.length();

		std::string s_cmd_read;
		if (!b_get_parse_value(rsInput, iCurrentPosition, s_cmd_read, rsErrorMsg))
		{
			return std::string::npos;
		}

		if(!c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MC::SYMBOL_MENU_CHILD_LIST_START))
		{
			rsErrorMsg = s_construct_parse_error_msg(rsInput, MC::SYMBOL_MENU_CHILD_LIST_START, iCurrentPosition);
			return std::string::npos;
		}

		s_name = s_name_read;
		s_command = s_cmd_read;
		iCurrentPosition += MC::SYMBOL_MENU_CHILD_LIST_START.length();

		while(!c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MC::SYMBOL_MENU_CLOSE_TAG))
		{
			CMenuItem* pc_new_child = nullptr;
			if(c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MC::SYMBOL_MENU_OPEN_TAG))
			{
				pc_new_child = new CMenu();
			}
			else if(c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MC::SYMBOL_MENU_CMD_OPEN_TAG))
			{
				pc_new_child = pc_make_command();
			}

			if(pc_new_child != nullptr)
			{
				iCurrentPosition = pc_new_child->iDeserialize(rsInput, iCurrentPosition, rsErrorMsg);
				if(iCurrentPosition == std::string::npos)
				{
					delete pc_new_child;
					return std::string::npos;
				}

				pc_new_child->bSetParentItem(this);
				v_menu_items.push_back(pc_new_child);

				if(c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MC::SYMBOL_ATTRIBUTE_SEPARATOR))
				{
					iCurrentPosition += MC::SYMBOL_ATTRIBUTE_SEPARATOR.length();
				}
				else
				{
					std::string s_expected_value = MC::SYMBOL_ATTRIBUTE_SEPARATOR + MC::SYMBOL_VALUE_OPEN_TAG
						+ pc_new_child->sGetCommand() + MC::SYMBOL_VALUE_CLOSE_TAG;
					rsErrorMsg = s_construct_parse_error_msg(rsInput, s_expected_value, iCurrentPosition);
					return std::string::npos;
				}

				std::string s_expected_cmd_value = pc_new_child->sGetCommand();
				bool b_cmd_validation_success = b_validate_child_cmd(rsInput, iCurrentPosition,
					s_expected_cmd_value, rsErrorMsg);

				if(!b_cmd_validation_success)
				{
					return std::string::npos;
				}

				if (c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MC::SYMBOL_ATTRIBUTE_SEPARATOR))
				{
					iCurrentPosition += MC::SYMBOL_ATTRIBUTE_SEPARATOR.length();
				}
			}
			else
			{
				rsErrorMsg = s_construct_parse_error_msg(rsInput, MC::SYMBOL_MENU_CLOSE_TAG, iCurrentPosition);
				return std::string::npos;
			}
		} // while(!c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MC::SYMBOL_MENU_CLOSE_TAG))

		iCurrentPosition += MC::SYMBOL_MENU_CLOSE_TAG.length();
		return iCurrentPosition;
	}
	else
	{
		rsErrorMsg = s_construct_parse_error_msg(rsInput, MC::SYMBOL_MENU_OPEN_TAG, iCurrentPosition);
		return std::string::npos;
	}
} // int CMenu::iDeserialize(std::string & rsInput, int iCurrentPosition, std::string & rsErrorMsg)

void CMenu::vSearch(std::vector<CMenuItem*>& rvFoundItems, const std::string & rsCmdToFind)
{
	if(sGetCommand() == rsCmdToFind)
	{
		rvFoundItems.push_back(this);
	}

	for(int i = 0; i < v_menu_items.size(); i++)
	{
		v_menu_items.at(i)->vSearch(rvFoundItems, rsCmdToFind);
	} // for(int i = 0; i < v_menu_items.size(); i++)
} // void CMenu::vSearch(std::vector<CMenuItem*>* rvFoundItems, const std::string & rsCmdToFind)

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

CMenuItem * CMenu::pc_make_command()
{
	return new CMenuCommand();
} // CMenuItem * CMenu::pc_make_command()

bool CMenu::b_is_restricted_cmd(CMenuItem * pcMenuItem)
{
	bool b_is_restricted = false;

	if(pcMenuItem->sGetCommand() == MC::CMD_SERIALIZE
		||pcMenuItem->sGetCommand() == MC::CMD_BACK
		|| pcMenuItem->sGetCommand() == MC::CMD_EXIT)
	{
		b_is_restricted = true;
	}

	return b_is_restricted;
} // bool CMenu::b_is_restricted_cmd(CMenuItem * pcMenuItem)

bool CMenu::b_check_duplicate(CMenuItem * pcMenuItem)
{
	bool b_is_duplicate = false;

	if (!b_is_restricted_cmd(pcMenuItem))
	{
		for (int i = 0; i < v_menu_items.size() && !b_is_duplicate; i++)
		{
			CMenuItem* pc_current_item = v_menu_items.at(i);

			if (pcMenuItem->sGetName() == pc_current_item->sGetName()
				|| pcMenuItem->sGetCommand() == pc_current_item->sGetCommand()
				|| pcMenuItem->sGetCommand() == MC::CMD_HELP + MC::MSG_WHITE_SPACE + pc_current_item->sGetCommand()
				|| pcMenuItem->sGetCommand() == MC::CMD_SEARCH + MC::MSG_WHITE_SPACE + pc_current_item->sGetCommand())
			{
				b_is_duplicate = true;
			}
		} // for(int i = 0; i < v_menu_items.size() && !b_check_duplicate; i++) 
	}

	return b_is_duplicate;
} // bool CMenu::b_check_duplicate(CMenuItem * pcMenuItem)

std::string CMenu::s_construct_parse_error_msg(std::string sInput, std::string sExpectedValue, int& riCurrentPos)
{
	std::ostringstream c_error_msg;
	c_error_msg << MC::PARSE_ERR_MSG_FAILED_AT;
	c_error_msg << riCurrentPos;
	c_error_msg << MC::PARSE_ERR_MSG_EXPECTED;
	c_error_msg << sExpectedValue;
	c_error_msg << MC::PARSE_ERR_MSG_FOUND;
	c_error_msg << sInput.substr(riCurrentPos, sExpectedValue.length());
	c_error_msg << MC::PARSE_ERR_MSG_INSTEAD;
	return c_error_msg.str();
} // std::string CMenu::s_construct_parse_error_msg(std::string sInput, std::string sExpectedValue, int& riCurrentPos)

bool CMenu::b_get_parse_value(std::string& rsInput, int& riCurrentPosition, std::string& rsResult, std::string& rsErrMsg)
{
	CStringHelper c_string_helper;
	if (c_string_helper.bStartsWith(rsInput.substr(riCurrentPosition), MC::SYMBOL_VALUE_OPEN_TAG))
	{
		riCurrentPosition += MC::SYMBOL_VALUE_OPEN_TAG.length();
		int i_value_close_tag_pos = rsInput.find(MC::SYMBOL_VALUE_CLOSE_TAG, riCurrentPosition);
		if (i_value_close_tag_pos != std::string::npos)
		{
			rsResult = rsInput.substr(riCurrentPosition, i_value_close_tag_pos - riCurrentPosition);
			riCurrentPosition = i_value_close_tag_pos + 1;
			return true;
		}
		else
		{
			std::ostringstream c_error_msg;
			c_error_msg << MC::PARSE_ERR_MSG_FAILED_AT;
			c_error_msg << riCurrentPosition;/*rsInput.substr(riCurrentPosition);*/
			c_error_msg << MC::PARSE_ERR_MSG_MISSING_VALUE_CLOSE_TAG;
			c_error_msg << MC::PARSE_ERR_MSG_EXPECTED;
			c_error_msg << MC::SYMBOL_VALUE_CLOSE_TAG;
			c_error_msg << MC::MSG_APOSTROPHE;
			rsErrMsg = c_error_msg.str();
			riCurrentPosition = std::string::npos;
			return false;
		}
	}
	else
	{
		rsErrMsg = s_construct_parse_error_msg(rsInput, MC::SYMBOL_VALUE_OPEN_TAG,
			riCurrentPosition);
		return false;
	}
} // bool CMenu::b_get_parse_value(std::string& rsInput, int& riCurrentPosition, std::string& rsResult, std::string& rsErrMsg)

bool CMenu::b_validate_child_cmd(std::string & rsInput, int & riCurrentPosition, std::string& rsExpectedValue, std::string & rsErrMsg)
{
	CStringHelper c_string_helper;
	std::string s_cmd_value;
	int i_start_position = riCurrentPosition;
	bool b_success = b_get_parse_value(rsInput, riCurrentPosition, s_cmd_value, rsErrMsg);

	if(b_success)
	{
		if(s_cmd_value != rsExpectedValue)
		{
			b_success = false;
			rsErrMsg = s_construct_parse_error_msg(rsInput, rsExpectedValue, i_start_position);
		}
	}

	return b_success;
}