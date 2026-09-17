#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

struct Studentas {
	string pavarde;
	string vardas;
	vector<int> nd_rezultatai;
	int egz;
	double galutinis_vid;
};

double skaiciutiVidurki(const vector<int>& nd, int egz) {
	if (nd.empty()) return egz * 0.6;
	double sum = 0;
	for (int pazymys : nd) {
		sum += pazymys;
	}
	double vidurkis = sum / nd.size();
	return (vidurkis * 0.4) + (egz * 0.6);
}