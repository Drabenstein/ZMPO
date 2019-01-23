#include "pch.h"
#include "CTimeStamp.h"
#include <sstream>
#include "DisplayConstants.h"
#include <iomanip>

const int CTimeStamp::MIN_HOUR = 0;
const int CTimeStamp::MIN_MINUTE = 0;
const int CTimeStamp::MAX_HOUR = 23;
const int CTimeStamp::MAX_MINUTE = 59;
const int CTimeStamp::SECONDS_IN_HOUR = 3600;
const int CTimeStamp::SECONDS_IN_MINUTE = 60;
const char CTimeStamp::TIME_PART_SEPARATOR = ':';

CTimeStamp::CTimeStamp(int iDay, int iMonth, int iYear, int iHour, int iMinute, int * piError) : CDate(iDay, iMonth, iYear, piError)
{
	if(piError != nullptr && *piError == DateTimeErrorCodes::ERR_NO_ERROR)
	{
		int i_error_code = i_validate_time(iHour, iMinute);
		if(i_error_code == DateTimeErrorCodes::ERR_NO_ERROR)
		{
			v_calculate_time_seconds(iHour, iMinute);
		}

		*piError = i_error_code;
	}
} // CTimeStamp::CTimeStamp(int iDay, int iMonth, int iYear, int iHour, int iMinute, int * piError)

int CTimeStamp::operator-(const CTimeStamp& rcOther)
{
	double d_difference = d_seconds_elapsed - rcOther.d_seconds_elapsed;
	return d_difference / SECONDS_IN_MINUTE;
} // int CTimeStamp::operator-(const CTimeStamp& rcOther)

CTimeStamp CTimeStamp::operator-(const int iHourCount)
{
	double d_new_seconds_elapsed = d_seconds_elapsed - (iHourCount * static_cast<double>(SECONDS_IN_HOUR));
	return CTimeStamp(d_new_seconds_elapsed);
} // CTimeStamp CTimeStamp::operator-(const int iHourCount)

CTimeStamp CTimeStamp::operator+(const int iHourCount)
{
	double d_new_seconds_elapsed = d_seconds_elapsed + (iHourCount * static_cast<double>(SECONDS_IN_HOUR));
	return CTimeStamp(d_new_seconds_elapsed);
} // CTimeStamp CTimeStamp::operator+(const int iHourCount)

int CTimeStamp::i_validate_time(int iHour, int iMinute)
{
	if(iHour < MIN_HOUR || iHour > MAX_HOUR)
	{
		return DateTimeErrorCodes::ERR_INVALID_HOUR;
	}

	if(iMinute < MIN_MINUTE || iMinute > MAX_MINUTE)
	{
		return DateTimeErrorCodes::ERR_INVALID_MINUTE;
	}

	return DateTimeErrorCodes::ERR_NO_ERROR;
} // int CTimeStamp::i_validate_time(int iHour, int iMinute)

void CTimeStamp::v_calculate_time_seconds(int iHour, int iMinute)
{
	if (iHour >= MIN_HOUR && iHour <= MAX_HOUR && iMinute >= MIN_MINUTE && iMinute <= MAX_MINUTE)
	{
		d_seconds_elapsed += iHour * SECONDS_IN_HOUR + iMinute * SECONDS_IN_MINUTE;
	}
} // void CTimeStamp::v_calculate_time_seconds(int iHour, int iMinute)

CTimeStamp::CTimeStamp(double dSecondsElapsed) : CDate(dSecondsElapsed)
{
} // CTimeStamp::CTimeStamp(double dSecondsElapsed)

bool CTimeStamp::operator<(const CTimeStamp& rcOther)
{
	return d_seconds_elapsed < rcOther.d_seconds_elapsed;
} // bool CTimeStamp::operator<(const CTimeStamp& rcOther)

bool CTimeStamp::operator<=(const CTimeStamp& rcOther)
{
	return d_seconds_elapsed <= rcOther.d_seconds_elapsed;
} // bool CTimeStamp::operator<=(const CTimeStamp& rcOther)

bool CTimeStamp::operator>(const CTimeStamp& rcOther)
{
	return d_seconds_elapsed > rcOther.d_seconds_elapsed;
} // bool CTimeStamp::operator>(const CTimeStamp& rcOther)

bool CTimeStamp::operator>=(const CTimeStamp& rcOther)
{
	return d_seconds_elapsed >= rcOther.d_seconds_elapsed;
} // bool CTimeStamp::operator>=(const CTimeStamp& rcOther)

bool CTimeStamp::operator==(const CTimeStamp& rcOther)
{
	return d_seconds_elapsed == rcOther.d_seconds_elapsed;
} // bool CTimeStamp::operator==(const CTimeStamp& rcOther)

int CTimeStamp::iGetHour()
{
	long l_days = static_cast<long>(d_seconds_elapsed / SECONDS_IN_DAY);
	double d_remaining_seconds = d_seconds_elapsed - (l_days * static_cast<double>(SECONDS_IN_DAY));
	return static_cast<int>(d_remaining_seconds / SECONDS_IN_HOUR);
} // int CTimeStamp::iGetHour()

int CTimeStamp::iGetMinutes()
{
	long l_days = static_cast<long>(d_seconds_elapsed / SECONDS_IN_DAY);
	double d_remaining_seconds = d_seconds_elapsed - (l_days * static_cast<double>(SECONDS_IN_DAY));
	d_remaining_seconds -= iGetHour() * SECONDS_IN_HOUR;
	return d_remaining_seconds / SECONDS_IN_MINUTE;
} // int CTimeStamp::iGetMinutes()

std::string CTimeStamp::sToString(char cDateSeparator)
{
	std::stringstream c_output;
	c_output << CDate::sToString(cDateSeparator);
	c_output << WHITESPACE;
	c_output << std::setfill(SPACE_FILL) << std::setw(W_HOUR) << iGetHour();
	c_output << TIME_PART_SEPARATOR;
	c_output << std::setfill(SPACE_FILL) << std::setw(W_MINUTE) <<  iGetMinutes();
	return c_output.str();
} // std::string CTimeStamp::sToString(char cDateSeparator)
