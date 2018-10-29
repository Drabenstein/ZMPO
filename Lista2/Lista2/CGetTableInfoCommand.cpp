#include "pch.h"
#include "CGetTableInfoCommand.h"
#include "MessageConstants.h"
#include "CConsoleInputHelper.h"

bool CGetTableInfoCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		CConsoleInputHelper c_input_helper;
		int i_table_index;
		if(c_input_helper.bReadTableIndex(&i_table_index) && i_table_index < pv_tables->size())
		{
			b_success = true;
			vSetResponse(psResponseMsg, pv_tables->at(i_table_index)->sToString());
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
} // bool CGetTableInfoCommand::bRunCommand(std::string * psResponseMsg)
