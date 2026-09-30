#pragma once

#include <string>

struct TestCaseInfo
{
    std::string category;
    std::string unit;
    std::string testCase;
    std::string description;
    std::string error;
    int resultCode = -1;
};