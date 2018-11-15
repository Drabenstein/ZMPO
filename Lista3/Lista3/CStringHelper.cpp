#include "pch.h"
#include "CStringHelper.h"

bool CStringHelper::bStartsWith(std::string sText, std::string sToken)
{
	if(sText.length() < sToken.length())
	{
		return false;
	}

	for(int i = 0; i < sToken.length(); i++)
	{
		if(sText[i] != sToken[i])
		{
			return false;
		}
	} // for(int i = 0; i < sToken.length(); i++)

	return true;
} // bool CStringHelper::bStartsWith(std::string sToken)
