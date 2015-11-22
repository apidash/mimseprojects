/*
 * Volume.cpp
 *
 *  Created on: 20 nov. 2015
 *      Author: rduclos
 */

#include "../include/Volume.h"


Volume::Volume() {
	// TODO Auto-generated constructor stub

}

Volume::~Volume() {
	// TODO Auto-generated destructor stub
}


vector<int> & Volume::greedy(Instance* inst){
	vector<int>  initial;
	vector<int> remaining;
	int qty = inst->qty();
	int W = inst->width();
	remaining.push_back(W);
	for(int i =0; i< qty; i++){

	}


	return initial;


}

void Volume::solve(double alpha, Instance & inst){
	int qty = inst.qty();
	vector<int> knpSol;
	double * price = new double[qty];
	//

	for(int i =0; i< qty; i++){
		price[i] = (double)inst.data()[i]->_width / (double)inst.width();
	}
	Dynamic* knap = new Dynamic();
	//knpSol = knap->solve()

}
