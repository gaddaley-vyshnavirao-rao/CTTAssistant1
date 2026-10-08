#include "ResultParser.h"
#include "tinyxml2.h"
#include <iostream>
using namespace tinyxml2;

void ResultParser::ParseNode(
    XMLElement* node,
    std::vector<TestCaseInfo>& tests,
    std::string category,
    std::string unit)
{
    if (!node)
    {
        return;
    }

    const char* name =
        node->Attribute("name");

    if (!name)
    {
        return;
    }

    std::string nodeName = name;

    // Category
    if (category.empty())
    {
        category = nodeName;
    }
    // Unit
    else if (unit.empty())
    {
        unit = nodeName;
    }

    int resultCode = -1;

    node->QueryIntAttribute(
        "testresult",
        &resultCode);

    // Actual test case
    if (nodeName.find(".js") != std::string::npos &&
        nodeName != "initialize.js" &&
        nodeName != "cleanup.js" &&
        nodeName != "beforeTest.js" &&
        nodeName != "afterTest.js")
    {
        TestCaseInfo test;

        const char* group =
            node->Attribute("groupkey");

        if (group)
        {
            test.category = group;
        }
        else
        {
            test.category = category;
        }

        const char* unitName =
            node->Attribute("unitkey");

        if (unitName)
        {
            test.unit = unitName;
        }
        else
        {
            test.unit = unit;
        }

        test.testCase = nodeName;
        test.resultCode = resultCode;

        const char* description =
            node->Attribute("description");

        if (description)
        {
            test.description = description;
        }
        std::cout
            << "Node: "
            << nodeName
            << "\n";

        std::cout
            << "Category: "
            << category
            << "\n";

        std::cout
            << "Unit: "
            << unit
            << "\n\n";
        std::cout
            << "ResultCode: "
            << resultCode
            << "\n";
        tests.push_back(test);
    }

    XMLElement* child =
        node->FirstChildElement("ResultNode");

    while (child)
    {
        ParseNode(
            child,
            tests,
            category,
            unit);

        child =
            child->NextSiblingElement("ResultNode");
    }
}

bool ResultParser::Parse(
    const std::string& resultFile,
    std::vector<TestCaseInfo>& tests)
{
    XMLDocument doc;

    if (doc.LoadFile(resultFile.c_str()) != XML_SUCCESS)
    {
        return false;
    }

    XMLElement* root =
        doc.FirstChildElement("UaCttResults");

    if (!root)
    {
        return false;
    }

    XMLElement* latestRun = nullptr;

    XMLElement* run =
        root->FirstChildElement("ResultNode");

    while (run)
    {
        latestRun = run;

        std::cout
            << "RUN: "
            << run->Attribute("name")
            << "\n";

        run =
            run->NextSiblingElement("ResultNode");
    }

    if (latestRun)
    {
        std::cout
            << "\nLATEST RUN: "
            << latestRun->Attribute("name")
            << "\n";

        ParseNode(
            latestRun,
            tests,
            "",
            "");
        
    }
    std::cout
        << "\nParsed Tests: "
        << tests.size()
        << "\n";

    return true;
}