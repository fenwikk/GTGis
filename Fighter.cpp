/**
 * Fighter.cpp
 * Definierar funktioner för Fighter-klassen
 */

#include <iostream>
#include "Library.h"

#include "Fighter.h"
#include "Game.h"

/**
 * Tar spelarens HP och skapar en string med förhållandet mellan
 * spelarens HP och maxHP i form av en bar.
 *
 * @param length - Längden av baren
 * @returns HP bar i form av en string
 */
std::string Fighter::GenHpBar(int length)
{
	/**
	 * Skapar en variabel vars värde är längden användaren matat in delat
	 * med 2 eftersom själva baren är omringad av [hakparenteser] som är
	 * inräknat i length.
	 */
	int barSize = length - 2;

	/**
	 * För fram relationen mellan HP och maxHP och multiplicerar det med
	 * hur många karaktärer baren ska ha för att få fram hur många
	 * av karaktärerna som ska vara HP som spelaren har.
	 */
	double hpLeft = ((double)hp() / (double)maxHp) * barSize;

	/**
	 * Om HP är mindre än hälften av maxHP avrundar man upp (så att baren
	 * inte är på 0 fastän man fortfarande har HP kvar).
	 * Om HP är mer eller lika med hälften av maxHP avrundar man ner (så
	 * att baren inte är full fastän man tagit skada).
	 */
	hpLeft = hp() < (maxHp / 2) ? ceil(hpLeft) : floor(hpLeft);

	/*  Definierar en string som man sedan kan bifoga karaktärer till  */
	std::string bar = "";

	/**
	 * Lägger först till karaktären '#' för varje HP bar-poäng som spelaren har.
	 * Fyller sedan resterande biten av baren med karaktären '-' för att
	 * symbolisera bar-poäng spelaren inte har
	 */
	for (int i = 0; i < hpLeft; i++)
		bar += '#';
	for (int i = 0; i < barSize - hpLeft; i++)
		bar += '-';

	/**
	 * Returnerar sedan baren omgivet av [hakparenteser] fär att visa att det
	 * är en HP bar.
	 */
	return "[" + bar + "]";
}

void Fighter::Attack()
{
	Clear();

	std::cout << "Who do you want to attack?\n";

	/**
	 * Definierar variabler som ska användas i Menu() som ska fyllas in i
	 * for-loopen nedan
	 */
	bool disabledItems[] = {false, false, false, false, false};
	std::string names[] = {"", "", "", "", ""};

	/**
	 * Itererar genom alla spelare för att fylla i menyn där man väljer vem
	 * man ska attackera och sätter definierar en ny variabel som sätts som
	 * den aktuella itererade spelaren
	 */
	for (size_t i = 0; i < 5; i++)
	{
		Fighter *player = Game::players[i];

		/**
		 * Finns spelaren inte fortsätter namnet i plats [i] vara tom och
		 * alternativet blir inaktiverad.
		 * Annars sätts namnet på plats [i] som spelare [i]s namn
		 */
		if (player == nullptr)
			disabledItems[i] = true;
		else
		{
			names[i] = player->name();

			/**
			 * Eftersom man inte kan attackera sig själv inaktiveras
			 * alternativet om den som attackerar är den aktuella
			 * itererade spelaren.
			 */
			if (player == this)
				disabledItems[i] = true;
		}
	}

	/**
	 * Ger spelaren en meny där den kan välja vem den vill attackera med
	 * funktionen Menu() med spelarnas namn som etiketter och tomma
	 * etiketter samt den aktuella itererade spelaren som inaktiverade
	 * alternativ
	 */
	int whoToAttack = Menu(names, 5, disabledItems);

	Fighter *playerToAttack = Game::players[whoToAttack];

	/**
	 * Beräknar hur mycket skada den attackerade ska ta av attacken.
	 * Om antalet skada den attackerade ska ta är mer än dess HP drar man ner attackskadan
	 * till hur mycket HP den attackerade har så att statistiken stämmer
	 */
	int damageDealt = (int)floor((float)this->strength() / (float)playerToAttack->defense()) * 20;
	if (damageDealt > hp())
		damageDealt = hp();

	_damageDealt += damageDealt;
	playerToAttack->_hp -= damageDealt;

	Clear();

	/* Skriver ut händelsen till konsollen så att de spelarna vet vad som händer */
	Write("<" + name() + "> attacked <" + playerToAttack->name() + ">!\n");
	Write("<" + name() + "> took " + std::to_string(damageDealt) + " damage.");

	/**
	 * Om den som blir attackerad har dött av attacken höjer man attackerarens kill-count
	 * med 1 och förstör den attackerades Fighter-objekt
	 */
	if (playerToAttack->hp() <= 0)
	{
		_kills++;
		delete playerToAttack;
	}

	/* Väntar på spelarens input för att säkerställa att spelarna förstått vad som hänt */
	WaitForEnterPress();
}
void Fighter::Defend()
{
	Clear();

	/* Informerar spelarna om vad som händer */
	Write("<" + name() + "> defended themselves\n");

	/* Ändrar spelarens statistik */
	_defense += 2;
	Write("Defense went up by 2 points\n");
	if (speed() > 0)
	{
		_speed--;
		Write("Speed went down by 1 point\n");
	}
	else
	{
		Write("Speed is already at minimum. Speed was not changed\n");
	}

	/* Väntar på spelarens input för att säkerställa att spelarna förstått vad som hänt */
	WaitForEnterPress();
}
void Fighter::WorkUp()
{
	Clear();

	Write("<" + name() + "> worked up!\n");

	/* Ändrar spelarens statistik */
	_strength += 2;
	Write("Strength went up by 2 points\n");
	if (speed() > 0)
	{
		_speed--;
		Write("Speed went down by 1 point\n");
	}
	else
	{
		Write("Speed is already at minimum. Speed was not changed\n");
	}

	/* Väntar på spelarens input för att säkerställa att spelarna förstått vad som hänt */
	WaitForEnterPress();
}

void Fighter::Rest()
{
	Clear();

	int originalHp = hp();

	Write("<" + _name + "> rested");

	/* Ändrar spelarens statistik */
	_hp += 20;
	if (hp() > 100)
		_hp = 100;
	Write("<" + name() + "> healed " + std::to_string(hp() - originalHp) + " HP");

	/* Väntar på spelarens input för att säkerställa att spelarna förstått vad som hänt */
	WaitForEnterPress();
}

/**
 * Går igenom processen för att spelaren ska mata in sitt namn.
 *
 * @param numberOfCharacters - Antalet karaktärer namnet ska ha
 * @returns Namnet spelaren matat in
 */
std::string Fighter::NameInput(int numberOfCharacters)
{
	/**
	 * Definierar variabler som kommer användas senare
	 * characterSet - Karaktärerna man kan använda för sitt namn
	 * input - Tom string som man sedan kommer lägga in
	 */
	std::string characterSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string input = "";

	/* Kör loopen för varje karaktär som man specificerat att namnet ska vara */
	for (size_t characterPlaceIndex = 0; characterPlaceIndex < numberOfCharacters; characterPlaceIndex++)
	{
		/**
		 * Definierar variabler som kommer användas senare
		 * selectedIndex - Indexen av den nuvarande karaktären i characterSet
		 */
		bool submitted = false;
		int selectedIndex = 0;

		/**
		 * Låter spelaren skriva in sitt namn, karaktär för karaktär.
		 * Fortsätter tills spelaren skickat in svaret.
		 */
		while (!submitted)
		{
			// Dekoration
			std::cout << "\r";
			ChangeConsoleColor(12);
			std::cout << "[";

			/**
			 * Skriver ut det namnet som spelaren hittills har skrivit in.
			 *
			 * Färgkoder:
			 * Vit - Valda bokstäver
			 * Gul - Den nuvarande karaktären
			 * Grå - Platser man inte kommit till än (kan bara var "-")
			 */
			for (size_t i = 0; i < numberOfCharacters; i++)
			{
				/**
				 * Om platsen är före den platsen spelaren ändrar,
				 * skriv ut karaktären i vit text.
				 * Fortsätt sedan till nästa plats
				 */
				if (i < characterPlaceIndex)
				{
					ChangeConsoleColor(15);
					std::cout << input.at(i);

					continue;
				}

				/**
				 * Om platsen är den som spelaren ändrar,
				 * skriv ut den valda karaktären i gul text.
				 * Fortsätt sedan till nästa plats
				 */
				if (i == characterPlaceIndex)
				{
					ChangeConsoleColor(14);
					std::cout << characterSet.at(selectedIndex);

					continue;
				}

				/**
				 * Om platsen inte är före eller lika med platsen spelaren ändrar
				 * har spelaren inte bestämt en karaktär för den platsen så man
				 * skriver ut "-" i grå text
				 */
				ChangeConsoleColor(7);
				std::cout << "-";
			}

			// Dekoration
			ChangeConsoleColor(12);
			std::cout << "]";
			ChangeConsoleColor(7);

			/**
			 * Lyssna efter ett giltigt kommando via ett knapptryck tills
			 * ett har skickats in. Väntar sedan tills den knappen blivit
			 * intryckt
			 *
			 * Giltiga kommandon:
			 * - Pil upp - Byter karaktär till den före den nuvarande
			 * 		i alfabetet. (Den valda bokstaven måste ha en bokstav
			 *  	innan, därav "selectedIndex > 0")
			 * - Pil ner - Byter karaktär till den efter den nuvarande
			 * 		i alfabetet. (Den valda bokstaven måste ha en bokstav
			 *  	efter, därav "selectedIndex < (characterSet.length() - 1)")
			 * - Delete/Pil vänster - Tar bort den nuvarande karaktären
			 * 		och går tillbaka till förgående plats
			 * - Enter/Pil höger - Skickar in svaret (Den valda bokstaven
			 * 		måste ha en bokstav innan, därav "selectedIndex > 0")
			 */
			bool commandPressed = false;
			while (!commandPressed)
			{
				// Lyssnar efter "Pil upp" kommandot
				if ((GetAsyncKeyState(VK_UP) & 0x8000) && selectedIndex > 0)
				{
					selectedIndex--;
					commandPressed = true;

					while (GetAsyncKeyState(VK_UP) & 0x8000)
						;
				}

				// Lyssnar efter "Pil ner" kommandot
				if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && selectedIndex < (characterSet.length() - 1))
				{
					selectedIndex++;
					commandPressed = true;

					while (GetAsyncKeyState(VK_DOWN) & 0x8000)
						;
				}

				// Lyssnar efter "Delete/Pil vänster" kommandot
				if ((GetAsyncKeyState(VK_DELETE) & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000) && characterPlaceIndex > 0)
				{
					commandPressed = true;

					input.erase(input.end() - 1);
					characterPlaceIndex--;
					selectedIndex = 0;

					while ((GetAsyncKeyState(VK_DELETE) & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000))
						;
				}

				// Lyssnar efter "Enter/Pil höger" kommandot
				if ((GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000))
				{
					submitted = true;
					commandPressed = true;

					input += characterSet.at(selectedIndex);

					while ((GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000))
						;
				}
			}
		}
	}

	// Dekoration
	ChangeConsoleColor(12);
	std::cout << "\r[";

	// Skriver ut namnet spelaren skickat in
	for (size_t i = 0; i < numberOfCharacters; i++)
	{
		ChangeConsoleColor(15);
		std::cout << input.at(i);
	}

	// Dekoration
	ChangeConsoleColor(12);
	std::cout << "]\n";
	ChangeConsoleColor(7);

	return input;
}

/**
 * Går igenom processen för att spelaren ska mata in sitt namn.
 *
 * @param availablePoints - Antalet poäng spelaren har att distribuera
 * @param playerName - Spelarens namn
 */
void Fighter::DistributePoints(int availablePoints, std::string playerName)
{
	/**
	 * Definierar variabler som kommer användas senare
	 * - labels - Vad de olika kategorierna heter med extra mellanrum så
	 * 		att talen är i samma linje
	 * - points - Ett fält som håller spelarens poäng. Initieras med ett
	 * 		startvärde så att de aldrig har 0 i en kategori
	 */
	std::string labels[]{
		"Defense:  ",
		"Strength: ",
		"Speed:    "};
	int points[]{5, 5, 5};

	/**
	 * Låter spelaren distruera sina poäng.
	 * Fortsätter tills spelaren konfirmerat sina poäng.
	 */
	bool confirmedPoints = false;
	while (!confirmedPoints)
	{
		/**
		 * Låter spelaren distruera sina poäng.
		 * Fortsätter tills spelaren spenderat alla sina poäng.
		 */
		int selectedIndex = 0;
		while (availablePoints > 0)
		{
			Clear();

			/**
			 * Dekoration - visat vems tur det är och hur många poäng
			 * de har kvar
			 */
			std::cout << "Distribute skillpoints for <" << playerName << ">\n";
			std::cout << "Remaining points: " << availablePoints << "\n\n";

			/**
			 * Skriver ut de olika kategorierna och hur mycket spelaren
			 * spenderat på just den kategorin
			 */
			for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++)
			{
				std::cout << labels[i];

				// Dekoration
				ChangeConsoleColor(12);
				std::cout << ((selectedIndex == i && points[i] != 5) ? "< " : "  ");

				ChangeConsoleColor(15);
				std::cout << points[i];

				// Dekoration
				ChangeConsoleColor(12);
				std::cout << (selectedIndex == i ? " >" : "  ");

				ChangeConsoleColor(7);
				std::cout << "\n";
			}

			/**
			 * Lyssna efter ett giltigt kommando via ett knapptryck tills
			 * ett har skickats in. Väntar sedan tills den knappen blivit
			 * intryckt
			 *
			 * Giltiga kommandon:
			 * - Pil upp - Byter kategori till den över den valda. (Den
			 * 		valda kategorin kan inte vara längst upp,
			 * 		därav "selectedIndex > 0")
			 * - Enter/Pil ner - Byter kategori till den under den valda. (Den
			 * 		valda kategorin kan inte vara längst upp, därav
			 *		"selectedIndex < (sizeof(points) / sizeof(points[0]) - 1)")
			 * - Pil vänster - Tar bort ett poäng till den valda kategorin
			 * 		(Den valda kategorin kan inte ha mindre poäng än
			 * 		standardvärdet, därav "points[selectedIndex] > 5")
			 * - Pil höger - Lägger till ett poäng till den valda kategorin
			 */
			bool commandPressed = false;
			while (!commandPressed)
			{
				if ((GetAsyncKeyState(VK_UP) & 0x8000) && selectedIndex > 0)
				{
					selectedIndex--;
					commandPressed = true;

					while (GetAsyncKeyState(VK_UP) & 0x8000)
						;
				}
				if (((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000)) && selectedIndex < (sizeof(points) / sizeof(points[0]) - 1))
				{
					selectedIndex++;
					commandPressed = true;

					while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000))
						;
				}

				if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && points[selectedIndex] > 5)
				{
					points[selectedIndex]--;
					availablePoints++;
					commandPressed = true;

					while (GetAsyncKeyState(VK_LEFT) & 0x8000)
						;
				}
				if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
				{
					points[selectedIndex]++;
					availablePoints--;
					commandPressed = true;

					while (GetAsyncKeyState(VK_RIGHT) & 0x8000)
						;
				}
			}
		}

		Clear();

		// Dekoration - spelarens namn
		std::cout << "<" << name() << ">"
				  << "\n";

		// Skriver ut hur många poäng spelaren valt vid varje kategori
		std::cout << "Defense:  ";
		ChangeConsoleColor(14);
		std::cout << points[0] << "\n";
		ChangeConsoleColor(7);

		std::cout << "Strength: ";
		ChangeConsoleColor(14);
		std::cout << points[1] << "\n";
		ChangeConsoleColor(7);

		std::cout << "Speed:    ";
		ChangeConsoleColor(14);
		std::cout << points[2] << "\n\n";
		ChangeConsoleColor(7);

		// Frågar spelaren om konfirmation. Accepterar spelaren ditrubutionen?
		std::cout << "Accept points distribution?\n";
		/**
		 * Menu funktionen returnerar indexen på det valda alternativet. Eftersom
		 * 0 == false, 1 == true, "Yes" är satt som 0 och "No" är satt som 1 kan
		 * man invertera resultatet av Menu för att konvertera svaret till en bool
		 */
		std::string confirmMenuItems[] = {"Yes", "No"};
		confirmedPoints = !Menu(confirmMenuItems, 2);
	}

	// Sätter svaren i respektive kategori i objektet
	_defense = points[0];
	_strength = points[1];
	_speed = points[2];
}

/**
 * Skapar ett fighterobjekt.
 *
 * @param playerNumber - Spelarens nummer
 */
Fighter::Fighter(int playerNumber) : _hp(maxHp), _damageDealt(0), _kills(0)
{
	Clear();

	// Frågar om spelarens namn tills spelaren konfirmerat svaret.
	bool confirmedName = false;
	while (!confirmedName)
	{
		// Dekoration
		std::cout << "Input name for [P" << playerNumber << "]\n";
		std::cout << "[Up/Down] to change character\n";

		_name = NameInput(3);

		Clear();

		// Kollar så att ingen annan har namnet spelaren matat in
		bool isDuplicate = false;
		for (size_t i = 0; i < 5; i++)
		{
			Fighter *player = Game::players[i];
			if (Game::players[i] != nullptr)
				if (Game::players[i]->name() == name())
				{
					ChangeConsoleColor(12);
					std::cout << "The name <" << name() << "> has already been taken. Retry with another name.\n";
					ChangeConsoleColor(7);

					isDuplicate = true;
				}
		}

		// Om inte, fråga om de verkligen vill ha det namnet
		if (!isDuplicate)
		{
			Clear();
			std::cout << "Accept name <" << name() << ">\n";

			std::string confirmMenuItems[] = {"Yes", "No"};
			confirmedName = !Menu(confirmMenuItems, 2);

			if (!confirmedName)
				Clear();
		}
	}

	DistributePoints(10, name());
}

Fighter::~Fighter()
{
	// Meddela spelarna att spelaren dött
	Write("\nPlayer <" + name() + "> perished.");

	// Sätt in spelarens statistik i "leaderboarden"
	Game::leaderboard[Game::PlayersLeft() - 1] = new LeaderboardItem(name(), damageDealt(), kills());

	// Tar bort pointern till objektet i spelar-fältet
	for (size_t i = 0; i < 5; i++)
		if (Game::players[i] == this)
			Game::players[i] = nullptr;
}