#include "pch.h"
#include "CTable.h"
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

#define ZERO_TABLE

CTable::CTable()
{
	s_name = "default";
	i_table_len = 10;
	std::cout << "bezp: " << s_name << "\n";
	pi_table = new int[i_table_len];
#ifdef ZERO_TABLE
		for(int i = 0; i < i_table_len; i++)
			pi_table[i] = 0;
#endif
} // CTable()

CTable::CTable(std::string sName, int iTableLen)
{
	s_name = sName;

	/*if (iTableLen <= 0)
		throw std::out_of_range("CTable: parameter iTableLen is <= 0 " + iTableLen);*/

	if (iTableLen > 0)
	{
		i_table_len = iTableLen;
		std::cout << "parametr: " << s_name << "\n";
		pi_table = new int[i_table_len];

#ifdef ZERO_TABLE
		for(int i = 0; i < i_table_len; i++)
			pi_table[i] = 0;
#endif
	}
	else
	{
		i_table_len = 0;
		pi_table = NULL;
	}
} // CTable(std::string sName, int iTableLen)\

CTable::CTable(CTable & pcOther)
{
	s_name = pcOther.s_name + "_copy";
	i_table_len = pcOther.i_table_len;
	std::cout << "kopiuj: " << s_name << "\n";
	pi_table = new int[i_table_len];
	memcpy(pi_table, pcOther.pi_table, sizeof(int) * i_table_len);
} // CTable(CTable & pcOther)

CTable::~CTable()
{
	std::cout << "usuwam: " << s_name << "\n";
	i_table_len = 0;
	delete[] pi_table;
} // ~CTable()

void CTable::vSetName(std::string sName)
{
	s_name = sName;
} // void vSetName(std::string sName)

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
		}

		b_is_success = true;
	}

	return b_is_success;
} // bool bSetTableLength(int iTableLen)

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

CTable* CTable::cClone()
{
	return new CTable(*this);
} // CTable CTable::cClone()

bool CTable::bCopyStateFrom(CTable & pcAnother)
{
	i_table_len = pcAnother.i_table_len;
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
	}
	c_result << pi_table[i_table_len - 1];
	return c_result.str();
} // std::string CTable::sToString()