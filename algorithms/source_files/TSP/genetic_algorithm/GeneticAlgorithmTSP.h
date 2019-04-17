#pragma once
#include <string>
#include <iostream>
#include <fstream>

class GeneticAlgorithmTSP
{
public:
	GeneticAlgorithmTSP();

	void startGA();

	void displayGraph();									//kontrolne wy�wietlenie grafu
	void readGraphFromFile(std::string filename);			//funkcja wczytuj�ca graf z pliku
	bool readLine(std::ifstream &file, int tab[], int size);//funkcja pomocnicza dla ww.
	bool graphExists();

	//gettery
	double getBestRoute(int d = 0);	//funckcja zwraca d�ugo�� najlepszego znalezionego rozwi�zania oraz kolejno�� wierzcho�k�w
									//1 - tylko d�ugo�� (do pomiar�w lepsze)
									//2 - d�ugo�� plus kolejno�� (do prezentacji lepsze)
	double getCurrentRoute(int d = 0);	//funckja zwraca rozwi�zanie kt�re algorytm posiada� przez osi�gni�ciem warunku stopu
	void getParameters(); //wy�wietlenie wszystkich bie��cych parametr�w
	int getSizeOfPopulation() { return sizeOfPopulation; }; //gdy ustawiana b�dzie liczba rycerzy w turnieju nie powinna by� ona wi�ksza od rozmiaru populacji - walidacja w menu

	//settery
	void setNumOfIterations(int n) { numOfIterations = n; };
	void setFinalTime(int n) { finalTime = n; };
	void setSizeOfPopulation(int n); //za�o�enie <32000 - walidacja na poziomie menu
	void setMutationProbability(double n) { mutationProbability = n; }; //walidacja przeprowadzana na poziomie menu
	void setCrossoverProbability(double n) { crossoverProbability = n; };
	void setNumOfSwaps(int n) { numOfSwaps = n; };
	void setNumOfKnights(int n) { numOfKnights = n; }

	~GeneticAlgorithmTSP();

private:
	//dane grafu:
	int numOfCities;
	int ** adjMatrix;

	//zmienne i parametry algorytmu genetycznego
	int numOfIterations;
	int finalTime;
	int sizeOfPopulation;
	double mutationProbability;
	double crossoverProbability;
	int numOfSwaps;
	int numOfKnights;

	/*STRUKTURA OSOBNIKA:
	--wektor o d�ugo�ci numOfCities
	----od 0 do numOfCities-2 znajduje si� permutacja miast
	----poniewa� miasto 0 jest przyjmowane, jako pocz�tkowe, dlatego nie jest uwzgl�dnie w permutacji
	----st�d ilo�� pozycji przeznaczona na permutacj�
	------na ostatniej pozycji, czyli numOfCities-1 znajduje si� warto�� przystosowania danego osobnika
	------przez warto�� przystosowania rozumiemy d�ugo�� trasy
	------im trasa kr�tsza, tym osobnik jest lepiej przystosowany
	*/

	//populacje
	int ** population;
	int ** parents;
	int ** children;

	//rozwi�zania:
    //najlepsze rozwi�zanie - utrzymuje rozwi�zanie najlepsze, podczas gdy rozwi�zanie bie��ce [currentOrder] mo�e zosta� zmienione na gorsze
	int *bestOrder;
	//bie��ce rozwi�zanie
	int *currentBestOrder;

	//funkcja wyznaczaj�ca pocz�tkow� populacj� sk�adaj�c� si� z sizeOfPopulation permutacji
	void generateInitialPopulation();

	//funkcja wyznaczaj�ca populacj� rodzic�w, metod� selekcji jest turniej
	void generateParentsPopulation();
	int tournament(); //metoda przeprowadza pojedynek numOfKnights osobnik�w z kt�rych wy�aniany jest ten z najlepszym dopasowaniem ("wygrywa najlepszy")
					  //nast�pnie zwraca indeks na osobnika, kt�ry wygra� turniej

	//funkcja rozmna�aj�ca - tworz�ca populacj� dzieci - children
	void generateChildrenPopulation();
	void generatePairOfChildren(int index);
	void tryToMutate(int *child);
	void mutate(int *child);

	//funkcja, kt�ra zabija poprzedni� populacj� wprowadzaj�c na jej miejsce now�, czyli: population<=children
	void setNewPopulation();

	//funkcja dopasowania
	int countRouteLength(int *order);

	//funkcja zwracaj�ca liczb� z przedzia�u [0,1]
	double getRandomProbability();

	//czyszczenie grafu
	void clearGraph();
};

