#pragma once
#include <string>

namespace MessageConstants
{
	extern const std::string MSG_WELCOME;
	extern const std::string MSG_PROMPT;

	extern const std::string CMD_CREATE_DEFAULT;
	extern const std::string CMD_CREATE_PARAMETER;
	extern const std::string CMD_CREATE_COPY;
	extern const std::string CMD_CLONE_TABLE;
	extern const std::string CMD_SET_VALUE;
	extern const std::string CMD_GET_VALUE;
	extern const std::string CMD_SET_NAME;
	extern const std::string CMD_GET_NAME;
	extern const std::string CMD_SET_LENGTH;
	extern const std::string CMD_GET_LENGTH;
	extern const std::string CMD_GET_INFO;
	extern const std::string CMD_DELETE;
	extern const std::string CMD_DELETE_ALL;
	extern const std::string CMD_HELP;
	extern const std::string CMD_EXIT;

	extern const std::string CMD_SUM_BY_VALUE;
	extern const std::string CMD_SUM_BY_POINTER;

	extern const std::string MSG_DEFAULT_TABLE_CREATED;
	extern const std::string MSG_PARAMETERED_TABLE_CREATED;
	extern const std::string MSG_TABLE_COPY_CREATED;
	extern const std::string MSG_TABLE_CLONED;
	extern const std::string MSG_VALUE_CHANGED;
	extern const std::string MSG_AT_INDEX;
	extern const std::string MSG_VALUE_GET;
	extern const std::string MSG_TABLE_NAME_CHANGED;
	extern const std::string MSG_TABLE_NAME;
	extern const std::string MSG_TABLE_LENGTH_CHANGED;
	extern const std::string MSG_TABLE_LENGTH;
	extern const std::string MSG_TABLE_DELETED;
	extern const std::string MSG_DELETED_ALL;
	extern const std::string MSG_UNKNOWN_CMD;
	extern const std::string MSG_CLEAR_RESOURCES;
	extern const std::string MSG_EXIT;

	extern const std::string MSG_SUM;

	extern const std::string ERR_MSG_WRONG_PARAMETERS_COUNT;
	extern const std::string ERR_MSG_WRONG_TABLE_SIZE;
	extern const std::string ERR_MSG_INVALID_INDEX;
	extern const std::string ERR_MSG_INVALID_VALUE_INDEX;
	extern const std::string ERR_MSG_INVALID_VALUE;
	extern const std::string ERR_MSG_INVALID_LENGTH;
	extern const std::string ERR_MSG_OPERATION_FAILED;

	extern const std::string MSG_CTABLE_DESTRUCTOR;
	extern const std::string MSG_CTABLE_DEFAULT_CONSTRUCTOR;
	extern const std::string MSG_CTABLE_PARAMETERED_CONSTRUCTOR;
	extern const std::string MSG_CTABLE_COPY_CONSTRUCTOR;
	extern const std::string CTABLE_COPY_NAME_APPEND_TEXT;
	extern const std::string CTABLE_CLONE_NAME_APPEND_TEXT;

	extern const std::string HELP_MSG_CREATE_DEFAULT_CMD;
	extern const std::string HELP_MSG_CREATE_PARAMETER_CMD;
	extern const std::string HELP_MSG_CREATE_COPY_CMD;
	extern const std::string HELP_MSG_CLONE_TABLE_CMD;
	extern const std::string HELP_MSG_SET_VALUE_CMD;
	extern const std::string HELP_MSG_GET_VALUE_CMD;
	extern const std::string HELP_MSG_SET_NAME_CMD;
	extern const std::string HELP_MSG_GET_NAME_CMD;
	extern const std::string HELP_MSG_SET_LENGTH_CMD;
	extern const std::string HELP_MSG_GET_LENGTH_CMD;
	extern const std::string HELP_MSG_GET_INFO_CMD;
	extern const std::string HELP_MSG_DELETE_CMD;
	extern const std::string HELP_MSG_DELETE_ALL_CMD;

	extern const std::string HELP_MSG_SUM_BY_VALUE_CMD;
	extern const std::string HELP_MSG_SUM_BY_POINTER_CMD;

	extern const std::string HELP_MSG_HELP_CMD;
	extern const std::string HELP_MSG_EXIT_CMD;
}