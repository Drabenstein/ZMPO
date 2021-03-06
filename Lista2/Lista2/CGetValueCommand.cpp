#include "pch.h"
#include "CGetValueCommand.h"
#include "MessageConstants.h"
#include "CConsoleInputHelper.h"
#include <iostream>
#include <sstream>

bool CGetValueCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		int i_table_index;
		CConsoleInputHelper c_input_helper;

		if(c_input_helper.bReadTableIndex(&i_table_index) && i_table_index < pv_tables->size())
		{
			CTable* pc_selected_table = pv_tables->at(i_table_index);
			int i_value_index;
			if(c_input_helper.bReadValueIndex(&i_value_index) 
				&& i_value_index < pc_selected_table->iGetLength())
			{
				std::stringstream c_output;
				c_output << MessageConstants::MSG_VALUE_GET << pc_selected_table->iGetElement(i_value_index, &b_success);
				vSetResponse(psResponseMsg, c_output.str());
			}
			else
			{
				vSetResponse(psResponseMsg, MessageConstants::ERR_MSG_INVALID_INDEX);
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

	return  b_success;
} // bool CGetValueCommand::bRunCommand(std::string * psResponseMsg)