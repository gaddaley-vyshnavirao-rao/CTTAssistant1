#pragma once

#include "TestCaseInfo.h"

#include <string>
#include <vector>

class HTMLReportGenerator
{
public:
    bool Generate(
        const std::string& outputFile,
        const std::string& projectName,
        const std::string& dateTime,
        const std::vector<TestCaseInfo>& approved,
        const std::vector<TestCaseInfo>& failed,
        const std::vector<TestCaseInfo>& warning,
        const std::vector<TestCaseInfo>& skipped);
};