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
	CTimeStamp c_first(22, 6, 2018, 1, 1, &i_error_code);
	CTimeStamp c_second(23, 6, 2018, 1, 1, &i_error_code);
	CTimeStamp c_third(24, 6, 2018, 1, 1, &i_error_code);
	CTimeStamp c_fourth(25, 6, 2018, 1, 1, &i_error_code);
	CTimeStamp c_fifth(29, 1, 2019, 1, 1, &i_error_code);
	CTimeStamp c_sixth(30, 1, 2019, 1, 1, &i_error_code);
	CTimeStamp c_seventh(31, 1, 2019, 1, 1, &i_error_code);
	std::cout << std::boolalpha << c_first.bIsWeekend() << std::endl
		<< c_second.bIsWeekend() << std::endl
		<< c_third.bIsWeekend() << std::endl
		<< c_fourth.bIsWeekend() << std::endl
		<< c_fifth.bIsWeekend() << std::endl
		<< c_sixth.bIsWeekend() << std::endl
		<< c_seventh.bIsWeekend() << std::endl;

	/*CTimeStamp* pc_base_timestamp = new CTimeStamp(BASE_DAY, BASE_MONTH, BASE_YEAR, BASE_HOUR, BASE_MINUTES, &i_error_code);	
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
				<< MSG_DIFFERENCE_BETWEEN << (*pc_base_timestamp - c_second_sample_timestamp) << MSG_MINUTES << std::endl
				<< MSG_IS_WEEKEND << std::boolalpha << pc_base_timestamp->bIsWeekend() << std::endl;
		}
	}*/

	//delete pc_base_timestamp;
} // int main()