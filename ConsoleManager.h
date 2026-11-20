#pragma once
#include "File.h"
#include "BitMap.h"

class ConsoleManager
{
private:
    BitMap file;
    std::vector <std::string> arguments;
    std::string command;

public:
    ConsoleManager();
    void Run(int argc, char* argv[]);
    void HideText();
    void ShowText();
    void HelpText();

    //~ConsoleManager();
};