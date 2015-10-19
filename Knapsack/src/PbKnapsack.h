/*
 * PbKnapsack.h
 *
 *  Created on: Oct 4, 2015
 *      Author: apidash
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <string>
#include <limits>

#include <fstream>
#include </usr/local/include/lemon/list_graph.h>
#include </usr/local/include/lemon/preflow.h>
#include </usr/local/include/lemon/bellman_ford.h>
using namespace lemon;
#ifndef PBKNAPSACK_H_
#define PBKNAPSACK_H_
struct item {
	int p;
	int w;
};
struct state {
	int a;
	int b;
	double wOut;
	double wIn;
	double pOut;
	double pIn;
	int item;
	state(const int & a, const int & b, const double & w1, const double & w2,
			const double & p1, const double & p2, const int & it) :
			a(a), b(b), wOut(w1), wIn(w2), pOut(p1), pIn(p2), item(it) {
	}
	const bool operator<(const state & s) {
		return (((this->wOut + this->wIn) < (s.wOut + s.wIn)
				and ((this->pOut + this->pIn) >= (s.pOut + s.pIn)))
				or ((this->wOut + this->wIn) == (s.wOut + s.wIn)
						and ((this->pOut + this->pIn) > (s.pOut + s.pIn))));
	}
};
struct setState {
	std::list<state> Set;
	void insert(state&s){

	}
	//bool dominance(const state& s){

};
class PbKnapsack {
public:
	int nbObj;
	int W;
	double LB;
	double dynSol;
	setState set;
	std::vector<item> objects;
	std::vector<int> /*weight, profit,*/x, dyn_x;
	std::vector<float> xcont;
	std::list<std::pair<int, double> > listRatio;
	std::vector<int> vecSort; // size (n+1)

	void Initialisation();
	PbKnapsack();
	PbKnapsack(int n, int W);
	bool FeasibilityTest();
	void ReadData(std::string str);
	void GenerateData(std::string str, int n);
	bool TrivialSolTest();
	void Ordering();
	void BaBApproch();
	double Pl(int j, double c);
	double ContPL(int i, double c);
	void PDynamic();
	void PDynCore();
	void printSolution();
	void printListPair();
	virtual ~PbKnapsack();
};

#endif /* PBKNAPSACK_H_ */
