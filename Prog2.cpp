#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

std::string addSpacesAroundKeywords(const std::string &line, std::vector<std::string> keywords)
{
    // Sort keywords descending by length so multi-char ops matched first
    std::sort(keywords.begin(), keywords.end(),
              [](const std::string &a, const std::string &b)
              {
                  return a.size() > b.size();
              });

    std::string result = line;
    size_t pos = 0;

    while (pos < result.size())
    {
        bool matched = false;

        for (const auto &keyword : keywords)
        {
            if (pos + keyword.size() <= result.size() &&
                result.compare(pos, keyword.size(), keyword) == 0)
            {
                // Check if need space before keyword
                if (pos > 0 && !std::isspace(result[pos - 1]))
                {
                    result.insert(pos, " ");
                    pos += 1; // Move forward due to insertion
                }

                // Check if need space after keyword
                size_t afterPos = pos + keyword.size();
                if (afterPos < result.size() && !std::isspace(result[afterPos]))
                {
                    result.insert(afterPos, " ");
                }

                pos += keyword.size();
                matched = true;
                break; // break for-loop, continue while-loop
            }
        }

        if (!matched)
        {
            ++pos;
        }
    }

    return result;
}

// Remove leading, trailing, and extra in-between spaces
std::string cleanSpaces(const std::string &line)
{
    std::string result;
    bool inSpace = false;
    size_t start = line.find_first_not_of(" \t");
    if (start == std::string::npos)
        return ""; // empty/whitespace-only line

    for (size_t i = start; i < line.size(); ++i)
    {
        char c = line[i];
        if (std::isspace(c))
        {
            if (!inSpace)
            {
                result += ' ';
                inSpace = true;
            }
        }
        else
        {
            result += c;
            inSpace = false;
        }
    }

    // Trim trailing space
    if (!result.empty() && result.back() == ' ')
        result.pop_back();

    return result;
}

bool isFullLineComment(const std::string &line)
{
    size_t first = line.find_first_not_of(" \t");
    return (first != std::string::npos && line.substr(first, 2) == "//");
}

std::string stripInlineComment(const std::string &line)
{
    size_t commentPos = line.find("//");
    return (commentPos != std::string::npos) ? line.substr(0, commentPos) : line;
}

int main()
{
    std::ifstream inFile("infile.txt");
    if (!inFile)
    {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    std::ofstream outFile("outfile.txt");
    if (!outFile)
    {
        std::cerr << "Error creating output file\n";
        return 1;
    }

    std::vector<std::string> keywords = {
        "cin>>", "cout<<", "for", "int", "=", "+", "-", "*", "/",
        "%", ">", "<", "!", "&&", "||", ",", ";", "(", ")", "{", "}"};

    std::string line;
    while (std::getline(inFile, line))
    {
        if (isFullLineComment(line))
            continue;

        std::string codeOnly = stripInlineComment(line);
        std::string spaced = addSpacesAroundKeywords(codeOnly, keywords);
        std::string cleaned = cleanSpaces(spaced);
        outFile << cleaned << "\n";
    }

    return 0;
}