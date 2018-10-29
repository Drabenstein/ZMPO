#pragma once
#include "CCTableCommand.h"
#include "CTable.h"
#include <vector>

class CSetValueCommand : public CCTableCommand
{
public:
	CSetValueCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string* psResponseMsg) override;
};
