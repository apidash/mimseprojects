//============================================================================
// Name        : Knapsack.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "PbKnapsack.h"
#include </usr/local/include/lemon/list_graph.h>
using namespace std;

int main() {

	/*cout << "Input the number of objects\n";
	 int n, w;
	 cin >> n;
	 cout << "Input the capacity of sack\n";
	 cin >> w;*/
	//PbKnapsack sack1(7, 50);
	using namespace lemon;
PbKnapsack sack1;
	cout << "Welcome to the Knapsack problem\n";
	cout << "Do you want read data(Press 1) or generate now(Press 2)\n";
	int dec;
	cin >> dec;
	if (dec == 1) {
		cout << "List of instances\n";
		cout << "Enter the name of instance (wth *.dat)\n";
		string str;
		cin >> str;
		sack1.ReadData(str);
	}
	if (dec == 2) {
		cout << "Give the name for your instance\n";
		string name;
		cin >> name;
		int n;
		cout << "Give a number of objects\n";
		cin>> n;
		sack1.GenerateData(name,n);
	}
	if (sack1.FeasibilityTest()) {
		cout << "Solution exists\n";
		if (!sack1.TrivialSolTest()) {
			cout << "BaB\n\n";
			sack1.BaBApproch();
			cout << "Dynamic\n\n";
			sack1.PDynamic();
			cout << "CORE\n\n";
			sack1.PDynCore();
		}
		sack1.printSolution();
	} else {
		cout
				<< "Solution doesn't exist because of the incompatibility of data\n";
	}
	return 0;
}
