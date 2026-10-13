#include <iostream>
#include "ProjectDiscovery.h"
#include "ExecutionManager.h"
#include "SelectionManager.h"
#include "ResultParser.h"
#include <vector>
#include "HTMLReportGenerator.h"
#ifdef _WIN32
#include <Windows.h>
#include <Shellapi.h>
#endif

#include <ctime>
#include <filesystem>
#include "ProjectConfigReader.h"
#include "ProjectConfiguration.h"
#include "EndpointParser.h"
#include "EndpointInfo.h"
int main()
{
    std::string projectPath;

    std::cout << "=====================================\n";
    std::cout << "         CTT Assistant\n";
    std::cout << "=====================================\n\n";

    std::cout << "Enter Project Path: ";

    std::getline(std::cin, projectPath);

    ProjectDiscovery discovery;
    ProjectInfo info;

    if (!discovery.Discover(projectPath, info))
    {
        std::cout << "\nProject files not found.\n";
        return 1;
    }

    std::cout << "\nProject File:\n"
        << info.projectFile;

    std::cout << "\n\nSelection File:\n"
        << info.selectionFile
        << "\n";
    
    ProjectConfigReader configReader;

    ProjectConfiguration config;

    if (configReader.Read(
        info.projectFile,
        config))
    {
        std::cout
            << "\n=====================================\n";

        std::cout
            << "      PROJECT CONFIGURATION\n";

        std::cout
            << "=====================================\n\n";

        std::cout
            << "Server URL : "
            << config.serverUrl
            << "\n";
        EndpointParser parser;

        EndpointInfo endpoint;

        if (parser.Parse(
            config.serverUrl,
            endpoint))
        {
            std::cout
                << "Host : "
                << endpoint.host
                << "\n";

            std::cout
                << "Port : "
                << endpoint.port
                << "\n";
        }
        

        std::cout
            << "Certificates : "
            << (config.hasCertificates
                ? "Configured"
                : "Not Configured")
            << "\n";
    }

    SelectionManager selectionManager;
    int choice;

    std::cout << "\nSelection Mode\n";
    std::cout << "1. Project Selection\n";
    std::cout << "2. MicroEmbedded2025 Standard Selection\n";
    std::cout << "Choice: ";

    std::cin >> choice;
    
    std::string selectionFile =
        selectionManager.GetSelectionFile(
            info.selectionFile,
            choice);

    std::cout << "\nUsing Selection:\n"
        << selectionFile
        << "\n";

    

    std::vector<TestCaseInfo> tests;
    std::filesystem::path projectFilePath(
        info.projectFile);

    std::string projectName =
        projectFilePath.stem().string();

    if (projectName.size() > 4 &&
        projectName.substr(projectName.size() - 4) == ".ctt")
    {
        projectName =
            projectName.substr(
                0,
                projectName.size() - 4);
    }
    std::filesystem::path runtimeProject =
        projectFilePath.parent_path() /
        (projectName + "_runtime.ctt.xml");

    std::filesystem::copy_file(
        projectFilePath,
        runtimeProject,
        std::filesystem::copy_options::overwrite_existing);

    ExecutionManager manager;

#ifdef _WIN32

    std::string cttPath =
        "C:\\Program Files\\OPC Foundation\\UA 1.05\\Compliance Test Tool\\uacompliancetest.exe";

#else

    std::string cttPath =
        "/home/siemens/Downloads/uactt/UaCtt-1.03.09-01.00.513-x86_64.AppImage";

#endif

    manager.Launch(
        cttPath,
        runtimeProject.string(),
        selectionFile);
    std::filesystem::path resultFile =
        std::filesystem::path(projectPath) /
        (projectName + "_runtime.results.xml");
    ResultParser parser;
    std::vector<TestCaseInfo> approved;
    std::vector<TestCaseInfo> failed;
    std::vector<TestCaseInfo> warning;
    std::vector<TestCaseInfo> skipped;

    int approvedCount = 0;
    int failedCount = 0;
    int warningCount = 0;
    int skippedCount = 0;
    std::cout
        << "\nParsing File:\n"
        << resultFile
        << "\n";
    if (parser.Parse(resultFile.string(), tests))
    {
        std::cout
            << "\nXML Parsed Successfully\n";

        for (const auto& test : tests)
        {
            if (test.resultCode == 6)
            {
                approved.push_back(test);
                approvedCount++;
            }
            else if (test.resultCode == 0)
            {
                failed.push_back(test);
                failedCount++;
            }
            else if (test.resultCode == 1)
            {
                warning.push_back(test);
                warningCount++;
            }
            else if (test.resultCode == 4)
            {
                skipped.push_back(test);
                skippedCount++;
            }
        }
        std::cout
            << "\nParsed Tests: "
            << tests.size()
            << "\n";
        int total =
            approvedCount +
            failedCount +
            warningCount +
            skippedCount;

        double successRate =
            (total == 0)
            ? 0.0
            : (approvedCount * 100.0) / total;

        std::cout
            << "\n=====================================\n";

        std::cout
            << "            TEST SUMMARY\n";

        std::cout
            << "=====================================\n\n";

        std::cout
            << "Total Tests : "
            << total
            << "\n";

        std::cout
            << "Approved    : "
            << approvedCount
            << "\n";

        std::cout
            << "Failed      : "
            << failedCount
            << "\n";

        std::cout
            << "Warning     : "
            << warningCount
            << "\n";

        std::cout
            << "Skipped     : "
            << skippedCount
            << "\n";

        std::cout
            << "\nSuccess Rate : "
            << successRate
            << "%\n";
    }
    else
    {
        std::cout
            << "\nFailed To Parse XML\n";
    }
    HTMLReportGenerator report;
    time_t now = time(nullptr);

    tm localTime;
#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    char dateTime[100];

    strftime(
        dateTime,
        sizeof(dateTime),
        "%d-%b-%Y %I:%M %p",
        &localTime);

    std::filesystem::path reportPath =
        std::filesystem::path(projectPath) /
        "CTT_Report.html";
    
    
    if(report.Generate(
        reportPath.string(),
        projectName,
        dateTime,
        approved,
        failed,
        warning,
        skipped))

    {
        std::cout
            << "\nHTML Report Generated\n";

        std::cout
            << "\nReport Location:\n"
            << reportPath
            << "\n";

        std::cout
            << "\nOpening Report...\n";

#ifdef _WIN32

        ShellExecuteA(
            NULL,
            "open",
            reportPath.string().c_str(),
            NULL,
            NULL,
            SW_SHOW);

#else

        std::string openCommand =
            "xdg-open \"" +
            reportPath.string() +
            "\"";

        system(openCommand.c_str());

#endif
    }
    else
    {
        std::cout
            << "\nFailed To Generate HTML Report\n";
    }
    if (std::filesystem::exists(runtimeProject))
    {
        std::filesystem::remove(runtimeProject);
    }
    return 0;
}