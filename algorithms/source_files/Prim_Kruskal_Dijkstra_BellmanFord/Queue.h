#pragma once
#include "queueElement.h"
class Queue
{
public:
	Queue(int capacity);
	int size;
	int capacity;
	queueElement ** Q = nullptr;			   //kolejka, tablica o dlugosci capacity (ilosci wierzcho�k�w), przechowuj�ca wska�niki na obiekty typu queueElement

	void insertNode(int v, int key);		   //dodanie nowego elementu do kopcja
	void insertEdge(int u, int v, int key);	   //funkcja dla algorytmu Prima - heapsort (przynajmniej co� ala)
	int  extractRoot();						   //funkcja zwraca korze� kolejki (kopca typu min)
	int* extractEdge();						   //funkcja zwraca tablice z wartosciami (u,v,w) w tej kolejno�ci	
	void minHeapify(int index, int direction); //przywracanie wlasnosci kopca typu min
	int search(int val);					   //zwraca indeks elemntu o zadanym kluczu (numerze wierzcho�ka)
											   //wierzcho�ek ten b�dzie mie� modyfikowany klucz 
											   //wiec potrzebny jest w�a�nie jego indeks w kolejce
	int searchEdge(int u, int v);			   //szuka w grafie danej kraw�dzi
	void decreaseKey(int ver, int val);        //tutaj potrzebna jest dodatkowa funkcja do zmniejszenia klucza danego wierzcho�ka!!!
	bool isEmpty();							   //zwraca informacj� o tym, czy kolejka jest pusta: true jesli jest
	bool isInQueue(int v);					   //zwraca informacje czy dany wierzcho�ek jest w kolejce, je�li jest, to true
	bool isEdgeInQueue(int u, int v);		   //zwraca iniformacj� o tym czy dana kraw�d� NIESKIEROWANA ju� istnieje

	int Parent(int index);					   //zwraca indeks rodzica
	int leftSon(int index);					   //zwraca indeks lewego syna
	int rightSon(int index);				   //zwraca index prawego syna

	static const short int up = 1;             //przywracanie wlasnoci w g�r�
	static const short int down = -1;		   //przywracanie wlasnoci w d�

	//pomocnicza funkcja kotrolna
	void printQueue();

	~Queue();
};

