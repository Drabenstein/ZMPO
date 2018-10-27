#pragma once
#include <string>

class CTable 
{
public:
	CTable();
	CTable(std::string sName, int iTableLen);
	CTable(CTable & pcOther);
	
	~CTable();
	
	void vSetName(std::string sName);

	int iGetLength();
	std::string sGetName();

	bool bSetTableLength(int iTableLen);
	bool bSetElement(int iOffset, int iElementValue);
	int iGetElement(int iOffset, bool * pbSuccess);

	CTable* cClone(bool * pbIsSuccess);
	bool bCopyStateFrom(CTable & pcAnother);

	std::string sToString();

	int iSumValues();

	static const std::string DEFAULT_NAME;
	static const int DEFAULT_TABLE_LENGTH;
	static const int DEFAULT_VALUE;

private:
	std::string s_name;
	int * pi_table;
	int i_table_len;
};