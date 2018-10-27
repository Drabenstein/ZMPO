#include "pch.h"
#include "CCreateDefaultTableCommand.h"
#include "CTableConstants.h"
#include <sstream>

CCreateDefaultTableCommand::CCreateDefaultTableCommand(std::vector<CTable*>* pvTables)
{
	pv_tables = pvTables;
} // CCreateDefaultTableCommand::CCreateDefaultTableCommand(std::vector<CTable*>* pvTables)

bool CCreateDefaultTableCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if (pv_tables != nullptr)
	{
		CTable* pc_default_table = new CTable;
		pv_tables->push_back(pc_default_table);
		b_success = true;
		std::stringstream c_output;
		c_output << CTableConstants::MSG_DEFAULT_TABLE_CREATED << pv_tables->size() - 1;
		vSetResponse(psResponseMsg , c_output.str());
	}
	else
	{
		vSetResponse(psResponseMsg, CTableConstants::ERR_MSG_TABLES_VECTOR_UNINITIALIZED);
	}

	return b_success;
}
