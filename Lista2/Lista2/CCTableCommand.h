#pragma once
#include "CCommand.h"
#include <vector>
#include "CTable.h"

class CCTableCommand : public CCommand
{
protected:
	CCTableCommand(std::vector<CTable*>* pvTables);

	std::vector<CTable*>* pv_tables;
};
