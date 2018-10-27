#pragma once
#include "CCommand.h"
#include "CTable.h"
#include <vector>

class CSetValueCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CSetValueCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string* psResponseMsg) override;
};
