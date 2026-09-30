#pragma once

#include <string>

class ExecutionManager
{
public:
    bool Launch(
        const std::string& cttPath,
        const std::string& projectFile,
        const std::string& selectionFile);
};