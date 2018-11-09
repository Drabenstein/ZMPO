#pragma once;

class CConsoleInputHelper
{
private:
	bool b_readTableIndex(int * piIndex) const;

public:
	static const CConsoleInputHelper& rcGetInstance();

	bool bReadTableIndex(int * piTableIndex) const;

	bool bReadValueIndex(int * piValueIndex) const;

	bool bReadTableLength(int * piTableLength) const;

	bool bReadValue(int * piValue) const;
};