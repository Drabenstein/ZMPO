#pragma once
#include "CDate.h"

#ifndef TIME_ERROR_CODES
#define TIME_ERROR_CODES
namespace DateTimeErrorCodes
{
	static const int ERR_INVALID_HOUR = 4;
	static const int ERR_INVALID_MINUTE = 5;
}
#endif

class CTimeStamp : public CDate
{
public:
	CTimeStamp(int iDay, int iMonth, int iYear, int iHour, int iMinute, int* piError);

	int operator-(const CTimeStamp& rcOther);
	CTimeStamp operator-(const int iHourCount);
	CTimeStamp operator+(const int iHourCount);

	bool operator<(const CTimeStamp& rcOther);
	bool operator<=(const CTimeStamp& rcOther);
	bool operator>(const CTimeStamp& rcOther);
	bool operator>=(const CTimeStamp& rcOther);
	bool operator==(const CTimeStamp& rcOther);

	int iGetHour();
	int iGetMinutes();

	std::string sToString(char cDateSeparator) override;

private:
	int i_validate_time(int iHour, int iMinute);
	void v_calculate_time_seconds(int iHour, int iMinute);

	CTimeStamp(double dSecondsElapsed);

	static const int MIN_HOUR;
	static const int MIN_MINUTE;
	static const int MAX_HOUR;
	static const int MAX_MINUTE;
	static const int SECONDS_IN_HOUR;
	static const int SECONDS_IN_MINUTE;
	static const char TIME_PART_SEPARATOR;
};
