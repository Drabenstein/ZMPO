#pragma once
#include <vector>
#include "CTable.h"
#include "CCTableCommand.h"

class CDeleteTableCommand : public CCTableCommand
{
public:
	CDeleteTableCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string* psResponseMsg) override;
};
