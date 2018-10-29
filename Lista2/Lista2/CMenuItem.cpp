#include "pch.h"
#include "CMenuItem.h"
#include "MenuConstants.h"
#include <sstream>

CMenuItem::CMenuItem(std::string sName, std::string sCommand, bool * bSuccess)
{
	s_name = sName;
	s_command = sCommand;
	if (bSuccess != nullptr)
	{
		*bSuccess = s_command.length() > 0;
	}
} // CMenuItem::CMenuItem(std::string sName, std::string sCommand, bool * bSuccess)

std::string CMenuItem::sToString()
{
	std::ostringstream c_result;
	c_result << s_name << MenuConstants::MSG_TAG_OPEN_CMD << s_command << MenuConstants::MSG_TAG_CLOSE_CMD;
	return c_result.str();
} // std::string CMenuItem::sToString()

std::string CMenuItem::sGetCommand()
{
	return s_command;
} // std::string CMenuItem::sGetCommand()

std::string CMenuItem::sGetName()
{
	return s_name;
} // std::string CMenuItem::sGetName()

bool CMenuItem::bSetName(std::string sName)
{
	bool b_change_success = false;

	if(sName.length() > 0)
	{
		s_name = sName;
		b_change_success = true;
	}

	return b_change_success;
} // bool CMenuItem::bSetName(std::string sName)

bool CMenuItem::bSetCommand(std::string sCommand)
{
	bool b_change_success = false;

	if(sCommand.length() > 0)
	{
		s_command = sCommand;
		b_change_success = true;
	}

	return b_change_success;
} // bool CMenuItem::bSetCommand(std::string sCommand)
