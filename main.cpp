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
	double galutine_med;
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

double skaiciuotiMediana(vector<int> nd, int egz) {
	if (nd.empty()) return egz * 0.6;
	sort(nd.begin(), nd.end());
	size_t size = nd.size();
	double mediana;
	if (size % 2 == 0) {
		mediana = (nd[size / 2 - 1] + nd[size / 2]) / 2.0;
	} else {
		mediana = nd[size / 2];
	}
	return (mediana * 0.4) + (egz * 0.6);
}