#include "ExecutionManager.h"

#include <windows.h>
#include <iostream>

bool ExecutionManager::Launch(
    const std::string& cttPath,
    const std::string& projectFile,
    const std::string& selectionFile)
{
    std::string command =
        "\"" + cttPath + "\" "
        "--settings \"" + projectFile + "\" "
        "--selection \"" + selectionFile + "\"";

    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};

    si.cb = sizeof(si);

    char cmdLine[4096];
    strcpy_s(cmdLine, command.c_str());
    std::cout << "\nCOMMAND:\n"
        << command
        << "\n\n";
    BOOL success =
        CreateProcessA(
            NULL,
            cmdLine,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi);

    if (!success)
    {
        std::cout << "\nFailed to start CTT\n";
        return false;
    }

    std::cout << "\nCTT Started...\n";

    WaitForSingleObject(
        pi.hProcess,
        INFINITE);

    std::cout << "\nCTT Closed.\n";

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}