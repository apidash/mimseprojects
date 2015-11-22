//============================================================================
// Name        : RCSPC.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int nbActivities;
int nbRessources;
vector<int> duration;
vector<int> avalaibility;
vector<int> succes;
vector<vector<int> > Successors;
vector<vector<int> > consumption;
void InitializeData(string filename) {
	ifstream in;

	in.open(filename.c_str());
	if (in.good()) {
		string s;
		string skey = "jobs";
		while (s.find(skey)) {
			in.clear();
			in.ignore();
			in >> s;
		}
		while (1) {
			if (in >> nbActivities) {
				break;
			} else {
				in.clear();
				in.ignore();
			}
		}
		while (s != "renewable") {
			in.clear();
			in.ignore();
			in >> s;
		}
		while (1) {
			if (in >> nbRessources) {
				break;
			} else {
				in.clear();
				in.ignore();
			}
		}
		duration.reserve(nbActivities);
		succes.reserve(nbActivities);
		Successors.reserve(nbActivities);
		consumption.reserve(nbActivities);
		avalaibility.reserve(nbRessources);
		while (s.find("PRECEDENCE RELATIONS")) {
			getline(in, s);
		}
		getline(in, s);
		int temp;
		int countEnd = 0;
		int i = 0;
		while (countEnd < (nbActivities * 3)) {
			if (in >> temp) {
				i++;
				countEnd++;
				if (i == 3) {
					succes[countEnd / 3 - 1] = temp;
					Successors[countEnd / 3 - 1].reserve(
							succes[countEnd / 3 - 1]);
					int k = 0;
					while (k < succes[countEnd / 3 - 1]) {
						in >> Successors[countEnd / 3 - 1][k];
						k++;
					}
					i = 0;
				}
			} else {
				in.clear();
				in.ignore();
			}
		}
		while (s.find("REQUESTS/DURATIONS")) {
			getline(in, s);
		}
		getline(in, s);
		getline(in, s);
		countEnd = 0;
		while (countEnd < (nbActivities * 3)) {
			if (in >> temp) {
				i++;
				countEnd++;
				if (i == 3) {
					duration[countEnd / 3 - 1] = temp;
					consumption[countEnd / 3 - 1].reserve(nbRessources);
					for (int k = 0; k < nbRessources; k++) {
						in >> consumption[countEnd / 3 - 1][k];
					}
					i = 0;
				}
			} else {
				in.clear();
				in.ignore();
			}
		}
		getline(in, s);
		getline(in, s);
		getline(in, s);
		getline(in, s);
		for (int k = 0; k < nbRessources; k++) {
			in >> avalaibility[k];
		}
	}
}

int main() {
	string name;
	cout << "Input file name" << endl;
	cin>>name;
	name =name + ".sm";
	InitializeData(name);
	cout << "Precedence:\n";
	for (int i = 0; i < nbActivities; i++) {
		for (int j = 0; j < succes[i]; j++) {
			cout << " " << Successors[i][j];
		}
		cout << "\n";
	}
	cout << "Consumption:\n";
	for (int i = 0; i < nbActivities; i++) {
		for (int j = 0; j < nbRessources; j++) {
			cout << " " << consumption[i][j];
		}
		cout << "\n";
	}
	cout << "duration:\n";
	for (int i = 0; i < nbActivities; i++) {
		cout << " " << duration[i];
		cout << "\n";
	}
	cout << "duration:\n";
	for (int i = 0; i < nbRessources; i++) {
		cout << " " << avalaibility[i];
		cout << "\n";
	}
	cout << "kjhjhjk" << endl;
	return 0;
}
