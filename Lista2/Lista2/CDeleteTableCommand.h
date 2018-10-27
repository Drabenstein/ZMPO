#pragma once
#include "CCommand.h"
#include <vector>
#include "CTable.h"

class CDeleteTableCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CDeleteTableCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string* psResponseMsg) override;
};
