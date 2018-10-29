#pragma once
#include "CMenuItem.h"
#include <vector>

class CMenu : public CMenuItem
{
private:
	std::vector<CMenuItem*> v_menu_items;

public:
	CMenu(std::string sName, std::string sCommand, bool * bSuccess);

	virtual ~CMenu();

	bool bRun() override;

	bool bAddMenuItem(CMenuItem* pcMenuItem);

	const std::vector<CMenuItem*>& pvGetMenuItems();

	bool bRemoveMenuItem(int iOffset);

	std::string sGetMenuHeader();
};
