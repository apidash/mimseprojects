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
	//double relLin;
public:
	int a;
	int b;
	double wIn;
	double wOut;
	double pIn;
	double pOut;
	int item;
	double relLin;
	std::vector<int> sol;
	state(const int & a, const int & b, const double & w1, const double & w2,
			const double & p1, const double & p2, const int & it,
			const double & l) :
			a(a), b(b), wIn(w1), wOut(w2), pIn(p1), pOut(p2), item(it), relLin(
					l) {
	}
	state() {
		a = 0;
		b = 0;
		wIn = 0;
		wOut = 0;
		pIn = 0;
		pOut = 0;
		item = -1;
		relLin = 0;
	}
	state(const state& copy) :
			a(copy.a), b(copy.b), wIn(copy.wIn), wOut(copy.wOut), pIn(copy.pIn), pOut(
					copy.pOut), item(copy.item), relLin(copy.relLin) {
		sol=copy.sol;
	}
	void AddObj(int n) {
		sol[item] = 1;
	}
	const bool operator<(const state & s) {
		if ((a != s.a) and (b != s.b)) {
			return false;
		}
		return (((this->wOut + this->wIn) < (s.wOut + s.wIn)
				and ((this->pOut + this->pIn) >= (s.pOut + s.pIn)))
				or ((this->wOut + this->wIn) == (s.wOut + s.wIn)
						and ((this->pOut + this->pIn) > (s.pOut + s.pIn))));
	}
};
class setState {
public:
	std::list<state> Core;
	void Dominance() {
		std::list<state>::iterator it1;
		/*for (it1 = Core.begin(); it1 != Core.end(); it1++) {
			std::list<state>::iterator it2 = Core.begin();
			for (it2 = it1; it2 != Core.end(); it2++) {
				if ((*it2) < (*it1)) {
					it2 = Core.erase(it2);
				}
			}
		}*/
		it1 = Core.begin();
		while (it1 != Core.end()) {
			std::list<state>::iterator it2 = it1;
			while (it2 != Core.end()) {
				if ((*it2) < (*it1)) {
					it2 = Core.erase(it2);
					continue;
				}
				if((*it1) < (*it2)){
					it1 = Core.erase(it1);
					break;
				}
				it2++;
			}
			it1++;
		}
}
	void CutBound(int INC) {
		std::list<state>::iterator it = Core.begin();
		for (; it != Core.end(); it++) {
			if ((*it).relLin <= INC) {
				it = Core.erase(it);
			}
		}
	}
	//bool dominance(const state& s)
};
class PbKnapsack {
public:
	int nbObj;
	int W;
	double LB;
	double dynSol;
	setState listState;
	std::vector<item> objects;
	std::vector<int> /*weight, profit,*/x, dyn_x;
	std::vector<float> xcont;
	std::list<std::pair<int, double> > listRatio;
	std::vector<int> vecSort; // size (n+1)

	void Initialisation();
	PbKnapsack();
	bool FeasibilityTest();
	void ReadData(std::string str);
	void GenerateData(std::string str, int n);
	bool TrivialSolTest();
	//Branch and Bound
	void Ordering();
	void BaBApproch();
	double Pl(int j, double c);
	double ContPL(int i, double c);
	//Graph and the longest route
	void PDynamic();
	//Dynamic with core
	void PDynCore();
	int FindBreakItem(int j, double c);
	int CapacityOutcore(int, int, bool);
	int ProfitOutcore(int, int, bool);
	int FindINC(std::list<state>&);
	double U(state&, int, int);
	//Print the results
	void printSolution();
	void printListPair();
	virtual ~PbKnapsack();
};

#endif /* PBKNAPSACK_H_ */
