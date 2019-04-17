#pragma once
#include <string>
#include <iostream>
#include <fstream>

class SimmulatedAnnealingTSP
{
public:
	SimmulatedAnnealingTSP();

	void simmulateAnneal();//parametr n odpowiada za wyb�r typu s�sziedztwa
									//1 - swap
									//N\{1} - invert

	void setNeighbourhood();
	void setParameters();			//funkcja wyswietla bie��ce parametry oraz umo�liwia ustawienie nowych
	double getBestRoute(int d = 0);	//funckcja zwraca d�ugo�� najlepszego znalezionego rozwi�zania oraz kolejno�� wierzcho�k�w
									//1 - tylko d�ugo�� (do pomiar�w lepsze)
									//2 - d�ugo�� plus kolejno�� (do prezentacji lepsze)
	double getCurrentRoute(int d = 0);	//funckja zwraca rozwi�zanie kt�re algorytm posiada� przez osi�gni�ciem warunku stopu

	void displayGraph();									//kontrolne wy�wietlenie grafu
	void readGraphFromFile(std::string filename);			//funkcja wczytuj�ca graf z pliku
	bool readLine(std::ifstream &file, int tab[], int size);//funkcja pomocnicza dla ww.
	bool graphExists();										//funkcja zwraca informacje o istnieniu grafu

	void test();

	~SimmulatedAnnealingTSP();
private:
	//dane grafu:
	int numOfCities;
	int ** adjMatrix;

	//rozwi�zania:
	//najlepsze rozwi�zanie - utrzymuje rozwi�zanie najlepsze, podczas gdy rozwi�zanie bie��ce [currentOrder] mo�e zosta� zmienione na gorsze
	int *bestOrder;
	int bestOrderDistance;
	//bie��ce rozwi�zanie
	int *currentOrder;
	int currentOrderDistance;
	//nowe rozwi�zanie po perturbacji - s�siedztwo typu swap lub typu invert
	int *newOrder;
	int newOrderDistance;
	
	//typ s�siedztwa
	int neighbourhood; // 1 - swap 2 - invert

	//parametry algorytmu:
	float phi;			//sta�a s�u��ca do wyznaczenia temperatury pocz�tkowej
	float alpha;		//wsp�czynnik ch�odzenia
	float L;				//liczba iteracji
	float overTime;		//warunek stopu, czas w sekundach
	float temperature;  //temperatura metalu

	//wyzanczenie rozwi�zania pocz�tkowego -> bestOrder,currentOrder oraz 2x[...]OrderDistance
	//metod� zach�ann�
	void setInitialOrder();
	//wyznaczenie temperatury pocz�tkowej
	void setInitialTemperature();
	//wyznaczenie nowego rozwi�zania -> newOrder
	void insert();
	void swap();
	void invert();
	//wyznaczenie d�ugo�ci trasy
	int countRouteLength(int *order);

	//czyszczenie grafu
	void clearGraph();
};

