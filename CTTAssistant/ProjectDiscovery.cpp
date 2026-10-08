#include "ProjectDiscovery.h"

#include <filesystem>

namespace fs = std::filesystem;

bool ProjectDiscovery::Discover(
    const std::string& projectPath,
    ProjectInfo& info)
{
    if (!fs::exists(projectPath))
    {
        return false;
    }

    for (const auto& entry :
        fs::recursive_directory_iterator(projectPath))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }

        std::string file =
            entry.path().string();

        if (file.find("_runtime.ctt.xml") != std::string::npos)
        {
            continue;
        }

        if (file.find(".ctt.xml") != std::string::npos)
        {
            info.projectFile = file;
        }

        if (file.find(".selection.xml") != std::string::npos)
        {
            info.selectionFile = file;
        }
    }

    info.resultFolder = projectPath;

    return !info.projectFile.empty();
    
}