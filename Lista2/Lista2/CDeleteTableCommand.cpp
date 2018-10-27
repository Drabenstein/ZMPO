#include "pch.h"
#include "CDeleteTableCommand.h"
#include "MessageConstants.h"
#include "CConsoleInputHelper.h"
#include <sstream>

CDeleteTableCommand::CDeleteTableCommand(std::vector<CTable*>* pvTables)
{
	pv_tables = pvTables;
}

bool CDeleteTableCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		CConsoleInputHelper c_input_helper;
		int i_table_to_delete_index;
		if(c_input_helper.bReadTableIndex(&i_table_to_delete_index) 
			&& i_table_to_delete_index < pv_tables->size())
		{
			delete pv_tables->at(i_table_to_delete_index);
			pv_tables->erase(pv_tables->begin() + i_table_to_delete_index);
			b_success = true;
			std::stringstream c_output;
			c_output << MessageConstants::MSG_TABLE_DELETED << MessageConstants::MSG_AT_INDEX
				<< i_table_to_delete_index;
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
