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

bool palygintiStudentus(const Studentas& a, const Studentas& b) {
	if (a.vardas == b.vardas) {
		return a.pavarde < b.pavarde;
	}
	return a.vardas < b.vardas;
}

void spausdintiStudentus(const vector<Studentas>& studentai, bool rodytiVid, bool rodytiMed) {
	cout << left << setw(15) << "Pavarde"
		<< setw(15) << "Vardas";
	if (rodytiVid) cout << setw(15) << "Galutinis(Vid)";
	if (rodytiMed) cout << setw(15) << "Galutinis(Med)";
	cout << endl;

	cout << string(60, '-') << endl;

	for (const auto& s : studentai) {
		cout << left << setw(15) << s.pavarde
			<< setw(15) << s.vardas;
		if (rodytiVid) cout << setw(15) << fixed << setprecision(2) << s.galutinis_vid;
		if (rodytiMed) cout << setw(15) << fixed << setprecision(2) << s.galutine_med;
		cout << endl;
	}
}

vector<Studentas> skaitytiIsFailo(const string& studentai10000.txt) {
	vector<Studentas> studentai;
	ifstream failas(studentai10000.txt);

	if (!failas.is_open()) {
		cout << "Nepavyko atidaryti failo: " << studentai10000 << endl;
		return studentai;
	}

	string eilute;
	getline(failas, eilute);

	while (getline(failas, eilute)) {
		if (eilute.empty()) continue;

		stringstream ss(eilute);
		Studentas s;
		ss >> s.pavarde >> s.vardas;

		int pazymys;
		vector <int> visi_pazymiai;
		while (ss >> pazymys) {
			visi_pazymiai.push_back(pazymys);
		}

		if (!visi_pazymiai.empty()) {
			s.egz = visi_pazymiai.back();
			visi_pazymiai.pop_back();
			s.nd_rezultatai = visi_pazymiai;
		}
		else {
			s.egz = 0;
		}

		s.galutinis_vid = skaiciuotiVidurki(s.nd_rezultatai, s.egz);
		s.galutine_med = skaiciuotiMediana(s.nd_rezultatai, s.egz);

		studentai.push_back(s);
	}

	failas.close();
	return studentai;
}

