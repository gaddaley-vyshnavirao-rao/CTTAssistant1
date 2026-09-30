#include "HTMLReportGenerator.h"

#include <fstream>
#include <map>

static void WriteSection(
    std::ofstream& html,
    const std::string& title,
    const std::vector<TestCaseInfo>& tests)
{
    html << "<details open>";

    html << "<summary>"
        << title
        << " ("
        << tests.size()
        << ")"
        << "</summary>";

    std::map<
        std::string,
        std::map<
        std::string,
        std::vector<TestCaseInfo>
        >
    > grouped;

    for (const auto& test : tests)
    {
        grouped[test.category]
            [test.unit]
            .push_back(test);
    }

    for (const auto& category : grouped)
    {
        html << "<details>";

        html << "<summary>"
            << category.first
            << "</summary>";

        for (const auto& unit : category.second)
        {
            html << "<details>";

            html << "<summary>"
                << unit.first
                << "</summary>";

            for (const auto& test : unit.second)
            {
                html << "<div class='test'>";

                html << "<b>"
                    << test.testCase
                    << "</b><br><br>";

                html << test.description;

                html << "</div>";
            }

            html << "</details>";
        }

        html << "</details>";
    }

    html << "</details>";
}

bool HTMLReportGenerator::Generate(
    const std::string& outputFile,
    const std::string& projectName,
    const std::string& dateTime,
    const std::vector<TestCaseInfo>& approved,
    const std::vector<TestCaseInfo>& failed,
    const std::vector<TestCaseInfo>& warning,
    const std::vector<TestCaseInfo>& skipped)
{
    std::ofstream html(outputFile);

    if (!html.is_open())
    {
        return false;
    }

    html << R"(

<!DOCTYPE html>
<html>
<head>

<title>CTT Report</title>

<style>

body{
    font-family:Segoe UI;
    margin:40px;
    background:#f5f5f5;
}

h1{
    text-align:center;
}

.info{
    background:white;
    padding:15px;
    border-radius:8px;
    margin-bottom:20px;
}

.card{
    display:inline-block;
    width:180px;
    margin:10px;
    padding:20px;
    color:white;
    text-align:center;
    border-radius:8px;
    font-size:20px;
    font-weight:bold;
}

.approved{
    background:#28a745;
}

.failed{
    background:#dc3545;
}

.warning{
    background:#ff9800;
}

.skipped{
    background:#2196f3;
}

.test{
    background:white;
    padding:10px;
    margin:10px 0;
    border-radius:5px;
    border-left:4px solid #cccccc;
}

details{
    margin-top:10px;
    margin-left:15px;
}

summary{
    cursor:pointer;
    padding:10px;
    background:white;
    border-radius:5px;
    font-weight:bold;
}

summary:hover{
    background:#ececec;
}

</style>

</head>

<body>

<h1>CTT TEST REPORT</h1>

)";

    html << "<div class='info'>";

    html << "<b>Project Name:</b> "
        << projectName
        << "<br><br>";

    html << "<b>Generated On:</b> "
        << dateTime
        << "<br><br>";

    html << "<b>Total Issues:</b> "
        << (failed.size()
            + warning.size()
            + skipped.size());

    html << "</div>";

    html << "<div class='card approved'>Approved<br>"
        << approved.size()
        << "</div>";

    html << "<div class='card failed'>Failed<br>"
        << failed.size()
        << "</div>";

    html << "<div class='card warning'>Warning<br>"
        << warning.size()
        << "</div>";

    html << "<div class='card skipped'>Skipped<br>"
        << skipped.size()
        << "</div>";

    WriteSection(
        html,
        "Approved",
        approved);

    WriteSection(
        html,
        "Failed",
        failed);

    WriteSection(
        html,
        "Warning",
        warning);

    WriteSection(
        html,
        "Skipped",
        skipped);

    html << "</body></html>";

    html.close();

    return true;
}