#include "pch.h"
#include "MessageConstants.h"
#include <string>

const std::string MessageConstants::MSG_WELCOME = "Enter a command on the line with >. Type 'help' to list commands.";
const std::string MessageConstants::MSG_PROMPT = "> ";
	
const std::string MessageConstants::CMD_CREATE_DEFAULT = "createDefault";
const std::string MessageConstants::CMD_CREATE_PARAMETER = "createParameter";
const std::string MessageConstants::CMD_CREATE_COPY = "createCopy";
const std::string MessageConstants::CMD_CLONE_TABLE = "clone";
const std::string MessageConstants::CMD_SET_VALUE = "setValue";
const std::string MessageConstants::CMD_GET_VALUE = "getValue";
const std::string MessageConstants::CMD_SET_NAME = "setName";
const std::string MessageConstants::CMD_GET_NAME = "getName";
const std::string MessageConstants::CMD_SET_LENGTH = "setTableLength";
const std::string MessageConstants::CMD_GET_LENGTH = "getTableLength";
const std::string MessageConstants::CMD_GET_INFO = "getInfo";
const std::string MessageConstants::CMD_DELETE = "delete";
const std::string MessageConstants::CMD_DELETE_ALL = "deleteAll";
const std::string MessageConstants::CMD_HELP = "help";
const std::string MessageConstants::CMD_EXIT = "exit";

const std::string MessageConstants::CMD_SUM_BY_VALUE = "sumByValue";
const std::string MessageConstants::CMD_SUM_BY_POINTER = "sumByPointer";

const std::string MessageConstants::MSG_DEFAULT_TABLE_CREATED = "Created default table at index: ";
const std::string MessageConstants::MSG_PARAMETERED_TABLE_CREATED = "Created parametered CTable at index ";
const std::string MessageConstants::MSG_TABLE_COPY_CREATED = "Created table's copy at index ";
const std::string MessageConstants::MSG_TABLE_CLONED = "Table's clone placed at index ";
const std::string MessageConstants::MSG_AT_INDEX = " at index ";
const std::string MessageConstants::MSG_VALUE_CHANGED = "Changed table's value to ";
const std::string MessageConstants::MSG_VALUE_GET = "Table's value at specified index is: ";
const std::string MessageConstants::MSG_TABLE_NAME_CHANGED = "Table's name changed to: ";
const std::string MessageConstants::MSG_TABLE_NAME = "Table's name is: ";
const std::string MessageConstants::MSG_TABLE_LENGTH_CHANGED = "Changed table's length to: ";
const std::string MessageConstants::MSG_TABLE_LENGTH = "Table's length is: ";
const std::string MessageConstants::MSG_TABLE_DELETED = "Deleted table";
const std::string MessageConstants::MSG_DELETED_ALL = "Deleted all CTables";
const std::string MessageConstants::MSG_UNKNOWN_CMD = "Unknown command";
const std::string MessageConstants::MSG_CLEAR_RESOURCES = "Clearing resources..";
const std::string MessageConstants::MSG_EXIT = "Exiting..";

const std::string MessageConstants::MSG_SUM = "Sum for this table equals: ";

const std::string MessageConstants::ERR_MSG_WRONG_PARAMETERS_COUNT = "Wrong number of parameters";
const std::string MessageConstants::ERR_MSG_WRONG_TABLE_SIZE = "Wrong size of table passed as parameter";
const std::string MessageConstants::ERR_MSG_INVALID_INDEX = "Invalid index specified";
const std::string MessageConstants::ERR_MSG_INVALID_VALUE_INDEX = "Invalid value index specified";
const std::string MessageConstants::ERR_MSG_INVALID_VALUE = "Invalid value specified";
const std::string MessageConstants::ERR_MSG_INVALID_LENGTH = "Invalid length specified";
const std::string MessageConstants::ERR_MSG_OPERATION_FAILED = "Operation failed";

const std::string MessageConstants::MSG_CTABLE_DESTRUCTOR = "usuwam: ";
const std::string MessageConstants::MSG_CTABLE_DEFAULT_CONSTRUCTOR = "bezp: ";
const std::string MessageConstants::MSG_CTABLE_PARAMETERED_CONSTRUCTOR = "parametr: ";
const std::string MessageConstants::MSG_CTABLE_COPY_CONSTRUCTOR = "kopiuj: ";
const std::string MessageConstants::CTABLE_COPY_NAME_APPEND_TEXT = "_copy";
const std::string MessageConstants::CTABLE_CLONE_NAME_APPEND_TEXT = "_clone";

const std::string MessageConstants::HELP_MSG_CREATE_DEFAULT_CMD = "createDefault                   -   Creates default table and stores it at next available index";
const std::string MessageConstants::HELP_MSG_CREATE_PARAMETER_CMD = "createParameter <name> <length> -   Creates table with specified <name> and table <length>";
const std::string MessageConstants::HELP_MSG_CREATE_COPY_CMD = "createCopy <index>              -   Creates a table by copying a table from specified <index>";
const std::string MessageConstants::HELP_MSG_CLONE_TABLE_CMD = "clone <index>                   -   Clones the table from specified <index>";
const std::string MessageConstants::HELP_MSG_SET_VALUE_CMD = "setValue <index1> <index2> <val>-   Sets value at index <index2> of table at <index1> to <val>";
const std::string MessageConstants::HELP_MSG_GET_VALUE_CMD = "getValue <index1> <index2>      -   Displays value at index <index2> from table at index <index1>";
const std::string MessageConstants::HELP_MSG_SET_NAME_CMD = "setName <index> <name>          -   Sets name to <name> for table specified by <index>";
const std::string MessageConstants::HELP_MSG_GET_NAME_CMD = "getName <index>                 -   Gets name for table at specified <index>";
const std::string MessageConstants::HELP_MSG_SET_LENGTH_CMD = "setTableLength <index> <length> -   Changes length of table at <index> to <length>";
const std::string MessageConstants::HELP_MSG_GET_LENGTH_CMD = "getTableLength <index>          -   Gets length of table at <index>";
const std::string MessageConstants::HELP_MSG_GET_INFO_CMD = "getInfo <index>                 -   Displays info for table at specified <index>";
const std::string MessageConstants::HELP_MSG_DELETE_CMD = "delete <index>                  -   Deletes table at specified <index>";
const std::string MessageConstants::HELP_MSG_DELETE_ALL_CMD = "deleteAll                       -   Deletes all tables";
const std::string MessageConstants::HELP_MSG_SUM_BY_VALUE_CMD = "sumByValue <index>              -   Gets sum of values stored at table at index <index>";
const std::string MessageConstants::HELP_MSG_SUM_BY_POINTER_CMD = "sumByPointer <index>            -   Gets sum of values stored at table at index <index>";
const std::string MessageConstants::HELP_MSG_HELP_CMD = "help                            -   Displays this help message";
const std::string MessageConstants::HELP_MSG_EXIT_CMD = "exit                            -   Exits the program";