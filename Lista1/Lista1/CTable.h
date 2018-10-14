#pragma once
#include <string>

class CTable 
{
public:
	CTable();
	CTable(std::string sName, int iTableLen);
	CTable(CTable & pcOther);
	
	virtual ~CTable();
	
	void vSetName(std::string sName);

	int iGetLength();
	std::string sGetName();

	bool bSetTableLength(int iTableLen);
	bool bSetElement(int iOffset, int iElementValue);
	int iGetElement(int iOffset, bool * pbSuccess);

	CTable* cClone();
	bool bCopyStateFrom(CTable & pcAnother);

	std::string sToString();

private:
	std::string s_name;
	int * pi_table;
	int i_table_len;
};