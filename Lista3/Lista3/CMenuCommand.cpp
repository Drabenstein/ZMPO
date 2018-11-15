#include "pch.h"
#include "CMenuCommand.h"
#include <iostream>
#include <sstream>
#include "MenuConstants.h"
#include "CStringHelper.h"

const std::string CMenuCommand::DEFAULT_NAME = "Default Cmd";
const std::string CMenuCommand::DEFAULT_CMD = "DefaultCmd";

CMenuCommand::CMenuCommand() : CMenuItem(DEFAULT_NAME, DEFAULT_CMD, nullptr, nullptr)
{
	pc_command = nullptr;
} // CMenuCommand::CMenuCommand()

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, bool * pbSuccess) : CMenuItem(sName, sCommand, sHelpMsg, pcParentItem, pbSuccess)
{
	pc_command = nullptr;
} // CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, bool * pbSuccess) : CMenuItem(sName, sCommand, pbSuccess)

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, CCommand * pcCommand, bool * pbSuccess) : CMenuItem(sName, sCommand, sHelpMsg, pcParentItem, pbSuccess)
{
	bool b_command_set_success = bSetCCommand(pcCommand);
	if(pbSuccess != nullptr)
	{
		*pbSuccess = (*pbSuccess) && b_command_set_success;
	}
} // CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CCommand * pcCommand, bool * pbSuccess) : CMenuItem(sName, sCommand, pbSuccess)

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, bool * pbSuccess) : CMenuItem(sName, sCommand, sHelpMsg, nullptr, pbSuccess)
{
	pc_command = nullptr;
} // CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, bool * pbSuccess)

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CCommand * pcCommand, bool * pbSuccess) : CMenuItem(sName, sCommand, sHelpMsg, nullptr, pbSuccess)
{
	bool b_command_set_success = bSetCCommand(pcCommand);
	if (pbSuccess != nullptr)
	{
		*pbSuccess = (*pbSuccess) && b_command_set_success;
	}
} // CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CCommand * pcCommand, bool * pbSuccess)

CMenuCommand::~CMenuCommand()
{
	delete pc_command;
} // CMenuCommand::~CMenuCommand()

bool CMenuCommand::bRun()
{
	if(pc_command != nullptr)
	{
		std::string s_response_msg;
		bool b_success = pc_command->bRunCommand(&s_response_msg);

		std::cout << std::endl << s_response_msg << std::endl;
		std::cout << (b_success ? MenuConstants::MSG_CMD_COMPLETED : MenuConstants::ERR_MSG_CMD_FAILED);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::cout << MenuConstants::MSG_EMPTY_CMD << std::endl << std::endl;
	}

	return true;
} // void CMenuCommand::bRun()

std::string CMenuCommand::sSerialize()
{
	std::ostringstream c_result;

	c_result << MenuConstants::SYMBOL_MENU_CMD_OPEN_TAG;

	c_result << MenuConstants::SYMBOL_VALUE_OPEN_TAG;
	c_result << sGetName();
	c_result << MenuConstants::SYMBOL_VALUE_CLOSE_TAG;

	c_result << MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR;

	c_result << MenuConstants::SYMBOL_VALUE_OPEN_TAG;
	c_result << sGetCommand();
	c_result << MenuConstants::SYMBOL_VALUE_CLOSE_TAG;

	c_result << MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR;

	c_result << MenuConstants::SYMBOL_VALUE_OPEN_TAG;
	c_result << sGetHelp();
	c_result << MenuConstants::SYMBOL_VALUE_CLOSE_TAG;

	c_result << MenuConstants::SYMBOL_MENU_CMD_CLOSE_TAG;

	return c_result.str();
} // std::string CMenuCommand::sSerialize()

int CMenuCommand::iDeserialize(std::string & rsInput, int iCurrentPosition, std::string & rsErrorMsg)
{
	CStringHelper c_string_helper;
	if(c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MenuConstants::SYMBOL_MENU_CMD_OPEN_TAG))
	{
		iCurrentPosition += MenuConstants::SYMBOL_MENU_CMD_OPEN_TAG.length();
		std::string s_name_read;
		if (!b_get_parse_value(rsInput, iCurrentPosition, s_name_read, rsErrorMsg))
		{
			return std::string::npos;
		}

		if(!c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR))
		{
			rsErrorMsg = s_construct_parse_error_msg(rsInput, MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR, iCurrentPosition);
			return std::string::npos;
		}

		iCurrentPosition += MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR.length();
		std::string s_cmd_read;
		if (!b_get_parse_value(rsInput, iCurrentPosition, s_cmd_read, rsErrorMsg))
		{
			return std::string::npos;
		}

		if (!c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR))
		{
			rsErrorMsg = s_construct_parse_error_msg(rsInput, MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR, iCurrentPosition);
			return std::string::npos;
		}

		iCurrentPosition += MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR.length();
		std::string s_help_msg_read;
		if (!b_get_parse_value(rsInput, iCurrentPosition, s_help_msg_read, rsErrorMsg))
		{
			return std::string::npos;
		}

		if(!c_string_helper.bStartsWith(rsInput.substr(iCurrentPosition), MenuConstants::SYMBOL_MENU_CMD_CLOSE_TAG))
		{
			rsErrorMsg = s_construct_parse_error_msg(rsInput, MenuConstants::SYMBOL_MENU_CMD_CLOSE_TAG, iCurrentPosition);
			return std::string::npos;
		}

		iCurrentPosition += MenuConstants::SYMBOL_MENU_CMD_CLOSE_TAG.length();

		s_name = s_name_read;
		s_command = s_cmd_read;
		s_help_msg = s_help_msg_read;
		return iCurrentPosition;
	}
	else
	{
		rsErrorMsg = s_construct_parse_error_msg(rsInput, 
			MenuConstants::SYMBOL_MENU_CMD_OPEN_TAG,
			iCurrentPosition);
		return std::string::npos;
	}
} // int CMenuCommand::iDeserialize(std::string & rsInput, int iCurrentPosition, std::string & rsErrorMsg)

void CMenuCommand::vSearch(std::vector<CMenuItem*>& pvFoundItems, const std::string & rsCmdToFind)
{
	if(sGetCommand() == rsCmdToFind)
	{
		pvFoundItems.push_back(this);
	}
} // void CMenuCommand::vSearch(std::vector<CMenuItem*>* pvFoundItems, const std::string & rsCmdToFind)

bool CMenuCommand::bSetCCommand(CCommand * pcCommand)
{
	if (pc_command != nullptr)
	{
		delete pc_command;
	}
	pc_command = pcCommand;
	return true;
} // bool CMenuCommand::bSetCCommand(CCommand * pcCommand)

const CCommand* CMenuCommand::pcGetCCommand()
{
	return pc_command;
} // const CCommand* CMenuCommand::pcGetCCommand()

std::string CMenuCommand::s_construct_parse_error_msg(std::string& rsInput, std::string sExpectedValue, int& riCurrentPos)
{
	std::ostringstream c_error_msg;
	c_error_msg << MenuConstants::PARSE_ERR_MSG_FAILED_AT;
	c_error_msg << riCurrentPos;
	c_error_msg << MenuConstants::PARSE_ERR_MSG_EXPECTED;
	c_error_msg << sExpectedValue;
	c_error_msg << MenuConstants::PARSE_ERR_MSG_FOUND;
	c_error_msg << rsInput.substr(riCurrentPos, sExpectedValue.length());
	c_error_msg << MenuConstants::PARSE_ERR_MSG_INSTEAD;
	return c_error_msg.str();
} // std::string CMenuCommand::s_construct_parse_error_msg(std::string& rsInput, std::string sExpectedValue, int& riCurrentPos)

bool CMenuCommand::b_get_parse_value(std::string& rsInput, int& riCurrentPosition, std::string& rsResult, std::string& rsErrMsg)
{
	if(!rsInput.compare(riCurrentPosition, MenuConstants::SYMBOL_VALUE_OPEN_TAG.length(),
		MenuConstants::SYMBOL_VALUE_OPEN_TAG))
	{
		riCurrentPosition += MenuConstants::SYMBOL_VALUE_OPEN_TAG.length();
		int i_value_close_tag_pos = rsInput.find(MenuConstants::SYMBOL_VALUE_CLOSE_TAG, riCurrentPosition);
		if (i_value_close_tag_pos != std::string::npos)
		{
			rsResult = rsInput.substr(riCurrentPosition, i_value_close_tag_pos - riCurrentPosition);
			riCurrentPosition = i_value_close_tag_pos + 1;
			return true;
		}
		else
		{
			/*std::ostringstream c_error_msg;
			c_error_msg << MenuConstants::PARSE_ERR_MSG_FAILED_AT;
			c_error_msg << riCurrentPosition;
			c_error_msg << MenuConstants::PARSE_ERR_MSG_MISSING_VALUE_CLOSE_TAG;
			c_error_msg << MenuConstants::PARSE_ERR_MSG_EXPECTED;
			c_error_msg << MenuConstants::SYMBOL_VALUE_CLOSE_TAG;
			c_error_msg << MenuConstants::MSG_APOSTROPHE;
			rsErrMsg = c_error_msg.str();*/
			rsErrMsg = s_construct_parse_error_msg(rsInput, MenuConstants::SYMBOL_VALUE_CLOSE_TAG, ++riCurrentPosition);
			riCurrentPosition = std::string::npos;
			return false;
		}
	}
	else
	{
		std::string s_found_value = rsInput.substr(riCurrentPosition, 
			MenuConstants::SYMBOL_VALUE_OPEN_TAG.length());
		rsErrMsg = s_construct_parse_error_msg(rsInput, MenuConstants::SYMBOL_VALUE_OPEN_TAG,
			riCurrentPosition);
		return false;
	}
} // bool CMenuCommand::b_get_parse_value(std::string& rsInput, int& riCurrentPosition, std::string& rsResult, std::string& rsErrMsg)
