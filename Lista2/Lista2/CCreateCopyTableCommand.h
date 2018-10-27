#pragma once
#include "CTable.h"
#include <vector>
#include "CCommand.h"

class CCreateCopyTableCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CCreateCopyTableCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string * psResponseMsg) override;
};
