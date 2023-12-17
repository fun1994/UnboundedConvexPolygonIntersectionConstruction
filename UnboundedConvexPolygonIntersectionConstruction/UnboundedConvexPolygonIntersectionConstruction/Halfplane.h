#pragma once
#include "Point.h"

class Halfplane {
public:
	Point first;
	Point second;
	bool operator==(Halfplane& hp) {
		return first == hp.first && second == hp.second;
	}
};
