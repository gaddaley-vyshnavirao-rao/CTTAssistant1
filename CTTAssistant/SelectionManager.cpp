#include "SelectionManager.h"

std::string SelectionManager::GetSelectionFile(
    const std::string& projectSelection,
    int choice)
{
    if (choice == 1)
    {
        return projectSelection;
    }

    return "C:\\Users\\z005caxw\\Desktop\\CTTAssistant\\CTTAssistant\\CTTAssistant\\MicroEmbedded2025.selection.xml";

}