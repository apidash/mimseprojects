/*
 * Dynamic.cpp
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

#include "../include/Dynamic.h"

Dynamic::Dynamic() {
	// TODO Auto-generated constructor stub

}

Dynamic::~Dynamic() {
	// TODO Auto-generated destructor stub
}

int Dynamic::solve(Instance* instance, int* price, vector<item*> & newPattern) {
	int qty = instance->qty();
	int width = instance->width();
	int** tab = new int*[qty];
	for (int i = 0; i < qty; i++) {
		tab[i] = new int[width];
		for (int j = 0; j < width; j++) {
			tab[i][j] = 0;
		}
	}



	for (int i = 1; i < qty; i++) {
		for (int j = 0; j < width; j++) {
			if (j >= instance->data()[i - 1]->_width) {
				tab[i][j] = max(tab[i - 1][j],
						tab[i - 1][j - instance->data()[i - 1]->_width]
								+ price[i]);
			} else {
				tab[i][j] = tab[i - 1][j];

			}
		}
	}


	int profit = 0;
	width--;
	for (int i = qty-1; i > 0; i--) {
		if (tab[i-1][width] != tab[i][width]) {
			newPattern.push_back(instance->data()[i-1]);
			profit += price[i-1];
			width -= instance->data()[i-1]->_width;

		}
		if (width == 0)
			break;
	}

	vector<item*>::iterator it;
	int tot = 0;
	cout << "newPattern : ";
	for(it = newPattern.begin(); it != newPattern.end(); it++){
		tot += instance->data()[(*it)->_id]->_width;
		cout << (*it)->_id << "- " ;
	}
	cout << "Largeur : " << tot << endl;

	return profit;

//	return 0;
}

