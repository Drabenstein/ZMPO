#include "pch.h"
#include "CDate.h"
#include <sstream>
#include <iomanip>
#include "DisplayConstants.h"
#define FEBRUARY_INDEX 2

const int CDate::MIN_YEAR = 1;
const int CDate::MIN_MONTH = 1;
const int CDate::MIN_DAY = 1;
const int CDate::DAYS_IN_FOUR_YEARS = 1461;
const int CDate::DAYS_IN_NORMAL_YEAR = 365;
const int CDate::DAYS_IN_ONE_HUNDRED_YEARS = 36524;
const int CDate::DAYS_IN_FOUR_HUNDRED_YEARS = 146097;
const int CDate::SECONDS_IN_DAY = 86400;
const int CDate::ONE_DAY = 1;
const int CDate::THIRTY_ONE_DAYS = 31;
const int CDate::THIRTY_DAYS = 30;
const int CDate::TWENTY_NINE_DAYS = 29;
const int CDate::TWENTY_EIGHT_DAYS = 28;
const int CDate::LEAP_YEAR_DIV_BY_FOUR = 4;
const int CDate::LEAP_YEAR_DIV_BY_ONE_HUNDRED = 100;
const int CDate::LEAP_YEAR_DIV_BY_FOUR_HUNDREDS = 400;

const std::vector<int> CDate::v_normal_year_days_to_month = v_init_year_days(false);
const std::vector<int> CDate::v_leap_year_days_to_month = v_init_year_days(true);

CDate::CDate(int iDay, int iMonth, int iYear, int* piError)
{
	int i_error_code = i_validate_date(iDay, iMonth, iYear);
	if(i_error_code == DateTimeErrorCodes::ERR_NO_ERROR)
	{
		v_calculate_date_seconds(iDay, iMonth, iYear);
	}

	if (piError != nullptr)
	{
		*piError = i_error_code;
	}
} // CDate::CDate(int day, int month, int year)

#pragma region
long CDate::operator-(const CDate& rcOther)
{
	double d_seconds_difference = d_seconds_elapsed - rcOther.d_seconds_elapsed;
	return static_cast<long>(d_seconds_difference / SECONDS_IN_DAY);
} // int CDate::operator-(const CDate& rcOther)

CDate CDate::operator-(const int iDayCount)
{
	double d_new_elapsed_seconds = d_seconds_elapsed - (iDayCount * static_cast<double>(SECONDS_IN_DAY));
	return CDate(d_new_elapsed_seconds);
} // CDate CDate::operator-(const int iDayCount)

CDate CDate::operator+(const int iDayCount)
{
	double d_new_seconds_elapsed = d_seconds_elapsed + (iDayCount * static_cast<double>(SECONDS_IN_DAY));
	return CDate(d_new_seconds_elapsed);
} // bool CDate::vAddDays(int iDaysCount)
#pragma endregion Sub and Add Operators

#pragma region
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
#pragma endregion Comparison Operators

long CDate::lGetYear()
{
	long l_total_days = static_cast<long>(d_seconds_elapsed / SECONDS_IN_DAY);
	long l_days_without_leap_year_days = (l_total_days - l_leap_years_before());
	return l_days_without_leap_year_days / DAYS_IN_NORMAL_YEAR + MIN_YEAR;
} // long CDate::lGetYear()

int CDate::iGetMonth()
{
	long l_total_days = static_cast<long>(d_seconds_elapsed / SECONDS_IN_DAY);
	long l_year = lGetYear() - MIN_YEAR;
	long l_remaining_days = l_total_days - l_year * DAYS_IN_NORMAL_YEAR - l_leap_years_before(l_year);
	const std::vector<int>& rv_month_days = b_is_leap_year(l_year) ? v_leap_year_days_to_month : v_normal_year_days_to_month;
	int i_month_index = 0;
	while (l_remaining_days >= rv_month_days.at(i_month_index))
	{
		i_month_index++;
	} // while (l_remaining_days >= rv_month_days.at(i_month_index))

	return i_month_index;
} // int CDate::iGetMonth()

int CDate::iGetDay()
{
	long l_total_days = static_cast<long>(d_seconds_elapsed / SECONDS_IN_DAY);
	long l_year = lGetYear() - MIN_YEAR;
	int i_month = iGetMonth();
	long l_remaining_days = l_total_days - l_year * DAYS_IN_NORMAL_YEAR - l_leap_years_before(l_year);
	const std::vector<int>& rv_month_days = b_is_leap_year(l_year) ? v_leap_year_days_to_month : v_normal_year_days_to_month;
	l_remaining_days -= rv_month_days.at(i_month - 1);
	return ++l_remaining_days;
} // int CDate::iGetDay()

std::string CDate::sToString(char cDateSeparator)
{
	std::stringstream c_output;
	c_output << std::setfill(SPACE_FILL) << std::setw(W_DAY) << iGetDay();
	c_output << cDateSeparator;
	c_output << std::setfill(SPACE_FILL) << std::setw(W_MONTH) << iGetMonth();
	c_output << cDateSeparator;
	c_output << std::setfill(SPACE_FILL) << std::setw(W_YEAR) << lGetYear();
	return c_output.str();
} // std::string CDate::sToString(char cDateSeparator)

// Returns vector with days passed to specific month
std::vector<int> CDate::v_init_year_days(bool bIsLeapYear)
{
	std::vector<int> v_month_days;
	// January
	v_month_days.push_back(NULL);
	// February
	v_month_days.push_back(THIRTY_ONE_DAYS);
	// March
	if (bIsLeapYear)
	{
		v_month_days.push_back(v_month_days.back() + TWENTY_NINE_DAYS);
	}
	else
	{
		v_month_days.push_back(v_month_days.back() + TWENTY_EIGHT_DAYS);
	}
	// April
	v_month_days.push_back(v_month_days.back() + THIRTY_ONE_DAYS);
	// May
	v_month_days.push_back(v_month_days.back() + THIRTY_DAYS);
	// June
	v_month_days.push_back(v_month_days.back() + THIRTY_ONE_DAYS);
	// July
	v_month_days.push_back(v_month_days.back() + THIRTY_DAYS);
	// August
	v_month_days.push_back(v_month_days.back() + THIRTY_ONE_DAYS);
	// September
	v_month_days.push_back(v_month_days.back() + THIRTY_ONE_DAYS);
	// October
	v_month_days.push_back(v_month_days.back() + THIRTY_DAYS);
	// November
	v_month_days.push_back(v_month_days.back() + THIRTY_ONE_DAYS);
	// December
	v_month_days.push_back(v_month_days.back() + THIRTY_DAYS);
	// Full year days - for easier calculations
	v_month_days.push_back(v_month_days.back() + THIRTY_ONE_DAYS);

	return v_month_days;
} // void CDate::v_init_year_days(bool bIsLeapYear)

int CDate::i_validate_date(int iDay, int iMonth, int iYear)
{
	if (iYear < MIN_YEAR)
	{
		return DateTimeErrorCodes::ERR_INVALID_YEAR;
	}

	if (iMonth < MIN_MONTH || iMonth > v_leap_year_days_to_month.size() || iMonth > v_normal_year_days_to_month.size())
	{
		return DateTimeErrorCodes::ERR_INVALID_MONTH;
	}

	const std::vector<int>& rv_month_days = b_is_leap_year(iYear) ? v_leap_year_days_to_month : v_normal_year_days_to_month;

	if (iDay < MIN_DAY || iDay > rv_month_days.at(iMonth) - rv_month_days.at(iMonth - 1))
	{
		return DateTimeErrorCodes::ERR_INVALID_DAY;
	}

	return DateTimeErrorCodes::ERR_NO_ERROR;
} // int CDate::i_validate_date(int iDay, int iMonth, int iYear)

CDate::CDate(double dSecondsElapsed)
{
	d_seconds_elapsed = dSecondsElapsed;
} // CDate::CDate(double dSecondsElapsed)

void CDate::v_calculate_date_seconds(int iDay, int iMonth, int iYear)
{
	if (iYear >= MIN_YEAR && (iMonth >= MIN_MONTH && iMonth <= v_normal_year_days_to_month.size() 
		&& iMonth <= v_leap_year_days_to_month.size()))
	{
		const std::vector<int>& rv_days_to_month = b_is_leap_year(iYear) ? v_leap_year_days_to_month : v_normal_year_days_to_month;
		if (iDay >= MIN_DAY && iDay <= rv_days_to_month.at(iMonth) - rv_days_to_month.at(iMonth - 1))
		{
			iYear -= MIN_YEAR;
			iMonth -= MIN_MONTH;
			iDay -= MIN_DAY;
			this->d_seconds_elapsed = (iYear * DAYS_IN_NORMAL_YEAR + l_leap_years_before(iYear) + rv_days_to_month.at(iMonth) + iDay) * static_cast<double>(SECONDS_IN_DAY);
		}
	}
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

long CDate::l_leap_years_before(int iYear)
{
	long l_first_condition_leap_years = iYear / LEAP_YEAR_DIV_BY_FOUR - iYear / LEAP_YEAR_DIV_BY_ONE_HUNDRED;
	long l_second_condition_leap_years = iYear / LEAP_YEAR_DIV_BY_FOUR_HUNDREDS;
	return l_first_condition_leap_years + l_second_condition_leap_years;
} // long CDate::l_leap_years_before(int iYear)

long CDate::l_leap_years_before()
{
	long l_total_days = static_cast<long>(d_seconds_elapsed / SECONDS_IN_DAY);
	long l_first_leap_condition_years = l_total_days / DAYS_IN_FOUR_YEARS - l_total_days / DAYS_IN_ONE_HUNDRED_YEARS;
	long l_second_leap_condition_years = l_total_days / DAYS_IN_FOUR_HUNDRED_YEARS;
	return l_first_leap_condition_years + l_second_leap_condition_years;
} // long CDate::l_leap_years_before()