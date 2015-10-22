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
#include <time.h>
#include "PbKnapsack.h"
#include </usr/local/include/lemon/list_graph.h>
using namespace std;

int main() {
	using namespace lemon;
PbKnapsack sack1;
clock_t time,time2,time3;
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
		int type;
		cin >> name;
		int n;
		cout << "Give a number of objects\n";
		cin>> n;
		cout << "Give a type of instances:\n";
		cout << "Press 1 for uncorrelated instances:\n";
		cout << "Press 2 for weakly correlated instances:\n";
		cout << "Press 3 for profit=capacity instances:\n";
		cout << "Press 4 for strongly correlated instances:\n";
		cin>> type;
		sack1.GenerateData(name,n,type);
	}
	if (sack1.FeasibilityTest()) {
		cout << "Solution exists\n";
		if (!sack1.TrivialSolTest()) {
			cout << "BaB\n\n";
		  time=clock();
			sack1.BaBApproch();
		  time = clock() - time;


			cout << "Dynamic\n\n";
			time2=clock();
			sack1.PDynamic();
			time2 = clock() - time;


			cout << "CORE\n\n";
			time3=clock();
			sack1.PDynCore();
			time3 = clock() - time;

		}
		sack1.printSolution();
		cout<<endl;
		cout << "Time Branch and Bound:"<<(double)time/CLOCKS_PER_SEC<<"\n";
		cout << "Time GraphConcept:"<<(double)time2/CLOCKS_PER_SEC<<"\n";
		cout << "Time CoreConcept:"<<(double)time3/CLOCKS_PER_SEC<<"\n";
	} else {
		cout
				<< "Solution doesn't exist because of the incompatibility of data\n";
	}
	return 0;
}
