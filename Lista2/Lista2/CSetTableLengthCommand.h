#pragma once
#include "CCTableCommand.h"
#include <vector>
#include "CTable.h"

class CSetTableLengthCommand : public CCTableCommand
{
public:
	CSetTableLengthCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string* psResponseMsg) override;
};
