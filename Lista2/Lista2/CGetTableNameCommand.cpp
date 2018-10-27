#include "pch.h"
#include "CGetTableNameCommand.h"
#include "MessageConstants.h"
#include "CConsoleInputHelper.h"
#include <sstream>

CGetTableNameCommand::CGetTableNameCommand(std::vector<CTable*>* pvTables)
{
	pv_tables = pvTables;
} // CGetTableNameCommand::CGetTableNameCommand(std::vector<CTable*>* pvTables)

bool CGetTableNameCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		CConsoleInputHelper c_input_helper;
		int i_table_index;
		if(c_input_helper.bReadTableIndex(&i_table_index) && i_table_index < pv_tables->size())
		{
			b_success = true;
			std::stringstream c_output;
			c_output << MessageConstants::MSG_TABLE_NAME << pv_tables->at(i_table_index)->sGetName();
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
} // bool CGetTableNameCommand::bRunCommand(std::string * psResponseMsg)
