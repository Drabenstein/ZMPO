#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "CDate.h"
#include "CTimeStamp.h"
#include "DisplayConstants.h"

int main()
{
	int i_error_code;
	CTimeStamp* pc_base_timestamp = new CTimeStamp(BASE_DAY, BASE_MONTH, BASE_YEAR, BASE_HOUR, BASE_MINUTES, &i_error_code);
	if(i_error_code != DateTimeErrorCodes::ERR_NO_ERROR)
	{
		std::cout << ERR_CODE_MSG << i_error_code << std::endl;
	}
	else
	{
		std::cout << pc_base_timestamp->sToString(DATE_DELIMITER) << std::endl;
		CTimeStamp c_second_sample_timestamp(SECOND_SAMPLE_DAY, SECOND_SAMPLE_MONTH, SECOND_SAMPLE_YEAR, SECOND_SAMPLE_HOUR, SECOND_SAMPLE_MINUTES, &i_error_code);
		if (i_error_code != DateTimeErrorCodes::ERR_NO_ERROR)
		{
			std::cout << ERR_CODE_MSG << i_error_code << std::endl;
		}
		else
		{
			std::cout << c_second_sample_timestamp.sToString(DATE_DELIMITER) << std::endl;
			std::cout << std::boolalpha
				<< MSG_IS_LESS_THAN << (*pc_base_timestamp < c_second_sample_timestamp) << std::endl
				<< MSG_IS_LESS_OR_EQUAL << (*pc_base_timestamp <= c_second_sample_timestamp) << std::endl
				<< MSG_IS_EQUAL << (*pc_base_timestamp <= c_second_sample_timestamp) << std::endl
				<< MSG_IS_GREATER_THAN << (*pc_base_timestamp > c_second_sample_timestamp) << std::endl
				<< MSG_IS_GREATER_OR_EQUAL << (*pc_base_timestamp >= c_second_sample_timestamp) << std::endl
				<< MSG_DATE_AFTER_ADDING << ADDITION_HOUR_AMOUNT << MSG_HOURS_IS << (*pc_base_timestamp + ADDITION_HOUR_AMOUNT).sToString(DATE_DELIMITER) << std::endl
				<< MSG_DATE_AFTER_SUBTRACTING << SUBTRACTION_HOUR_AMOUNT << MSG_HOURS_IS << (*pc_base_timestamp - SUBTRACTION_HOUR_AMOUNT).sToString(DATE_DELIMITER) << std::endl
				<< MSG_DIFFERENCE_BETWEEN << (*pc_base_timestamp - c_second_sample_timestamp) << MSG_MINUTES << std::endl;
		}
	}

	delete pc_base_timestamp;
} // int main()