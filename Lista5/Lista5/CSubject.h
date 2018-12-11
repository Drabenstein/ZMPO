#pragma once

class CSubject
{
public:
	CSubject(double dValue, double dSize) : d_value(dValue), d_size(dSize) {}

	double dGetValue() { return d_value; }
	double dGetSize() { return d_size; }

private:
	double d_value;
	double d_size;
};