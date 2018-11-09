#include "pch.h"
#include "CMenuCommand.h"
#include <iostream>
#include <sstream>
#include "MenuConstants.h"

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