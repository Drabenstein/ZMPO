#pragma once
#include "CMenuItem.h"
#include "CCommand.h"

class CMenuCommand : public CMenuItem
{
public:
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, bool* bSuccess);
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, CCommand* pcCommand, bool * bSuccess);
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, bool* bSuccess);
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CCommand* pcCommand, bool * bSuccess);

	virtual ~CMenuCommand();

	bool bRun() override;

	void vSearch(std::vector<CMenuItem*>* pvFoundItems, const std::string& rsCmdToFind) override;

	bool bSetCCommand(CCommand* pcCommand);
	const CCommand* pcGetCCommand();

private:
	CCommand* pc_command;
};
