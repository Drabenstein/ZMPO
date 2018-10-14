// Lista1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "CTable.h"

//int main()
//{
//	CTable * pc_default_table = new CTable();
//	CTable * pc_parametered_table = new CTable("testowa nazwa", 15);
//	CTable * pc_copy_table = new CTable(*pc_parametered_table);
//
//	std::cout << pc_default_table->sToString() << std::endl << pc_parametered_table->sToString()
//		<< std::endl << pc_copy_table->sToString() << std::endl << std::endl;
//
//	for(int i = 0; i < 15; i++)
//		pc_parametered_table->bSetElement(i, i * 15 + 5);
//
//	CTable * pc_clone_table = pc_parametered_table->cClone();
//	
//	std::cout << pc_parametered_table->sToString() << std::endl << pc_clone_table->sToString()
//		<< std::endl << std::endl;
//
//	pc_default_table->bSetElement(5, 1998);
//	pc_default_table->vSetName("zmieniony default");
//	pc_default_table->bSetTableLength(20);
//	pc_clone_table->bCopyStateFrom(*pc_default_table);
//
//	std::cout << pc_default_table->sToString() << std::endl << pc_clone_table->sToString()
//		<< std::endl << std::endl;
//
//	return 0;
//}

int main()
{
	std::vector<CTable*> v_tables;
	bool b_exit_requested = false;
	std::cout << "Enter a command on the line with >. Type 'help' to list commands." 
		<< std::endl << std::endl;

	do
	{
		std::cout << "> ";
		std::string s_command_text;
		std::getline(std::cin, s_command_text);

		int i_first_space_index = s_command_text.find(" ");
		int i_second_space_index = s_command_text.find(" ", i_first_space_index + 1);
		int i_third_space_index = s_command_text.find(" ", i_second_space_index + 1);
		std::string s_command = s_command_text.substr(0, i_first_space_index);

		if(s_command == "createDefault")
		{
			CTable* pc_default_table = new CTable();
			v_tables.push_back(pc_default_table);
			std::cout << "Created default table at index: " << v_tables.size() - 1 << std::endl;
		}
		else if(s_command == "createParameter")
		{
			if(i_first_space_index == std::string::npos 
				|| i_second_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters!" << std::endl;
			}
			else
			{
				i_second_space_index = s_command_text.find_last_of(" ");
				int i_name_length = i_second_space_index - i_first_space_index - 1;
				std::string s_table_name = s_command_text.substr(i_first_space_index + 1, i_name_length);
				int i_table_length = strtol(s_command_text.substr(i_second_space_index).c_str(), NULL, 10);

				if (i_table_length > 0)
				{
					CTable * pc_parametered_table = new CTable(s_table_name, i_table_length);
					v_tables.push_back(pc_parametered_table);
					std::cout << "Created parametered CTable(" << s_table_name << ", "
						<< i_table_length << ") at index " << v_tables.size() - 1 << std::endl;
				}
				else
				{
					std::cout << "Wrong size of table passed as parameter" << std::endl;
				}
			}
		}
		else if(s_command == "createCopy")
		{
			if(i_first_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters!" << std::endl;
			}
			else
			{
				std::string s_copy_source_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_table_copy_source_index;

				if(s_copy_source_index_text.length() > 0 && s_copy_source_index_text[0] == '0')
				{
					i_table_copy_source_index = 0;
					if(i_table_copy_source_index < v_tables.size())
					{
						CTable * pc_table_copy = new CTable(*(v_tables.at(i_table_copy_source_index)));
						v_tables.push_back(pc_table_copy);
						std::cout << "Created copy of table at index " << i_table_copy_source_index << " at index "
							<< v_tables.size() - 1 << std::endl;
					}
					else
					{
						std::cout << "Invalid index specified" << std::endl;
					}
				}
				else
				{
					int i_table_copy_source_index = strtol(s_command_text.substr(i_first_space_index + 1).c_str(), NULL, 10);

					if(i_table_copy_source_index > 0 && i_table_copy_source_index < v_tables.size())
					{
						CTable * pc_table_copy = new CTable(*(v_tables.at(i_table_copy_source_index)));
						v_tables.push_back(pc_table_copy);
						std::cout << "Created copy of table at index " << i_table_copy_source_index << " at index "
							<< v_tables.size() - 1 << std::endl;
					}
					else
					{
						std::cout << "Invalid index specified" << std::endl;
					}
				}
			}
		}
		else if(s_command == "clone")
		{
			if(i_first_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters" << std::endl;
			}
			else
			{
				std::string s_clone_source_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_clone_source_index = -1;

				if(s_clone_source_index_text.length() > 0 && s_clone_source_index_text[0] == '0')
				{
					i_clone_source_index = 0;
				}
				else
				{
					i_clone_source_index = strtol(s_clone_source_index_text.c_str(), NULL, 10);
					if(i_clone_source_index <= 0)
					{
						i_clone_source_index = -1;
					}
				}

				if(i_clone_source_index >= 0 && i_clone_source_index < v_tables.size())
				{
					CTable * pc_cloned_table = v_tables.at(i_clone_source_index)->cClone();
					v_tables.push_back(pc_cloned_table);
					std::cout << "Cloned table from index " << i_clone_source_index << " and placed the copy at index "
						<< v_tables.size() - 1 << std::endl;		
				}
				else
				{
					std::cout << "Invalid index specified" << std::endl;
				}
			}
		}
		else if(s_command == "setValue")
		{
			if(i_first_space_index == std::string::npos || i_second_space_index == std::string::npos || i_third_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters" << std::endl;
			}
			else
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_table_to_set_value_index = -1;

				if(s_table_index_text.length() > 0 && s_table_index_text[0] == '0')
				{
					i_table_to_set_value_index = 0;
				}
				else
				{
					i_table_to_set_value_index = strtol(s_table_index_text.c_str(), NULL, 10);
					if(i_table_to_set_value_index <= 0)
					{
						i_table_to_set_value_index = -1;
					}
				}

				if(i_table_to_set_value_index >= 0 && i_table_to_set_value_index < v_tables.size())
				{
					std::string s_value_index_text = s_command_text.substr(i_second_space_index + 1, i_third_space_index - i_second_space_index - 1);
					int i_value_index = -1;

					if(s_value_index_text.length() > 0 && s_value_index_text[0] == '0')
					{
						i_value_index = 0;
					}
					else
					{
						i_value_index = strtol(s_value_index_text.c_str(), NULL, 10);
						if(i_value_index <= 0)
						{
							i_value_index = -1;
						}
					}

					CTable * pc_table_to_set_value = v_tables.at(i_table_to_set_value_index);

					std::string s_value_text = s_command_text.substr(i_third_space_index + 1);
					int i_new_value;
					bool b_is_new_value_valid = true;

					if(s_value_text.length() > 0 && s_value_text[0] == '0')
					{
						i_new_value = 0;
					}
					else
					{
						i_new_value = strtol(s_value_text.c_str(), NULL, 10);
						if(i_new_value == 0)
						{
							b_is_new_value_valid = false;
						}
					}

					if(b_is_new_value_valid)
					{
						bool b_is_index_valid = pc_table_to_set_value->bSetElement(i_value_index, i_new_value);

						if(b_is_index_valid)
						{
							std::cout << "Changed table " << i_table_to_set_value_index << " value at index " << i_value_index
								<< " to: " << i_new_value << std::endl;
						}
						else
						{
							std::cout << "Invalid value index specified" << std::endl;
						}
					}
					else
					{
						std::cout << "Invalid value specified" << std::endl;
					}
				}
				else
				{
					std::cout << "Invalid index specified" << std::endl;
				}
			}
		}
		else if(s_command == "getValue")
		{
			if(i_first_space_index == std::string::npos || i_second_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters" << std::endl;
			}
			else
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_table_to_get_value_index = -1;

				if(s_table_index_text.length() > 0 && s_table_index_text[0] == '0')
				{
					i_table_to_get_value_index = 0;
				}
				else
				{
					i_table_to_get_value_index = strtol(s_table_index_text.c_str(), NULL, 10);
					if(i_table_to_get_value_index <= 0)
					{
						i_table_to_get_value_index = -1;
					}
				}

				if(i_table_to_get_value_index >= 0 && i_table_to_get_value_index <= v_tables.size())
				{
					std::string s_value_index_text = s_command_text.substr(i_second_space_index + 1);
					int i_value_index = -1;

					if(s_value_index_text.length() > 0 && s_value_index_text[0] == '0')
					{
						i_value_index = 0;
					}
					else
					{
						i_value_index = strtol(s_value_index_text.c_str(), NULL, 10);
						if(i_value_index <= 0)
						{
							i_value_index = -1;
						}
					}

					CTable * pc_table_to_get_value = v_tables.at(i_table_to_get_value_index);
					bool b_is_success;
					int i_table_value = pc_table_to_get_value->iGetElement(i_value_index, &b_is_success);

					if(b_is_success)
					{
						std::cout << "Table indexed " << i_table_to_get_value_index << "'s value at index " << i_value_index 
							<< ": " << i_table_value << std::endl; 
					}
					else
					{
						std::cout << "Invalid index specified" << std::endl;
					}
				}
				else
				{
					std::cout << "Invalid index specified" << std::endl;
				}
			}
		}
		else if(s_command == "setName")
		{
			if(i_first_space_index == std::string::npos || i_second_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters" << std::endl;
			}
			else
			{
				std::string s_table_index_text = s_command_text.substr(
					i_first_space_index + 1, 
					i_second_space_index - i_first_space_index - 1);
				int i_table_to_set_name_index = -1;

				if(s_table_index_text.length() > 0 && s_table_index_text[0] == '0')
				{
					i_table_to_set_name_index = 0;
				}
				else
				{
					i_table_to_set_name_index = strtol(s_table_index_text.c_str(), NULL, 10);
					if(i_table_to_set_name_index <= 0)
					{
						i_table_to_set_name_index = -1;
					}
				}

				if(i_table_to_set_name_index >= 0 && i_table_to_set_name_index < v_tables.size())
				{
					std::string s_table_new_name = s_command_text.substr(i_second_space_index + 1);
					v_tables.at(i_table_to_set_name_index)->vSetName(s_table_new_name);
					std::cout << "Changed name of table at index " << i_table_to_set_name_index
						<< " to: " << s_table_new_name << std::endl;
				}
				else
				{
					std::cout << "Invalid index specified" << std::endl;
				}
			}
		}
		else if(s_command == "getName")
		{
			if(i_first_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters" << std::endl;
			}
			else
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_table_to_get_name_index = -1;

				if(s_table_index_text.length() > 0 && s_table_index_text[0] == '0')
				{
					i_table_to_get_name_index = 0;
				}
				else
				{
					i_table_to_get_name_index = strtol(s_table_index_text.c_str(), NULL, 10);
					if(i_table_to_get_name_index <= 0)
					{
						i_table_to_get_name_index = -1;
					}
				}

				if(i_table_to_get_name_index >= 0 && i_table_to_get_name_index < v_tables.size())
				{
					std::cout << "Name of table at index " << i_table_to_get_name_index 
						<< ": " << v_tables.at(i_table_to_get_name_index)->sGetName() << std::endl;
				}
				else
				{
					std::cout << "Invalid index specified" << std::endl;
				}
			}
		}
		else if(s_command == "setTableLength")
		{
			if(i_first_space_index == std::string::npos || i_second_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters" << std::endl;
			}
			else
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1, i_second_space_index - i_first_space_index - 1);
				int i_table_to_change_length_index = -1;

				if(s_table_index_text.length() > 0 && s_table_index_text[0] == '0')
				{
					i_table_to_change_length_index = 0;
				}
				else
				{
					i_table_to_change_length_index = strtol(s_table_index_text.c_str(), NULL, 10);
					if(i_table_to_change_length_index <= 0)
					{
						i_table_to_change_length_index = -1;
					}
				}

				if(i_table_to_change_length_index >= 0 && i_table_to_change_length_index < v_tables.size())
				{
					int i_table_new_length = strtol(s_command_text.substr(i_second_space_index + 1).c_str(), NULL, 10);
					if(i_table_new_length > 0)
					{
						CTable* pc_table_to_change_length = v_tables.at(i_table_to_change_length_index);
						pc_table_to_change_length->bSetTableLength(i_table_new_length);
						std::cout << "Changed length of table at index " << i_table_to_change_length_index 
							<< " to " << i_table_new_length << std::endl;
					}
					else
					{
						std::cout << "Invalid length specified" << std::endl;
					}
				}
				else
				{
					std::cout << "Invalid index specified" << std::endl;
				}
			}
		}
		else if(s_command == "getTableLength")
		{
			if(i_first_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters" << std::endl;
			}
			else
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1, i_second_space_index - i_first_space_index - 1);
				int i_table_to_get_length_index = -1;

				if(s_table_index_text.length() > 0 && s_table_index_text[0] == '0')
				{
					i_table_to_get_length_index = 0;
				}
				else
				{
					i_table_to_get_length_index = strtol(s_table_index_text.c_str(), NULL, 10);
					if(i_table_to_get_length_index <= 0)
					{
						i_table_to_get_length_index = -1;
					}
				}

				if(i_table_to_get_length_index >=0 && i_table_to_get_length_index < v_tables.size())
				{
					std::cout << "Size of table at index " << i_table_to_get_length_index << ": " 
						<< v_tables.at(i_table_to_get_length_index)->iGetLength() << std::endl;
				}
				else
				{
					std::cout << "Invalid index specified" << std::endl;
				}
			}
		}
		else if(s_command == "getInfo")
		{
			if(i_first_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters" << std::endl;
			}
			else
			{
				std::string s_table_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_table_index = -1;

				if(s_table_index_text.length() > 0 && s_table_index_text[0] == '0')
				{
					i_table_index = 0;
				}
				else
				{
					i_table_index = strtol(s_table_index_text.c_str(), NULL, 10);
					if(i_table_index <= 0)
					{
						i_table_index = -1;
					}
				}

				if(i_table_index >= 0 && i_table_index < v_tables.size())
				{
					std::cout << v_tables.at(i_table_index)->sToString() << std::endl;
				}
				else
				{
					std::cout << "Invalid index specified" << std::endl;
				}
			}
		}
		else if(s_command == "delete")
		{
			if(i_first_space_index == std::string::npos)
			{
				std::cout << "Wrong number of parameters" << std::endl;
			}
			else
			{
				std::string s_index_text = s_command_text.substr(i_first_space_index + 1);
				int i_table_to_delete_index;
				if(s_index_text.length() > 0 && s_index_text[0] == '0')
				{
					i_table_to_delete_index = 0;
					delete v_tables.at(i_table_to_delete_index);;
					v_tables.erase(v_tables.begin());
					std::cout << "Deleted table at index " << i_table_to_delete_index << " (following tables' indexes were decremented)"
						<< std::endl;
				}
				else
				{
					i_table_to_delete_index = strtol(s_index_text.c_str(), NULL, 10);
					if(i_table_to_delete_index > 0 && i_table_to_delete_index < v_tables.size())
					{
						delete v_tables.at(i_table_to_delete_index);;
						v_tables.erase(v_tables.begin() + i_table_to_delete_index);
						std::cout << "Deleted table at index " << i_table_to_delete_index 
							<< " (following tables' indexes were decremented)" << std::endl;
					}
					else
					{
						std::cout << "Wrong index value" << std::endl;
					}
				}

			}
		}
		else if(s_command == "deleteAll")
		{
			for(int i = 0; i < v_tables.size(); i++)
			{
				if(v_tables[i] != NULL)
				{
					delete v_tables[i];
				}
			}

			v_tables.clear();
			
			std::cout << "Deleted all CTables" << std::endl;
		}
		else if(s_command == "help")
		{
			std::cout << "createDefault                   -   Creates default table and stores it at next available index";
			std::cout << std::endl;
			std::cout << "createParameter <name> <length> -   Creates table with specified <name> and table <length>";
			std::cout << std::endl;
			std::cout << "createCopy <index>              -   Creates a table by copying a table from specified <index>";
			std::cout << std::endl;
			std::cout << "clone <index>                   -   Clones the table from specified <index>";
			std::cout << std::endl;
			std::cout << "setValue <index1> <index2> <val>-   Sets value at index <index2> of table at <index1> to <val>";
			std::cout << std::endl;
			std::cout << "getValue <index1> <index2>      -   Displays value at index <index2> from table at index <index1>";
			std::cout << std::endl;
			std::cout << "setName <index> <name>          -   Sets name to <name> for table specified by <index>";
			std::cout << std::endl;
			std::cout << "getName <index>                 -   Gets name for table at specified <index>";
			std::cout << std::endl;
			std::cout << "setTableLength <index> <length> -   Changes length of table at <index> to <length>";
			std::cout << std::endl;
			std::cout << "getTableLength <index>          -   Gets length of table at <index>";
			std::cout << std::endl;
			std::cout << "getInfo <index>                 -   Displays info for table at specified <index>";
			std::cout << std::endl;
			std::cout << "delete <index>                  -   Deletes table at specified <index>";
			std::cout << std::endl;
			std::cout << "deleteAll                       -   Deletes all tables";
			std::cout << std::endl;
			std::cout << "help                            -   Displays this help message";
			std::cout << std::endl;
			std::cout << "exit                            -   Exits the program";
			std::cout << std::endl;
		}
		else if(s_command == "exit")
		{
			b_exit_requested = true;
		}
		else
		{
			std::cout << "Unknown command" << std::endl;
		}

	} while (!b_exit_requested);

	std::cout << "Clearing resources.." << std::endl;

	for (int i = 0; i < v_tables.size(); i++)
	{
		if (v_tables[i] != NULL)
		{
			delete v_tables[i];
		}
	}

	v_tables.clear();

	std::cout << "Exiting.." << std::endl;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie