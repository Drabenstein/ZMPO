#pragma once;

class CConsoleInputHelper
{
public:
	static const CConsoleInputHelper& rcGetInstance();

	bool bReadTableIndex(int * piTableIndex) const;

	bool bReadValueIndex(int * piValueIndex) const;

	bool bReadTableLength(int * piTableLength) const;

	bool bReadValue(int * piValue) const;

private:
	bool b_readTableIndex(int * piIndex) const;
};