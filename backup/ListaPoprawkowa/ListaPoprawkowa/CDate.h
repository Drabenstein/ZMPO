#pragma once
#include <vector>

#ifndef DATE_ERROR_CODES
#define DATE_ERROR_CODES
namespace DateErrorCodes
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

	int operator-(const CDate& rcOther);
	CDate operator-(const int iDayCount);
	CDate operator+(const int iDayCount);

	bool operator<(const CDate& rcOther);
	bool operator<=(const CDate& rcOther);
	bool operator>(const CDate& rcOther);
	bool operator>=(const CDate& rcOther);
	bool operator==(const CDate& rcOther);

	int iGetYear();
	int iGetMonth();
	int iGetDay();

protected:
	double d_seconds_elapsed;

	void v_calculate_seconds_interval(int iDay, int iMonth, int iYear);
	int i_validate_date(int iDay, int iMonth, int iYear);

private:
	CDate(double dSecondsElapsed);
	
	const std::vector<int> v_month_days;
	std::vector<int> v_init_month_days();

	bool b_is_leap_year(int iYear);
	int i_get_leap_years_before(int iYear);
	long l_get_days_count();

	static const int BASE_DATE_DAY;
	static const int BASE_DATE_MONTH;
	static const int BASE_DATE_YEAR;
	static const int SECONDS_IN_YEAR;
	static const int SECONDS_IN_DAY;
	static const int ONE_DAY;
	static const int THIRTY_ONE_DAYS;
	static const int THIRTY_DAYS;
	static const int TWENTY_NINE_DAYS;
	static const int TWENTY_EIGHT_DAYS;
	static const int LEAP_YEAR_DIV_BY_FOUR;
	static const int LEAP_YEAR_DIV_BY_ONE_HUNDRED;
	static const int LEAP_YEAR_DIV_BY_FOUR_HUNDREDS;
};
