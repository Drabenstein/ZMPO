#pragma once
#include "CMenuItem.h"
#include <vector>
#include "CMenuCommand.h"

class CMenu : public CMenuItem
{
public:
	CMenu();

	CMenu(std::string sName, std::string sCommand, CMenuItem* pcParentItem, bool * bSuccess);

	virtual ~CMenu();

	bool bRun() override;

	std::string sSerialize() override;

	int iDeserialize(std::string& sInput, int iCurrentPosition, std::string& sErrorMsg) override;

	void vSearch(std::vector<CMenuItem*>* pvFoundItems, const std::string& rsCmdToFind) override;

	bool bAddMenuItem(CMenuItem* pcMenuItem);

	const std::vector<CMenuItem*>& pvGetMenuItems();

	bool bRemoveMenuItem(int iOffset);

	std::string sGetMenuHeader();

	static const std::string DEFAULT_NAME;
	static const std::string DEFAULT_CMD;

protected:
	virtual CMenuItem* makeCommand();

private:
	std::vector<CMenuItem*> v_menu_items;

	bool b_check_duplicate(CMenuItem* pcMenuItem);
	std::string s_construct_parse_error_msg(std::string sInput, std::string sExpectedValue, int& iCurrentPos);
	bool b_get_parse_value(std::string& sInput, int& iCurrentPosition, std::string& sResult, std::string& sErrMsg);
};
