#pragma once
#include "CTable.h"
#include <vector>
#include "CCTableCommand.h"

class CGetValueCommand : public CCTableCommand
{
public:
	CGetValueCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string * psResponseMsg) override;
};
