#pragma once

#import "Neptune.tlb" named_guids rename_namespace("NEPTUNELib")

class CNeptunePublicWrap
{
public:
	CNeptunePublicWrap(void);
	~CNeptunePublicWrap(void);

	static BOOL IsInitSuccessed(void) { return m_bInitSusccessed; }
	static BOOL CreateNeptunePublicComPtr();
	static void ReleaseNeptunePublicComPtr();

// Actual Interface method
	static long MachineGoto(double x, double y, double z);
	static long GetCurrentMachinePosition(double& x, double& y, double& z);
	static bool IsMachineIdle();

	static	NEPTUNELib::IKNeptunePublicPtr	m_spNeptunePublic;
private:
	static	BOOL	m_bInitSusccessed;
};
