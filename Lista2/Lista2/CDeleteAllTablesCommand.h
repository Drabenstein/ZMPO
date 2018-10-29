#pragma once
#include <vector>
#include "CTable.h"
#include "CCTableCommand.h"

class CDeleteAllTablesCommand : public CCTableCommand
{
public:
	CDeleteAllTablesCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string* psResponseMsg) override;
};
