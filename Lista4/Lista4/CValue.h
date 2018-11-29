#pragma once

class CValue
{
public:
	CValue();

	CValue(const CValue& rcOther);

	~CValue();

	bool bEquals(CValue* pcOther);

	void vSetValue(void* pvValue, bool bOwner);

private:
	void* pv_value;
	bool b_is_owner;

	void v_clear_ptr();
};