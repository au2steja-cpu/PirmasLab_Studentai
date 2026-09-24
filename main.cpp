#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>
#include <random>
#include <chrono>

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
	}
	else {
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

	cout << string(rodytiVid && rodytiMed ? 66 : 48, '-') << endl;

	for (const auto& s : studentai) {
		cout << left << setw(15) << s.pavarde
			<< setw(15) << s.vardas;
		if (rodytiVid) cout << setw(18) << fixed << setprecision(2) << s.galutinis_vid;
		if (rodytiMed) cout << setw(18) << fixed << setprecision(2) << s.galutine_med;
		cout << endl;
	}
}

void generuotiAtsitiktinai(Studentas& s) {
	static mt19937 gen(random_device{}());
	uniform_int_distribution<> dist(1, 10);
	uniform_int_distribution<> kiekis(3, 7);

	int k = kiekis(gen);
	s.nd_rezultatai.clear();
	for (int i = 0; i < k; i++) s.nd_rezultatai.push_back(dist(gen));
	s.egz = dist(gen);
}

vector<Studentas> skaitytiIsFailo(const string& kursiokai) {
	vector<Studentas> studentai;
	ifstream failas(kursiokai);

	if (!failas.is_open()) {
		cout << "Nepavyko atidaryti failo: " << kursiokai << endl;
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
	cout << "Nuskaityta" << studentai.size() << " studentu is failo" << kursiokai.txt << endl;
	return studentai;
}

void ivestiRankiniuBudu(vectos<Studentas>& studentai) {
	studentai.clear();

	int studentuSkaicius;
	cout << "Kiek norite ivesti studentu? ";
	cin >> studentuSkaicius;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < studentuSkaicius; i++) {
		Studentas s;
		cout << "\n ----" << i + 1 << "studentas ---" << endl;
		cout << "Iveskite pavarde: "; cin >> s.pavarde;
		cout << "Iveskite varda: "; cin >> s.vardas;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Generuoti pazymius atsitiktinai? (t/n): ";
		char pasirinkimas;
		cin >> pasirinkimas;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (pasirinkimas == 't' || pasirinkimas == 'T') {
			generuotiAtsitiktinai(s);
			cout << "Sugeneruoti nd rezultatai: ";
			for (int p : s.nd_rezultatai) cout << p << " ";
			cout << "/ Egzaminas:" << s.egz << endl;
		}
		else {
			cout << "Ivekite namu darbu rezultatus" << endl;

			string eilute;
			while (getline(cin, eilute)) {
				if (eilute.empty()) break;
				stringstream ss(eilute);
				int val;
				while (sscanf >> val) s.nd_rezultatai.push_back(val);
			}

			cout << "Iveskite egzamino rezultata: ";
			cin >> s.egz;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		s.galutinis_vid = skaiciuotiVidurki(s.nd_rezultatai, s.egz);
		s.galutine_med = skaiciuotiMediana(s.nd_rezultatai, s.egz);
		studentai.push_back(s);
	}
}


void spausdintiMeniu() {
	cout << " --- Meniu ---" << endl;
	cout << " 1. Ivesti duomenis rankiniu budu" << endl;
	cout << " 2. Nuskaityti duomenis is failo" << endl;
	cout << " 3. Spausdinti rezultatus (vid.)" << endl;
	cout << " 4. Spausdinti rezultatus (med.)" << endl;
	cout << " 5. Spausdinti abu" << endl;
	cout << " 0. Baigti darba" << endl;

}

int main() {
	vector<Studentas> studentai;
	int pasirinkimas;

	do {
		spausdintiMeniu();
		if (!(cin >> pasirinkimas)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
			continue;
		}

		if (pasirinkimas == 1) {
			ivestiRankiniuBudu(studentai);
			studentai.clear();
		}
		else if (pasirinkimas == 2) {
			cout << "Iveskite failo pavadinima: ";
			string kursiokai.txt;
			cin >> kursiokai.txt;
			studentai = skaitytiIsFailo(kursiokai.txt);
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