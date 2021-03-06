/*
FileCopyEx - Extended File Copy plugin for Far 2 file manager

Copyright (C) 2004 - 2010
Idea & core: Max Antipin
Coding: Serge Cheperis aka craZZy
Bugfixes: slst, CDK, Ivanych, Alter, Axxie and Nsky
Special thanks to Vitaliy Tsubin
Far 2 (32 & 64 bit) full unicode version by djdron

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Framework/stdhdr.h"
#include "Framework/objstring.h"
#include "common.h"

void FWError(const wchar_t *s)
{
	if (errorHandler) {
		errorHandler(s);
	} else {
		MessageBox(0, s, L"FileCopyEx plugin error", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
		DebugBreak();
	}
}

void FWError(const String &s)
{
	FWError(s.ptr());
}

ErrorHandler errorHandler=NULL;

int WinNT, WinNT4, Win2K, WinXP;
HANDLE hInstance;

BOOL __stdcall DllMain(HANDLE hInst, ULONG reason, LPVOID)
{
	hInstance = hInst;
	if(reason == DLL_PROCESS_ATTACH)
	{
		_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG)|_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
		OSVERSIONINFO osv;
		osv.dwOSVersionInfoSize=sizeof(osv);
		GetVersionEx(&osv);
		WinNT=osv.dwPlatformId==VER_PLATFORM_WIN32_NT;
		WinNT4=WinNT && osv.dwMajorVersion==4;
		Win2K=WinNT && osv.dwMajorVersion>=5;
		WinXP=Win2K && (osv.dwMajorVersion>5 || osv.dwMinorVersion>=1);
	}
	return TRUE;
}

const String& LOC(const String& l)
{
	try {
		return plugin->getLocale().at(l);
	} catch (const std::out_of_range&) {
		return l; 
	}
}