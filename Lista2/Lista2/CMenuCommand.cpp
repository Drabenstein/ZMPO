#include "pch.h"
#include "CMenuCommand.h"
#include <iostream>
#include <sstream>
#include "MenuConstants.h"

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, bool * bSuccess) : CMenuItem(sName, sCommand, bSuccess)
{
	pc_command = nullptr;
} // CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, bool * bSuccess) : CMenuItem(sName, sCommand, bSuccess)

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, CCommand * pcCommand, bool * bSuccess) : CMenuItem(sName, sCommand, bSuccess)
{
	bool b_command_set_success = bSetCCommand(pcCommand);
	if(bSuccess != nullptr)
	{
		*bSuccess = (*bSuccess) && b_command_set_success;
	}
} // CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, CCommand * pcCommand, bool * bSuccess) : CMenuItem(sName, sCommand, bSuccess)

CMenuCommand::~CMenuCommand()
{
	delete pc_command;
} // CMenuCommand::~CMenuCommand()

void CMenuCommand::vRun()
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
} // void CMenuCommand::vRun()

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

std::string CMenuCommand::sToString()
{
	std::ostringstream c_result;
	c_result << s_name << "(" << s_command << ")";
	return c_result.str();
} // std::string CMenuCommand::sToString()

std::string CMenuCommand::sGetCommand()
{
	return s_command;
} // std::string CMenuCommand::sGetCommand()

std::string CMenuCommand::sGetName()
{
	return s_name;
} // std::string CMenuCommand::sGetName()

bool CMenuCommand::bSetName(std::string sName)
{
	bool b_change_success = false;

	if(sName.length() > 0)
	{
		s_name = sName;
		b_change_success = true;
	}

	return b_change_success;
} // bool CMenuCommand::bSetName(std::string sName)

bool CMenuCommand::bSetCommand(std::string sCommand)
{
	bool b_change_success = false;

	if(sCommand.length() > 0)
	{
		s_command = sCommand;
		b_change_success = true;
	}

	return b_change_success;
} // bool CMenuCommand::bSetCommand(std::string sCommand)