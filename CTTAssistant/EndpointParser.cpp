#include "EndpointParser.h"

bool EndpointParser::Parse(
    const std::string& endpoint,
    EndpointInfo& info)
{
    std::string prefix =
        "opc.tcp://";

    size_t start =
        endpoint.find(prefix);

    if (start == std::string::npos)
    {
        return false;
    }

    start += prefix.length();

    size_t colon =
        endpoint.find(':', start);

    if (colon == std::string::npos)
    {
        return false;
    }

    info.host =
        endpoint.substr(
            start,
            colon - start);

    std::string portText =
        endpoint.substr(colon + 1);

    info.port =
        std::stoi(portText);

    return true;
}