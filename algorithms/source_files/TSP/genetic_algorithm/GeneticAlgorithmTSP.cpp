#pragma once
#include "GeneticAlgorithmTSP.h"
#include <iostream>
#include <sstream>
#include <random>
#include <cmath>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include "Timer.h"
using namespace std;

GeneticAlgorithmTSP::GeneticAlgorithmTSP()
{
	//startowe warto�ci parametr�w
	numOfCities = 0;

	numOfIterations = 100;
	finalTime = 15;
	sizeOfPopulation = 100;
	mutationProbability = 0.01; //wartosci p-p ustawione wg instrukcji
	crossoverProbability = 0.8;
	numOfSwaps = 1;
	numOfKnights = 10;

	adjMatrix = nullptr;

	bestOrder = nullptr;
	currentBestOrder = nullptr;

	population = nullptr;
	parents = nullptr;
	children = nullptr;

	srand(time(NULL));
}

void GeneticAlgorithmTSP::startGA()
{
	//zmienna iteracyjna
	int iteration = 0;
	//stoper
	Timer *t = new Timer();
	t->startTimer();
	int workingTime = 0;

	//generacja populacji pocz�tkowej oraz wyniku jaki jest najlepszy na pocz�tku
	generateInitialPopulation();
	cout << "Wynik: " << getCurrentRoute() << endl;

	while (t->getTime() <= finalTime && iteration < numOfIterations) {

		generateParentsPopulation();  //generacja populacji rodzic�w
		generateChildrenPopulation(); //generacja dzieci z wybranej populacji rodzic�w
		setNewPopulation();			  //zamiana pokole� population<=children
		//co 1s wyswietl bie��cy najlepszy wynik
		if (workingTime != t->getIntTime()) {
			workingTime = t->getIntTime();
			cout << "Wynik: " << getCurrentRoute() << endl;
		}
		iteration++;
	}

	cout << "\nCzas wykonywania: " << t->getTime() << endl;
	cout << "Najlepszy wynik: " << getBestRoute() << endl;
	delete t;
}

void GeneticAlgorithmTSP::displayGraph()
{
	if (adjMatrix != nullptr) {
		for (int i = 0; i < numOfCities; i++) {
			for (int j = 0; j < numOfCities; j++) {
				std::cout << adjMatrix[i][j] << " ";
				if (j == numOfCities - 1) {
					std::cout << std::endl;
				}
			}
		}

		cout << "\nLiczba miast: " << numOfCities << endl;
	}
	else {
		cout << "Macierz sasiedztwa jest pusta.\n";
	}
}

void GeneticAlgorithmTSP::readGraphFromFile(std::string filename)
{
	std::ifstream file;
	int cities[1];
	file.open(filename.c_str());

	//wczytanie grafu z pliku
	if (file.is_open()) {
		//jezeli nazwa pliku jest poprawna, to poprzedni graf zostaje usuniety
		//w.p.w. nie ma sensu usuwa� istniej�cego grafu
		//zak�ada si� poprawno�� struktury danych w pliku
		clearGraph();

		if (readLine(file, cities, 1)) {

			//wczytanie i inicjalzacja podstawowych danych
			numOfCities = cities[0];

			//utworzenie macierzy
			adjMatrix = new int *[numOfCities];
			for (int i = 0; i < numOfCities; i++) {
				adjMatrix[i] = new int[numOfCities];
			}

			//wektor przechowuj�cy wiersz macierzy
			int *dist = new int[numOfCities];

			//wczytanie macierzy s�siedztwa z pliku
			for (int i = 0; i < numOfCities; i++) {
				if (readLine(file, dist, numOfCities)) {
					for (int j = 0; j < numOfCities; j++) {
						adjMatrix[i][j] = dist[j];
					}
				}
				else {
					std::cout << "\nFILE ERROR - EDGE\n";
				}
			}

			delete[]dist;

			//utworzenie trzech populacji
			population = new int *[sizeOfPopulation];
			for (int i = 0; i < sizeOfPopulation; i++) {
				population[i] = new int[numOfCities];
			}
			parents = new int *[sizeOfPopulation];
			for (int i = 0; i < sizeOfPopulation; i++) {
				parents[i] = new int[numOfCities];
			}
			children = new int *[sizeOfPopulation];
			for (int i = 0; i < sizeOfPopulation; i++) {
				children[i] = new int[numOfCities];
			}
			//oraz dw�ch rozwi�za�
			bestOrder = new int[numOfCities];
			currentBestOrder = new int[numOfCities];
		}
		else {
			std::cout << "\nFILE ERROR - INFO\n";
		}

		file.close();

	}
	else {
		std::cout << "\nFILE ERROR - OPEN\n";
	}
}

bool GeneticAlgorithmTSP::readLine(std::ifstream & file, int tab[], int size)
{
	std::string s;
	getline(file, s);
	if (file.fail() || s.empty())
		return false;
	std::istringstream in_ss(s);
	for (int i = 0; i < size; i++) {
		in_ss >> tab[i];
		if (in_ss.fail())
			return false;
	}
	return true;
}

bool GeneticAlgorithmTSP::graphExists()
{
	return adjMatrix != nullptr;
}

double GeneticAlgorithmTSP::getBestRoute(int d)
{
	if (d == 1) {
		cout << "Best Length: " << bestOrder[numOfCities - 1] << endl;
		return bestOrder[numOfCities - 1];
	}
	else if (d == 2) {
		cout << "Best Length: " << bestOrder[numOfCities - 1] << endl;
		cout << "0 -> ";
		for (int i = 0; i < (numOfCities - 1); i++) {
			cout << bestOrder[i] << "-> ";
		}
		cout << "0\n";
		return bestOrder[numOfCities - 1];
	}
	else {
		return bestOrder[numOfCities - 1];
	}
}

double GeneticAlgorithmTSP::getCurrentRoute(int d)
{
	if (d == 1) {
		cout << "Current Length: " << currentBestOrder[numOfCities - 1] << endl;
		return currentBestOrder[numOfCities - 1];
	}
	else if (d == 2) {
		cout << "Current Length: " << currentBestOrder[numOfCities - 1] << endl;
		cout << "0 -> ";
		for (int i = 0; i < (numOfCities - 1); i++) {
			cout << currentBestOrder[i] << "-> ";
		}
		cout << "0\n";
		return currentBestOrder[numOfCities - 1];
	}
	else {
		return currentBestOrder[numOfCities - 1];
	}
}

void GeneticAlgorithmTSP::getParameters()
{
	cout << "BIEZACA KONFIGURACJA PARAMETROW\n\n"
		<< "rozmiar populacji: " << sizeOfPopulation << endl
		<< "liczba osobnikow w turnieju: " << numOfKnights << endl
		<< "prawdopodobienstwo krzyzowania: " << crossoverProbability << endl
		<< "prawdopodobienstwo mutacji: " << mutationProbability << endl
		<< "liczba iteracji: " << numOfIterations << endl
		<< "liczba mutowanych genow: " << numOfSwaps << endl
	    << "czas dzialania [s]: " << finalTime << endl;
}

void GeneticAlgorithmTSP::setSizeOfPopulation(int n)
{
	if (n % 2 == 1) n++; //je�li u�ytkownik poda� nieparzyst� liczb� to zwi�kszamy j� o jeden
						 //parzysty rozmiar populacji jest niezb�nym za�o�eniem dla funkcji generuj�cej par� dzieci
						 //poniewa� zawsze generowana jest para, czyli liczba dzieci b�dzie parzystac
						 //na�o�enie takiego ograniczenia jest najprostszym rozwi�zaniem tego problemu
						 //a jednocze�nie jeden osobnik wi�cej nie jest, a� tak znacz�c� ingerencja w dzia�anie algorytmu,
						 //kt�ry opiera si� tak�e w�a�nie na odpowiednio du�ym ROZMIARZE populacji

	//po upewnieniu si�, �e n jest parzysta, mo�na zmieni� rozmiar populacji
	if (graphExists()) {
		//zmieniaj�c rozmiar populacji musimy usun�� to co by�o
		if (population != nullptr) {
			for (int i = 0; i < sizeOfPopulation; i++) {
				delete[] population[i];
			}
			delete[]population;
			population = nullptr;
			//cout << "Graf usuniety.\n";
		}
		if (parents != nullptr) {
			for (int i = 0; i < sizeOfPopulation; i++) {
				delete[] parents[i];
			}
			delete[]parents;
			parents = nullptr;
			//cout << "Graf usuniety.\n";
		}
		if (children != nullptr) {
			for (int i = 0; i < sizeOfPopulation; i++) {
				delete[] children[i];
			}
			delete[]children;
			children = nullptr;
			sizeOfPopulation = 0;
			//cout << "Graf usuniety.\n";
		}

		//wtedy mo�emy zmieni� rozmiar populacji
		sizeOfPopulation = n;

		//a nast�pnie ponownie utworzy� populacje
		//utworzenie trzech populacji
		population = new int *[sizeOfPopulation];
		for (int i = 0; i < sizeOfPopulation; i++) {
			population[i] = new int[numOfCities];
		}
		parents = new int *[sizeOfPopulation];
		for (int i = 0; i < sizeOfPopulation; i++) {
			parents[i] = new int[numOfCities];
		}
		children = new int *[sizeOfPopulation];
		for (int i = 0; i < sizeOfPopulation; i++) {
			children[i] = new int[numOfCities];
		}
	}
	else {
		//jezeli graf nie istnieje to znaczy, �e jest to pierwsze uruchomienie programu
		//zatem nie mo�emy dublowa� alokacji miejsca, kt�ra odb�dzie si� i tak w momencie wczytywania grafu
		//w�wczas potrzeba tylko rozmiaru populacji
		//na g�rze, kiedy graf istnieje a my zmieniamy rozmiar populacji, to trzeba usun�� istniej�ce trzy populacje
		//a nast�pnie utworzy� nowe w mi�dzy czassie ustawiaj�c nowy rozmiar populacji
		//gdyby�my ponownie wczytywali graf z pliku, to nie ma problemu, bo i tak na pocz�tku robimy clearGraph(),
		//wi�c potem zn�w utworzymy 3 populacje rozmiaru takiego, jaki by� uprzednio ustawiony.
		sizeOfPopulation = n;
	}
}

GeneticAlgorithmTSP::~GeneticAlgorithmTSP()
{
	clearGraph();
}

void GeneticAlgorithmTSP::generateInitialPopulation()
{
	//wszystkie osobniki startowe to permutacje 1,2,3,..., n-2, n-1
	for (int i = 0; i < sizeOfPopulation; i++) {
		for (int j = 1; j < numOfCities; j++) {
			population[i][j - 1] = j;
		}
	}
	//w ka�dym osobniku dokonujemy losowych zmian - generujemy nowe permutacje
	//nast�pnie obliczamy dla ka�dego warto�� funkcji przystosowania
	int m, n, k;
	for (int i = 0; i < sizeOfPopulation; i++) {
		//M1
		for (int j = 0; j < numOfCities; j++) {
			//wylosuj dwie pozycje
			do {
				m = rand() % (numOfCities - 1);
				n = rand() % (numOfCities - 1);
			} while (m == n);
			//zamie� je miejscami
			k = population[i][m];
			population[i][m] = population[i][n];
			population[i][n] = k;
		}
		/*M2
		for (int j = 0; j < (numOfCities - 1); j++) {
			int delta = rand() % (numOfCities - 1 - j);
			int temp = population[i][j];
			population[i][j] = population[i][j + delta];
			population[i][j + delta] = temp;
		}*/
		population[i][numOfCities-1] = countRouteLength(population[i]);
	}

	//wyznaczenie najlepszego rozwi�zania w populacji pocz�tkowej
	int min = INT_MAX;
	int index = 0;
	for (int i = 0; i < sizeOfPopulation; i++) {
		if (population[i][numOfCities - 1] < min) {
			min = population[i][numOfCities - 1];
			index = i;
		}
	}

	memcpy(bestOrder, population[index], numOfCities * 4);
	memcpy(currentBestOrder, population[index], numOfCities * 4);
}

void GeneticAlgorithmTSP::generateParentsPopulation()
{
	for (int i = 0; i < sizeOfPopulation; i++) {
		int indexOfWinner = tournament();	//indeks zwyci�zcy
		memcpy(parents[i], population[indexOfWinner], numOfCities * 4);	//zwyci�zca jest wstawiany na pozycj� i-t� do populacji rodzic�w
	}
}

int GeneticAlgorithmTSP::tournament()
{
	//u�ycie maszyny mt generuje bardzo du�y nak�ad czasowy
	//dla pewnej instancji mt - 45s a rand() - 16s
	//jednak u�ycie funkcji rand() nie pozwoli na posiadanie populacji wi�kszej, ni� 32000,
	//gdy� nie b�dziemy w stanie wylosowa� liczby >32000, zatem osobniki takie jak np. 50000 b�d� pomijane
	//drugie podej�cie to na�o�enie ogranicze� na rozmiar populacji, nie mo�na ustawi� rozmiaru >32000,
	//w�wczas zyskujemy pr�dko�� dzia�ania algorytmu
	//drugie podej�cie zosta�o wybrane

	//int val;
	//random_device rd;
	//mt19937 gen(rd());
	//uniform_int_distribution<> dist(0, (sizeOfPopulation - 1));

	int indexOfWinner;
	int vffOfWinner;
	//indexOfWinner = dist(gen); //pierwszy wybrany osobnik jest domniemanym zwyci�zc�
	indexOfWinner = rand() % sizeOfPopulation; //zbyt ma�y przedzial 0-32000
	vffOfWinner = population[indexOfWinner][numOfCities - 1]; //warto�� jego funkcji dopasowania staje sie odno�nikiem
	
	int index;
	//pojedynek przeprowadzamy numOfKnights razy
	for (int i = 0; i < numOfKnights; i++) {
		//osobnik nie mo�e rywalizowac z samym sob�
		do {
			//index = dist(gen);
			index = rand() % sizeOfPopulation;
		} while (index == indexOfWinner);
		//powy�sza p�tla dopuszcza pojedynek powt�rny pomi�dzy dwoma osobnikami
		//nie ma �adnej listy tabu wybieranych osobnik�w
		//szansa powt�rzenia liczby to 0.000031 zatem mo�na za�o�y�, �e liczby losowane
		//b�d� powtarza� si� rzadko
		if (population[index][numOfCities - 1] < vffOfWinner) {
			vffOfWinner = population[index][numOfCities - 1];
			indexOfWinner = index;
		}
	}

	//na koniec pojedynku w indexOfWinner znajduje si� indeks zwyci�zcy
	return indexOfWinner;
}

void GeneticAlgorithmTSP::generateChildrenPopulation()
{
	for (int i = 0; i < sizeOfPopulation; i = i + 2) {
		generatePairOfChildren(i);
	}
}

void GeneticAlgorithmTSP::generatePairOfChildren(int index)
{
	//wybierz dw�ch rodzic�w
	int m, n;
	do {
		m = rand() % (sizeOfPopulation);
		n = rand() % (sizeOfPopulation);
	} while (m == n);
	int *p1 = parents[m];
	int *p2 = parents[n];
	//utw�rz dw�jk� dzieci i sklonuj do nich genotyp rodzic�w
	int *c1 = new int[numOfCities];
	int *c2 = new int[numOfCities];
	memcpy(c1, p1, numOfCities * 4);
	memcpy(c2, p2, numOfCities * 4);
	//wybierz dwa punkty krzy�owania (m ma by� < n)
	do {
		m = rand() % (numOfCities - 1);
		n = rand() % (numOfCities - 1);
	} while (m == n);
	//sprawdz poprawno�� punkt�w - aby zawsze m by� tym bli�ej pocz�tku a n tym bli�ej ko�ca
	if (m > n) {
		int k = n;
		n = m;
		m = k;
	}
	//implementowane jest krzy�owanie PMX z dwoma punktami ci�cia
	//z penym p-p przeprowadz krzy�owanie na pierwszym dziecku
	if (getRandomProbability() <= crossoverProbability) {
		//dzia�amy w przedziale wyznaczonym przez punkty krzy�owania
		for (int i = m; i <= n; i++) {
			//chc� wstawi� na pozycj� i-t� warto�� z rodzica p2[i], musimy odnale�� t� warto�� w dziecku c1
			//a nast�pnie dokona� zamiany swap pomi�dzy pozycj� c1[i], gdzie znajduje si� pewna warto�� X oraz pozycj� gdzie znajduje si� w c1 warto�� r�wna p2[i]
			//gdyby zrobi� od razu c1[i]=p2[i], to gubimy warto�� z tej pozycji oraz tworzymy cykl oraz nie odwiedzamy wszystkich miast
			for (int k = 0; k < (numOfCities - 1); k++) {
				if (c1[k] == p2[i]) {
					c1[k] = c1[i];
					break;
				}
			}
			c1[i] = p2[i];//na dana pozycj� przekopiuj gen rodzica
		}
	}
	//z pewnym innym p-p przeprowadz krzy�owanie na drugim dziecku
	if (getRandomProbability() <= crossoverProbability) {
		for (int i = m; i <= n; i++) {
			for (int k = 0; k < (numOfCities - 1); k++) {
				if (c2[k] == p1[i]) {
					c2[k] = c2[i];
					break;
				}
			}
			c2[i] = p1[i];
		}
	}
	//spr�buj dokona� mutacji na pierwszym dziecku
	tryToMutate(c1);
	//spr�buj odkonac mutacji na drugim dziecku
	tryToMutate(c2);
	//oblicz now� warto�� funkcji przystosowania dla obu dzieci
	c1[numOfCities - 1] = countRouteLength(c1);
	c2[numOfCities - 1] = countRouteLength(c2);
	//po tych czynno�ciach wpisz dzieci do populacji children na miejsca index oraz index+1 --- memcpy kopiuje zawarto��
	//w zewn�trznej p�tli poruszamy si� po indeksach parzystych 0, 2, 4
	//gdy n=100 to p�tla wykona si� jeszcze dla 98, wi�c znajdziemy dzieci na pozycje 98 oraz 99, czyli otrzymamy 100 dzieci
	//pojawia si� tu problem z nieparzysto�ci� populacji, dlatego parzysto�� populacji jest za�o�eniem
	//w menu kontekstowym nale�y zabezpieczy� tak� sytuacj�, je�li u�ytkownik b�dzie chcia� poda� liczb� nieparzyst�, to nale�y j� zwi�kszy� o 1
	memcpy(children[index], c1, numOfCities * 4);
	memcpy(children[index + 1], c2, numOfCities * 4);
	//ca�kowicie bezpiecznie usun obiekty tymczasowych dzieci, rodzic�w nie usuwamy, bo te wska�niki tylko pomocnie wskazywa�y na odpowiedni miejsca w populacji rodzic�w
	delete[]c1;
	delete[]c2;
}

void GeneticAlgorithmTSP::tryToMutate(int * child)
{
	if (getRandomProbability() <= mutationProbability)
		mutate(child);
}

void GeneticAlgorithmTSP::mutate(int * child)
{
	int m, n, k;
	for (int i = 0; i < numOfSwaps; i++) {
		//wylosuj dwa r�ne pojedyncze geny
		do {
			m = rand() % (numOfCities - 1);
			n = rand() % (numOfCities - 1);
		} while (m == n);
		//zamie� je miejscami
		k = child[m];
		child[m] = child[n];
		child[n] = k;
		//mutacja powinna byc jak njabardziej subtelna
	}
}

void GeneticAlgorithmTSP::setNewPopulation()
{
	//przeniesienie populacji dzieci na miejsce nowej populacji
	for (int i = 0; i < sizeOfPopulation; i++) {
		memcpy(population[i], children[i], numOfCities * 4);
	}
	//aktualizacja rozwi�za� wpierw bie��cego i je�li uleg�o polepszeniu, to tak�e najlepszego ze wszytskich
	int min = INT_MAX;
	int index = 0;
	for (int i = 0; i < sizeOfPopulation; i++) {
		if (population[i][numOfCities - 1] < min) {
			min = population[i][numOfCities - 1];
			index = i;
		}
	}
	//przekopiuj najlepsze bie��ce rozwi�zanie
	memcpy(currentBestOrder, population[index], numOfCities * 4);
	//jesli jest ono lepsze ni� najlepsze, to przekopiuj je do najlepszego
	if (currentBestOrder[numOfCities - 1] < bestOrder[numOfCities - 1])
		memcpy(bestOrder, currentBestOrder, numOfCities * 4);
}

int GeneticAlgorithmTSP::countRouteLength(int * order)
{
	int dist = 0;

	dist += adjMatrix[0][order[0]];

	for (int i = 0; i < (numOfCities - 2); i++) {
		dist += adjMatrix[order[i]][order[i + 1]];
	}

	dist += adjMatrix[order[(numOfCities - 2)]][0];

	return dist;
}

double GeneticAlgorithmTSP::getRandomProbability()
{
	return (double)rand() / (double)RAND_MAX;
}

void GeneticAlgorithmTSP::clearGraph()
{
	if (adjMatrix != nullptr) {
		for (int i = 0; i < numOfCities; i++) {
			delete[] adjMatrix[i];
		}
		delete[]adjMatrix;
		adjMatrix = nullptr;
		numOfCities = 0;
		//cout << "Graf usuniety.\n";
	}
	if (population != nullptr) {
		for (int i = 0; i < sizeOfPopulation; i++) {
			delete[] population[i];
		}
		delete[]population;
		population = nullptr;
		//cout << "Graf usuniety.\n";
	}
	if (parents != nullptr) {
		for (int i = 0; i < sizeOfPopulation; i++) {
			delete[] parents[i];
		}
		delete[]parents;
		parents = nullptr;
		//cout << "Graf usuniety.\n";
	}
	if (children != nullptr) {
		for (int i = 0; i < sizeOfPopulation; i++) {
			delete[] children[i];
		}
		delete[]children;
		children = nullptr;
		//cout << "Graf usuniety.\n";
	}
	if (bestOrder != nullptr) {
		delete[]bestOrder;
		bestOrder = nullptr;
		// << "BO usuniety.\n";
	}
	if (currentBestOrder != nullptr) {
		delete[]currentBestOrder;
		currentBestOrder = nullptr;
		//cout << "CO usuniety.\n";
	}
}
