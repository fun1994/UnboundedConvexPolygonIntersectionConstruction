#pragma once

class Point {
public:
	double x;
	double y;
	std::pair<int, int> first;
	std::pair<int, int> second;
	char type;
	bool operator==(Point& p) {
		return x == p.x && y == p.y;
	}
};
