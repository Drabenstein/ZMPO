#pragma once
#include <string>

class CCommand
{
public:
	virtual bool bRunCommand(std::string * psResponseMsg);

protected:
	virtual void vSetResponse(std::string * psResponse, const std::string & psMsg);
};
