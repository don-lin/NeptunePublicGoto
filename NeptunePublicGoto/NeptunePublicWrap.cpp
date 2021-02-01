#include "StdAfx.h"
#include "NeptunePublicWrap.h"

BOOL CNeptunePublicWrap::m_bInitSusccessed = FALSE;
NEPTUNELib::IKNeptunePublicPtr	CNeptunePublicWrap::m_spNeptunePublic;

CNeptunePublicWrap::CNeptunePublicWrap(void)
{
}

CNeptunePublicWrap::~CNeptunePublicWrap(void)
{
}

BOOL CNeptunePublicWrap::CreateNeptunePublicComPtr()
{
	for(int i = 0; i < 5; i++)
	{
		HRESULT hr = m_spNeptunePublic.CreateInstance(_T("Neptune.KNeptunePublic"));
		if (SUCCEEDED(hr))
			break;
		Sleep(3000);
	}

	if (m_spNeptunePublic == NULL)
	{
		m_bInitSusccessed = FALSE;
		AfxMessageBox(_T("Can not find Neptune server!"));
	}
	else
	{
		m_bInitSusccessed = TRUE;
	}

	return m_bInitSusccessed;
}

void CNeptunePublicWrap::ReleaseNeptunePublicComPtr()
{
	if(m_bInitSusccessed)
	{
		if (m_spNeptunePublic != NULL)		
			m_spNeptunePublic.Release();
	}
}

long CNeptunePublicWrap::MachineGoto(double x, double y, double z)
{
	long lRet = -1;
	if(m_bInitSusccessed)	
		lRet = m_spNeptunePublic->EASI_MachineGoto(x, y, z);

	return lRet;
}

long CNeptunePublicWrap::GetCurrentMachinePosition(double& x, double& y, double& z)
{
	long lRet = -1;
	if(m_bInitSusccessed)	
		lRet = m_spNeptunePublic->EASI_GetCurrentMachinePosition(&x, &y, &z);

	return lRet;
}

bool CNeptunePublicWrap::IsMachineIdle()
{
	bool bRet = false;
	if(m_bInitSusccessed)	
	{
		LONG lStatus = 0;
		if(!m_spNeptunePublic->EASI_GetMachineStatus(&lStatus))
		{
			if(lStatus & 0x00000001)//0x00000001 for IDLE
				bRet = true;		//0x00000002 for HOMED
									//0x00000004 for SENSOR READY
		}
	}

	return bRet;
}
