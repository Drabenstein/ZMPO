// Lista2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "CMenu.h"
#include "CMenuCommand.h"
#include <sstream>
#include "CCreateDefaultTableCommand.h"
#include "MenuConstants.h"
#include "CCreateParameterTableCommand.h"
#include "CCreateCopyTableCommand.h"
#include "CGetValueCommand.h"
#include "CSetValueCommand.h"
#include "CGetTableLengthCommand.h"
#include "CSetTableLengthCommand.h"
#include "CCloneTableCommand.h"
#include "CGetTableNameCommand.h"
#include "CSetTableNameCommand.h"
#include "CGetTableInfoCommand.h"
#include "CDeleteTableCommand.h"
#include "CDeleteAllTablesCommand.h"

CMenu* pcInitializeMenu(std::vector<CTable*> * pvTables);

int main()
{
    std::vector<CTable*> v_tables;
	CMenu* pc_main_menu = pcInitializeMenu(&v_tables);
	pc_main_menu->bRun();

	for(int i = 0; i < v_tables.size(); i++)
	{
		delete v_tables.at(i);
	}
	v_tables.clear();
	delete pc_main_menu;
	return 0;
} // int main()

CMenu* pcInitializeMenu(std::vector<CTable*> * pvTables)
{
	CMenu* pc_main_menu = new CMenu(MenuConstants::NAME_MAIN_MENU, MenuConstants::CMD_MAIN_MENU, nullptr);

	//CREATION MENU
	CMenu* pc_creation_menu = new CMenu(MenuConstants::NAME_CREATION_MENU, MenuConstants::CMD_CREATION_MENU, nullptr);
	
	CMenuCommand* pc_create_default_menu_cmd = new CMenuCommand(MenuConstants::NAME_CREATE_DEFAULT_MENU_CMD, MenuConstants::CMD_CREATE_DEFAULT_MENU_CMD, new CCreateDefaultTableCommand(pvTables), nullptr);

	pc_creation_menu->bAddMenuItem(pc_create_default_menu_cmd);

	CMenuCommand* pc_create_parameter_menu_cmd = new CMenuCommand(MenuConstants::NAME_CREATE_PARAMETER_MENU_CMD, MenuConstants::CMD_CREATE_PARAMETER_MENU_CMD, new CCreateParameterTableCommand(pvTables), nullptr);
	
	pc_creation_menu->bAddMenuItem(pc_create_parameter_menu_cmd);

	CMenuCommand* pc_create_copy_menu_cmd = new CMenuCommand(MenuConstants::NAME_CREATE_COPY_MENU_CMD, MenuConstants::CMD_CREATE_COPY_MENU_CMD, new CCreateCopyTableCommand(pvTables), nullptr);
	
	pc_creation_menu->bAddMenuItem(pc_create_copy_menu_cmd);

	CMenuCommand* pc_clone_table_menu_cmd = new CMenuCommand(MenuConstants::NAME_CLONE_TABLE_MENU_CMD, MenuConstants::CMD_CLONE_TABLE_MENU_CMD, new CCloneTableCommand(pvTables), nullptr);

	pc_creation_menu->bAddMenuItem(pc_clone_table_menu_cmd);

	pc_main_menu->bAddMenuItem(pc_creation_menu);
	//~CREATION MENU

	//VALUES MENU
	CMenu* pc_values_menu = new CMenu(MenuConstants::NAME_VALUES_MENU, MenuConstants::CMD_VALUES_MENU, nullptr);

	CMenuCommand* pc_get_value_menu_cmd = new CMenuCommand(MenuConstants::NAME_GET_VALUE_MENU_CMD, MenuConstants::CMD_GET_VALUE_MENU_CMD,
		new CGetValueCommand(pvTables), nullptr);

	pc_values_menu->bAddMenuItem(pc_get_value_menu_cmd);

	CMenuCommand* pc_set_value_menu_cmd = new CMenuCommand(MenuConstants::NAME_SET_VALUE_MENU_CMD, MenuConstants::CMD_SET_VALUE_MENU_CMD,
		new CSetValueCommand(pvTables), nullptr);

	pc_values_menu->bAddMenuItem(pc_set_value_menu_cmd);

	CMenuCommand* pc_get_table_length_menu_cmd = new CMenuCommand(MenuConstants::NAME_GET_TABLE_LENGTH_MENU_CMD, MenuConstants::CMD_GET_TABLE_LENGTH_MENU_CMD, new CGetTableLengthCommand(pvTables), nullptr);

	pc_values_menu->bAddMenuItem(pc_get_table_length_menu_cmd);

	CMenuCommand* pc_set_table_length_menu_cmd = new CMenuCommand(MenuConstants::NAME_SET_TABLE_LENGTH_MENU_CMD, MenuConstants::CMD_SET_TABLE_LENGTH_MENU_CMD, new CSetTableLengthCommand(pvTables), nullptr);

	pc_values_menu->bAddMenuItem(pc_set_table_length_menu_cmd);

	pc_main_menu->bAddMenuItem(pc_values_menu);
	//~VALUES MENU

	//NAMES MENU
	CMenu* pc_names_menu = new CMenu(MenuConstants::NAME_NAMES_MENU, MenuConstants::CMD_NAMES_MENU, nullptr);

	CMenuCommand* pc_get_table_name_menu_cmd = new CMenuCommand(MenuConstants::NAME_GET_TABLE_NAME_MENU_CMD, MenuConstants::CMD_GET_TABLE_NAME_MENU_CMD,
		new CGetTableNameCommand(pvTables), nullptr);

	pc_names_menu->bAddMenuItem(pc_get_table_name_menu_cmd);

	CMenuCommand* pc_set_table_name_menu_cmd = new CMenuCommand(MenuConstants::NAME_SET_TABLE_NAME_MENU_CMD, MenuConstants::CMD_SET_TABLE_NAME_MENU_CMD,
		new CSetTableNameCommand(pvTables), nullptr);
	
	pc_names_menu->bAddMenuItem(pc_set_table_name_menu_cmd);

	pc_main_menu->bAddMenuItem(pc_names_menu);
	//~NAMES MENU

	//INFO
	CMenuCommand* pc_get_table_info_menu_cmd = new CMenuCommand(MenuConstants::NAME_GET_INFO_MENU_CMD, MenuConstants::CMD_GET_INFO_MENU_CMD, new CGetTableInfoCommand(pvTables), nullptr);

	pc_main_menu->bAddMenuItem(pc_get_table_info_menu_cmd);
	//~INFO

	//DELETION MENU
	CMenu* pc_deletion_menu = new CMenu(MenuConstants::NAME_DELETION_MENU, MenuConstants::CMD_DELETION_MENU, nullptr);

	CMenuCommand* pc_delete_table_menu_cmd = new CMenuCommand(MenuConstants::NAME_DELETE_TABLE_MENU_CMD,
		MenuConstants::CMD_DELETE_TABLE_MENU_CMD, new CDeleteTableCommand(pvTables), nullptr);

	pc_deletion_menu->bAddMenuItem(pc_delete_table_menu_cmd);

	CMenuCommand* pc_delete_all_tables_menu_cmd = new CMenuCommand(MenuConstants::NAME_DELETE_ALL_TABLES_MENU_CMD, MenuConstants::CMD_DELETE_ALL_TABLES_MENU_CMD, new CDeleteAllTablesCommand(pvTables), nullptr);

	pc_deletion_menu->bAddMenuItem(pc_delete_all_tables_menu_cmd);

	pc_main_menu->bAddMenuItem(pc_deletion_menu);
	//~DELETION MENU

	return pc_main_menu;
} // CMenu* pcInitializeMenu(std::vector<CTable*> * pvTables)