#pragma once
#include "CCommand.h"
#include <vector>
#include "CTable.h"

class CGetTableLengthCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CGetTableLengthCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string* psResponseMsg) override;
};
