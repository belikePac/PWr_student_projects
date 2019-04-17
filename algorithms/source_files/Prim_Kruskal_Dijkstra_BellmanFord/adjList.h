#pragma once
#include "adjListElement.h"
class adjList
{
public:
	adjList();

	adjListElement* head;

	void addEdge(int v, int w); //funkcja dodaje now� kraw�d� do danej listy
	int searchWeight(int v);    //funkcja zwraca wag� danej kraw�dzi

	~adjList();
};

