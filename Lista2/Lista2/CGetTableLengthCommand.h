#pragma once
#include "CCTableCommand.h"
#include <vector>
#include "CTable.h"

class CGetTableLengthCommand : public CCTableCommand
{
public:
	CGetTableLengthCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {}

	bool bRunCommand(std::string* psResponseMsg) override;
};
