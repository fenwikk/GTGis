#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <format>

#include "Error.h"
#include "Fighter.h"
#include "Library.h"
#include "Game.h"

/**
 * Rensar konsollen och skriver ut spelets logotyp.
 * Har spelet börjat skriver den även ut statistiken
 */
void Clear()
{
	system("CLS");

	Logo();

	if (Game::started)
		Game::Stats();
}

void ChangeConsoleColor(int colorId)
{
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorId);
}

void Write(std::string s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		std::cout << s[i];
		Sleep(25);
	}
}

/**
 * Stannar spelet tills Enter har blivit nedtryckt
 */
void WaitForEnterPress()
{
	std::cout << "\nPress enter to continue...\r";

	bool enterPressed = false;
	while (!enterPressed)
	{
		if ((GetAsyncKeyState(VK_RETURN) & 0x8000))
		{
			enterPressed = true;

			while (GetAsyncKeyState(VK_RETURN) & 0x8000)
				;
		}
	}

	std::cout << "                          \r";
}

/**
 * Skriver ut logotypen
 */
void Logo()
{
	std::cout << ",-----------------------------------------------------------------------,\n";
	std::cout << "|            ___________.__       .__     __                            |\n";
	std::cout << "|            \\_   _____/|__| ____ |  |___/  |_  ___________             |\n";
	std::cout << "|             |    __)  |  |/ ___\\|  |  \\   __\\/ __ \\_  __ \\            |\n";
	std::cout << "|             |     \\   |  / /_/  >   Y  \\  | \\  ___/|  | \\/            |\n";
	std::cout << "|             \\___  /   |__\\___  /|___|  /__|  \\___  >__|               |\n";
	std::cout << "|                 \\/      /_____/      \\/          \\/                   |\n";
	std::cout << "|                                                                       |\n";
	std::cout << "'-----------------------------------------------------------------------'\n\n";
}

/**
 * Skriver ut en rad med "numberOfColumns" antal kolumner på "maxChars"
 * antal karaktärer.
 *
 * @param row - Fältet av strängar man vill göra om till en rad
 * @param numberOfColumns - Antalet kolumner man vill att raden ska ga
 * @param maxChars - Det maximala antalet karaktärer man vill att raden ska ha
 * @return En rad
 */
void Row(std::string row[], int numberOfColumns, int maxChars)
{
	for (size_t i = 0; i < numberOfColumns; i++)
	{
		std::string cell = row[i];

		std::string space = "";
		for (size_t i = 0; i < (maxChars / numberOfColumns - cell.length()); i++)
		{
			space += " ";
		}
		std::cout << cell + space;
	}

	std::cout << std::endl;
}

/**
 * Skapar en meny där spelaren kan välja mellan alternativen med pilarna
 *
 * @param labels - Ett fält av strängar man vill ha som alternativ
 * @param numberOfLabels - Antalet strängar i "labels"
 * @param disabled - Ett fält av booleans som bestämmer om alternativen är tillgängliga eller inte
 */
int Menu(std::string labels[], int numberOfLabels, bool disabled[])
{
	bool noDisabled = disabled == nullptr;
	bool submitted = false;
	int selectedIndex = 0;

	while ((noDisabled ? false : disabled[selectedIndex]) && selectedIndex <= (numberOfLabels - 1))
	{
		selectedIndex++;
	}
	if (selectedIndex > (numberOfLabels - 1))
		throw new Error("Menu only has disabled items.");

	while (submitted == false)
	{
		std::cout << "\r";

		for (size_t i = 0; i < numberOfLabels; i++)
		{
			ChangeConsoleColor(12);
			std::cout << (selectedIndex == i ? ">" : " ");
			ChangeConsoleColor((noDisabled ? true : disabled[i]) ? 7
																 : 15);
			std::cout << labels[i];
			ChangeConsoleColor(12);
			std::cout << (selectedIndex == i ? "<" : " ");
			ChangeConsoleColor(7);
			std::cout << "  ";
		}

		bool commandPressed = false;
		while (!commandPressed)
		{
			if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && selectedIndex > 0)
			{
				int originalIndex = selectedIndex;
				selectedIndex--;
				while (selectedIndex >= 0 && (noDisabled ? false : disabled[selectedIndex]))
				{
					selectedIndex--;
				}
				if (selectedIndex < 0)
					selectedIndex = originalIndex;

				commandPressed = true;

				while (GetAsyncKeyState(VK_LEFT) & 0x8000)
					;
			}
			if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && selectedIndex < (numberOfLabels - 1))
			{
				int originalIndex = selectedIndex;
				selectedIndex++;
				while (selectedIndex <= (numberOfLabels - 1) && (noDisabled ? false : disabled[selectedIndex]))
				{
					selectedIndex++;
				}
				if (selectedIndex > (numberOfLabels - 1))
					selectedIndex = originalIndex;

				commandPressed = true;

				while (GetAsyncKeyState(VK_RIGHT) & 0x8000)
					;
			}
			if ((GetAsyncKeyState(VK_RETURN) & 0x8000))
			{
				submitted = true;
				commandPressed = true;

				while (GetAsyncKeyState(VK_RETURN) & 0x8000)
					;
			}
		}
	}

	return selectedIndex;
}

Fighter **SortFightersBySpeed(Fighter **fighters)
{
	bool fightersSorted = false;

	while (!fightersSorted)
	{
		fightersSorted = true;
		for (size_t i = 1; i < 5; i++)
		{
			if (fighters[i] != nullptr)
			{
				if (fighters[i - 1] == nullptr || fighters[i]->speed() > fighters[i - 1]->speed())
				{
					Fighter *tempFighter = fighters[i];
					fighters[i] = fighters[i - 1];
					fighters[i - 1] = tempFighter;

					fightersSorted = false;
				}
			}
		}
	}

	return fighters;
}