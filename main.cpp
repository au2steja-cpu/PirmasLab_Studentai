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
		cout << " Meniu" << endl;
		cout << " Ivesti studentus rankiniu budu" << endl;
		cout << " Generuoti studentus atsitiktinai" << endl;
		cout << " Spausdinti rezultatus" << endl;
		cout << " Issaugoti rezultatus i faila" << endl;
		cout << " Baigti darba" << endl;
		cout << " Pasirinkti veiksma: " << endl;
		cin >> pasirinkimas;

		if (pasirinkimas == 0) {
			cout << "Programa baigia darba";
			return 0;
		}
	}

	return 0;
} 