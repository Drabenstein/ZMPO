#pragma once
#include "CCommand.h"
#include <vector>
#include "CTable.h"

class CGetTableLengthCommand : public CCommand
{
public:
	CGetTableLengthCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string* psResponseMsg) override;

private:
	std::vector<CTable*>* pv_tables;
};
