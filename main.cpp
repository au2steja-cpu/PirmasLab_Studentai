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

double skaiciuotiVidurki(const vector<int>& nd, int egz) {
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

vector<Studentas> skaitytiIsFailo(const string& studentai10000) {
	vector<Studentas> studentai;
	ifstream failas(studentai10000);

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

int main() {
	vector<Studentas> studentai;
	int pasirinkimas;

	do {
		cout << " --- Meniu ---" << endl;
		cout << " 1. Ivesti duomenis rankiniu budu" << endl;
		cout << " 2. Nuskaityti duomenis is failo" << endl;
		cout << " 3. Spausdinti rezultatus (vid.)" << endl;
		cout << " 4. Spausdinti rezultatus (med.)" << endl;
		cout << " 5. Spausdinti abu" << endl;
		cout << " 0. Baigti darba" << endl;
		cin >> pasirinkimas;

		if (pasirinkimas == 1) {
			studentai.clear();
			int studentuSkaicius;
			cout << "Kiek studentu noresite ivesti? ";
			cin >> studentuSkaicius;

			for (int i = 0; i < studentuSkaicius; i++) {
				Studentas s;
				cout << "---" << i + 1 << "studentas ---" << endl;
				cout << "Iveskite pavarde: "; cin >> s.pavarde;
				cout << "Iveskite varda: "; cin >> s.vardas;

				cout << "Iveskite namu darbu rezultatus (iveskite -1, kad baigtumete): " << endl;

				int nd_pazymys;
				while (cin >> nd_pazymys && nd_pazymys != -1) {
					s.nd_rezultatai.push_back(nd_pazymys);
				}

				cout << "Iveskite egzamino rezultata: "; cin >> s.egz;

				s.galutinis_vid = skaiciuotiVidurki(s.nd_rezultatai, s.egz);
				s.galutine_med = skaiciuotiMediana(s.nd_rezultatai, s.egz);

				studentai.push_back(s);
			}
		}
		else if (pasirinkimas == 2) {
			studentai = skaitytiIsFailo("studentai10000.txt");
			if (!studentai.empty()) {
				cout << "Duomenys sekmingai nuskaityti" << endl;
			}
		}
		else if (pasirinkimas >= 3 && pasirinkimas <= 5) {
			if (studentai.empty()) {
				cout << "Nera duomenu. Padarykite 1 arba 2 punkta" << endl;
			}
			else {
				sort(studentai.begin(), studentai.end(), palygintiStudentus);
				if (pasirinkimas == 3) spausdintiStudentus(studentai, true, false);
				else if (pasirinkimas == 4) spausdintiStudentus(studentai, false, true);
				else spausdintiStudentus(studentai, true, true);
			}
		}
	} while (pasirinkimas != 0);
	cout << "Programa baigta" << endl;
	return 0;
}