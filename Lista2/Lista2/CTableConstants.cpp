#include "pch.h"
#include "CTableConstants.h"

const std::string CTableConstants::MSG_INPUT_TABLE_INDEX = "Insert table index: ";
const std::string CTableConstants::MSG_INPUT_VALUE_INDEX = "Insert value index: ";
const std::string CTableConstants::MSG_INPUT_TABLE_NAME = "Insert name for table: ";
const std::string CTableConstants::MSG_INPUT_TABLE_LENGTH = "Insert table length: ";
const std::string CTableConstants::MSG_INPUT_VALUE = "Insert value: ";

const std::string CTableConstants::MSG_DEFAULT_TABLE_CREATED = "Created default table at index: ";
const std::string CTableConstants::MSG_TABLE_PARAMETERED_CREATED = "Created parametered CTable at index ";
const std::string CTableConstants::MSG_TABLE_COPY_CREATED = "Created table's copy at index ";
const std::string CTableConstants::MSG_TABLE_CLONED = "Table's clone placed at index ";
const std::string CTableConstants::MSG_AT_INDEX = " at index ";
const std::string CTableConstants::MSG_VALUE_CHANGED = "Changed table's value to ";
const std::string CTableConstants::MSG_VALUE_GET = "Table's value at specified index is: ";
const std::string CTableConstants::MSG_TABLE_NAME_CHANGED = "Table's name changed to: ";
const std::string CTableConstants::MSG_TABLE_NAME = "Table's name is: ";
const std::string CTableConstants::MSG_TABLE_LENGTH_CHANGED = "Changed table's length to: ";
const std::string CTableConstants::MSG_TABLE_LENGTH = "Table's length is: ";
const std::string CTableConstants::MSG_TABLE_DELETED = "Deleted table";
const std::string CTableConstants::MSG_DELETED_ALL = "Deleted all CTables";
const std::string CTableConstants::MSG_CLEAR_RESOURCES = "Clearing resources..";
const std::string CTableConstants::MSG_EXIT = "Exiting..";

const std::string CTableConstants::ERR_MSG_WRONG_PARAMETERS_COUNT = "Wrong number of parameters";
const std::string CTableConstants::ERR_MSG_WRONG_TABLE_SIZE = "Wrong size of table passed as parameter";
const std::string CTableConstants::ERR_MSG_INVALID_INDEX = "Invalid index specified";
const std::string CTableConstants::ERR_MSG_INVALID_VALUE_INDEX = "Invalid value index specified";
const std::string CTableConstants::ERR_MSG_INVALID_VALUE = "Invalid value specified";
const std::string CTableConstants::ERR_MSG_INVALID_LENGTH = "Invalid length specified";
const std::string CTableConstants::ERR_MSG_OPERATION_FAILED = "Operation failed";
const std::string CTableConstants::ERR_MSG_TABLES_VECTOR_UNINITIALIZED = "Vector<CTable*> passed to command is nullptr";

const std::string CTableConstants::CTABLE_DEFAULT_NAME = "Default";
const int CTableConstants::CTABLE_DEFAULT_TABLE_LENGTH = 10;
const int CTableConstants::CTABLE_DEFAULT_TABLE_VALUE = 0;
const std::string CTableConstants::MSG_CTABLE_DESTRUCTOR = "usuwam: ";
const std::string CTableConstants::MSG_CTABLE_DEFAULT_CONSTRUCTOR = "bezp: ";
const std::string CTableConstants::MSG_CTABLE_PARAMETERED_CONSTRUCTOR = "parametr: ";
const std::string CTableConstants::MSG_CTABLE_COPY_CONSTRUCTOR = "kopiuj: ";
const std::string CTableConstants::CTABLE_COPY_NAME_APPEND_TEXT = "_copy";
const std::string CTableConstants::CTABLE_CLONE_NAME_APPEND_TEXT = "_clone";