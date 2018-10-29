#include "pch.h"
#include "CSetTableLengthCommand.h"
#include "MessageConstants.h"
#include "CConsoleInputHelper.h"
#include <sstream>

bool CSetTableLengthCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		CConsoleInputHelper c_input_helper;
		int i_table_index;
		if(c_input_helper.bReadTableIndex(&i_table_index) && i_table_index >= 0
			&& i_table_index < pv_tables->size())
		{
			CTable* pc_selected_table = pv_tables->at(i_table_index);
			int i_new_length;
			if(c_input_helper.bReadTableLength(&i_new_length))
			{
				b_success = pc_selected_table->bSetTableLength(i_new_length);
				std::stringstream c_output;
				c_output << MessageConstants::MSG_TABLE_LENGTH_CHANGED << i_new_length;
				vSetResponse(psResponseMsg, c_output.str());
			}
			else
			{
				vSetResponse(psResponseMsg, MessageConstants::ERR_MSG_INVALID_LENGTH);
			}
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
} // bool CSetTableLengthCommand::bRunCommand(std::string * psResponseMsg)
