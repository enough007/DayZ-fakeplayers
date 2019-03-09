#include <iostream>
#include <windows.h>

void AddFakePlayers(BYTE players)
{
	uintptr_t base = (uintptr_t)GetModuleHandleA("steamclient64.dll");
	uintptr_t offset = 0x6FB703;
	uintptr_t addr = base + offset;

	unsigned char instr[] = {0x83, 0xC2, players, 0x03, 0x5B, 0xD0};

	HANDLE processHandle = GetCurrentProcess();

	DWORD oldProtection;
	VirtualProtect(reinterpret_cast<void*>(addr), sizeof(instr), PAGE_EXECUTE_READWRITE, &oldProtection);

	memcpy(reinterpret_cast<void*>(addr), instr, sizeof(instr));

	VirtualProtect(reinterpret_cast<void*>(addr), sizeof(instr), oldProtection, &oldProtection);
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		AddFakePlayers(10);
	}
	return TRUE;
}
