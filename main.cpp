#include "pch.h"
#include "ConsoleManager.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    ConsoleManager console;

    console.Run(argc, argv);

    return 0;
}