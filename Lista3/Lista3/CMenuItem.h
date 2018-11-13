#pragma once
#include <string>
#include <vector>

class CMenuItem
{
public:
	virtual ~CMenuItem() {}

	virtual bool bRun() = 0;

	virtual std::string sGetHelp();

	virtual std::string sToString();

	virtual std::string sSerialize() = 0;

	virtual int iDeserialize(std::string& sInput, int iCurrentPosition, std::string& sErrorMsg) = 0;

	virtual void vSearch(std::vector<CMenuItem*>* pvFoundItems, const std::string& rsCmdToFind) = 0;

	std::vector<CMenuItem*>* pvInitSearch(std::string& rsCmdToFind);

	std::string sGetPath();

	std::string sGetCommand();

	std::string sGetName();

	bool bSetName(std::string sName);

	bool bSetCommand(std::string sCommand);

	void bSetParentItem(CMenuItem* pcParentItem);

	CMenuItem* pcGetParentItem();

protected:
	CMenuItem(std::string sName, std::string sCommand, CMenuItem* pcParentItem, bool * bSuccess);
	CMenuItem(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, bool * bSuccess);
	CMenuItem() {}

	std::string s_command;
	std::string s_name;
	std::string s_help_msg;
	CMenuItem* pc_parent_item;
};
