#pragma once
#include "CMenu.h"

class CMenuManager
{
public:
	CMenuManager();

	~CMenuManager();

	bool bRun();

private:
	CMenu* pc_root_menu;
};
