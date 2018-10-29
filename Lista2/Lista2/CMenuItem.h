#pragma once
#include <string>

class CMenuItem
{
public:
	virtual ~CMenuItem() {}

	virtual bool bRun() = 0;

	virtual std::string sToString() = 0;

	virtual std::string sGetCommand() = 0;

	virtual std::string sGetName() = 0;

	virtual bool bSetName(std::string sName) = 0;

	virtual bool bSetCommand(std::string sCommand) = 0;

protected:
	CMenuItem(std::string sCommand, std::string sName, bool * bSuccess);
	CMenuItem() {};

	std::string s_command;
	std::string s_name;
};
