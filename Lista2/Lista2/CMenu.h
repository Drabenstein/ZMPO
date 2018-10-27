#pragma once
#include "CMenuItem.h"
#include <vector>

class CMenu : public CMenuItem
{
private:
	std::vector<CMenuItem*>* pv_menu_items;

public:
	CMenu(std::string sName, std::string sCommand, bool * bSuccess);

	virtual ~CMenu();

	void vRun() override;
	std::string sToString() override;
	virtual std::string sGetCommand() override;
	virtual std::string sGetName() override;
	virtual bool bSetName(std::string sName) override;
	virtual bool bSetCommand(std::string sCommand) override;

	bool bAddMenuItem(CMenuItem* pcMenuItem);

	const std::vector<CMenuItem*>& pvGetMenuItems();

	bool bRemoveMenuItem(int iOffset);

	std::string sGetMenuHeader();
};
