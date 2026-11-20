#include "pch.h"
#include "ConsoleManager.h"
ConsoleManager::ConsoleManager() {}

void ConsoleManager::Run(int argc, char* argv[])
{
	arguments.clear();

	for (int i = 1; i < argc; i++)
	{
		arguments.push_back(argv[i]);
	}
	if (arguments.empty())
	{
		HelpText();
		return;
	}
	
	command = arguments[0];

	if (command == "-hide")
		HideText();
	else if (command == "-show")
		ShowText();
	else if (command == "-help")
		HelpText();
	else
		std::cout << "Mauvaise saisie\n";
}

void ConsoleManager::HideText()
{
	if (file.ReadImage(arguments[1]) && file.WriteImage(arguments[3]))
		file.SavingImage(arguments[2]);
	else
		return;
}

void ConsoleManager::ShowText()
{
	if (file.ReadImage(arguments[1]))
		file.WriteText();
	else
	{
		std::cout << "aucun code caché" << std::endl;
		return;
	}	
}

void ConsoleManager::HelpText() 
{
	std::cout << "Help :\n";
	std::cout << "-hide : Permet de cacher un message dans une image\n";
	std::cout << "-show : Permet de decouvrir un message cacher dans une image (seulement si ca vient du meme programme)\n";
	std::cout << "\nUtilisation de -hide : App.exe -hide image.bmp image2.bmp secret";
	std::cout << "\nUtilisation de -show : App.exe -show image.bmp\n\n";
}