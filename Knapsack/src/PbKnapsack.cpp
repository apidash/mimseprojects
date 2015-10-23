/*
 * PbKnapsack.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: apidash
 */

#include "PbKnapsack.h"
void PbKnapsack::Initialisation() {
	for (int i = 0; i < nbObj; i++) {
		x.push_back(0);
		xcont.push_back(0);
		dyn_x.push_back(-1);
		core_x.push_back(0);
	}
}

PbKnapsack::PbKnapsack() {
	LB = 0;
	W = 0;
	nbObj = 0;
	dynSol = 0;
	CoreSol = 0;
}
void PbKnapsack::GenerateData(std::string str, int n,int type ) {

	srand(time(NULL));
	//W = 100 + rand() % 40;
	int sum=0;
	nbObj = n;
	objects.reserve(nbObj);
	Initialisation();
	if (type == 1) {
		for (int i = 0; i < nbObj; i++) {
			objects[i].p = (1 + rand()% 70);
			objects[i].w = (1 + rand() % 70);
			sum+=objects[i].w;
			listRatio.push_back(
					std::make_pair(i,
							(double) objects[i].p / (double) objects[i].w));
		}

	}
	if (type == 2) {
		for (int i = 0; i < nbObj; i++) {
			objects[i].w = (10 + rand() % 100);
			objects[i].p = ( 2*(rand()% 10)+objects[i].w -10);
			if(objects[i].p<=0){
				objects[i].p=1;
			}
			sum+=objects[i].w;
			listRatio.push_back(
					std::make_pair(i,
							(double) objects[i].p / (double) objects[i].w));
		}
	}
	if (type == 3) {
		for (int i = 0; i < nbObj; i++) {
			objects[i].p = (1 + rand() % 101);
			objects[i].w = objects[i].p;
			sum+=objects[i].w;
			listRatio.push_back(std::make_pair(i,1));
		}
	}
	if (type == 4) {
		for (int i = 0; i < nbObj; i++) {
			objects[i].w = (1 + rand() % 100);
			objects[i].p = objects[i].w+10;
			sum+=objects[i].w;
			listRatio.push_back(
					std::make_pair(i,
							(double) objects[i].p / (double) objects[i].w));
		}
	}

    W=(int)(sum)/10;
	std::string name = "/home/apidash/workspace/Knapsack/" + str + ".dat";
	std::ofstream ofs1(name.c_str());
	ofs1 << "nbObj= ";
	ofs1 << nbObj << ";" << std::endl;
	ofs1 << "Capacity= ";
	ofs1 << W << ";" << std::endl;
	ofs1 << "Profit =[ ";
	for (int i = 0; i < nbObj - 1; i++) {
		ofs1 << objects[i].p << ",";
	}
	ofs1 << objects[nbObj - 1].p << "];" << std::endl;
	ofs1 << "Weight =[ ";
	for (int i = 0; i < nbObj - 1; i++) {
		ofs1 << objects[i].w << ",";
	}
	ofs1 << objects[nbObj - 1].w << "];" << std::endl;

}
void PbKnapsack::ReadData(std::string str) {

	std::ifstream in;
	std::string name = "/home/apidash/workspace/Knapsack/" + str + ".dat";
	in.open(name.c_str());
	if (in.good()) {
		std::string tmp;
		in >> tmp;
		//in >> tmp;
		in >> nbObj >> tmp >> std::ws;
		in >> tmp;
		//in >> tmp;
		in >> W >> tmp >> std::ws;
		objects.reserve(nbObj);
		if (objects.size() == objects.capacity()) {
			std::cout << "Allocate memory's problem\n";
			exit(1);
		}
		Initialisation();
		int i = 0, j = 0;
		while (i != nbObj) {
			if (in >> objects[i].p) {
				i++;
			}

			else {
				in.clear();
				in.ignore();
			}
		}
		while (j != nbObj) {
			if (in >> objects[j].w) {
				j++;
			}

			else {
				in.clear();
				in.ignore();
			}
		}
	}
	for (int i = 0; i < nbObj; i++) {
		listRatio.push_back(
				std::make_pair(i,
						(double) objects[i].p / (double) objects[i].w));
	}
}
bool PbKnapsack::FeasibilityTest() {
	bool flag = false;
	for (int i = 0; i < nbObj; i++) {
		if (objects[i].w > W) {
		} else {
			flag = true;
		}
	}
	if (flag)
		return true;
	return false;
}
bool PbKnapsack::TrivialSolTest() {
	int sum = 0;
	int res;
	for (int i = 0; i < nbObj; i++) {
		sum += objects[i].w;
		res += objects[i].p;
	}
	if (sum < W) {
		for (int i = 0; i < nbObj; i++) {
			x[i] = 1;
		}
		LB = res;
		std::cout << "Trivial solution: all objects in the Knapsack\n";
		return true;
	}
	return false;
}
bool MyDataSortPredicate(const std::pair<int, double>& lhs,
		const std::pair<int, double>& rhs) {
	return lhs.second > rhs.second;
}
void PbKnapsack::Ordering() {
	listRatio.sort(MyDataSortPredicate); //sortiruet li
	int k = 0;
	vecSort.push_back(-1);
	std::list<std::pair<int, double> >::iterator it;
	for (it = listRatio.begin(); it != listRatio.end(); ++it) {
		++k;
		vecSort.push_back((*it).first);
	}

}
double PbKnapsack::Pl(int j, double c) {
	double sum = c;
	double u = 0;
	int i=j;
	//if(i==nbObj){
	//	return 0;
	//}
	while(i<=nbObj){
		if(objects[vecSort[i]].w <= sum){
			sum -= objects[vecSort[i]].w;
			u += objects[vecSort[i]].p;
		}else{
			u+=(double) objects[vecSort[i]].p* ((double) (sum) / (double) objects[vecSort[i]].w);
			break;
		}
		i++;
	}
	return u;
}
int PbKnapsack::FindBreakItem(int j, double c) {
	double sum = 0;
	double u = 0;
	int critItem = -1;
	for (int i = j; i <= nbObj; i++) {
		sum += objects[vecSort[i]].w;
		u += objects[vecSort[i]].p;
		if (sum > c) {
			critItem = i; //or vecSort[i]
			break;
		}
	}
	return critItem;
}
void PbKnapsack::BaBApproch() {
	Ordering();
	int counter = 0;
	int i = 0;
	double c = W;
	double z = 0;
	LB = 0;
	std::vector<int> x_cur(nbObj);
	bool step5 = false, contin = true;

	while (contin) {
		step5 = false;
		double u =z + Pl(i, c);
	//	std::cout<<"UB="<<u<<"\n";
		if (LB >= u) {
			step5 = true;
		}
		//step 3
		if (!step5) {
			while (i < nbObj and objects[vecSort[i+1]].w <= c) { //and i<nbObj) {
				c -= objects[vecSort[i+1]].w;
				z += objects[vecSort[i+1]].p;
				x_cur[vecSort[i+1]] = 1;
				i++;
			}
			if (i < nbObj) {
				x_cur[vecSort[i+1]] = 0;
				i++;
			} else {
				if (z > LB) {
					counter++;
					if(counter==11){
						std::cout<<"lalal";
					}
					LB = z;
					std::cout << counter;
					std::cout << "LB=jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj" << LB << "\n";
					for (int k = 0; k < nbObj; k++) {
						x[k] = x_cur[k];
						//std::cout << "x=" << x[k] << "\n";
					}
				}
				step5 = true;
				i--;
			}
		}

		if (step5)
		{
			//i = nbObj;
			if (i==nbObj-1 and x_cur[vecSort[i+1]] == 1) { // nbObj-1
				c += objects[vecSort[i+1]].w;
				z -= objects[vecSort[i+1]].p;
				x_cur[vecSort[i+1]] = 0;
				i--;
			}
			//if(i==nbObj){
				//i--;
			//}
			int k = x_cur[vecSort[i+1]];
			while (k==0) { //(k-1 < i)
				i--;
				if (i>=0) {
					 k=x_cur[vecSort[i+1]]; //k+1
				}else{
					k=1;
				}
			}
			if (i>=0) {
				c += objects[vecSort[i+1]].w;
				z -= objects[vecSort[i+1]].p;
				x_cur[vecSort[i+1]] = 0;
				i++;
			} else {
				contin = false;	//exit(0); //finish
			}
		}
	}
}

void PbKnapsack::PDynamic() {
	ListDigraph g;
	ListDigraph::ArcMap<int> profit(g);
	ListDigraph::Node source = g.addNode();
	for (int b = 0; b < W; b++) {
		ListDigraph::Node u = g.addNode();
	}
	for (int w = 0; w < W; w++) {
		ListDigraph::Arc first1 = g.addArc(g.nodeFromId(0),
				g.nodeFromId(w + 1));
		profit[first1] = 0;
	}
	std::vector<std::vector<int> > mDyn(W + 1, std::vector<int>(nbObj + 1, 0));
	for (int i = 1; i <= nbObj; i++) {
		ListDigraph::Arc art = g.addArc(g.nodeFromId((W + 1) * (i - 1)),
				g.addNode());
		profit[art] = 0;
		for (int j = 1; j <= W; j++) {
			ListDigraph::Node cur = g.addNode();
			if (objects[i - 1].w <= j) {
				if (mDyn[j][i - 1]
						>= mDyn[j - objects[i - 1].w][i - 1]
								+ objects[i - 1].p) {
					mDyn[j][i] = mDyn[j][i - 1];
					ListDigraph::Arc a = g.addArc(
							g.nodeFromId((W + 1) * (i - 1) + j), cur);
					profit[a] = 0;
				} else {
					mDyn[j][i] = mDyn[j - objects[i - 1].w][i - 1]
							+ objects[i - 1].p;
					ListDigraph::Arc a = g.addArc(
							g.nodeFromId(
									(W + 1) * (i - 1) + (j - objects[i - 1].w)),
							cur);
					profit[a] = -objects[i - 1].p;
					ListDigraph::Arc sup = g.addArc(
							g.nodeFromId((W + 1) * (i - 1) + j), cur);
					profit[sup] = 0;
				}
			} else {
				ListDigraph::Arc a = g.addArc(
						g.nodeFromId((W + 1) * (i - 1) + j), cur);
				mDyn[j][i] = mDyn[j][i - 1];
				profit[a] = 0;
			}
		}
	}
	// g.addNode();
	//ListDigraph::Arc last = g.addArc(g.nodeFromId(countNodes(g)-1),g.nodeFromId(countNodes(g)));
	//		profit[last] = 0;
	for (int w = 0; w < W; w++) {
		ListDigraph::Arc last1 = g.addArc(
				g.nodeFromId((W + 1) * (nbObj) + (w + 1)),
				g.nodeFromId(countNodes(g) - 1));
		profit[last1] = 0;
	}
	int size = (nbObj + 1) * (W + 1);
	int sizeNoed = countNodes(g);
	int sizeArc = countArcs(g);
	BellmanFord<ListDigraph> bellman(g, profit);
	bellman.run(source);
	//const ListDigraph::NodeMap <int> &distMap = bellman.distMap();
	Path<ListDigraph> p = bellman.path(g.nodeFromId(countNodes(g) - 1));
	//Path<ListDigraph>::ArcIt it(p);
	//int y=0;
	//for(int y=0;y<nbObj;y++)
	//while(g.nodeFromId(y)!= INVALID)
	//for (ListDigraph::NodeIt n=distMap.ItemIt; n != INVALID; ++n)
	//for (; it != INVALID; ++it)
	//for (ListGraph::NodeIt it(distMap()); it != INVALID; ++it)
	/*{
	 LisDigraph::Node l = distMap[0];
	 //id=id-(W+1)*y;
	 dyn_x[y]=id;
	 std::cout<<dyn_x[y]<<std::endl;
	 }*/
	//std::cout << "Id last element " << last_element<< std::endl;
	std::cout << "Size " << size << std::endl;
	std::cout << "Count noeud " << sizeNoed << std::endl;
	std::cout << "Count arc: " << sizeArc << std::endl;
	std::cout << "Bellman : " << -bellman.dist(g.nodeFromId(countNodes(g) - 1))
			<< std::endl;
	int max = mDyn[0][nbObj];
	int k = 0;
	for (int l = 1; l < W + 1; l++) {
		if (mDyn[l][nbObj] >= max) {
			max = mDyn[l][nbObj];
			k = l;
		}
	}
	dynSol = max;
	std::cout << "valeur de Dynamic " << max << "in k" << k << std::endl;
	//Vector solution
	int b = W;
	int obj = nbObj;
	int val = max;
	while (dyn_x[0] == -1) {
		while (obj != 0 and mDyn[b][obj] == val) {
			dyn_x[obj - 1] = 0;
			obj--;
		}
		val -= objects[obj].p;
		if (val >= 0) {
			dyn_x[obj] = 1;
			b -= objects[obj].w;
		}

	}
}

int PbKnapsack::CapacityOutcore(int a, int b, bool after_core) {
	double sum = 0;
	for (int i = 1; i < a; i++) {
		sum += objects[vecSort[i]].w;
	}
	if (after_core == true) {
		for (int i = b + 1; i <= nbObj; i++) {
			sum += objects[vecSort[i]].w;
		}
	}
	return sum;
}
int PbKnapsack::ProfitOutcore(int a, int b, bool after_core) {
	double sum = 0;
	for (int i = 1; i < a; i++) {
		sum += objects[vecSort[i]].p;
	}
	if (after_core == true) { //il faut penser de ne pas dépasser la capacité cest pout relaxation
		for (int i = b + 1; i <= nbObj; i++) {
			sum += objects[vecSort[i]].p;
		}
	}
	return sum;
}
int PbKnapsack::FindINC(setState& v) {
	int INC = 0;
	state best;
	for (std::list<state>::iterator i = v.Core.begin(); i != v.Core.end();
			i++) {
		if ((*i).pIn + (*i).pOut > INC and (*i).wIn + (*i).wOut <= W) {
			INC = (*i).pIn + (*i).pOut;
			best = (*i);
		}
		listState.BestINC = INC;
		listState.best = best;
	}
	return INC;
}
double PbKnapsack::U(state& s) {
	double sum = 0;
	int i = 1;
	double u = 0;
	if (i == s.a) {
		i = s.b + 1;
	}
	if (i == nbObj + 1) {
		return s.pIn + u;
	}
	while (W - s.wIn >= sum + objects[vecSort[i]].w) {
		sum += objects[vecSort[i]].w;
		u += objects[vecSort[i]].p;
		i++;
		if (i == s.a) {
			i = s.b + 1;
		}
		if (i == nbObj + 1) {
			return s.pIn + u;
		}
	}
	return (s.pIn + u
			+ (double) objects[vecSort[i]].p
					* ((double) ((W - s.wIn - sum)
							/ (double) objects[vecSort[i]].w)));
}

void PbKnapsack::PDynCore() {
//Initialisation
	//ne zabut zapolnit vectSort
	//Ordering();
	//Ordering();
	bestINC = 0;
	std::vector<int> tmp(nbObj, 0);
	int crit = FindBreakItem(1, W);
	int a = crit, b = crit - 1;
	state init(a, b, 0, CapacityOutcore(a, b, false), 0,
			ProfitOutcore(a, b, false), crit, 0);
	init.sol.assign(nbObj, 0);
	for (int i = 1; i < crit; i++) {
		init.sol[vecSort[i]] = 1;
	}
	listState.Core.push_back(init);
	while ((a > 1) or (b < nbObj)) {
		if (b < nbObj) {
			if (b == 14) {

			}
			setState recurList;
			for (std::list<state>::iterator i = listState.Core.begin();
					i != listState.Core.end(); i++) {
				state bFalse;
				bFalse = *i;
				bFalse.b = b + 1;
				bFalse.sol[vecSort[b + 1]] = 0;
				bFalse.item = b + 1;
				bFalse.relLin = U(bFalse);
				recurList.Core.push_back(bFalse);//faut-il faire bool pour "pas prendre"
				if ((*i).wIn + objects[vecSort[b + 1]].w <= W) {
					state bTrue;
					bTrue = (*i);
					bTrue.b = b + 1;
					bTrue.wIn += objects[vecSort[b + 1]].w;
					bTrue.pIn += objects[vecSort[b + 1]].p;
					bTrue.item = b + 1;
					bTrue.sol[vecSort[b + 1]] = 1;
					bTrue.relLin = U(bTrue);
					recurList.Core.push_back(bTrue);
				}
			}
			recurList.Dominance();
			int INC = FindINC(recurList);
			//recurList.BestINC=INC;
			//std::cout << "INC b" << INC << "\n";
			if (CoreSol < listState.BestINC) {
				CoreSol = listState.BestINC;
				core_x = listState.best.sol;
			}
			recurList.CutBound(INC);

			if (recurList.Core.empty()) {
				std::cout << "EMPTY";
				//core_x = listState.best.sol;
				//CoreSol = listState.BestINC;
				break;
			}
			listState = recurList;
			recurList.Core.clear();
			b++;
		}
		//std::list<state>::iterator itB = listState.Core.begin();
		//b = (*listState.Core.begin()).b;
		//b++;
		//std::cout << "b " << b;
		if (a > 1) {
			setState recurList;
			for (std::list<state>::iterator i = listState.Core.begin();
					i != listState.Core.end(); i++) {
				state aFalse;
				aFalse = *i;
				aFalse.a = a - 1;
				aFalse.wOut -= objects[vecSort[a - 1]].w;
				aFalse.wIn += objects[vecSort[a - 1]].w;
				aFalse.pOut -= objects[vecSort[a - 1]].p;
				aFalse.pIn += objects[vecSort[a - 1]].p;
				aFalse.relLin = U(aFalse);
				aFalse.item = a - 1;
				aFalse.sol[vecSort[a - 1]] = 1;
				recurList.Core.push_back(aFalse);//faut-il faire bool pour "pas prendre"
				state aTrue;
				aTrue = (*i);
				aTrue.a = a - 1;
				aTrue.wOut -= objects[vecSort[a - 1]].w;
				aTrue.pOut -= objects[vecSort[a - 1]].p;
				aTrue.item = a - 1;
				aTrue.sol[vecSort[a - 1]] = 0;
				aTrue.relLin = U(aTrue);
				recurList.Core.push_back(aTrue);

			}
			recurList.Dominance();
			int INC = FindINC(recurList);
			//std::cout << "INC a" << INC << "\n";
			if (CoreSol < listState.BestINC) {
				CoreSol = listState.BestINC;
				core_x = listState.best.sol;
			}
			recurList.CutBound(INC);
			if (recurList.Core.empty()) {
				std::cout << "EMPTY";

				//core_x = listState.best.sol;
				//CoreSol = listState.BestINC;
				break;
			}

			listState = recurList;
			recurList.Core.clear();
			a--;

		}

		//std::list<state>::iterator itA = listState.Core.begin();
		//a = (*listState.Core.begin()).a;

		//std::cout << "a " << a;

	}
}

void PbKnapsack::printListPair() {
	int k = 0;
	Ordering();
	std::list<std::pair<int, double> >::iterator it;
	for (it = listRatio.begin(); it != listRatio.end(); ++it) {
		++k;
		std::cout << "Object: " << (*it).first + 1 << " with ratio "
				<< (*it).second << std::endl << std::endl;
	}
}
void PbKnapsack::printSolution() {
	std::cout << "Solution of BandB=" << LB << "\n";
	for (int i = 0; i < nbObj; i++) {
		if (x[i] == 1) {
			std::cout << " " << i + 1;
		}
	}
	std::cout << "\n";
	std::cout << "Solution of Longest Path=" << dynSol << "\n";
	for (int i = 0; i < nbObj; i++) {
		if (dyn_x[i] == 1) {
			std::cout << " " << i + 1;
		}
	}
	std::cout << "\n";
	std::cout << "Solution of Core=" << CoreSol << "\n";
	for (int i = 0; i < nbObj; i++) {

		if (core_x[i] == 1) {
			std::cout << " " << i + 1;
		}
	}
}
PbKnapsack::~PbKnapsack() {
	x.clear();
	dyn_x.clear();
	xcont.clear();
	vecSort.clear();
	objects.clear();
	std::vector<int>().swap(x);
	std::vector<int>().swap(dyn_x);
	std::vector<int>().swap(vecSort);
	std::vector<item>().swap(objects);
	std::vector<float>().swap(xcont);

}

