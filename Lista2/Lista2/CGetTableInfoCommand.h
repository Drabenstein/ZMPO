#pragma once
#include "CCommand.h"
#include <vector>
#include "CTable.h"

class CGetTableInfoCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CGetTableInfoCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string* psResponseMsg) override;
};
