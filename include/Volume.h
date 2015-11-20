/*
 * Volume.h
 *
 *  Created on: 20 nov. 2015
 *      Author: rduclos
 */

#ifndef SCE_VOLUME_H_
#define SCE_VOLUME_H_
#include "Dynamic.h"


class Volume {
	private :
	int _g;
	double _d;

public:
	Volume();
	virtual ~Volume();
	void solve(double alpha, Instance & inst);
	vector<int> & greedy(Instance* inst);
};

#endif /* SCE_VOLUME_H_ */
