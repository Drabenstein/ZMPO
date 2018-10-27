#include "pch.h"
#include "CCloneTableCommand.h"
#include "MessageConstants.h"
#include "CConsoleInputHelper.h"
#include <sstream>

CCloneTableCommand::CCloneTableCommand(std::vector<CTable*>* pvTables)
{
	pv_tables = pvTables;
}

bool CCloneTableCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		CConsoleInputHelper c_input_helper;
		int i_table_index;
		if(c_input_helper.bReadTableIndex(&i_table_index) 
			&& i_table_index < pv_tables->size())
		{
			CTable* pc_cloned_table = pv_tables->at(i_table_index)->cClone(&b_success);
			pv_tables->push_back(pc_cloned_table);
			std::stringstream c_output;
			c_output << MessageConstants::MSG_TABLE_CLONED << pv_tables->size() - 1;
			vSetResponse(psResponseMsg, c_output.str());
		}
		else
		{
			vSetResponse(psResponseMsg, MessageConstants::ERR_MSG_INVALID_INDEX);
		}
	}
	else
	{
		vSetResponse(psResponseMsg, MessageConstants::ERR_MSG_TABLES_VECTOR_UNINITIALIZED);
	}

	return b_success;
}
