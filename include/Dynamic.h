/*
 * Dynamic.h
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

#ifndef SCE_DYNAMIC_H_
#define SCE_DYNAMIC_H_

#include "Instance.h"
#include <math.h>
#include <algorithm>

class Dynamic {
public:
	Dynamic();
	virtual ~Dynamic();
	int solve(Instance* instance, int * price, vector<item*> & newPattern);
};

#endif /* SCE_DYNAMIC_H_ */
