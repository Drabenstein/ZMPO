#pragma once
#include <string>

class CMenuItem
{
public:
	virtual ~CMenuItem() {}

	virtual bool bRun() = 0;

	virtual std::string sToString();

	std::string sGetCommand();

	std::string sGetName();

	bool bSetName(std::string sName);

	bool bSetCommand(std::string sCommand);

protected:
	CMenuItem(std::string sName, std::string sCommand, bool * bSuccess);
	CMenuItem() {};

	std::string s_command;
	std::string s_name;
};
