#pragma once
#include "CMenuItem.h"
#include <vector>
#include "CMenuCommand.h"

class CMenu : public CMenuItem
{
public:
	CMenu(std::string sName, std::string sCommand, CMenuItem* pcParentItem, bool * bSuccess);

	virtual ~CMenu();

	bool bRun() override;

	void vSearch(std::vector<CMenuItem*>* pvFoundItems, const std::string& rsCmdToFind) override;

	bool bAddMenuItem(CMenuItem* pcMenuItem);

	const std::vector<CMenuItem*>& pvGetMenuItems();

	bool bRemoveMenuItem(int iOffset);

	std::string sGetMenuHeader();

private:
	std::vector<CMenuItem*> v_menu_items;

	bool b_check_duplicate(CMenuItem* pcMenuItem);
};
