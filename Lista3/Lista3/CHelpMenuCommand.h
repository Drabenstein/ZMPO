#pragma once
#include "CMenuItem.h"

class CHelpMenuCommand : public CMenuItem
{
public:
	CHelpMenuCommand(CMenuItem* pcConnectedItem, CMenuItem* pcParentItem, bool* bSuccess);

private:
	CMenuItem* pc_connected_item;
};
