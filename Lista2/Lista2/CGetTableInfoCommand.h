#pragma once
#include "CCTableCommand.h"
#include <vector>
#include "CTable.h"

class CGetTableInfoCommand : public CCTableCommand
{
public:
	CGetTableInfoCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string* psResponseMsg) override;
};
