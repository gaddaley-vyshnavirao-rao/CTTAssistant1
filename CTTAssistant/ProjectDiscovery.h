#pragma once

#include "ProjectInfo.h"
#include <string>

class ProjectDiscovery
{
public:
    bool Discover(
        const std::string& projectPath,
        ProjectInfo& info);
};