#pragma once
#include "CCommand.h"
#include <vector>
#include "CTable.h"

class CSetTableLengthCommand : public CCommand
{
public:
	CSetTableLengthCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string* psResponseMsg) override;

private:
	std::vector<CTable*>* pv_tables;
};
