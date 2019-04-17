#pragma once
#include <limits.h>
#include <string>
#include <iostream>
#include <fstream>

class tspDynamicProgramming
{
public:
	tspDynamicProgramming();
	int countPath(int node = 0, int bitmask = 1);	//metoda obliczaj�ca d�ugo�� minimalnego cyklu Hamiltona
													//node - aktualny w�ze� z kt�rego idziemy dalej
													//bitmask - reprezentacja zbioru mini�tych miast
	void displayPath();								//metoda wy�wietlaj�ca minimalny cykl Hamiltona
													//display path --> spr�bwa� u�y� analogicznie tablicy jednowymiarowej 1x2^n
	void generateGraph(int n);						//generacja grafu, gdzie n - liczba miast

	void displayGraph();							//wy�wietlenie grafu - funkcja do kontroli - nie do��czona do MENU testowego

	void loadGraphFromFile(std::string filename);				//wczytywanie grafu z pliku
	bool readLine(std::ifstream &file, int tab[], int size);	//funckja pomocnicza dla ww.

	bool graphExists();			//zapobieganie b��dom wywo�ania countPath(), gdy graf nie istnieje

	~tspDynamicProgramming();	//destruktor wywo�uje clearGraph()
private:
	//atrybuty grafu
	int numOfCities;	//liczba miast
	int **adjMatrix;	//macierz s�siedztwa

	//zmienne do algorytmu
	int **DPtable;	//tablica rekurencji
	int **Path;		//tablica do odtworzenia drogi
	static const int INF = INT_MAX;
	int ALL_PASSED; //warto�� maski bitowej odpowiadaj�ca zbiorowi, w kt�rym wszytskie wierzcho�ki zosta�y ju� sprawdzone
					//ALL_PASSED = 1(0)...1(N-1) 

	void clearGraph();
};

