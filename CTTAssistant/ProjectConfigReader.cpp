#include "ProjectConfigReader.h"

#include "tinyxml2.h"

using namespace tinyxml2;

namespace
{
    void TraverseNode(
        XMLElement* node,
        ProjectConfiguration& config,
        bool& nextIsServerUrl)
    {
        if (!node)
        {
            return;
        }

        const char* data =
            node->Attribute("data");

        if (data)
        {
            std::string value = data;

            // Found the field name
            if (value == "Server URL")
            {
                nextIsServerUrl = true;
            }

            // Next value after "Server URL"
            else if (nextIsServerUrl)
            {
                config.serverUrl = value;
                nextIsServerUrl = false;
            }

            // Certificate detection
            if (value.find("PKI/CA") != std::string::npos)
            {
                config.hasCertificates = true;
            }
        }

        for (XMLElement* child =
            node->FirstChildElement();
            child;
            child =
            child->NextSiblingElement())
        {
            TraverseNode(
                child,
                config,
                nextIsServerUrl);
        }
    }
}

bool ProjectConfigReader::Read(
    const std::string& projectFile,
    ProjectConfiguration& config)
{
    XMLDocument doc;

    if (doc.LoadFile(projectFile.c_str())
        != XML_SUCCESS)
    {
        return false;
    }

    XMLElement* root =
        doc.RootElement();

    if (!root)
    {
        return false;
    }

    bool nextIsServerUrl = false;

    TraverseNode(
        root,
        config,
        nextIsServerUrl);

    return true;
}