#pragma once

// host.h
// 8/23/2013 jichi
// Branch: ITH/IHF.h, rev 105

//#include "host/settings.h"
#include "host/hookman.h"

struct Settings;
struct HookParam;

void Host_Init();
void Host_Destroy();

DWORD Host_Start();
BOOL Host_Open();
DWORD Host_Start();
DWORD Host_Close();
DWORD Host_GetPIDByName(LPCWSTR pwcTarget);
DWORD Host_InjectByPID(DWORD pid);
DWORD Host_ActiveDetachProcess(DWORD pid);
DWORD Host_GetHookManager(HookManager **hookman);
DWORD Host_GetSettings(Settings **settings);
DWORD Host_InsertHook(DWORD pid, HookParam *hp, LPWSTR name = nullptr);
DWORD Host_ModifyHook(DWORD pid, HookParam *hp);
DWORD Host_RemoveHook(DWORD pid, DWORD addr);
DWORD Host_AddLink(DWORD from, DWORD to);
DWORD Host_UnLink(DWORD from);
DWORD Host_UnLinkAll(DWORD from);

// EOF
