#pragma once
#include <vector>
#include "CTable.h"
#include "CCTableCommand.h"

class CGetTableNameCommand : public CCTableCommand
{
public:
	CGetTableNameCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string* psResponseMsg) override;
};
