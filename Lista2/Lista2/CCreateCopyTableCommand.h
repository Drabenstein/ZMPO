#pragma once
#include "CTable.h"
#include <vector>
#include "CCTableCommand.h"

class CCreateCopyTableCommand : public CCTableCommand
{
public:
	CCreateCopyTableCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string * psResponseMsg) override;
};
