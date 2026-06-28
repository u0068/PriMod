//
// Created by tayler on 6/28/26.
//

#include "main.h"

#include <windows.h>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <ostream>

// #include <MinHook.h>

// basic main
int main(int argc, char ** argv) {

    std::string path = std::filesystem::current_path().string();
    printf("Current working directory: %s\n", path.c_str());

    // find primordialis file in current running directory
    char exe[MAX_PATH];
    snprintf(exe, sizeof(exe), "%s\\primordialis.exe", path.c_str());

    // launch Primordialis
    printf("Launching Primordialis from: %s\n", exe);

    SHELLEXECUTEINFO info = {0};
    info.cbSize = sizeof(SHELLEXECUTEINFO);
    info.fMask = SEE_MASK_NOCLOSEPROCESS;
    info.hwnd = NULL;
    info.lpVerb = "open";
    info.lpFile = exe;
    info.lpParameters = "";
    info.lpDirectory = argv[1];
    info.nShow = SW_SHOW;

    if (ShellExecuteEx(&info)) {
        int pid = 0;
        HANDLE hProc = NULL;


        hProc = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION |
                     PROCESS_VM_OPERATION  | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, GetProcessId(info.hProcess));
        if (hProc != NULL) {

            // we now have primordialis handle??


            // uintptr_t base = (uintptr_t)hProc;
            // AllocConsole();
            //
            // // log base
            // printf("Base address: 0x%p\n", (void*)base);
            // using LogPrintfFn = int(*)(const char*);
            // LogPrintfFn logPrintf = nullptr;
            //
            // logPrintf = reinterpret_cast<LogPrintfFn>(base + 0x218C0);
            // logPrintf("LOG WORKS :D");
            //
            // CloseHandle(hProc);
        }

        // injection time >:)

    }


    while (true) {
        // do nothing
    }
    return 0;
}