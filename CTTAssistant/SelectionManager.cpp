#include "SelectionManager.h"

std::string SelectionManager::GetSelectionFile(
    const std::string& projectSelection,
    int choice)
{
    if (choice == 1)
    {
        return projectSelection;
    }

#ifdef _WIN32

    return "MicroEmbedded2025.selection.xml";

#else

    return "./MicroEmbedded2025.selection.xml";

#endif
}