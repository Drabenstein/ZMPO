#pragma once
#include "CTable.h"
#include <vector>
#include "CCommand.h"

class CCreateParameterTableCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CCreateParameterTableCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string * psResponseMsg) override;
};
