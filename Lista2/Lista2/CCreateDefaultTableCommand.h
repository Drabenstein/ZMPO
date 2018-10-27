#pragma once
#include "CCommand.h"
#include "CTable.h"
#include <vector>

class CCreateDefaultTableCommand : public CCommand
{
public:
	CCreateDefaultTableCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string * psResponseMsg) override;

private:
	std::vector<CTable*>* pv_tables;
};
