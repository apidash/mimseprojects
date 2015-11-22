/*
 * Instance.cpp
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

#include "../include/Instance.h"
#include <iostream>

Instance::Instance() {
	_itemQty = 0;
	_masterWidth = 0;

}

Instance::~Instance() {
	_data.clear();
}

void Instance::generate() {

}

void Instance::generate(int itemQty, int W) {
	_masterWidth = W;
	_itemQty = itemQty;
	_data.reserve(W);
	srand(time(NULL));

	int qty = _itemQty;
	int minWidth = W/10;
	int id =0;
	while (qty >= 0) {
		int width = minWidth + rand() % (W - minWidth);
		_data.push_back(new item(id, width));
		id++;
		qty --;
	}
}

vector<item*> & Instance::data(){
	return _data;
}

int Instance::qty(){
	return _itemQty;
}

int Instance::width(){
	return _masterWidth;
}

ostream & operator <<(ostream & os, Instance & instance) {
	std::vector<item*>::iterator it;
	for (it = instance.data().begin(); it != instance.data().end();
			it++) {
		os << " item " << (*it)->_id;
		os << " width : " << (*it)->_width
				<< endl;
	}
	return os;
}

