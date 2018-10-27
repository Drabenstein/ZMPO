#include "pch.h"
#include "CMenuItem.h"

CMenuItem::CMenuItem(std::string sName, std::string sCommand, bool * bSuccess)
{
	s_name = sName;
	s_command = sCommand;
	if (bSuccess != nullptr)
	{
		*bSuccess = s_command.length() > 0;
	}
} // CMenuItem::CMenuItem(std::string sName, std::string sCommand, bool * bSuccess)
