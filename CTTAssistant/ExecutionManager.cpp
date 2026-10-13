#include "ExecutionManager.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

bool ExecutionManager::Launch(
    const std::string& cttPath,
    const std::string& projectFile,
    const std::string& selectionFile)
{
    std::string command =
        "\"" + cttPath + "\" "
        "--settings \"" + projectFile + "\" "
        "--selection \"" + selectionFile + "\"";

    std::cout
        << "\nCOMMAND:\n"
        << command
        << "\n\n";

#ifdef _WIN32

    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};

    si.cb = sizeof(si);

    char cmdLine[4096];
    strcpy_s(cmdLine, command.c_str());

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
        std::cout
            << "\nFailed to start CTT\n";

        return false;
    }

    std::cout
        << "\nCTT Started...\n";

    WaitForSingleObject(
        pi.hProcess,
        INFINITE);

    std::cout
        << "\nCTT Closed.\n";

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;

#else

    std::cout
        << "\nCTT Started...\n";

    int result =
        std::system(command.c_str());

    std::cout
        << "\nCTT Closed.\n";

    return result == 0;

#endif
}