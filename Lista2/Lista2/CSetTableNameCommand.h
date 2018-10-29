#pragma once
#include <vector>
#include "CTable.h"
#include "CCTableCommand.h"

class CSetTableNameCommand : public CCTableCommand
{
public:
	CSetTableNameCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string* psResponseMsg) override;
};
