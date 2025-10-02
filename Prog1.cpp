/**
 * Name: Jacob Hellebrand
 * Email: jacobhellebrand@csu.fullerton.edu
 * CWID: 887343457
 */

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

int main()
{

    std::cout << "Enter a string given the alphabet  L=(a* | b) ab*\n";
    std::string input;
    std::getline(std::cin, input);
    if (input.empty() || input.back() != '$')
    {
        std::cout << "Input needs to end with $\n";
        return 1;
    }

    int currentState = 12;
    for (char c : input)
    {
        if (c == '$')
        {
            break;
        }

        switch (currentState)
        {
        case 12: // start state
            if (c == 'a')
            {
                currentState = 123;
            }
            else if (c == 'b')
            {
                currentState = 2;
            }
            else
            {
                currentState = -1; // if no input break switch
            }
            break;
        case 123: // accepting
            if (c == 'a')
            {
                currentState = 123; // loop for a*
            }
            else if (c == 'b')
            {
                currentState = 23;
            }
            else
            {
                currentState = -1; // if no input break switch
            }
            break;
        case 23: // accepting
            if (c == 'a' || c == 'b')
            {
                currentState = 3;
            }
            else
            {
                currentState = -1; // if no input break switch
            }
            break;
        case 3: // accepting
            if (c == 'b')
            {
                currentState = 3; // loop for b*
            }
            else
            {
                currentState = -1; // if no input break switch
            }
            break;
        case 2:
            if (c == 'a')
            {
                currentState = 3; // mandatory 'a' move to 3
            }
            else
            {
                currentState = -1; // if no input break switch
            }
            break;

        default:
            currentState = -1;
        }

        if (currentState == -1)
        {
            break;
        }
    }

    if (currentState == 123 || currentState == 23 || currentState == 3)
    {
        std::cout << "YES\n";
    }
    else
    {
        std::cout << "NO\n";
    }
    return 0;
}
