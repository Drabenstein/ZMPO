#pragma once
#include "CTable.h"
#include <vector>
#include "CCTableCommand.h"

class CCreateDefaultTableCommand : public CCTableCommand
{
public:
	CCreateDefaultTableCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string * psResponseMsg) override;
};
