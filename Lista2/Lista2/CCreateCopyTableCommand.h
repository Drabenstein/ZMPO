#pragma once
#include "CTable.h"
#include <vector>
#include "CCommand.h"

class CCreateCopyTableCommand : public CCommand
{
	public:
	CCreateCopyTableCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string * psResponseMsg) override;

private:
	std::vector<CTable*>* pv_tables;
};
