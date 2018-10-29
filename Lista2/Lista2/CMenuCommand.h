#pragma once
#include "CMenuItem.h"
#include "CCommand.h"

class CMenuCommand : public CMenuItem
{
private:
	CCommand* pc_command;

public:
	CMenuCommand(std::string sName, std::string sCommand, bool* bSuccess);
	CMenuCommand(std::string sName, std::string sCommand, CCommand* pcCommand, bool * bSuccess);

	virtual ~CMenuCommand();

	bool bRun() override;

	bool bSetCCommand(CCommand* pcCommand);
	const CCommand* pcGetCCommand();

	virtual std::string sToString() override;
	virtual std::string sGetCommand() override;
	virtual std::string sGetName() override;
	virtual bool bSetName(std::string sName) override;
	virtual bool bSetCommand(std::string sCommand) override;
};
