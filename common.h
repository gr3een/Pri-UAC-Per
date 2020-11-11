#ifndef COMMON_H
#define COMMON_H

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "Shell32.lib")

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <winuser.h>
#include <shellapi.h>
#include <time.h>
#include <algorithm>
#include <Shlwapi.h>
#include <Synchapi.h>
#include <fileapi.h>  
#include <map>
#include <shlobj_core.h>

#pragma comment(lib, "Shlwapi.lib")

using namespace std;

BOOL modify_key(HKEY hkey_root, LPCSTR path, LPCSTR name, LPCSTR value, BOOL create = TRUE, BOOL disableRedirection = FALSE);
BOOL process_create(LPCWSTR payload, LPCWSTR params);
BOOL process_create_cmstp(LPCWSTR payload, LPCWSTR params, BOOL windows = FALSE);
BOOL process_runas(LPCWSTR payload, LPCWSTR params = NULL);
BOOL endsWith(string mainstr, string tomatch);


#endif