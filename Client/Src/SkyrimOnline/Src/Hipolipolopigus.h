#include						"MetaHost.h"
#include						"MSCorEE.h"
#include						"common\plugin.h"
#pragma							comment(lib, "mscoree.lib") 
#import							"mscorlib.tlb" raw_interfaces_only                \
								high_property_prefixes("_get","_put","_putref")        \
								rename("ReportEvent", "InteropServices_ReportEvent")
#pragma once

#define							SkyNet_Core				L"SkyNet.exe"
#define							SkyNet_Globals			L"globals"
#define							SkyNet_Check			L"Core_Check"
#define							SkyNet_Main				L"Core_Main"

using namespace					mscorlib;

ICLRRuntimeHost					*pClrRuntimeHost = NULL;
ICLRRuntimeInfo					*pRuntimeInfo = NULL;
ICorRuntimeHost					*pCorRuntimeHost = NULL;
IUnknownPtr						spAppDomainThunk = NULL;
_AppDomainPtr					spDefaultAppDomain = NULL;
ICLRMetaHost					*pMetaHost = NULL;

class sPipe
{
public:
	sPipe(LPTSTR Name)
	{

	}
}

void Hipo_MakeHostPipe(LPTSTR Name)
{
	sPipe p = sPipe(Name);
	
}

int CLR_Execute(LPCWSTR Assembly, LPCWSTR Class, LPCWSTR Method, LPCWSTR Argument)
{
	DWORD result = 0;
	pClrRuntimeHost->ExecuteInDefaultAppDomain(Assembly, Class, Method, Argument, &result);
	return result;
}

void CLR_Init()
{
	HRESULT hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_PPV_ARGS(&pMetaHost));
	if (FAILED(hr))
	{
		PrintNote("CLR Failed at CLRCreateInstance");
		goto clean;
	}
	hr = pMetaHost->GetRuntime(L"v4.0.30319", IID_PPV_ARGS(&pRuntimeInfo));
	if (FAILED(hr))
	{
		PrintNote("CLR Failed at GetRuntime");
		goto clean;
	}
	BOOL fLoadable;
	hr = pRuntimeInfo->IsLoadable(&fLoadable);
	if (FAILED(hr))
	{
		PrintNote("CLR Failed at IsLoadable");
		goto clean;
	}
	if (!fLoadable)
	{
		PrintNote("CLR is not loadable.");
		goto clean;
	}
	hr = pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_PPV_ARGS(&pClrRuntimeHost));
	if (FAILED(hr))
	{
		PrintNote("CLR Failed at GetInterface (COR)");
		goto clean;
	}
	hr = pClrRuntimeHost->Start();
	if (FAILED(hr))
	{
		PrintNote("CLR Failed at Start");
		goto clean;
	}
	goto success;
clean:
	{
		goto exit;
	}
success:
	{
		int r = CLR_Execute(SkyNet_Core, SkyNet_Globals, SkyNet_Check, L"");
		if(r)
		{
			//Execute returned process handle of an active SkyNet service, connect to it
		}
		else
		{
			//Execute returned 0, start a new SkyNet service and connect to it
			r = CLR_Execute(SkyNet_Core, SkyNet_Globals, SkyNet_Main, L"");
		}
	}
exit:
	{

	}
}