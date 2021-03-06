// project_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include "Graph.h"
#include "Queue.h"
#include <Windows.h>
#include <ctime>
#include <iomanip>

#define loop 100

using namespace std;

long long int read_QPC() {
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return ((long long int) count.QuadPart);
}

int main()
{
	//TUTAJ NALEŻY ZAIMPLEMENTOWAć MENU
	bool testing = true;
	while (testing) {
		cout << "Minimalne drzewo rozpinajace --- 1\n"
				"Najkrotsza sciezka z jednym zrodlem --- 2\n"
				"Zakoncz --- 0\n"
				"Decyzja: ";

		int decision;
		cin >> decision;

		if (decision == 0) {
			testing = false;
		}
		else if (decision == 1) {
			system("cls");
			Graph* g = new Graph();
			bool testing_mst = true;
			string filename;

			while (testing_mst) {
				cout << "Wczytaj nieskierowany graf z pliku --- 1\n"
						"Wyswietl graf --- 2\n"
						"Algorytm Prima (macierz/lista) --- 3\n"
						"Algorytm Kruskala (macierz/lista) --- 4\n"
						"Zakoncz --- 0\n"
						"Decyzja: ";

				int decision; cin >> decision;
				system("cls");

				switch (decision) {
				case 1:
					cout << "Podaj nazwe pliku: "; cin >> filename; cout << endl;
					g->readUndirectedGraphFromFile(filename);
					cout << "\nWcisnij ENTER.";
					_getch();
					system("cls");
					break;
				case 2:
					g->printAdjMatrix();
					cout << endl;
					g->printAdjList();
					cout << endl;
					cout << "\nWcisnij ENTER.";
					_getch();
					system("cls");
					break;
				case 3:
					g->primMatrix(0);
					cout << endl;
					g->primList(0);
					cout << endl;
					cout << "\nWcisnij ENTER.";
					_getch();
					system("cls");
					break;
				case 4:
					g->kruskalMatrix(0);
					cout << endl;
					g->kruskalList(0);
					cout << endl;
					cout << "\nWcisnij ENTER.";
					_getch();
					system("cls");
					break;
				case 0:
					testing_mst = false;
					break;
				default:
					cout << "\nNie ma takiej opcji. \n\nWcisnij ENTER.";
					_getch();
					system("cls");
					break;
				}
			}

			delete g;
		}
		else if (decision == 2) {
			system("cls");
			Graph* g = new Graph();
			bool testing_sp = true;
			string filename;

			while (testing_sp) {
				cout << "Wczytaj skierowany graf z pliku --- 1\n"
						"Wyswietl graf --- 2\n"
						"Algorytm Dijkstry (macierz/lista) --- 3\n"
						"Algorytm Bellmana-Forda (macierz/lista) --- 4\n"
						"Zakoncz --- 0\n"
						"Decyzja: ";

				int decision; cin >> decision;
				system("cls");

				switch (decision) {
				case 1:
					cout << "Podaj nazwe pliku: "; cin >> filename; cout << endl;
					g->readDirectedGraphFromFile(filename);
					cout << "\nWcisnij ENTER.";
					_getch();
					system("cls");
					break;
				case 2:
					g->printAdjMatrix();
					cout << endl;
					g->printAdjList();
					cout << endl;
					cout << "\nWcisnij ENTER.";
					_getch();
					system("cls");
					break;
				case 3:
					g->dijkstraMatrix();
					cout << endl;
					g->dijkstraList();
					cout << endl;
					cout << "\nWcisnij ENTER.";
					_getch();
					system("cls");
					break;
				case 4:
					g->bellmanfordMatrix();
					cout << endl;
					g->bellmanfordList();
					cout << endl;
					cout << "\nWcisnij ENTER.";
					_getch();
					system("cls");
					break;
				case 0:
					testing_sp = false;
					break;
				default:
					cout << "\nNie ma takiej opcji. \n\nWcisnij ENTER.";
					_getch();
					system("cls");
					break;
				}
			}

			delete g;
		}
		else {
			cout << "\nNie ma takie opcji. Kliknij ENTER by kontynuowac.\n";
			_getch();
		}
		system("cls");
	}
	cout << "Kliknij ENTER by zakonczyc program.";
	_getch();

	/*
	//TESTY - POMIARY 
	//generujemy graf a następnie 10 razy wykonujemy na nim dany algorytm
	//zebrane 10 pomiarów czasów zostanie uśrednione
	//wygenerowane zostanie jeszcze 9 takich samych grafów
	//otrzymamy jeszcze 9 pomiarów
	//10 uśrednionych pomiarów zostanie przeniesione do excela i tam już przetwarzane

	//utworzenie obietku grafu
	Graph* g = new Graph();

	//zmienne do pomiarów
	long long int freq, start, end;
	long long int time = 0;

	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

	//10-krotne wykonanie na danym grafie wybranego algorytmu
	for (int i = 0; i < loop; i++) {

		//generacja grafu nieskierowanego/skierowanego
		//g->generateUndirectedGraph(300, 99);
		g->generateDirectedGraph(500, 99);

		start = read_QPC();
		//g->primMatrix(0);
		//g->primList(0);
		//g->kruskalMatrix(0);
		//g->kruskalList(0);
		//g->dijkstraMatrix(0);
		//g->dijkstraList(0);
		//g->bellmanfordMatrix(0);
		g->bellmanfordList(0);
		end = read_QPC() - start;
		time += end;
	}
 
	time /= loop;
	
	cout << "Time [s] : " << fixed << setprecision(3) << (float) time / freq << endl;
	cout << "Time [ms] : " << setprecision(2) << (1000.0 * time) / freq << endl;
	cout << "Time [us] : " << setprecision(0) << (1000000.0 * time) / freq << endl;
	delete g;
	g = nullptr;
	*/

    return 0;
}

