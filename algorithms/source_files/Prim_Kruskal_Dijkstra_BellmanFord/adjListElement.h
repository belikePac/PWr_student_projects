#pragma once
class adjListElement
{
public:
	adjListElement();
	adjListElement(int v, int w);

	int v; //wierzcho�ek s�siedni
	int w; //waga kraw�dzi
	adjListElement* next;

	//funkcja tworz�ca nowy s�siedni wierzcho�ek
	adjListElement* newVerticle(int v, int w);

	~adjListElement();
};

