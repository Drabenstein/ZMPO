#pragma once
#include "CCommand.h"
#include <vector>
#include "CTable.h"

class CCloneTableCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CCloneTableCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string* psResponseMsg) override;
};
