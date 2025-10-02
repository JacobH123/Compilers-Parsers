/**
 * Name: Jacob Hellebrand
 * Email: jacobhellebrand@csu.fullerton.edu
 * CWID: 887343457
 */

#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cctype>
#include <limits>
#include <iomanip>
#include <regex>

const size_t MAXSIZE = 255;
enum class Tokens
{
    reservedWord,
    specialSymbol,
    identifier,
    number,
    Operator
};

bool isNumber(const std::string &s)
{
    static const std::regex numberRegex(R"([+-]?\d+)");
    return std::regex_match(s, numberRegex);
}

bool isIdentifier(const std::string &s)
{
    static const std::regex idRegex(R"([a-zA-Z_][a-zA-Z0-9_]*)");
    return std::regex_match(s, idRegex);
}

int main(int argc, char *argv[])
{

    std::unordered_map<std::string, Tokens> symbolTable = {
        {"cin>>", Tokens::reservedWord},
        {"for", Tokens::reservedWord},
        {"int", Tokens::reservedWord},
        {"cout<<", Tokens::reservedWord},

        {"+", Tokens::Operator},
        {"-", Tokens::Operator},
        {"*", Tokens::Operator},
        {"/", Tokens::Operator},
        {"++", Tokens::Operator},
        {"--", Tokens::Operator},

        {"<", Tokens::specialSymbol},
        {"=", Tokens::specialSymbol},
        {";", Tokens::specialSymbol},
        {"(", Tokens::specialSymbol},
        {")", Tokens::specialSymbol},
        {"<=", Tokens::specialSymbol},
        {",", Tokens::specialSymbol}};

    /*if (argc < 2)
    {
        std::cerr << "Enter an argument with argv[1]\n";
        return 1;
    }
    */
    // std::string argvInput = argv[1];
    while (true)
    {
        std::cout << "Enter a command:\n";
        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::string word;

        while (iss >> word)
        {
            // std::cout << "Read word: '" << word << "'\n";
            auto type = symbolTable.find(word);
            if (type != symbolTable.end())
            {
                switch (type->second)
                {
                case Tokens::reservedWord:
                    std::cout << std::left << std::setw(15) << word << " reserved word\n";
                    break;
                case Tokens::Operator:
                    std::cout << std::left << std::setw(15) << word << " operator\n";
                    break;
                case Tokens::specialSymbol:
                    std::cout << std::left << std::setw(15) << word << " special\n";
                    break;
                }
            }
            else if (isIdentifier(word))
            {
                std::cout << std::left << std::setw(15) << word << " identifier\n";
            }
            else if (isNumber(word))
            {
                std::cout << std::left << std::setw(15) << word << " number\n";
            }
            else
            {
                std::cout << std::left << std::setw(15) << word << " invalid\n";
            }
        }
        while (true)
        {
            std::cout << "Do you want to continue? (y/n): ";
            char userChoice;
            std::cin >> userChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (tolower(userChoice) == 'y')
            {
                break;
            }
            else if (tolower(userChoice) == 'n')
            {
                return 0;
            }
            else
            {
                std::cout << "Enter either y or n\n";
            }
        }
    }

    return 0;
}