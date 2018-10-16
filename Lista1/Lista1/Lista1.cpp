// Lista1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "CTable.h"
#include "MessageConstants.h"

bool checkParameterCount(int & iFirstSpaceIndex, int & iSecondSpaceIndex, int & iThirdSpaceIndex, int iParameterCount);

bool checkIndexParameterValidity(std::string & sIndexInputText, int & iResultIndex, int iMaxSize, const std::string & sErrorMessage);

int main()
{
	std::vector<CTable*> v_tables;
	bool b_exit_requested = false;
	std::cout << MessageConstants::WELCOME_MSG
		<< std::endl << std::endl;

	do
	{
		std::cout << MessageConstants::PROMPT_MSG;
		std::string s_command_text;
		std::getline(std::cin, s_command_text);

		int i_first_space_index = s_command_text.find(" ");
		int i_second_space_index = s_command_text.find(" ", i_first_space_index + 1);
		int i_third_space_index = s_command_text.find(" ", i_second_space_index + 1);
		std::string s_command = s_command_text.substr(0, i_first_space_index);

		if(s_command == MessageConstants::CREATE_DEFAULT_CMD)
		{
			CTable* pc_default_table = new CTable();
			v_tables.push_back(pc_default_table);
			std::cout << MessageConstants::DEFAULT_TABLE_CREATED_MSG << v_tables.size() - 1 << std::endl;
		}
		else if(s_command == MessageConstants::CREATE_PARAMETER_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 2))
			{
				i_second_space_index = s_command_text.find_last_of(" ");
				int i_name_length = i_second_space_index - i_first_space_index - 1;
				std::string s_table_name = s_command_text.substr(i_first_space_index + 1, i_name_length);
				int i_table_length = strtol(s_command_text.substr(i_second_space_index).c_str(), NULL, 10);

				if (i_table_length > 0)
				{
					CTable * pc_parametered_table = new CTable(s_table_name, i_table_length);
					v_tables.push_back(pc_parametered_table);
					std::cout << MessageConstants::PARAMETERED_TABLE_CREATED_MSG << v_tables.size() - 1 << std::endl;
				}
				else
				{
					std::cout << MessageConstants::WRONG_TABLE_SIZE_MSG << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::CREATE_COPY_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_copy_source_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_table_copy_source_index;

				if(checkIndexParameterValidity(s_copy_source_index_text, i_table_copy_source_index, 
					v_tables.size(), MessageConstants::INVALID_INDEX_MSG))
				{
					CTable * pc_table_copy = new CTable(*(v_tables.at(i_table_copy_source_index)));
					v_tables.push_back(pc_table_copy);
					std::cout << MessageConstants::TABLE_COPY_CREATED_MSG << v_tables.size() - 1 << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::CLONE_TABLE_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_clone_source_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_clone_source_index;

				if(checkIndexParameterValidity(s_clone_source_index_text, i_clone_source_index, 
					v_tables.size(), MessageConstants::INVALID_INDEX_MSG))
				{
					bool b_is_success;
					CTable * pc_cloned_table = v_tables.at(i_clone_source_index)->cClone(&b_is_success);
					if (b_is_success)
					{
						v_tables.push_back(pc_cloned_table);
						std::cout << MessageConstants::TABLE_CLONED_MSG << v_tables.size() - 1 << std::endl;
					}
					else
					{
						std::cout << MessageConstants::OPERATION_FAILED_MSG << std::endl;
					}
				}
			}
		}
		else if(s_command == MessageConstants::SET_VALUE_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 3))
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1, i_second_space_index - i_first_space_index - 1);
				int i_table_to_set_value_index;

				if(checkIndexParameterValidity(s_table_index_text, i_table_to_set_value_index, 
					v_tables.size(), MessageConstants::INVALID_INDEX_MSG))
				{
					std::string s_value_index_text = s_command_text.substr(i_second_space_index + 1, i_third_space_index - i_second_space_index - 1);
					int i_value_index;
					CTable * pc_table_to_set_value = v_tables.at(i_table_to_set_value_index);
					//TODO: Reimplement this code

					if(checkIndexParameterValidity(s_value_index_text, i_value_index, 
						pc_table_to_set_value->iGetLength(), MessageConstants::INVALID_VALUE_INDEX_MSG))
					{
						std::string s_value_text = s_command_text.substr(i_third_space_index + 1);
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
								std::cout << MessageConstants::VALUE_CHANGED_MSG << i_new_value
									<< MessageConstants::AT_INDEX_MSG << i_value_index << std::endl;
							}
							else
							{
								std::cout << MessageConstants::INVALID_VALUE_INDEX_MSG << std::endl;
							}
						}
						else
						{
							std::cout << MessageConstants::INVALID_VALUE_MSG << std::endl;
						}
					}
				}
			}
		}
		else if(s_command == MessageConstants::GET_VALUE_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 2))
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1, i_second_space_index - i_first_space_index - 1);
				int i_table_to_get_value_index;

				if(checkIndexParameterValidity(s_table_index_text, i_table_to_get_value_index,
					v_tables.size(), MessageConstants::INVALID_INDEX_MSG))
				{
					std::string s_value_index_text = s_command_text.substr(i_second_space_index + 1);
					int i_value_index;
					CTable * pc_table_to_get_value = v_tables.at(i_table_to_get_value_index);

					if(checkIndexParameterValidity(s_value_index_text, i_value_index, pc_table_to_get_value->iGetLength(), MessageConstants::INVALID_VALUE_INDEX_MSG))
					{
						bool b_is_success;
						int i_table_value = pc_table_to_get_value->iGetElement(i_value_index, &b_is_success);

						if(b_is_success)
						{
							std::cout << MessageConstants::VALUE_GET_MSG << i_table_value << std::endl; 
						}
						else
						{
							std::cout << MessageConstants::OPERATION_FAILED_MSG << std::endl;
						}
					}
				}
			}
		}
		else if(s_command == MessageConstants::SET_NAME_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 2))
			{
				std::string s_table_index_text = s_command_text.substr(
					i_first_space_index + 1, 
					i_second_space_index - i_first_space_index - 1);
				int i_table_to_set_name_index;

				if(checkIndexParameterValidity(s_table_index_text, i_table_to_set_name_index, 
					v_tables.size(), MessageConstants::INVALID_INDEX_MSG))
				{
					std::string s_table_new_name = s_command_text.substr(i_second_space_index + 1);
					v_tables.at(i_table_to_set_name_index)->vSetName(s_table_new_name);
					std::cout << MessageConstants::TABLE_NAME_CHANGED_MSG << s_table_new_name << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::GET_NAME_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_table_to_get_name_index;

				if(checkIndexParameterValidity(s_table_index_text, i_table_to_get_name_index, 
					v_tables.size(), MessageConstants::INVALID_INDEX_MSG))
				{
					std::cout << MessageConstants::TABLE_NAME_MSG << v_tables.at(i_table_to_get_name_index)->sGetName() << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::SET_LENGTH_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 2))
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1, i_second_space_index - i_first_space_index - 1);
				int i_table_to_change_length_index;

				if(checkIndexParameterValidity(s_table_index_text, i_table_to_change_length_index,
					v_tables.size(), MessageConstants::INVALID_INDEX_MSG))
				{
					int i_table_new_length = strtol(s_command_text.substr(i_second_space_index + 1).c_str(), NULL, 10);
					if(i_table_new_length > 0)
					{
						CTable* pc_table_to_change_length = v_tables.at(i_table_to_change_length_index);
						pc_table_to_change_length->bSetTableLength(i_table_new_length);
						std::cout << MessageConstants::TABLE_LENGTH_CHANGED_MSG << i_table_new_length << std::endl;
					}
					else
					{
						std::cout << MessageConstants::INVALID_LENGTH_MSG << std::endl;
					}
				}
			}
		}
		else if(s_command == MessageConstants::GET_LENGTH_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1, i_second_space_index - i_first_space_index - 1);
				int i_table_to_get_length_index;

				if(checkIndexParameterValidity(s_table_index_text, i_table_to_get_length_index,
					v_tables.size(), MessageConstants::INVALID_INDEX_MSG))
				{
					std::cout << MessageConstants::TABLE_LENGTH_MSG << v_tables.at(i_table_to_get_length_index)->iGetLength() << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::GET_INFO_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_table_index;

				if(checkIndexParameterValidity(s_table_index_text, i_table_index,
					v_tables.size(), MessageConstants::INVALID_INDEX_MSG))
				{
					std::cout << v_tables.at(i_table_index)->sToString() << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::DELETE_CMD)
		{
			if(checkParameterCount(i_first_space_index, i_second_space_index, i_third_space_index, 1))
			{
				std::string s_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_table_to_delete_index;
				
				if(checkIndexParameterValidity(s_index_text, i_table_to_delete_index,
					v_tables.size(), MessageConstants::INVALID_INDEX_MSG))
				{
					delete v_tables.at(i_table_to_delete_index);;
					v_tables.erase(v_tables.begin() + i_table_to_delete_index);
					std::cout << MessageConstants::TABLE_DELETED_MSG << MessageConstants::AT_INDEX_MSG 
						<< i_table_to_delete_index << std::endl;
				}
			}
		}
		else if(s_command == MessageConstants::DELETE_ALL_CMD)
		{
			for(int i = 0; i < v_tables.size(); i++)
			{
				if(v_tables[i] != NULL)
				{
					delete v_tables[i];
				}
			}

			v_tables.clear();
			
			std::cout << MessageConstants::DELETED_ALL_MSG << std::endl;
		}
		else if(s_command == MessageConstants::HELP_CMD)
		{
			std::cout << MessageConstants::CREATE_DEFAULT_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::CREATE_PARAMETER_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::CREATE_COPY_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::CLONE_TABLE_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::SET_VALUE_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::GET_VALUE_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::SET_NAME_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::GET_NAME_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::SET_LENGTH_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::GET_LENGTH_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::GET_INFO_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::DELETE_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::DELETE_ALL_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::HELP_CMD_HELP_MSG << std::endl;
			std::cout << MessageConstants::EXIT_CMD_HELP_MSG << std::endl;
		}
		else if(s_command == MessageConstants::EXIT_CMD)
		{
			b_exit_requested = true;
		}
		else
		{
			std::cout << MessageConstants::UNKNOWN_CMD_MSG << std::endl;
		}

	} while (!b_exit_requested);

	std::cout << MessageConstants::CLEAR_RESOURCES_MSG << std::endl;

	for (int i = 0; i < v_tables.size(); i++)
	{
		if (v_tables[i] != NULL)
		{
			delete v_tables[i];
		}
	}

	v_tables.clear();

	std::cout << MessageConstants::EXIT_MSG << std::endl;
}

bool checkParameterCount(int & iFirstSpaceIndex, int & iSecondSpaceIndex, int & iThirdSpaceIndex, int iParameterCount)
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
		std::cout << MessageConstants::WRONG_PARAMETERS_COUNT_MSG << std::endl;
	}

	return  b_result;
}

bool checkIndexParameterValidity(std::string & sIndexInputText, int & iResultIndex, int iMaxSize, const std::string & sErrorMessage)
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