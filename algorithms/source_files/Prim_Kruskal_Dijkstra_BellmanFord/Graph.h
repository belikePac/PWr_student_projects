#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "adjList.h"
#include "Queue.h"
using namespace std;


class Graph
{
public:
	Graph();

	int ** adjMatrix = nullptr;	//macierz s�siedztwa
	adjList * list = nullptr;   //tablica list s�siedztwa

	int V;
	int E;
	int firstV;
	int lastV;
	static const int INF = INT_MAX;
	static const int INF_BF = 1000000;
	
	//UWAGA
	//Wywo�anie algorytmu Dijsktry lub Bellmana-Forda z arg. domy�lnym
	//uruchamia dany algorytm z wierzcho�kiem firstV

	//ALGORYTM PRIMA
	void primMatrix(int root);
	void primList(int root);

	//ALGORYTM KRUSKALA
	void kruskalMatrix(int root);
	void kruskalList(int root);

	//ALGORYTM DIJKSTRY
	void dijkstraMatrix(int s = -1);
	void dijkstraList(int s = -1);

	//ALGORYTM BELLMANA-FORDA
	void bellmanfordMatrix(int s = -1);
	void bellmanfordList(int s = -1);

	//ALGORYTM PRIMA - prezentacja wynik�w
	void printMSTMatrix(int *parent);
	void printMSTList(int *parent);

	//ALGORYTM KRUSKALA - prezentacja wynik�w
	void printMST(queueElement **MST, int e);

	//ALGORYTM DIJKSTRY & BELLMANA-FORDA - prezentacja wynik�w
	void printSP(int *parent, int *distance, int s);
	void printPath(int *parent, int s, int v);

	//Dla algorytm�w z problemu MST operuj�cych na macierzy
	//zosta�y zaimplementowane poni�sze dwie metody
	//zast�puj�ce kolejk� priorytetow� Q

	//funckja dodatkowa dla alg Prima rep macierzowej
	int minKey(bool *mst, int *keys);
	//funkcja dodatkowa dla alg Dijkstry rep macierzowej
	int minDis(int *distance, bool *Set);


	void createEmptyAdjMatrix();						//funkcja tworzy macierz zer o rozmairze [V][V]
														//V musi by� ju� znane
	void createList();									//funkcja tworzy list� s�siedztwa na podstawie macierzy s�siedztwa
														//jezeli macierz jest pusta oznacza to, �e graf jest pusty,
														//wiec lista nie zostanie utworzona

	//dwa generatory graf�w o podanej g�sto�ci
	//odpowiednio grafu nieskierowanego i skierowanego
	//przyj�to, �e wagi losowane b�d� z przedzia�u [1, 1M] gdy� jest to przedzia� wystarczaj�cy
	//dla przeprowadzanych test�w, gdzie liczba wierzcho�k�w maksymalnie wynosi� b�dzie 1000
	//bior�c pod uwage �e dla odpowiedniej g�sto�ci istnieje wiele �cie�ek, a algorytm i tak musi sprawdzi� wszystkie.
	void generateUndirectedGraph(int v, int d);			//v - liczba wierzcho�k�w w grafie - >0
	void generateDirectedGraph(int v, int d);			//d - g�sto�� grafu wyra�ana w procentach 0 - 100

	void readUndirectedGraphFromFile(string filename);	//wczytanie grafu nieskierowanego z pliku .txt
	void readDirectedGraphFromFile(string filename);    //wczytanie grafu skierowanego z pliku .txt
	bool readLine(ifstream &file, int tab[], int size); //pomocnicza funckja
														//funkcje wg SDIZO_time.pdf

	void printAdjMatrix();								//funkcje kontrolne, wy�wietlaj�ce struktur� grafu
	void printAdjList();

	void clearGraph();									//usuwa aktualnie przechowywany graf
														//usuwa macierz i list� s�siedztwa oraz zeruje dane takie jak V,E
														//pierwszy i ostatni wierzcho�ek ustawia na warto�ci -1

	~Graph();
};

