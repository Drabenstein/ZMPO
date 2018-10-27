#include "pch.h"
#include "CGetTableLengthCommand.h"
#include "CTableConstants.h"
#include "CConsoleInputHelper.h"
#include <sstream>

CGetTableLengthCommand::CGetTableLengthCommand(std::vector<CTable*>* pvTables)
{
	pv_tables = pvTables;
}

bool CGetTableLengthCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		int i_table_index;
		CConsoleInputHelper c_input_helper;
		if(c_input_helper.bReadTableIndex(&i_table_index)	&& i_table_index < pv_tables->size())
		{
			b_success = true;
			std::stringstream c_output;
			c_output << CTableConstants::MSG_TABLE_LENGTH << pv_tables->at(i_table_index)->iGetLength();
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
