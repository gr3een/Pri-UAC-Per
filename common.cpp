#include "common.h"


BOOL modify_key(HKEY hkey_root, LPCSTR path, LPCSTR name, LPCSTR value, BOOL create, BOOL disableRedirection)
{
	HKEY hKey;

	if (!create){
		LSTATUS lStat = RegOpenKeyExA(hkey_root, path, 0, KEY_ALL_ACCESS, &hKey);
		if (lStat != ERROR_SUCCESS){
			printf("Cannot open Key: %x \n", GetLastError());
			return FALSE;
		}
	}
	else{
		LSTATUS lCreate = RegCreateKeyA(hkey_root, path, &hKey);
		if (lCreate != ERROR_SUCCESS){
			printf("Cannot create key: %x \n", GetLastError());
			return FALSE;
		}
	}

	//if (disableRedirection)
	//{
	//	// Disable the redirection in x64 based PC
	//	if (RegDisableReflectionKey(hKey) != ERROR_SUCCESS)
	//	{
	//		printf("Cannot successfully disable the reflection key. Error : %x\n", GetLastError());
	//		return FALSE;
	//	}

	//}

	LSTATUS lSet = RegSetValueExA(hKey, name, 0, REG_SZ, (LPBYTE)value, strlen(value));
	if (lSet != ERROR_SUCCESS){
		printf("Cannot set value: %x \n", GetLastError());
		return FALSE;
	}

	LSTATUS lClose = RegCloseKey(hKey);
	return TRUE;
}

BOOL process_create(LPCWSTR payload, LPCWSTR params)
{
	SHELLEXECUTEINFOW shellInfo = { 0 };
	shellInfo.cbSize = sizeof(shellInfo);
	shellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	//shellInfo.lpVerb = L"runas";
	shellInfo.lpFile = payload;
	shellInfo.nShow = SW_SHOW;
	shellInfo.lpParameters = params;

	return ShellExecuteExW(&shellInfo);
}

BOOL process_create_cmstp(LPCWSTR payload, LPCWSTR params, BOOL windows)
{
	SHELLEXECUTEINFOW shellInfo = { 0 };
	shellInfo.cbSize = sizeof(shellInfo);
	shellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	shellInfo.lpVerb = L"runas";
	shellInfo.lpFile = payload;
	shellInfo.nShow = SW_HIDE;
	shellInfo.lpParameters = params;

	return ShellExecuteExW(&shellInfo);
}


BOOL process_runas(LPCWSTR payload, LPCWSTR params )
{
	SHELLEXECUTEINFOW shinfo = { 0 };
	shinfo.cbSize = sizeof(shinfo);
	shinfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	shinfo.lpVerb = L"runas";
	shinfo.lpFile = payload;
	shinfo.nShow = SW_HIDE;
	shinfo.lpParameters = params;


	return ShellExecuteExW(&shinfo);
}

 BOOL endsWith(string mainStr,string toMatch)
   {
		if (mainStr.size() >= toMatch.size() && mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}


 