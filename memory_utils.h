#pragma once
#include <windows.h>
#include <psapi.h>
#include <iostream>

// แปลง Bytes → MB
inline double toMB(SIZE_T bytes) {
    return bytes / (1024.0 * 1024.0);
}

// หน่วยความจำที่โปรแกรมนี้ใช้
inline void printProgramMemoryUsage() {
    PROCESS_MEMORY_COUNTERS_EX pmc{};
    if (GetProcessMemoryInfo(GetCurrentProcess(),
        (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        std::cout << "Program RAM used: "
                  << toMB(pmc.WorkingSetSize) << " MB";
        }
}

// RAM ว่างของระบบทั้งหมด
inline void printSystemFreeMemory() {
    MEMORYSTATUSEX statex{};
    statex.dwLength = sizeof(statex);
    if (GlobalMemoryStatusEx(&statex)) {
        std::cout << ", System free RAM: "
                  << toMB(statex.ullAvailPhys) << " MB";
    }
    std::cout << "\n";
}
