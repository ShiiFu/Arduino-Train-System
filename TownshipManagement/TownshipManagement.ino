// Fichier de programmation en C de la carte Arduino gérant automatiquement le réseau N
// Par LEROY Damien	(damien7leroy@gmail.com)
// 26/01/2015


#define NBCANTON 11 // Nombre de canton
#define BTMODE 38

// Struture utilisé pour les canton
typedef struct
{
	int ils;
	int relaisLent;
	int relaisRapide;
} Canton;


//
void initialise (Canton *cantonTab);

// Définition des 11 cantons avec leurs entrées (ILS) et sorties (Relais)
// {ILS, relais lent, relais rapide}
Canton cantonTab[NBCANTON] = {{2, 24, 42},
						{3, 25, 43},
						{4, 26, 44},
						{5, 27, 45},
						{6, 28, 46},
						{7, 29, 47},
						{8, 30, 48},
						{9, 31, 49},
						{10, 32, 50},
						{11, 33, 51},
						{12, 34, 52}};


// Fonction setup lancé une fois au démarrage de la carte et lors de son reset
void setup()
{
	Serial.begin(9600);
	initialise (cantonTab);
	pinMode(BTMODE, INPUT_PULLUP);
}

// Fonction loop qui s'exécute en boucle pour toujours
void loop()
{
	if (digitalRead(BTMODE) == LOW)
	{
		// Pour chaque canton i allant de 0 à NBCANTON
		for (int i = 0 ; i < NBCANTON ; i++)
		{
			digitalWrite(cantonTab[i].relaisLent, LOW);
			digitalWrite(cantonTab[i].relaisRapide, HIGH);
		}
	}
	else
	{
		int i;
		int j;
		// Pour chaque canton i allant de 0 à NBCANTON
		for (i=0 ; i<NBCANTON ; i++)
		{
			if (digitalRead(cantonTab[i].ils) == LOW)
			{
				String message = "ILS ";
				i++;
				//message = message + i;
				Serial.println(i);
				i--;
				j = i;

				// un canton avant on arrête
				j--;
				if (j == -1)
					j = NBCANTON-1;
				digitalWrite(cantonTab[j].relaisRapide, LOW);
				digitalWrite(cantonTab[j].relaisLent, LOW);

				// deux cantons avant on ralenti
				j--;
				if (j == -1)
					j = NBCANTON-1;
				digitalWrite(cantonTab[j].relaisRapide, LOW);
				digitalWrite(cantonTab[j].relaisLent, HIGH);

				// trois cantons avant on met à allure rapide
				j--;
				if (j == -1)
					j = NBCANTON-1;
				digitalWrite(cantonTab[j].relaisLent, LOW);
				digitalWrite(cantonTab[j].relaisRapide, HIGH);
			}
		}
	}

}

void initialise (Canton *cantonTab)
{
	// Pour chaque canton i allant de 0 à NBCANTON
	for (int i = 0 ; i < NBCANTON ; i++)
	{
		// Définition de l'ILS en tant qu'entrée
		pinMode(cantonTab[i].ils, INPUT_PULLUP);

		// Définition du relais lent en tant que sortie
		pinMode(cantonTab[i].relaisLent, OUTPUT);
		digitalWrite(cantonTab[i].relaisLent, HIGH);

		// Définition du relais rapide en tant que sortie
		pinMode(cantonTab[i].relaisRapide, OUTPUT);
		digitalWrite(cantonTab[i].relaisRapide, LOW);
	}
}
