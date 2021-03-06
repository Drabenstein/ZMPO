// Program.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "CTable.h"
#include "MessageConstants.h"

bool bCheckParameterCount(int & iFirstSpaceIndex, int & iSecondSpaceIndex, int & iThirdSpaceIndex, int iParameterCount);

bool bCheckIndexParameterValidity(std::string & sIndexInputText, int & iResultIndex, int iMaxSize, const std::string & sErrorMessage);

void vSum(CTable cTable);

void vSum(CTable * pcTable);

int main()
{
	std::vector<CTable*> v_tables;
	bool b_exit_requested = false;
	std::cout << MessageConstants::MSG_WELCOME
		<< std::endl << std::endl;

	do
	{
		std::cout << MessageConstants::MSG_PROMPT;
		std::string s_command_full_text;
		std::getline(std::cin, s_command_full_text);

		int i_first_space_index = s_command_full_text.find(" ");
		int i_second_space_index = s_command_full_text.find(" ", i_first_space_index + 1);
		int i_third_space_index = s_command_full_text.find(" ", i_second_space_index + 1);
		std::string s_command = s_command_full_text.substr(0, i_first_space_index);

		if(s_command == MessageConstants::CMD_CREATE_DEFAULT)
		{
			CTable* pc_default_table = new CTable();
			v_tables.push_back(pc_default_table);
			std::cout << MessageConstants::MSG_DEFAULT_TABLE_CREATED << v_tables.size() - 1 << std::endl;
		}
		else if(s_command == MessageConstants::CMD_CREATE_PARAMETER)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 2))
			{
				i_second_space_index = s_command_full_text.find_last_of(" ");
				int i_name_length = i_second_space_index - i_first_space_index - 1;
				std::string s_table_name = s_command_full_text.substr(i_first_space_index + 1, i_name_length);
				int i_table_length = strtol(s_command_full_text.substr(i_second_space_index).c_str(), NULL, 10);

				if (i_table_length > 0)
				{
					CTable * pc_parametered_table = new CTable(s_table_name, i_table_length);
					v_tables.push_back(pc_parametered_table);
					std::cout << MessageConstants::MSG_PARAMETERED_TABLE_CREATED << v_tables.size() - 1 << std::endl;
				}
				else
				{
					std::cout << MessageConstants::ERR_MSG_WRONG_TABLE_SIZE << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::CMD_CREATE_COPY)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_copy_source_index_text = s_command_full_text.substr(i_first_space_index + 1);
				int i_table_copy_source_index;

				if(bCheckIndexParameterValidity(s_copy_source_index_text, i_table_copy_source_index, 
					v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					CTable * pc_table_copy = new CTable(*(v_tables.at(i_table_copy_source_index)));
					v_tables.push_back(pc_table_copy);
					std::cout << MessageConstants::MSG_TABLE_COPY_CREATED << v_tables.size() - 1 << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::CMD_CLONE_TABLE)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_clone_source_index_text = s_command_full_text.substr(i_first_space_index + 1);
				int i_clone_source_index;

				if(bCheckIndexParameterValidity(s_clone_source_index_text, i_clone_source_index, 
					v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					bool b_is_success;
					CTable * pc_cloned_table = v_tables.at(i_clone_source_index)->cClone(&b_is_success);
					if (b_is_success)
					{
						v_tables.push_back(pc_cloned_table);
						std::cout << MessageConstants::MSG_TABLE_CLONED << v_tables.size() - 1 << std::endl;
					}
					else
					{
						std::cout << MessageConstants::ERR_MSG_OPERATION_FAILED << std::endl;
					}
				}
			}
		}
		else if(s_command == MessageConstants::CMD_SET_VALUE)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 3))
			{
				std::string s_table_index_text = s_command_full_text.substr(i_first_space_index + 1, i_second_space_index - i_first_space_index - 1);
				int i_table_to_set_value_index;

				if(bCheckIndexParameterValidity(s_table_index_text, i_table_to_set_value_index, 
					v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					std::string s_value_index_text = s_command_full_text.substr(i_second_space_index + 1, i_third_space_index - i_second_space_index - 1);
					int i_value_index;
					CTable * pc_table_to_set_value = v_tables.at(i_table_to_set_value_index);
					//TODO: Reimplement this code

					if(bCheckIndexParameterValidity(s_value_index_text, i_value_index, 
						pc_table_to_set_value->iGetLength(), MessageConstants::ERR_MSG_INVALID_VALUE_INDEX))
					{
						std::string s_value_text = s_command_full_text.substr(i_third_space_index + 1);
						int i_new_value;
						bool b_is_new_value_valid = true;

						if (s_value_text.length() > 0 && s_value_text[0] == '0')
						{
							i_new_value = 0;
						}
						else
						{
							i_new_value = strtol(s_value_text.c_str(), NULL, 10);
							if (i_new_value == 0)
							{
								b_is_new_value_valid = false;
							}
						}

						if (b_is_new_value_valid)
						{
							bool b_is_success = pc_table_to_set_value->bSetElement(i_value_index, i_new_value);

							if (b_is_success)
							{
								std::cout << MessageConstants::MSG_VALUE_CHANGED << i_new_value
									<< MessageConstants::MSG_AT_INDEX << i_value_index << std::endl;
							}
							else
							{
								std::cout << MessageConstants::ERR_MSG_INVALID_VALUE_INDEX << std::endl;
							}
						}
						else
						{
							std::cout << MessageConstants::ERR_MSG_INVALID_VALUE << std::endl;
						}
					}
				}
			}
		}
		else if(s_command == MessageConstants::CMD_GET_VALUE)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 2))
			{
				std::string s_table_index_text = s_command_full_text.substr(i_first_space_index + 1, i_second_space_index - i_first_space_index - 1);
				int i_table_to_get_value_index;

				if(bCheckIndexParameterValidity(s_table_index_text, i_table_to_get_value_index,
					v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					std::string s_value_index_text = s_command_full_text.substr(i_second_space_index + 1);
					int i_value_index;
					CTable * pc_table_to_get_value = v_tables.at(i_table_to_get_value_index);

					if(bCheckIndexParameterValidity(s_value_index_text, i_value_index, pc_table_to_get_value->iGetLength(), MessageConstants::ERR_MSG_INVALID_VALUE_INDEX))
					{
						bool b_is_success;
						int i_table_value = pc_table_to_get_value->iGetElement(i_value_index, &b_is_success);

						if(b_is_success)
						{
							std::cout << MessageConstants::MSG_VALUE_GET << i_table_value << std::endl; 
						}
						else
						{
							std::cout << MessageConstants::ERR_MSG_OPERATION_FAILED << std::endl;
						}
					}
				}
			}
		}
		else if(s_command == MessageConstants::CMD_SET_NAME)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 2))
			{
				std::string s_table_index_text = s_command_full_text.substr(
					i_first_space_index + 1, 
					i_second_space_index - i_first_space_index - 1);
				int i_table_to_set_name_index;

				if(bCheckIndexParameterValidity(s_table_index_text, i_table_to_set_name_index, 
					v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					std::string s_table_new_name = s_command_full_text.substr(i_second_space_index + 1);
					v_tables.at(i_table_to_set_name_index)->vSetName(s_table_new_name);
					std::cout << MessageConstants::MSG_TABLE_NAME_CHANGED << s_table_new_name << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::CMD_GET_NAME)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_table_index_text = s_command_full_text.substr(i_first_space_index + 1);
				int i_table_to_get_name_index;

				if(bCheckIndexParameterValidity(s_table_index_text, i_table_to_get_name_index, 
					v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					std::cout << MessageConstants::MSG_TABLE_NAME << v_tables.at(i_table_to_get_name_index)->sGetName() << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::CMD_SET_LENGTH)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 2))
			{
				std::string s_table_index_text = s_command_full_text.substr(i_first_space_index + 1, i_second_space_index - i_first_space_index - 1);
				int i_table_to_change_length_index;

				if(bCheckIndexParameterValidity(s_table_index_text, i_table_to_change_length_index,
					v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					int i_table_new_length = strtol(s_command_full_text.substr(i_second_space_index + 1).c_str(), NULL, 10);
					if(i_table_new_length > 0)
					{
						CTable* pc_table_to_change_length = v_tables.at(i_table_to_change_length_index);
						pc_table_to_change_length->bSetTableLength(i_table_new_length);
						std::cout << MessageConstants::MSG_TABLE_LENGTH_CHANGED << i_table_new_length << std::endl;
					}
					else
					{
						std::cout << MessageConstants::ERR_MSG_INVALID_LENGTH << std::endl;
					}
				}
			}
		}
		else if(s_command == MessageConstants::CMD_GET_LENGTH)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_table_index_text = s_command_full_text.substr(i_first_space_index + 1, i_second_space_index - i_first_space_index - 1);
				int i_table_to_get_length_index;

				if(bCheckIndexParameterValidity(s_table_index_text, i_table_to_get_length_index,
					v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					std::cout << MessageConstants::MSG_TABLE_LENGTH << v_tables.at(i_table_to_get_length_index)->iGetLength() << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::CMD_GET_INFO)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_table_index_text = s_command_full_text.substr(i_first_space_index + 1);
				int i_table_index;

				if(bCheckIndexParameterValidity(s_table_index_text, i_table_index,
					v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					std::cout << v_tables.at(i_table_index)->sToString() << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::CMD_DELETE)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_index_text = s_command_full_text.substr(i_first_space_index + 1);
				int i_table_to_delete_index;
				
				if(bCheckIndexParameterValidity(s_index_text, i_table_to_delete_index,
					v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					delete v_tables.at(i_table_to_delete_index);;
					v_tables.erase(v_tables.begin() + i_table_to_delete_index);
					std::cout << MessageConstants::MSG_TABLE_DELETED << MessageConstants::MSG_AT_INDEX 
						<< i_table_to_delete_index << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::CMD_DELETE_ALL)
		{
			for(int i = 0; i < v_tables.size(); i++)
			{
				if(v_tables[i] != NULL)
				{
					delete v_tables[i];
				}
			}

			v_tables.clear();
			
			std::cout << MessageConstants::MSG_DELETED_ALL << std::endl;
		}
		else if(s_command == MessageConstants::CMD_SUM_BY_VALUE)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_index_text = s_command_full_text.substr(i_first_space_index + 1);
				int i_table_index;

				if(bCheckIndexParameterValidity(s_index_text, i_table_index, v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					CTable * pc_selected_table = v_tables.at(i_table_index);
					vSum(*pc_selected_table);
				}
			}
		}
		else if(s_command == MessageConstants::CMD_SUM_BY_POINTER)
		{
			if(bCheckParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_index_text = s_command_full_text.substr(i_first_space_index + 1);
				int i_table_index;

				if(bCheckIndexParameterValidity(s_index_text, i_table_index, v_tables.size(), MessageConstants::ERR_MSG_INVALID_INDEX))
				{
					CTable * pc_selected_table = v_tables.at(i_table_index);
					vSum(pc_selected_table);
				}
			}
		}
		else if(s_command == MessageConstants::CMD_HELP)
		{
			std::cout << MessageConstants::HELP_MSG_CREATE_DEFAULT_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_CREATE_PARAMETER_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_CREATE_COPY_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_CLONE_TABLE_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_SET_VALUE_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_GET_VALUE_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_SET_NAME_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_GET_NAME_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_SET_LENGTH_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_GET_LENGTH_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_GET_INFO_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_DELETE_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_DELETE_ALL_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_SUM_BY_VALUE_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_SUM_BY_POINTER_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_HELP_CMD << std::endl;
			std::cout << MessageConstants::HELP_MSG_EXIT_CMD << std::endl;
		}
		else if(s_command == MessageConstants::CMD_EXIT)
		{
			b_exit_requested = true;
		}
		else
		{
			std::cout << MessageConstants::MSG_UNKNOWN_CMD << std::endl;
		}

	} while (!b_exit_requested);

	std::cout << MessageConstants::MSG_CLEAR_RESOURCES << std::endl;

	for (int i = 0; i < v_tables.size(); i++)
	{
		if (v_tables[i] != NULL)
		{
			delete v_tables[i];
		}
	}

	v_tables.clear();

	std::cout << MessageConstants::MSG_EXIT << std::endl;
}

bool bCheckParameterCount(int & iFirstSpaceIndex, int & iSecondSpaceIndex, int & iThirdSpaceIndex, int iParameterCount)
{
	bool b_result = true;

	switch(iParameterCount)
	{
	case 3:
		b_result = b_result && iThirdSpaceIndex != std::string::npos;
	case 2:
		b_result = b_result && iSecondSpaceIndex != std::string::npos;
	case 1:
		b_result = b_result && iFirstSpaceIndex != std::string::npos;
		break;
	default:
		b_result = false;
	}

	if(!b_result)
	{
		std::cout << MessageConstants::ERR_MSG_WRONG_PARAMETERS_COUNT << std::endl;
	}

	return  b_result;
}

bool bCheckIndexParameterValidity(std::string & sIndexInputText, int & iResultIndex, int iMaxSize, const std::string & sErrorMessage)
{
	bool b_is_success = true;

	if(sIndexInputText.length() > 0 && sIndexInputText[0] == '0')
	{
		iResultIndex = 0;
	}
	else
	{
		iResultIndex = strtol(sIndexInputText.c_str(), NULL, 10);

		if(iResultIndex <= 0)
		{
			b_is_success = false;
		}
	}

	if(!b_is_success || iResultIndex >= iMaxSize)
	{
		b_is_success = false;
		std::cout << sErrorMessage << std::endl;
	}

	return b_is_success;
}

void vSum(CTable cTable)
{
	std::cout << MessageConstants::MSG_SUM << cTable.iSumValues() << std::endl;
}

void vSum(CTable * pcTable)
{
	std::cout << MessageConstants::MSG_SUM << pcTable->iSumValues() << std::endl;
}