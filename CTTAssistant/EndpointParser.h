#pragma once

#include "EndpointInfo.h"

#include <string>

class EndpointParser
{
public:
    bool Parse(
        const std::string& endpoint,
        EndpointInfo& info);
};