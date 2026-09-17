#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

struct Studentas {
	string vardas;
	string pavarde;
	vector<int> nd;
	int egz;
	double galutinisVid = 0.0;
	double galutineMed = 0.0;
};

int main() {
	vector<Studentas> studentai;
	int pasirinkimas;

	while (true) {
		cout << " Meniu";
		cout << " Ivesti studentus rankiniu budu";
		cout << " Generuoti studentus atsitiktinai";
		cout << " Spausdinti rezultatus";
		cout << " Issaugoti rezultatus i faila";
		cout << " Baigti darba";
		cout << " Pasirinkti veiksma: ";
		cin >> pasirinkimas;

		if (pasirinkimas == 0) {
			cout << "Programa baigia darba";
			return 0;
		}
	}

	return 0;
} 