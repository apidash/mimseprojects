/*
 * main.cpp
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

#include "../include/Instance.h"
#include "../include/Dynamic.h"

using namespace std;

int main(int argc, char** argv) {

	Instance* inst = new Instance();
	inst->generate(50, 200);
	cout << (*inst) << endl;

	vector<item*> essai;
	int* price = new int[inst->qty()];
	for (int i = 0; i < inst->qty(); i++) {
		price[i] = 1;
	}

	Dynamic* dynamic = new Dynamic();
	dynamic->solve(inst, price, essai);



	return 0;
}

