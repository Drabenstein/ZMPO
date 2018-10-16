#include "pch.h"
#include "MessageConstants.h"
#include <string>

const std::string MessageConstants::WELCOME_MSG = "Enter a command on the line with >. Type 'help' to list commands.";
const std::string MessageConstants::PROMPT_MSG = "> ";
	
const std::string MessageConstants::CREATE_DEFAULT_CMD = "createDefault";
const std::string MessageConstants::CREATE_PARAMETER_CMD = "createParameter";
const std::string MessageConstants::CREATE_COPY_CMD = "createCopy";
const std::string MessageConstants::CLONE_TABLE_CMD = "clone";
const std::string MessageConstants::SET_VALUE_CMD = "setValue";
const std::string MessageConstants::GET_VALUE_CMD = "getValue";
const std::string MessageConstants::SET_NAME_CMD = "setName";
const std::string MessageConstants::GET_NAME_CMD = "getName";
const std::string MessageConstants::SET_LENGTH_CMD = "setTableLength";
const std::string MessageConstants::GET_LENGTH_CMD = "getTableLength";
const std::string MessageConstants::GET_INFO_CMD = "getInfo";
const std::string MessageConstants::DELETE_CMD = "delete";
const std::string MessageConstants::DELETE_ALL_CMD = "deleteAll";
const std::string MessageConstants::HELP_CMD = "help";
const std::string MessageConstants::EXIT_CMD = "exit";

const std::string MessageConstants::DEFAULT_TABLE_CREATED_MSG = "Created default table at index: ";
const std::string MessageConstants::PARAMETERED_TABLE_CREATED_MSG = "Created parametered CTable at index ";
const std::string MessageConstants::TABLE_COPY_CREATED_MSG = "Created table's copy at index ";
const std::string MessageConstants::TABLE_CLONED_MSG = "Table's clone placed at index ";
const std::string MessageConstants::AT_INDEX_MSG = " at index ";
const std::string MessageConstants::VALUE_CHANGED_MSG = "Changed table's value to ";
const std::string MessageConstants::VALUE_GET_MSG = "Table's value at specified index is: ";
const std::string MessageConstants::TABLE_NAME_CHANGED_MSG = "Table's name changed to: ";
const std::string MessageConstants::TABLE_NAME_MSG = "Table's name is: ";
const std::string MessageConstants::TABLE_LENGTH_CHANGED_MSG = "Changed table's length to: ";
const std::string MessageConstants::TABLE_LENGTH_MSG = "Table's length is: ";
const std::string MessageConstants::TABLE_DELETED_MSG = "Deleted table";
const std::string MessageConstants::DELETED_ALL_MSG = "Deleted all CTables";
const std::string MessageConstants::UNKNOWN_CMD_MSG = "Unknown command";
const std::string MessageConstants::CLEAR_RESOURCES_MSG = "Clearing resources..";
const std::string MessageConstants::EXIT_MSG = "Exiting..";

const std::string MessageConstants::WRONG_PARAMETERS_COUNT_MSG = "Wrong number of parameters";
const std::string MessageConstants::WRONG_TABLE_SIZE_MSG = "Wrong size of table passed as parameter";
const std::string MessageConstants::INVALID_INDEX_MSG = "Invalid index specified";
const std::string MessageConstants::INVALID_VALUE_INDEX_MSG = "Invalid value index specified";
const std::string MessageConstants::INVALID_VALUE_MSG = "Invalid value specified";
const std::string MessageConstants::INVALID_LENGTH_MSG = "Invalid length specified";
const std::string MessageConstants::OPERATION_FAILED_MSG = "Operation failed";

const std::string MessageConstants::CTABLE_DESTRUCTOR_MSG = "usuwam: ";
const std::string MessageConstants::CTABLE_DEFAULT_CONSTRUCTOR_MSG = "bezp: ";
const std::string MessageConstants::CTABLE_PARAMETERED_CONSTRUCTOR_MSG = "parametr: ";
const std::string MessageConstants::CTABLE_COPY_CONSTRUCTOR_MSG = "kopiuj: ";
const std::string MessageConstants::CTABLE_COPY_NAME_APPEND_TEXT = "_copy";
const std::string MessageConstants::CTABLE_CLONE_NAME_APPEND_TEXT = "_clone";

const std::string MessageConstants::CREATE_DEFAULT_CMD_HELP_MSG = "createDefault                   -   Creates default table and stores it at next available index";
const std::string MessageConstants::CREATE_PARAMETER_CMD_HELP_MSG = "createParameter <name> <length> -   Creates table with specified <name> and table <length>";
const std::string MessageConstants::CREATE_COPY_CMD_HELP_MSG = "createCopy <index>              -   Creates a table by copying a table from specified <index>";
const std::string MessageConstants::CLONE_TABLE_CMD_HELP_MSG = "clone <index>                   -   Clones the table from specified <index>";
const std::string MessageConstants::SET_VALUE_CMD_HELP_MSG = "setValue <index1> <index2> <val>-   Sets value at index <index2> of table at <index1> to <val>";
const std::string MessageConstants::GET_VALUE_CMD_HELP_MSG = "getValue <index1> <index2>      -   Displays value at index <index2> from table at index <index1>";
const std::string MessageConstants::SET_NAME_CMD_HELP_MSG = "setName <index> <name>          -   Sets name to <name> for table specified by <index>";
const std::string MessageConstants::GET_NAME_CMD_HELP_MSG = "getName <index>                 -   Gets name for table at specified <index>";
const std::string MessageConstants::SET_LENGTH_CMD_HELP_MSG = "setTableLength <index> <length> -   Changes length of table at <index> to <length>";
const std::string MessageConstants::GET_LENGTH_CMD_HELP_MSG = "getTableLength <index>          -   Gets length of table at <index>";
const std::string MessageConstants::GET_INFO_CMD_HELP_MSG = "getInfo <index>                 -   Displays info for table at specified <index>";
const std::string MessageConstants::DELETE_CMD_HELP_MSG = "delete <index>                  -   Deletes table at specified <index>";
const std::string MessageConstants::DELETE_ALL_CMD_HELP_MSG = "deleteAll                       -   Deletes all tables";
const std::string MessageConstants::HELP_CMD_HELP_MSG = "help                            -   Displays this help message";
const std::string MessageConstants::EXIT_CMD_HELP_MSG = "exit                            -   Exits the program";