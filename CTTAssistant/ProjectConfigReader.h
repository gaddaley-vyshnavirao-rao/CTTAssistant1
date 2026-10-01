#pragma once

#include "ProjectConfiguration.h"

#include <string>

class ProjectConfigReader
{
public:
    bool Read(
        const std::string& projectFile,
        ProjectConfiguration& config);
};