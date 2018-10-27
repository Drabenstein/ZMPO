#pragma once
#include "CTable.h"
#include <vector>
#include "CCommand.h"

class CGetValueCommand : public CCommand
{
private:
	std::vector<CTable*>* pv_tables;

public:
	CGetValueCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string * psResponseMsg) override;
};
