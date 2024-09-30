#include "Initialization.h"

#include <comdef.h>
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")



// ������� ��� ������������� WMI
HRESULT InitializeWMI(IWbemServices** pSvc) {
    HRESULT hres;

    // ������������� COM-����������
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        MessageBox(NULL, L"Failed to initialize COM library. Error code = 0x", L"Error", MB_OK);
        return hres;
    }

    // ���������� ����� ������������
    hres = CoInitializeSecurity(
        NULL,
        -1,                          // ��������� ������������ �� ���������
        NULL,                        // ���������� ������������
        NULL,                        // ���������������
        RPC_C_AUTHN_LEVEL_DEFAULT,    // ������� ��������������
        RPC_C_IMP_LEVEL_IMPERSONATE,  // ������� �������������
        NULL,                        // ��������� ��������������
        EOAC_NONE,                   // ��������� ���������
        NULL                         // ���������������
    );

    if (FAILED(hres)) {
        MessageBox(NULL, L"Failed to initialize security. Error code = 0x", L"Error", MB_OK);
        CoUninitialize();
        return hres;
    }

    // �������� IWbemLocator
    IWbemLocator* pLoc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);

    if (FAILED(hres)) {
        MessageBox(NULL, L"Failed to create IWbemLocator object. Error code = 0x", L"Error", MB_OK);
        CoUninitialize();
        return hres;
    }

    // ������������ � WMI
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), // WMI namespace
        NULL,                    // User name (NULL = current user)
        NULL,                    // User password (NULL = current password)
        0,                       // Locale 
        NULL,                    // Security flags
        0,                       // Authority 
        0,                       // Context object
        pSvc                    // IWbemServices proxy
    );

    if (FAILED(hres)) {
        MessageBox(NULL, L"Could not connect to WMI. Error code = 0x", L"Error", MB_OK);
        pLoc->Release();
        CoUninitialize();
        return hres;
    }

    MessageBox(NULL, L"Connected to WMI\n", L"Successfully", MB_OK);

    // ������������� ������� �������������
    hres = CoSetProxyBlanket(
        *pSvc,                        // ��������� �� ���������
        RPC_C_AUTHN_WINNT,            // ������������ NTLM
        RPC_C_AUTHZ_NONE,             // ��� �����������
        NULL,                         // ��������� �������������� �� ���������
        RPC_C_AUTHN_LEVEL_CALL,       // ������� ��������������
        RPC_C_IMP_LEVEL_IMPERSONATE,  // ������� �������������
        NULL,                         // �������� �������
        EOAC_NONE                     // ��������� ���������
    );

    if (FAILED(hres)) {
        MessageBox(NULL, L"Could not set proxy blanket. Error code = 0x", L"Error", MB_OK);
        pLoc->Release();
        CoUninitialize();
        return hres;
    }

    pLoc->Release();
    return hres;
}

void QueryWMI(IWbemServices* pSvc, const wchar_t* query, const wchar_t* property, wchar_t write_Query_buffer[100])
{
    IEnumWbemClassObject* pEnumerator = NULL;
    HRESULT hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t(query),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres)) {

        return;
    }

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;

    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (0 == uReturn) {
            break;
        }

        VARIANT vtProp;
        hr = pclsObj->Get(property, 0, &vtProp, 0, 0);
        if (SUCCEEDED(hr)) 
        {
            for (int a = 0; vtProp.bstrVal[a] != L'\0'; a++)
            {
                write_Query_buffer[a] = vtProp.bstrVal[a];
            }
        }
        VariantClear(&vtProp);
        pclsObj->Release();
    }
    pEnumerator->Release();
}

HRESULT Initialization::Get_System_Parameters()
{
    HRESULT hr = S_OK;

        //IWbemServices* pSvc = NULL;
        //if (SUCCEEDED(InitializeWMI(&pSvc)))
        //{
            //QueryWMI(pSvc, L"SELECT Name         FROM Win32_Processor",       L"Name",           write_Query_buffer); 

            //QueryWMI(pSvc, L"SELECT Name         FROM Win32_VideoController", L"Name",           write_Query_buffer);
            //QueryWMI(pSvc, L"SELECT ScreenWidth  FROM Win32_VideoController", L"ScreenWidth",    write_Query_buffer);
            //QueryWMI(pSvc, L"SELECT ScreenHeight FROM Win32_VideoController", L"ScreenHeight",   write_Query_buffer);
            //QueryWMI(pSvc, L"SELECT RefreshRate  FROM Win32_VideoComtroller", L"RefreshRate ",   write_Query_buffer);
        //}


    return hr;
}