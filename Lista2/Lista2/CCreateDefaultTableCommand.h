#pragma once
#include "CCommand.h"
#include "CTable.h"
#include <vector>

class CCreateDefaultTableCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CCreateDefaultTableCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string * psResponseMsg) override;
};
