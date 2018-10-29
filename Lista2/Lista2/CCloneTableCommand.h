#pragma once
#include <vector>
#include "CTable.h"
#include "CCTableCommand.h"

class CCloneTableCommand : public CCTableCommand
{
public:
	CCloneTableCommand(std::vector<CTable*>* pvTables) : CCTableCommand(pvTables) {};

	bool bRunCommand(std::string* psResponseMsg) override;
};
