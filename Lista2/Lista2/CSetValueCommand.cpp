#include "pch.h"
#include "CSetValueCommand.h"
#include "MessageConstants.h"
#include "CConsoleInputHelper.h"
#include <sstream>

CSetValueCommand::CSetValueCommand(std::vector<CTable*>* pvTables)
{
	pv_tables = pvTables;
} // CSetValueCommand::CSetValueCommand(std::vector<CTable*>* pvTables)

bool CSetValueCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		int i_table_index;
		CConsoleInputHelper c_input_helper;
		if(c_input_helper.bReadTableIndex(&i_table_index)	&& i_table_index < pv_tables->size())
		{
			CTable* pc_selected_table = pv_tables->at(i_table_index);
			int i_value_index;
			if(c_input_helper.bReadValueIndex(&i_value_index)	
				&& i_value_index < pc_selected_table->iGetLength())
			{
				int i_new_value;
				if(c_input_helper.bReadValue(&i_new_value))
				{
					b_success = pc_selected_table->bSetElement(i_value_index, i_new_value);
					std::stringstream c_output;
					c_output << MessageConstants::MSG_VALUE_CHANGED << i_new_value 
						<< MessageConstants::MSG_AT_INDEX << pv_tables->size() - 1;
					vSetResponse(psResponseMsg, c_output.str());
				}
				else
				{
					vSetResponse(psResponseMsg, MessageConstants::ERR_MSG_INVALID_VALUE);
				}
			}
			else
			{
				vSetResponse(psResponseMsg, MessageConstants::ERR_MSG_INVALID_VALUE_INDEX);
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
} // bool CSetValueCommand::bRunCommand(std::string * psResponseMsg)
