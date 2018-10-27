#pragma once
#include "CTable.h"
#include <vector>
#include "CCommand.h"

class CCreateParameterTableCommand : public CCommand
{
public:
	CCreateParameterTableCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string * psResponseMsg) override;

private:
	std::vector<CTable*>* pv_tables;
};
