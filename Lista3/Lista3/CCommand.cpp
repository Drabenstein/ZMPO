#include "pch.h"
#include "CCommand.h"
#include <iostream>
#include "MenuConstants.h"

bool CCommand::bRunCommand(std::string * psResponseMsg)
{
	std::cout << MenuConstants::MSG_DEFAULT_CMD << std::endl;
	return true;
} // bool CCommand::bRunCommand(std::string * psResponseMsg)

void CCommand::vSetResponse(std::string * psResponse, const std::string & rsMsg)
{
	if(psResponse != nullptr)
	{
		*psResponse = rsMsg;
	}
} // void CCommand::vSetResponse(std::string * psResponse, const std::string & rsMsg)
