#include "pch.h"
#include "CTable.h"
#include "CTableConstants.h"
#include <iostream>
#include <sstream>

const std::string CTable::DEFAULT_NAME = CTableConstants::CTABLE_DEFAULT_NAME;

const int CTable::DEFAULT_TABLE_LENGTH = CTableConstants::CTABLE_DEFAULT_TABLE_LENGTH;

const int CTable::DEFAULT_VALUE = CTableConstants::CTABLE_DEFAULT_TABLE_VALUE;

CTable::CTable()
{
	s_name = DEFAULT_NAME;
	i_table_len = DEFAULT_TABLE_LENGTH;
	std::cout << CTableConstants::MSG_CTABLE_DEFAULT_CONSTRUCTOR << s_name << std::endl;
	pi_table = new int[i_table_len];

	for(int i = 0; i < i_table_len; i++)
	{
		pi_table[i] = DEFAULT_VALUE;
	} // for(int i = 0; i < i_table_len; i++)
} // CTable::CTable()

CTable::CTable(std::string sName, int iTableLen)
{
	s_name = sName;

	if (iTableLen > 0)
	{
		i_table_len = iTableLen;
		std::cout << CTableConstants::MSG_CTABLE_PARAMETERED_CONSTRUCTOR << s_name << std::endl;
		pi_table = new int[i_table_len];

		for(int i = 0; i < i_table_len; i++)
		{
			pi_table[i] = DEFAULT_VALUE;
		}
	}
	else
	{
		i_table_len = 0;
		pi_table = NULL;
	}
} // CTable::CTable(std::string sName, int iTableLen)\

CTable::CTable(CTable & pcOther)
{
	s_name = pcOther.s_name + CTableConstants::CTABLE_COPY_NAME_APPEND_TEXT;
	i_table_len = pcOther.i_table_len;
	std::cout << CTableConstants::MSG_CTABLE_COPY_CONSTRUCTOR << s_name << std::endl;
	pi_table = new int[i_table_len];
	memcpy(pi_table, pcOther.pi_table, sizeof(int) * i_table_len);
} // CTable::CTable(CTable & pcOther)

CTable::~CTable()
{
	std::cout << CTableConstants::MSG_CTABLE_DESTRUCTOR << s_name << std::endl;
	i_table_len = 0;
	delete[] pi_table;
} // CTable::~CTable()

void CTable::vSetName(std::string sName)
{
	s_name = sName;
} // void CTable::vSetName(std::string sName)

int CTable::iGetLength()
{
	return i_table_len;
} //int CTable::bGetTableLength()

std::string CTable::sGetName()
{
	return s_name;
} //std::string CTable::sGetName()

bool CTable::bSetTableLength(int iTableLen)
{
	bool b_is_success = false;

	if (i_table_len == iTableLen)
	{
		b_is_success = true;
	}
	else if (iTableLen > 0)
	{
		int * pi_temp_table = new int[iTableLen];
		int i_size = iTableLen < i_table_len ? iTableLen : i_table_len;
		memcpy(pi_temp_table, pi_table, sizeof(int) * i_size);
		delete[] pi_table;
		i_table_len = iTableLen;
		pi_table = pi_temp_table;
		
		for (int i = i_size; i < i_table_len; i++)
		{
			pi_table[i] = 0;
		} // for (int i = i_size; i < i_table_len; i++)

		b_is_success = true;
	}

	return b_is_success;
} // bool CTable::bSetTableLength(int iTableLen)

bool CTable::bSetElement(int iOffset, int iElementValue)
{
	bool b_is_success = false;

	if (iOffset >= 0 && iOffset < i_table_len)
	{
		*(pi_table + iOffset) = iElementValue;
		b_is_success = true;
	}

	return b_is_success;
} // bool CTable::bSetElementAt(int iOffset, int iElementValue)

int CTable::iGetElement(int iOffset, bool * pbSuccess)
{
	int i_result = 0;
	if (iOffset >= 0 && iOffset < i_table_len)
	{
		i_result = *(pi_table + iOffset);
		*(pbSuccess) = true;
	}
	else
	{
		*(pbSuccess) = false;
	}

	return i_result;
} // int CTable::iGetElement(int iOffset, bool * pbSuccess)

CTable* CTable::cClone(bool * pbIsSuccess)
{
	CTable * pc_table_clone = new CTable(s_name + CTableConstants::CTABLE_CLONE_NAME_APPEND_TEXT, i_table_len);
	*pbIsSuccess = pc_table_clone->bCopyStateFrom(*this);
	return *pbIsSuccess ? pc_table_clone : NULL;
} // CTable CTable::cClone()

bool CTable::bCopyStateFrom(CTable & pcAnother)
{
	i_table_len = pcAnother.i_table_len;
	delete pi_table;
	pi_table = new int[i_table_len];
	memcpy(pi_table, pcAnother.pi_table, sizeof(int) * i_table_len);
	return true;
} // bool CTable::bCopyStateFrom(CTable & pcAnother)

std::string CTable::sToString()
{
 	std::ostringstream c_result;
	c_result << s_name << " len: " << i_table_len << " values: ";

	for (int i = 0; i < i_table_len - 1; i++)
	{
		c_result << pi_table[i] << ", ";
	} // for (int i = 0; i < i_table_len - 1; i++)
	
	c_result << pi_table[i_table_len - 1];
	return c_result.str();
} // std::string CTable::sToString()

int CTable::iSumValues()
{
	int i_sum = 0;

	for(int i = 0; i < i_table_len; i++)
	{
		i_sum += pi_table[i];
	} // for(int i = 0; i < i_table_len; i++)

	return i_sum;
} // int CTable::iSumValues()