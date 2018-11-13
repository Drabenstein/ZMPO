#pragma once
#include "CMenuItem.h"
#include "CCommand.h"

class CMenuCommand : public CMenuItem
{
public:
	CMenuCommand();
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, bool* bSuccess);
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CMenuItem* pcParentItem, CCommand* pcCommand, bool * bSuccess);
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, bool* bSuccess);
	CMenuCommand(std::string sName, std::string sCommand, std::string sHelpMsg, CCommand* pcCommand, bool * bSuccess);

	virtual ~CMenuCommand();

	bool bRun() override;

	std::string sSerialize() override;

	int iDeserialize(std::string& sInput, int iStartPosition, std::string& sErrorMsg) override;

	void vSearch(std::vector<CMenuItem*>& rvFoundItems, const std::string& rsCmdToFind) override;

	bool bSetCCommand(CCommand* pcCommand);

	const CCommand* pcGetCCommand();

	static const std::string DEFAULT_NAME;
	static const std::string DEFAULT_CMD;
private:
	CCommand* pc_command;

	std::string s_construct_parse_error_msg(std::string& sInput, std::string sExpectedValue, int& iCurrentPos);
	bool b_get_parse_value(std::string& sInput, int& iCurrentPosition, std::string& sResult, std::string& sErrMsg);
};
