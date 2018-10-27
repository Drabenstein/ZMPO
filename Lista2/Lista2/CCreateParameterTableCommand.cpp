#include "pch.h"
#include "CCreateParameterTableCommand.h"
#include <iostream>
#include "MessageConstants.h"
#include "CConsoleInputHelper.h"
#include <sstream>

CCreateParameterTableCommand::CCreateParameterTableCommand(std::vector<CTable*>* pvTables)
{
	pv_tables = pvTables;
}

bool CCreateParameterTableCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		std::cout << MessageConstants::MSG_INPUT_TABLE_NAME << std::endl;
		std::string s_name;
		std::getline(std::cin, s_name);
		
		int i_table_length;
		CConsoleInputHelper c_input_helper;

		if(c_input_helper.bReadTableLength(&i_table_length))
		{
			CTable* pc_parametered_table = new CTable(s_name, i_table_length);
			pv_tables->push_back(pc_parametered_table);
			b_success = true;
			std::stringstream c_output;
			c_output << MessageConstants::MSG_TABLE_PARAMETERED_CREATED << pv_tables->size() - 1;
			vSetResponse(psResponseMsg, c_output.str());
		}
		else
		{
			vSetResponse(psResponseMsg, MessageConstants::ERR_MSG_INVALID_LENGTH);
		}
	}
	else
	{
		vSetResponse(psResponseMsg, MessageConstants::ERR_MSG_TABLES_VECTOR_UNINITIALIZED);
	}

	return b_success;
}
