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
	this->u = u;		//wierzcho�ek pocz�tkowy
	this->v = v;		//wierzcho�ek ko�cowy
	this->key = key;    //kluczem jest waga kraw�dzi
}


queueElement::~queueElement()
{
}
