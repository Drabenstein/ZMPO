#pragma once
#include "CCommand.h"
#include <vector>
#include "CTable.h"

class CGetTableNameCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CGetTableNameCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string* psResponseMsg) override;
};
