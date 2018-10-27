#pragma once
#include "CTable.h"
#include <vector>
#include "CCommand.h"

class CGetValueCommand : public CCommand
{
public:
	CGetValueCommand(std::vector<CTable*>* pvTables);

	bool bRunCommand(std::string * psResponseMsg) override;

private:
	std::vector<CTable*>* pv_tables;
};
