#pragma once

#include <string>

struct ProjectConfiguration
{
    std::string serverUrl;
    std::string securityMode;
    std::string securityPolicy;

    bool hasCertificates = false;
};