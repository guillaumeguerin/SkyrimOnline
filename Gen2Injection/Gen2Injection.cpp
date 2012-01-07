// Gen2Injection.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include <stdio.h>
#include <windows.h>
#include <mscoree.h>
#include <metahost.h>
#pragma comment(lib, "mscoree.lib")

#import "mscorlib.tlb"	\
	raw_interfaces_only														\
	high_property_prefixes("_get","_put","_putref")							\
	rename("ReportEvent", "InteropServices_ReportEvent")

using namespace mscorlib;

extern "C"
{
	__declspec(dllexport) void __cdecl Loader();
	__declspec(dllexport) UINT _cdecl GetCurrentPlayerID();
}

UINT GetCurrentPlayerID()
{
	return 666;
}

void Loader()
{
	LPCTSTR failMessage = NULL;
	MessageBox(NULL, L"Starting", NULL, MB_OK);
	ICLRMetaHost *pMetaHost = NULL;
	ICLRRuntimeInfo *pRuntimeInfo = NULL;
	ICLRRuntimeHost *pClrRuntimeHost = NULL;
	ICorRuntimeHost *pCorRuntimeHost = NULL;
	IUnknownPtr spAppDomainThunk = NULL;
	_AppDomainPtr spDefaultAppDomain = NULL;
	_AssemblyPtr spAssembly = NULL;
	_TypePtr spType = NULL;
	SAFEARRAY *psaStaticMethodArgs = NULL;
	variant_t vtEmpty;
	variant_t vtLengthRet;
	bstr_t bstrAssemblyName(L"Gen2Host.exe");
	bstr_t bstrClassName(L"Gen2Host.Program");
	bstr_t bstrStaticMethodName(L"Main");

	HRESULT hr= CLRCreateInstance(CLSID_CLRMetaHost, IID_PPV_ARGS(&pMetaHost));
	if (FAILED(hr))
		{
			failMessage = L"CLRCreateInstance";
			goto Cleanup;
		}

	hr = pMetaHost->GetRuntime(L"v4.0.30319", IID_PPV_ARGS(&pRuntimeInfo));
	if (FAILED(hr))
	{
		failMessage = L"GetRuntime";
		goto Cleanup;
	}

	BOOL fLoadable;

	hr = pRuntimeInfo->IsLoadable(&fLoadable);
	if (FAILED(hr) || !fLoadable)
	{
		failMessage = L"IsLoadable";
		goto Cleanup;
	}

	hr = pRuntimeInfo->GetInterface(CLSID_CorRuntimeHost, IID_PPV_ARGS(&pCorRuntimeHost));
	if (FAILED(hr))
	{
		failMessage = L"GetInterface";
		goto Cleanup;
	}

	hr = pCorRuntimeHost->Start();
	if (FAILED(hr)) 
	{
		failMessage = L"Start";
		goto Cleanup;
	}

	hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(bstrAssemblyName, bstrClassName, bstrStaticMethodName, NULL, NULL);
	if (FAILED(hr)) 
	{
		failMessage = L"ExecuteInDefaultAppDomain";
		goto Cleanup;
	}

Cleanup:
	if(failMessage)
		MessageBox(NULL, failMessage, NULL, MB_OK);
}