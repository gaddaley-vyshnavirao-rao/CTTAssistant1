#pragma once

#include <string>

class SelectionManager
{
public:
    std::string GetSelectionFile(
        const std::string& projectSelection,
        int choice);
};