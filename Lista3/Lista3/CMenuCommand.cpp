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

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, bool * bSuccess) : CMenuItem(sName, sCommand, sHelpMsg, pcParentItem, bSuccess)
{
	pc_command = nullptr;
} // CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, bool * bSuccess) : CMenuItem(sName, sCommand, bSuccess)

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, CCommand * pcCommand, bool * bSuccess) : CMenuItem(sName, sCommand, sHelpMsg, pcParentItem, bSuccess)
{
	bool b_command_set_success = bSetCCommand(pcCommand);
	if(bSuccess != nullptr)
	{
		*bSuccess = (*bSuccess) && b_command_set_success;
	}
} // CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CCommand * pcCommand, bool * bSuccess) : CMenuItem(sName, sCommand, bSuccess)

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, bool * bSuccess) : CMenuItem(sName, sCommand, sHelpMsg, nullptr, bSuccess)
{
	pc_command = nullptr;
} // CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, bool * bSuccess)

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CCommand * pcCommand, bool * bSuccess) : CMenuItem(sName, sCommand, sHelpMsg, nullptr, bSuccess)
{
	bool b_command_set_success = bSetCCommand(pcCommand);
	if (bSuccess != nullptr)
	{
		*bSuccess = (*bSuccess) && b_command_set_success;
	}
} // CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CCommand * pcCommand, bool * bSuccess)

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
}

int CMenuCommand::iDeserialize(std::string & sInput, int iCurrentPosition, std::string & sErrorMsg)
{
	CStringHelper c_string_helper;
	if(c_string_helper.bStartsWith(sInput.substr(iCurrentPosition), MenuConstants::SYMBOL_MENU_CMD_OPEN_TAG))
	{
		iCurrentPosition += MenuConstants::SYMBOL_MENU_CMD_OPEN_TAG.length();
		std::string s_name_read;
		if (!b_get_parse_value(sInput, iCurrentPosition, s_name_read, sErrorMsg))
		{
			return std::string::npos;
		}

		if(!c_string_helper.bStartsWith(sInput.substr(iCurrentPosition), MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR))
		{
			sErrorMsg = s_construct_parse_error_msg(sInput, MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR, iCurrentPosition);
			return std::string::npos;
		}

		iCurrentPosition += MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR.length();
		std::string s_cmd_read;
		if (!b_get_parse_value(sInput, iCurrentPosition, s_cmd_read, sErrorMsg))
		{
			return std::string::npos;
		}

		if (!c_string_helper.bStartsWith(sInput.substr(iCurrentPosition), MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR))
		{
			sErrorMsg = s_construct_parse_error_msg(sInput, MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR, iCurrentPosition);
			return std::string::npos;
		}

		iCurrentPosition += MenuConstants::SYMBOL_ATTRIBUTE_SEPARATOR.length();
		std::string s_help_msg_read;
		if (!b_get_parse_value(sInput, iCurrentPosition, s_help_msg_read, sErrorMsg))
		{
			return std::string::npos;
		}

		if(!c_string_helper.bStartsWith(sInput.substr(iCurrentPosition), MenuConstants::SYMBOL_MENU_CMD_CLOSE_TAG))
		{
			sErrorMsg = s_construct_parse_error_msg(sInput, MenuConstants::SYMBOL_MENU_CMD_CLOSE_TAG, iCurrentPosition);
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
		sErrorMsg = s_construct_parse_error_msg(sInput, 
			MenuConstants::SYMBOL_MENU_CMD_OPEN_TAG,
			iCurrentPosition);
		return std::string::npos;
	}
} // int CMenuCommand::iDeserialize(std::string & sInput, int iStartPosition, std::string & sErrorMsg)

void CMenuCommand::vSearch(std::vector<CMenuItem*>* pvFoundItems, const std::string & rsCmdToFind)
{
	if(sGetCommand() == rsCmdToFind)
	{
		pvFoundItems->push_back(this);
	}
} // void CMenuCommand::vSearch(std::vector<CMenuItem*>* pvFoundItems, const std::string & rsCmdToFind)

bool CMenuCommand::bSetCCommand(CCommand * pcCommand)
{
	delete pc_command;
	pc_command = pcCommand;
	return true;
} // bool CMenuCommand::bSetCCommand(CCommand * pcCommand)

const CCommand* CMenuCommand::pcGetCCommand()
{
	return pc_command;
} // const CCommand* CMenuCommand::pcGetCCommand()

std::string CMenuCommand::s_construct_parse_error_msg(std::string& sInput, std::string sExpectedValue, int& iCurrentPos)
{
	std::ostringstream c_error_msg;
	c_error_msg << MenuConstants::PARSE_ERR_MSG_FAILED_AT;
	c_error_msg << iCurrentPos;
	c_error_msg << MenuConstants::PARSE_ERR_MSG_EXPECTED;
	c_error_msg << sExpectedValue;
	c_error_msg << MenuConstants::PARSE_ERR_MSG_FOUND;
	c_error_msg << sInput.substr(iCurrentPos, sExpectedValue.length());
	c_error_msg << MenuConstants::PARSE_ERR_MSG_INSTEAD;
	return c_error_msg.str();
} // std::string CMenuCommand::s_construct_parse_error_msg(std::string & sInput, std::string & sExpectedValue, std::string & sFoundValue)

bool CMenuCommand::b_get_parse_value(std::string& sInput, int& iCurrentPosition, std::string& sResult, std::string& sErrMsg)
{
	if(!sInput.compare(iCurrentPosition, MenuConstants::SYMBOL_VALUE_OPEN_TAG.length(),
		MenuConstants::SYMBOL_VALUE_OPEN_TAG))
	{
		iCurrentPosition += MenuConstants::SYMBOL_VALUE_OPEN_TAG.length();
		int i_value_close_tag_pos = sInput.find(MenuConstants::SYMBOL_VALUE_CLOSE_TAG, iCurrentPosition);
		if (i_value_close_tag_pos != std::string::npos)
		{
			sResult = sInput.substr(iCurrentPosition, i_value_close_tag_pos - iCurrentPosition);
			iCurrentPosition = i_value_close_tag_pos + 1;
			return true;
		}
		else
		{
			/*std::ostringstream c_error_msg;
			c_error_msg << MenuConstants::PARSE_ERR_MSG_FAILED_AT;
			c_error_msg << iCurrentPosition;
			c_error_msg << MenuConstants::PARSE_ERR_MSG_MISSING_VALUE_CLOSE_TAG;
			c_error_msg << MenuConstants::PARSE_ERR_MSG_EXPECTED;
			c_error_msg << MenuConstants::SYMBOL_VALUE_CLOSE_TAG;
			c_error_msg << MenuConstants::MSG_APOSTROPHE;
			sErrMsg = c_error_msg.str();*/
			sErrMsg = s_construct_parse_error_msg(sInput, MenuConstants::SYMBOL_VALUE_CLOSE_TAG, ++iCurrentPosition);
			iCurrentPosition = std::string::npos;
			return false;
		}
	}
	else
	{
		std::string s_found_value = sInput.substr(iCurrentPosition, 
			MenuConstants::SYMBOL_VALUE_OPEN_TAG.length());
		sErrMsg = s_construct_parse_error_msg(sInput, MenuConstants::SYMBOL_VALUE_OPEN_TAG,
			iCurrentPosition);
		return false;
	}
} // std::string CMenuCommand::b_get_parse_value(std::string & sInput, int & iCurrentPosition)
