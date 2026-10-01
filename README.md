# CTTAssistant


CTT Assistant is a C++ automation framework developed to automate OPC UA Compliance Test Tool (CTT) execution and reporting.

## Overview

The tool simplifies the CTT testing workflow by:

- Discovering CTT project files automatically
- Loading project or standard selection files
- Launching OPC UA Compliance Test Tool (CTT)
- Parsing generated XML results
- Calculating execution statistics
- Generating dynamic HTML reports
- Opening reports automatically after execution

## Features

### Project Discovery
- Auto-detects `.ctt.xml` project files
- Auto-detects project selection files

### Selection Management
- Use project-specific selection files
- Use standard `MicroEmbedded2025.selection.xml`

### CTT Automation
- Launches CTT through CLI
- Loads selected configuration automatically
- Waits for test execution completion

### Result Processing
- Parses generated XML result files
- Extracts test execution results
- Calculates:
  - Approved
  - Failed
  - Warning
  - Skipped
  - Success Rate

### HTML Reporting
- Interactive expandable report
- Status-based grouping
- Category grouping
- Conformance Unit grouping
- Automatic report opening

### Report Summary
Displays:
- Project Name
- Execution Date & Time
- Total Issues
- Approved Count
- Failed Count
- Warning Count
- Skipped Count
- Success Rate

## Workflow

```text
RunCTT.bat
    ↓
Enter Project Path
    ↓
Choose Selection
    ↓
Launch CTT
    ↓
Execute Tests
    ↓
Close CTT
    ↓
Parse Results XML
    ↓
Generate Statistics
    ↓
Generate HTML Report
    ↓
Open Report Automatically
``
