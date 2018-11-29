#include "pch.h"
#include "CValue.h"

CValue::CValue()
{
	pv_value = nullptr;
	b_is_owner = false;
} // CValue::CValue()

CValue::CValue(const CValue& rcOther)
{
	pv_value = rcOther.pv_value;
	b_is_owner = false;
} // CValue::CValue(CValue & rcOther)

CValue::~CValue()
{
	v_clear_ptr();
} // CValue::~CValue()

bool CValue::bEquals(CValue* pcOther)
{
	if(pcOther == nullptr)
	{
		return false;
	}

	return pv_value == pcOther->pv_value;
} // bool CValue::bEquals(CValue * pcOther)

void CValue::vSetValue(void* pvValue, bool bOwner)
{
	v_clear_ptr();
	pv_value = pvValue;
	b_is_owner = bOwner;
} // void CValue::vSetValue(void ** pvValue, bool bOwner)

void CValue::v_clear_ptr()
{
	if (b_is_owner && pv_value != nullptr)
	{
		delete pv_value;
	}
} // void CValue::v_clear_ptr()
