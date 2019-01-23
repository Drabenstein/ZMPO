#include "pch.h"
#include <iostream>
#include "CDate.h"

void v_display_date(CDate& rcDate)
{
	std::cout << rcDate.iGetDay() << "." << rcDate.iGetMonth() << "." << rcDate.iGetYear() << std::endl;
} // void v_display_date(const CDate& rcDate)

int main()
{
	int pi_error;
	CDate c_now(1, 1, 2019, &pi_error);
	if(pi_error != DateErrorCodes::ERR_NO_ERROR)
	{
		std::cout << "Wystapil blad\n\n";
	}
	else
	{
		v_display_date(c_now);
		CDate c_year_before = c_now - 1;
		v_display_date(c_year_before);
		/*v_display_date(c_now);
		CDate c_two_days_after = c_now - 2;
		v_display_date(c_two_days_after);
		CDate c_five_days_before = c_now - 5;
		v_display_date(c_five_days_before);
		CDate c_31_days_later = c_now + 31;
		v_display_date(c_31_days_later);
		int diff1 = c_now - c_two_days_after;
		std::cout << diff1 << std::endl;
		int diff2 = c_now - c_five_days_before;
		std::cout << diff2 << std::endl;*/
	}
} // int main()