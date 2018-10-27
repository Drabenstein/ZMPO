#include "pch.h"
#include "CCreateCopyTableCommand.h"
#include "CConsoleInputHelper.h"
#include "CTableConstants.h"
#include <sstream>

CCreateCopyTableCommand::CCreateCopyTableCommand(std::vector<CTable*>* pvTables)
{
	pv_tables = pvTables;
}

bool CCreateCopyTableCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		int i_table_index;
		CConsoleInputHelper c_input_helper;
		if(c_input_helper.bReadTableIndex(&i_table_index) && i_table_index < pv_tables->size())
		{
			CTable* pc_table_copy = new CTable(*(pv_tables->at(i_table_index)));
			pv_tables->push_back(pc_table_copy);
			b_success = true;
			std::stringstream c_output;
			c_output << CTableConstants::MSG_TABLE_COPY_CREATED << pv_tables->size() - 1;
			vSetResponse(psResponseMsg, c_output.str());
		}
		else 
		{
			vSetResponse(psResponseMsg, CTableConstants::ERR_MSG_INVALID_INDEX);
		}
	}
	else
	{
		vSetResponse(psResponseMsg, CTableConstants::ERR_MSG_TABLES_VECTOR_UNINITIALIZED);
	}

	return b_success;
}
