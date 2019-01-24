#pragma once
#include <vector>

#ifndef DATE_ERROR_CODES
#define DATE_ERROR_CODES
namespace DateTimeErrorCodes
{
	static const int ERR_NO_ERROR = 0;
	static const int ERR_INVALID_YEAR = 1;
	static const int ERR_INVALID_MONTH = 2;
	static const int ERR_INVALID_DAY = 3;
}
#endif

class CDate
{
public:
	CDate(int iDay, int iMonth, int iYear, int* piError);

	long operator-(const CDate& rcOther);
	CDate operator-(const int iDayCount);
	CDate operator+(const int iDayCount);

	bool operator<(const CDate& rcOther);
	bool operator<=(const CDate& rcOther);
	bool operator>(const CDate& rcOther);
	bool operator>=(const CDate& rcOther);
	bool operator==(const CDate& rcOther);

	long lGetYear();
	int iGetMonth();
	int iGetDay();

	bool bIsWeekend();

	virtual std::string sToString(char cDateSeparator);

protected:
	double d_seconds_elapsed;

	CDate(double dSecondsElapsed);

	void v_calculate_date_seconds(int iDay, int iMonth, int iYear);
	bool b_is_leap_year(int iYear);
	long l_leap_years_before(int iYear);

	static const int SECONDS_IN_DAY;

private:

	static const std::vector<int> v_normal_year_days_to_month;
	static const std::vector<int> v_leap_year_days_to_month;
	static std::vector<int> v_init_year_days(bool bIsLeapYear);

	int i_validate_date(int iDay, int iMonth, int iYear);
	long l_leap_years_before();

	static const int MIN_YEAR;
	static const int MIN_MONTH;
	static const int MIN_DAY;
	static const int DAYS_IN_FOUR_YEARS;
	static const int DAYS_IN_NORMAL_YEAR;
	static const int DAYS_IN_ONE_HUNDRED_YEARS;
	static const int DAYS_IN_FOUR_HUNDRED_YEARS;
	static const int ONE_DAY;
	static const int THIRTY_ONE_DAYS;
	static const int THIRTY_DAYS;
	static const int TWENTY_NINE_DAYS;
	static const int TWENTY_EIGHT_DAYS;
	static const int LEAP_YEAR_DIV_BY_FOUR;
	static const int LEAP_YEAR_DIV_BY_ONE_HUNDRED;
	static const int LEAP_YEAR_DIV_BY_FOUR_HUNDREDS;
	static const int WEEK_DAYS;
	static const int SUNDAY_INDEX;
	static const int SATURDAY_INDEX;
	static const int SAKOMOTO_MONTH_START;
};
