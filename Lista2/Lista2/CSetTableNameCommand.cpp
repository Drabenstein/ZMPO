#include "pch.h"
#include "CSetTableNameCommand.h"
#include "MessageConstants.h"
#include "CConsoleInputHelper.h"
#include <iostream>
#include <sstream>

CSetTableNameCommand::CSetTableNameCommand(std::vector<CTable*>* pvTables)
{
	pv_tables = pvTables;
}

bool CSetTableNameCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		CConsoleInputHelper c_input_helper;
		int i_table_index;
		if(c_input_helper.bReadTableIndex(&i_table_index) && i_table_index < pv_tables->size())
		{
			std::cout << MessageConstants::MSG_INPUT_TABLE_NAME << std::endl;
			std::string s_new_table_name;
			std::getline(std::cin, s_new_table_name);
			pv_tables->at(i_table_index)->vSetName(s_new_table_name);
			b_success = true;
			std::stringstream c_output;
			c_output << MessageConstants::MSG_TABLE_NAME_CHANGED << s_new_table_name;
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
