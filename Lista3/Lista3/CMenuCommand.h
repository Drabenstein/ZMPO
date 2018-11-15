#pragma once
#include "CMenuItem.h"
#include "CCommand.h"

class CMenuCommand : public CMenuItem
{
public:
	CMenuCommand();
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, bool* pbSuccess);
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, CCommand* pcCommand, bool * pbSuccess);
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, bool* pbSuccess);
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CCommand* pcCommand, bool * pbSuccess);

	virtual ~CMenuCommand();

	bool bRun() override;

	std::string sSerialize() override;

	int iDeserialize(std::string& rsInput, int iStartPosition, std::string& rsErrorMsg) override;

	void vSearch(std::vector<CMenuItem*>& rvFoundItems, const std::string& rsCmdToFind) override;

	bool bSetCCommand(CCommand* pcCommand);

	const CCommand* pcGetCCommand();

	static const std::string DEFAULT_NAME;
	static const std::string DEFAULT_CMD;
private:
	CCommand* pc_command;

	std::string s_construct_parse_error_msg(std::string& rsInput, std::string sExpectedValue, int& riCurrentPos);
	bool b_get_parse_value(std::string& rsInput, int& riCurrentPosition, std::string& rsResult, std::string& rsErrMsg);
};
