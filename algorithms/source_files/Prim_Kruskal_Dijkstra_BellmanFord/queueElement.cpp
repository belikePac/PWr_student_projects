#include "stdafx.h"
#include "queueElement.h"


queueElement::queueElement(int v, int key)
{
	this->u = 0;
	this->v = v;
	this->key = key;
}

queueElement::queueElement(int u, int v, int key)
{
	this->u = u;		//wierzchołek początkowy
	this->v = v;		//wierzchołek końcowy
	this->key = key;    //kluczem jest waga krawędzi
}


queueElement::~queueElement()
{
}
