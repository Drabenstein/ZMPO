#pragma once
#include "CTable.h"
#include <vector>
#include "CCTableCommand.h"

class CCreateParameterTableCommand : public CCTableCommand
{
public:
	CCreateParameterTableCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string * psResponseMsg) override;
};
