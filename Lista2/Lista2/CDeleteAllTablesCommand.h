#pragma once
#include "CCommand.h"
#include <vector>
#include "CTable.h"

class CDeleteAllTablesCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CDeleteAllTablesCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string* psResponseMsg) override;
};
