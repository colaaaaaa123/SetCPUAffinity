#include <Windows.h>

static inline void Log(const char* s) { OutputDebugStringA(s); OutputDebugStringA("\n"); }

BOOL APIENTRY DllMain(HINSTANCE h, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(h);

        DWORD_PTR processMask = 0, systemMask = 0;
        if (GetProcessAffinityMask(GetCurrentProcess(), &processMask, &systemMask)) {
            if (!SetProcessAffinityMask(GetCurrentProcess(), systemMask)) {
                Log("Error: SetProcessAffinityMask failed.");
            }
            else {
                Log("SetProcessAffinityMask succeeded.");
            }
        }
        else {
            Log("Error: GetProcessAffinityMask failed.");
        }
    }
    return TRUE;
}
