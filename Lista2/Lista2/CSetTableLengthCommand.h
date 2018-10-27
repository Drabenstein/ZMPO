#pragma once
#include "CCommand.h"
#include <vector>
#include "CTable.h"

class CSetTableLengthCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CSetTableLengthCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string* psResponseMsg) override;
};
