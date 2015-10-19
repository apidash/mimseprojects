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
	}
}
PbKnapsack::PbKnapsack() {
	LB = 0;
	W = 0;
	nbObj = 0;
	dynSol=0;
}
void PbKnapsack::GenerateData(std::string str,int n) {

	srand(time(NULL));
	W = 100 + rand() % 40;
	//nbObj = 10 + rand() % 40;
	nbObj =n;
	objects.reserve(nbObj);
	Initialisation();
	for (int i = 0; i < nbObj; i++) {
		objects[i].p = (10 + rand() % 101);
		objects[i].w = (0.01 * (20 + rand() % 31)) * W;
		listRatio.push_back(
				std::make_pair(i,
						(double) objects[i].p / (double) objects[i].w));
	}

	std::string name = "/home/apidash/workspace/Knapsack/" + str + ".dat";
	std::ofstream ofs1(name.c_str());
	ofs1 << "nbObj= ";
	ofs1 << nbObj << ";"<<std::endl;
	ofs1 << "Capacity= ";
	ofs1 << W << ";"<<std::endl;
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
		in >> nbObj >> tmp>> std::ws;
		in >> tmp;
		//in >> tmp;
		in >> W>> tmp >> std::ws;
		objects.reserve(nbObj);
		if(objects.size()==objects.capacity()){
			std::cout<<"Allocate memory's problem\n";
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
PbKnapsack::PbKnapsack(int n, int W) {
	nbObj = n;
	objects.reserve(n);
	Initialisation();
	//objects.size()=7;
	this->W = W;
	objects[0].p = 70;
	objects[0].w = 31;
	objects[1].p = 20;
	objects[1].w = 10;
	objects[2].p = 39;
	objects[2].w = 20;
	objects[3].p = 37;
	objects[3].w = 19;
	objects[4].p = 7;
	objects[4].w = 4;
	objects[5].p = 5;
	objects[5].w = 3;
	objects[6].p = 10;
	objects[6].w = 6;
	for (int i = 0; i < nbObj; i++) {
		listRatio.push_back(
				std::make_pair(i,
						(double) objects[i].p / (double) objects[i].w)); //proverka lista ne zatiraet li on
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
	double sum = 0;
	double u = 0;
	int critItem = -1;
	for (int i = j; i <= nbObj; i++) {
		sum += objects[vecSort[i]].w;
		u += objects[vecSort[i]].p;
		if (sum > c) {
			critItem = vecSort[i];
			u -= objects[critItem].p;
			sum -= objects[critItem].w;
			break;
		}
	}
	u += //floor(
			 (double) objects[critItem].p*((c - sum)
						/ (double) objects[critItem].w);//); //proverit okruglenie
	return u;
}
void PbKnapsack::BaBApproch() {
	Ordering();
	int counter = 0;
	int i = 1;
	double c = W;
	double z = 0;
	LB = 0;
	std::vector<int> x_cur(nbObj);
	bool step2 = false, step5 = false, contin=true;
	while (contin) {
		//body of 2 step
		step5 = false;
		step2 = false;
		double u = Pl(i, c);
		std::cout<<"Borne = "<<u+z<<"\n";
		if (LB >= z + u) {
			step5 = true;
		}
		//step 3
		if (step5 == false) {
			while (3) {
				while (objects[vecSort[i]].w <= c )
				{//and i<nbObj) {
					c -= objects[vecSort[i]].w;
					z += objects[vecSort[i]].p;
					x_cur[vecSort[i]] = 1;
					i++;
				}
				if (i <= nbObj) {
					x_cur[vecSort[i]] = 0;
					i++;
					//step2 = true;
				}
				/*if (i < nbObj) {
					step2 = true;
					break; //go to step 2
				}*/

				if (i == nbObj) {
					//break;//stay in step 3
				}
				if (i > nbObj) {
					step2=false;
					break; //go to step 4
				}
			} // end step 3
			if (step2 == false) {
				//step 4
				if (z > LB) {
					counter++;
					LB = z;
					std::cout << counter;
					std::cout << "LB=" << LB << "\n";
					for (int k = 0; k < nbObj; k++) {
						x[k] = x_cur[k];
						//std::cout << "x=" << x[k] << "\n";
					}
				}
				i = nbObj;
				if (x_cur[vecSort[nbObj]] == 1) { // nbObj-1
				 c += objects[vecSort[nbObj]].w;
				 z -= objects[vecSort[nbObj]].p;
				 x_cur[vecSort[nbObj]] = 0;
				 //i--;
				 }
			}
			// end step 4
		}
		//step 5
		if (step2 == false) //and step5==true)
		{
			int k = 0;
			int index = -1;
			while (k-1< i) { //(k-1 < i)
				if (x_cur[k] == 1) {
					index = k; //k+1
				}
				k++;
			}
			if (index != -1) {
				c += objects[index].w;
				z -= objects[index].p;
				x_cur[index] = 0;
				i = index+2;
				// go to step 2
			} else {
				//break;
			 contin=false;	//exit(0); //finish
			}
		}
	}
}

void PbKnapsack::PDynamic() {
	ListDigraph g;
	ListDigraph::ArcMap<int> profit(g);
	ListDigraph::Node source  = g.addNode();
	for (int b = 0; b < W ; b++) {
		ListDigraph::Node u = g.addNode();
	}
	for (int w = 0; w < W ; w++) {
			ListDigraph::Arc first1 = g.addArc(g.nodeFromId(0),g.nodeFromId(w+1));
			profit[first1] = 0;
		}
	std::vector<std::vector<int> > mDyn(W + 1, std::vector<int>(nbObj + 1, 0));
	for (int i = 1; i <= nbObj; i++) {
		ListDigraph::Arc art = g.addArc(g.nodeFromId((W+1)*(i-1)), g.addNode());
			profit[art]=0;
		for (int j = 1; j <= W; j++) {
			ListDigraph::Node cur = g.addNode();
			if (objects[i - 1].w <= j) {
				if (mDyn[j][i - 1]>= mDyn[j - objects[i - 1].w][i - 1]+ objects[i - 1].p) {
					mDyn[j][i] = mDyn[j][i - 1];
					ListDigraph::Arc a = g.addArc(g.nodeFromId((W + 1) * (i-1) + j),cur);
					profit[a] = 0;
				} else {
					mDyn[j][i] = mDyn[j - objects[i - 1].w][i - 1]+ objects[i - 1].p;
					ListDigraph::Arc a = g.addArc(g.nodeFromId((W + 1) * (i-1) + (j - objects[i - 1].w)),cur);
					profit[a] = -objects[i - 1].p;
					ListDigraph::Arc sup = g.addArc(g.nodeFromId((W + 1) * (i - 1) + j),cur);
					profit[sup] = 0;
				}
			} else {
				ListDigraph::Arc a = g.addArc(g.nodeFromId((W + 1) * (i-1) + j),cur);
				mDyn[j][i] = mDyn[j][i - 1];
				profit[a] = 0;
			}
		}
	}
 // g.addNode();
	//ListDigraph::Arc last = g.addArc(g.nodeFromId(countNodes(g)-1),g.nodeFromId(countNodes(g)));
		//		profit[last] = 0;
	for (int w = 0; w < W ; w++) {
		ListDigraph::Arc last1 = g.addArc(g.nodeFromId((W + 1) * (nbObj)+(w+1)),g.nodeFromId(countNodes(g)-1));
		profit[last1] = 0;
	}
	int size=(nbObj+1)*(W+1);
	int sizeNoed=countNodes(g);
	int sizeArc=countArcs(g);
	BellmanFord<ListDigraph> bellman(g,profit);
	bellman.run(source);
	//const ListDigraph::NodeMap <int> &distMap = bellman.distMap();
	Path<ListDigraph> p = bellman.path(g.nodeFromId(countNodes(g)-1));
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
	dynSol=max;
	std::cout << "valeur de Dynamic " << max << "in k" << k << std::endl;
	//Vector solution
	int b = W;
	int obj = nbObj;
	int val = max;
	while (dyn_x[0] == -1) {
		while (obj!=0 and mDyn[b][obj]==val) {
			dyn_x[obj-1]=0;
         obj--;
		}
		val-=objects[obj].p;
        if(val>=0){
		dyn_x[obj]=1;
		b-=objects[obj].w;
        }

	}
}
void PbKnapsack::printSolution() {
	std::cout << "Solution of BandB=" << LB << "\n";
	for (int i = 0; i < nbObj; i++) {
		std::cout /*<< "Decision x="*/ << x[i]; //<< "\t";
	}
	std::cout  << "\n";
	std::cout << "Solution of Dynamic=" << dynSol << "\n";
	for (int i = 0; i < nbObj; i++) {

			std::cout /*<< "Decision x=" */<< dyn_x[i];// << "\t";
		}
}
void PbKnapsack::PDynCore(){

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

