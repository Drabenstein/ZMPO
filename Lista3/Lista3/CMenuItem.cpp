#include "pch.h"
#include "CMenuItem.h"
#include "MenuConstants.h"
#include <sstream>

CMenuItem::CMenuItem(std::string sName, std::string sCommand, CMenuItem* pcParentItem, bool * bSuccess)
{
	s_name = sName;
	s_command = sCommand;
	pc_parent_item = pcParentItem;
	s_help_msg = std::string();
	if (bSuccess != nullptr)
	{
		*bSuccess = s_command.length() > 0;
	}
} // CMenuItem::CMenuItem(std::string sName, std::string sCommand, bool * bSuccess)

CMenuItem::CMenuItem(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem * pcParentItem, bool * bSuccess)
{
	s_name = sName;
	s_command = sCommand;
	pc_parent_item = pcParentItem;
	s_help_msg = sHelpMsg;
	if (bSuccess != nullptr)
	{
		*bSuccess = s_command.length() > 0;
	}
} // CMenuItem::CMenuItem(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem * pcParentItem, bool * bSuccess)

std::string CMenuItem::sGetHelp()
{
	return s_help_msg;
} // std::string CMenuItem::sGetHelp()

std::string CMenuItem::sToString()
{
	std::ostringstream c_result;
	c_result << s_name << MenuConstants::MSG_WHITE_SPACE 
		<< MenuConstants::MSG_TAG_OPEN_CMD << s_command << MenuConstants::MSG_TAG_CLOSE_CMD;
	return c_result.str();
} // std::string CMenuItem::sToString()

std::string CMenuItem::sInitSerialize()
{
	if(pc_parent_item != nullptr)
	{
		return pc_parent_item->sInitSerialize();
	}
	else
	{
		return sSerialize();
	}
}

void CMenuItem::pvInitSearch(std::vector<CMenuItem*>& rvFoundItems, std::string& rsCmdToFind)
{
	if(pc_parent_item != nullptr)
	{
		pc_parent_item->pvInitSearch(rvFoundItems, rsCmdToFind);
	}
	else
	{
		vSearch(rvFoundItems, rsCmdToFind);
	}
} // std::vector<CMenuItem*>* CMenuItem::pvInitSearch()

std::string CMenuItem::sGetPath()
{
	if(pc_parent_item != nullptr)
	{
		return pc_parent_item->sGetPath() + MenuConstants::MSG_PATH_SEPARATOR + sGetCommand();
	}
	else
	{
		return sGetName();
	}
} // std::string CMenuItem::sGetPath()

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

void CMenuItem::bSetParentItem(CMenuItem * pcParentItem)
{
	pc_parent_item = pcParentItem;
} // void CMenuItem::bSetParentItem(CMenuItem * pcParentItem)

CMenuItem * CMenuItem::pcGetParentItem()
{
	return pc_parent_item;
} // CMenuItem * CMenuItem::pcGetParentItem()
