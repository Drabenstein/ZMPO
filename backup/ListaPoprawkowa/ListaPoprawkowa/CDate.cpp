#include "pch.h"
#include "CDate.h"

const int CDate::BASE_DATE_DAY = 1;
const int CDate::BASE_DATE_MONTH = 1;
const int CDate::BASE_DATE_YEAR = 1;
const int CDate::SECONDS_IN_YEAR = 31536000;
const int CDate::SECONDS_IN_DAY = 86400;
const int CDate::ONE_DAY = 1;
const int CDate::THIRTY_ONE_DAYS = 31;
const int CDate::THIRTY_DAYS = 30;
const int CDate::TWENTY_NINE_DAYS = 29;
const int CDate::TWENTY_EIGHT_DAYS = 28;
const int CDate::LEAP_YEAR_DIV_BY_FOUR = 4;
const int CDate::LEAP_YEAR_DIV_BY_ONE_HUNDRED = 100;
const int CDate::LEAP_YEAR_DIV_BY_FOUR_HUNDREDS = 400;

CDate::CDate(int iDay, int iMonth, int iYear, int* piError) : v_month_days(v_init_month_days())
{
	int i_error_code = i_validate_date(iDay, iMonth, iYear);
	if(i_error_code == DateErrorCodes::ERR_NO_ERROR)
	{
		v_calculate_seconds_interval(iDay, iMonth, iYear);
	}

	if (piError != nullptr)
	{
		*piError = i_error_code;
	}
} // CDate::CDate(int day, int month, int year)

int CDate::operator-(const CDate& rcOther)
{
	double d_seconds_difference = d_seconds_elapsed - rcOther.d_seconds_elapsed;
	return static_cast<int>(d_seconds_difference / SECONDS_IN_DAY);
} // int CDate::operator-(const CDate& rcOther)

CDate CDate::operator-(const int iDayCount)
{
	double d_difference = iDayCount * static_cast<double>(SECONDS_IN_DAY);
	return CDate(d_seconds_elapsed - d_difference);
} // CDate CDate::operator-(const int iDayCount)

CDate CDate::operator+(const int iDayCount)
{
	return CDate(d_seconds_elapsed + (iDayCount * static_cast<double>(SECONDS_IN_DAY)));
} // bool CDate::vAddDays(int iDaysCount)

bool CDate::operator<(const CDate& rcOther)
{
	return d_seconds_elapsed < rcOther.d_seconds_elapsed;
} // bool CDate::operator<(const CDate & rcOther)

bool CDate::operator<=(const CDate& rcOther)
{
	return d_seconds_elapsed <= rcOther.d_seconds_elapsed;;
} // bool CDate::operator<=(const CDate & rcOther)

bool CDate::operator>(const CDate& rcOther)
{
	return d_seconds_elapsed > rcOther.d_seconds_elapsed;
} // bool CDate::operator>(const CDate & rcOther)

bool CDate::operator>=(const CDate& rcOther)
{
	return d_seconds_elapsed >= rcOther.d_seconds_elapsed;
} // bool CDate::operator>=(const CDate & rcOther)

bool CDate::operator==(const CDate& rcOther)
{
	return d_seconds_elapsed == rcOther.d_seconds_elapsed;
} // bool CDate::operator==(const CDate & rcOther)

int CDate::iGetYear()
{
	int i_first_time_try = d_seconds_elapsed / SECONDS_IN_YEAR;
	int i_leaps = i_get_leap_years_before(i_first_time_try);
	int i_second_time_try = (d_seconds_elapsed + SECONDS_IN_DAY - (i_leaps * static_cast<double>(SECONDS_IN_DAY))) / SECONDS_IN_YEAR;
	return i_second_time_try;
	/*return (d_seconds_elapsed / SECONDS_IN_YEAR);*/
} // int CDate::iGetYear()

int CDate::iGetMonth()
{
	long l_days_remaining = l_get_days_count();

	int i_month_index = 0;

	for(int i = 0; i < v_month_days.size(); i++)
	{
		int i_month_days = v_month_days.at(i);

		if (i == 1 && b_is_leap_year(iGetYear()))
		{
			i_month_days = TWENTY_NINE_DAYS;
		}

		if(l_days_remaining > i_month_days)
		{
			l_days_remaining -= i_month_days;
			i_month_index++;
		}
		else
		{
			i = v_month_days.size();
		}
	} // for(int i = 0; i < v_month_days.size(); i++)

	return ++i_month_index;
} // int CDate::iGetMonth()

int CDate::iGetDay()
{
	long l_days_remaining = l_get_days_count();

	bool b_is_proper_days_found = false;

	for(int i = 0; i < v_month_days.size() && !b_is_proper_days_found; i++)
	{
		int i_month_days = v_month_days.at(i);

		if (i == 1 && b_is_leap_year(iGetYear()))
		{
			i_month_days = TWENTY_NINE_DAYS;
		}

		if (l_days_remaining > i_month_days)
		{
			l_days_remaining -= i_month_days;
		}
		else
		{
			b_is_proper_days_found = true;
		}
	} // for(int i = 0; i < v_month_days.size() && !b_is_proper_days_found; i++)

	return l_days_remaining + BASE_DATE_DAY;
} // int CDate::iGetDay()

std::vector<int> CDate::v_init_month_days()
{
	std::vector<int> v_month_days;
	// January
	v_month_days.push_back(THIRTY_ONE_DAYS);
	// February
	v_month_days.push_back(TWENTY_EIGHT_DAYS);
	// March
	v_month_days.push_back(THIRTY_ONE_DAYS);
	// April
	v_month_days.push_back(THIRTY_DAYS);
	// May
	v_month_days.push_back(THIRTY_ONE_DAYS);
	// June
	v_month_days.push_back(THIRTY_DAYS);
	// July
	v_month_days.push_back(THIRTY_ONE_DAYS);
	// August
	v_month_days.push_back(THIRTY_ONE_DAYS);
	// September
	v_month_days.push_back(THIRTY_DAYS);
	// October
	v_month_days.push_back(THIRTY_ONE_DAYS);
	// November
	v_month_days.push_back(THIRTY_DAYS);
	// December
	v_month_days.push_back(THIRTY_ONE_DAYS);

	return v_month_days;
} // void CDate::v_init_month_days()

int CDate::i_validate_date(int iDay, int iMonth, int iYear)
{
	if (iYear < 0)
	{
		return DateErrorCodes::ERR_INVALID_YEAR;
	}

	if (iMonth <= 0 || iMonth > v_month_days.size())
	{
		return DateErrorCodes::ERR_INVALID_MONTH;
	}

	int i_day_count;

	if (b_is_leap_year(iYear) && iMonth == 2)
	{
		i_day_count = TWENTY_NINE_DAYS;
	}
	else
	{
		i_day_count = v_month_days.at(iMonth - 1);
	}

	if (iDay <= 0 || iDay > i_day_count)
	{
		return DateErrorCodes::ERR_INVALID_DAY;
	}

	return DateErrorCodes::ERR_NO_ERROR;
} // int CDate::i_validate_date(int iDay, int iMonth, int iYear)

CDate::CDate(double dSecondsElapsed) : v_month_days(v_init_month_days())
{
	d_seconds_elapsed = dSecondsElapsed;
} // CDate::CDate(double dSecondsElapsed)

void CDate::v_calculate_seconds_interval(int iDay, int iMonth, int iYear)
{
	iYear -= BASE_DATE_YEAR;
	iDay -= BASE_DATE_DAY;

	double d_elapsed_seconds = iYear * static_cast<double>(SECONDS_IN_YEAR);

	int i_elapsed_days = 0;

	for (int i = 0; i < iMonth - BASE_DATE_MONTH; i++)
	{
		i_elapsed_days += v_month_days.at(i);
	} // for(int i = 0; i < iMonth - 2; i++)

	i_elapsed_days += iDay;
	i_elapsed_days += i_get_leap_years_before(iYear);

	d_elapsed_seconds += i_elapsed_days * static_cast<double>(SECONDS_IN_DAY);

	this->d_seconds_elapsed = d_elapsed_seconds;
} // double CDate::d_calculate_seconds_interval(int iDay, int iMonth, int iYear)

bool CDate::b_is_leap_year(int iYear)
{
	if (iYear % LEAP_YEAR_DIV_BY_FOUR == 0 && iYear % LEAP_YEAR_DIV_BY_ONE_HUNDRED != 0)
	{
		return true;
	}

	if (iYear % LEAP_YEAR_DIV_BY_FOUR_HUNDREDS)
	{
		return true;
	}

	return false;
} // bool CDate::b_is_leap_year(int iYear)

int CDate::i_get_leap_years_before(int iYear)
{
	int i_first_condition_leap_years = static_cast<int>(iYear / LEAP_YEAR_DIV_BY_FOUR - iYear / LEAP_YEAR_DIV_BY_ONE_HUNDRED);
	int i_second_condition_leap_year = static_cast<int>(iYear / LEAP_YEAR_DIV_BY_FOUR_HUNDREDS);
	return i_first_condition_leap_years + i_second_condition_leap_year;
} // int CDate::i_get_leap_years_before(int iYear)

long CDate::l_get_days_count()
{
	int i_year = iGetYear();
	double d_days_count_seconds_elapsed = d_seconds_elapsed - (i_year * static_cast<double>(SECONDS_IN_YEAR));
	d_days_count_seconds_elapsed -= i_get_leap_years_before(i_year) * static_cast<double>(SECONDS_IN_DAY);
	return static_cast<long>(d_days_count_seconds_elapsed / SECONDS_IN_DAY);
} // long CDate::l_get_days_count()