#pragma once

#include "TestCaseInfo.h"
#include "tinyxml2.h"

#include <string>
#include <vector>

class ResultParser
{
public:
    bool Parse(
        const std::string& resultFile,
        std::vector<TestCaseInfo>& tests);

private:
    void ParseNode(
        tinyxml2::XMLElement* node,
        std::vector<TestCaseInfo>& tests,
        std::string category,
        std::string unit);
};