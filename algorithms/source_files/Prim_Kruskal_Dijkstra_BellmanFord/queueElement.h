#pragma once
class queueElement
{
public:
	queueElement(int v, int key);
	queueElement(int u, int v, int key);
	int u;   //src vertex - wierzcho�ek startowy
	int v;   //dest vertex - wierzcho�ek ko�cowy
	int key; //klucz
	~queueElement();
};

