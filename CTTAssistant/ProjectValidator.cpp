#include "ProjectValidator.h"

bool ProjectValidator::Validate(
    const ProjectConfiguration& config)
{
    if (config.serverUrl.empty())
    {
        return false;
    }

    return true;
}