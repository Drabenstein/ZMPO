#include "pch.h"
#include "CDeleteAllTablesCommand.h"
#include "MessageConstants.h"

CDeleteAllTablesCommand::CDeleteAllTablesCommand(std::vector<CTable*>* pvTables)
{
	pv_tables = pvTables;
}

bool CDeleteAllTablesCommand::bRunCommand(std::string * psResponseMsg)
{
	bool b_success = false;

	if(pv_tables != nullptr)
	{
		for(int i = 0; i < pv_tables->size(); i++)
		{
			delete pv_tables->at(i);
		}

		pv_tables->clear();
		b_success = true;
		vSetResponse(psResponseMsg, MessageConstants::MSG_DELETED_ALL);
	}
	else
	{
		vSetResponse(psResponseMsg, MessageConstants::ERR_MSG_TABLES_VECTOR_UNINITIALIZED);
	}

	return b_success;
}
