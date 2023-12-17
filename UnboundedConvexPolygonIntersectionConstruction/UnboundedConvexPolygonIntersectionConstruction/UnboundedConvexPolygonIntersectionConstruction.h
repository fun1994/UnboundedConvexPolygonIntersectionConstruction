#pragma once
#include <iostream>
#include <vector>
#include "Halfplane.h"

class UnboundedConvexPolygonIntersectionConstruction {
	double area2(Point& p, Point& q, Point& r) {
		return p.x * q.y - p.y * q.x + q.x * r.y - q.y * r.x + r.x * p.y - r.y * p.x;
	}
	bool toLeft(Point& p, Point& q, Point& r) {
		return area2(p, q, r) > 0;
	}
	Point intersectionPoint(Halfplane& hp1, Halfplane& hp2) {
		double a1 = area2(hp1.first, hp2.first, hp2.second);
		double a2 = area2(hp1.second, hp2.first, hp2.second);
		Point p;
		p.x = a2 / (a2 - a1) * hp1.first.x + a1 / (a1 - a2) * hp1.second.x;
		p.y = a2 / (a2 - a1) * hp1.first.y + a1 / (a1 - a2) * hp1.second.y;
		return p;
	}
	bool inConvexPolygon(std::vector<Halfplane>& P, Point& p) {
		for (int i = 0; i < P.size(); i++) {
			if (!toLeft(P[i].first, P[i].second, p)) {
				return false;
			}
		}
		return true;
	}
	bool inConvexPolygon(std::vector<Halfplane>& P, Point& p, int index) {
		for (int i = 0; i < P.size(); i++) {
			if (i != index) {
				if (!toLeft(P[i].first, P[i].second, p)) {
					return false;
				}
			}
		}
		return true;
	}
	bool inConvexPolygon(std::vector<Halfplane>& P, Point& p, int index1, int index2) {
		for (int i = 0; i < P.size(); i++) {
			if (i != index1 && i != index2) {
				if (!toLeft(P[i].first, P[i].second, p)) {
					return false;
				}
			}
		}
		return true;
	}
	int LTL(std::vector<Point>& P) {
		int ltl = 0;
		for (int k = 1; k < P.size(); k++) {
			if (P[k].y < P[ltl].y || (P[k].y == P[ltl].y && P[k].x < P[ltl].x)) {
				ltl = k;
			}
		}
		return ltl;
	}
	int polarAnglePartition(std::vector<Point>& P, int low, int high) {
		Point pivot = P[low];
		while (low < high) {
			while (low < high && (toLeft(P[0], pivot, P[high]) || (P[high].x == pivot.x && P[high].y == pivot.y))) {
				high--;
			}
			P[low] = P[high];
			while (low < high && (toLeft(P[0], P[low], pivot) || (P[low].x == pivot.x && P[low].y == pivot.y))) {
				low++;
			}
			P[high] = P[low];
		}
		P[low] = pivot;
		return low;
	}
	void polarAngleQuickSort(std::vector<Point>& P, int low, int high) {
		if (low < high) {
			int pivot = polarAnglePartition(P, low, high);
			polarAngleQuickSort(P, low, pivot - 1);
			polarAngleQuickSort(P, pivot + 1, high);
		}
	}
	void polarAngleQuickSort(std::vector<Point>& P) {
		polarAngleQuickSort(P, 1, P.size() - 1);
	}
	bool isBounded(std::vector<Point>& V, int& index) {
		if (V.empty()) {
			return true;
		}
		if (V.size() == 1) {
			return false;
		}
		for (int i = 0; i < V.size(); i++) {
			if (V[i].second.first != V[(i + 1) % V.size()].first.first || V[i].second.second != V[(i + 1) % V.size()].first.second) {
				index = (i + 1) % V.size();
				return false;
			}
		}
		return true;
	}
	double crossProduct(Halfplane& hp1, Halfplane& hp2) {
		return (hp1.second.x - hp1.first.x) * (hp2.second.y - hp2.first.y) - (hp1.second.y - hp1.first.y) * (hp2.second.x - hp2.first.x);
	}
	bool isLower(Halfplane& hp) {
		return hp.first.x > hp.second.x;
	}
	void partition(std::vector<Halfplane>& P, std::vector<Halfplane>& PL, std::vector<Halfplane>& PU) {
		int index1 = -1;
		int index2 = -1;
		for (int i = 0; i < P.size() - 1; i++) {
			if (isLower(P[i]) != isLower(P[i + 1])) {
				if (index1 == -1) {
					index1 = i + 1;
				}
				else {
					index2 = i + 1;
				}
			}
		}
		if (isLower(P[0])) {
			if (index1 == -1) {
				PU.insert(PU.end(), P.rbegin(), P.rend());
			}
			else {
				if (index2 == -1) {
					PL.insert(PL.end(), P.begin() + index1, P.end());
					PU.insert(PU.end(), P.rend() - index1, P.rend());
				}
				else {
					PL.insert(PL.end(), P.begin() + index1, P.begin() + index2);
					PU.insert(PU.end(), P.rend() - index1, P.rend());
					PU.insert(PU.end(), P.rbegin(), P.rend() - index2);
				}
			}
		}
		else {
			if (index1 == -1) {
				PL.insert(PL.end(), P.begin(), P.end());
			}
			else {
				if (index2 == -1) {
					PL.insert(PL.end(), P.begin(), P.begin() + index1);
					PU.insert(PU.end(), P.rbegin(), P.rend() - index1);
				}
				else {
					PL.insert(PL.end(), P.begin() + index2, P.end());
					PL.insert(PL.end(), P.begin(), P.begin() + index1);
					PU.insert(PU.end(), P.rend() - index2, P.rend() - index1);
				}
			}
		}
	}
	std::vector<Halfplane> planeSweepingLU(std::vector<Halfplane>& P1, std::vector<Halfplane>& P2) {
		std::vector<Halfplane> P;
		int index1 = -1;
		int index2 = -1;
		char LU = 'L';
		if (!P1.empty()) {
			index1++;
			if (isLower(P1[0])) {
				LU = 'U';
			}
		}
		if (!P2.empty()) {
			index2++;
			if (isLower(P2[0])) {
				LU = 'U';
			}
		}
		if (0 <= index1 && 0 <= index2) {
			if (LU == 'L') {
				if (crossProduct(P1[index1], P2[index2]) > 0) {
					P.push_back(P1[index1]);
				}
				else {
					P.push_back(P2[index2]);
				}
			}
			else if (LU == 'U') {
				if (crossProduct(P1[index1], P2[index2]) < 0) {
					P.push_back(P1[index1]);
				}
				else {
					P.push_back(P2[index2]);
				}
			}
		}
		else if (0 <= index1 && index2 < 0) {
			P.push_back(P1[index1]);
		}
		else if (index1 < 0 && 0 <= index2) {
			P.push_back(P2[index2]);
		}
		Point* event = NULL;
		Point q;
		while (true) {
			Point* p = NULL;
			Point r, s;
			if (0 <= index1 && 0 <= index2) {
				r = intersectionPoint(P1[index1], P2[index2]);
				r.type = 'i';
				if ((event && event->x < r.x) || !event) {
					if ((p && r.x < p->x) || !p) {
						s = r;
						p = &s;
					}
				}
			}
			if (0 <= index1 && index1 < (int)P1.size() - 1) {
				r = intersectionPoint(P1[index1], P1[index1 + 1]);
				r.type = '1';
				if ((event && event->x < r.x) || !event) {
					if ((p && r.x < p->x) || !p) {
						s = r;
						p = &s;
					}
				}
			}
			if (0 <= index2 && index2 < (int)P2.size() - 1) {
				r = intersectionPoint(P2[index2], P2[index2 + 1]);
				r.type = '2';
				if ((event && event->x < r.x) || !event) {
					if ((p && r.x < p->x) || !p) {
						s = r;
						p = &s;
					}
				}
			}
			if (p) {
				q = s;
				event = &q;
			}
			else {
				break;
			}
			if (event->type == 'i') {
				if (LU == 'L') {
					if (crossProduct(P1[index1], P2[index2]) < 0) {
						P.push_back(P1[index1]);
					}
					else {
						P.push_back(P2[index2]);
					}
				}
				else if (LU == 'U') {
					if (crossProduct(P1[index1], P2[index2]) > 0) {
						P.push_back(P1[index1]);
					}
					else {
						P.push_back(P2[index2]);
					}
				}
			}
			else if (event->type == '1') {
				index1++;
				if (index2 < 0 || (0 <= index2 && toLeft(P2[index2].first, P2[index2].second, *event))) {
					P.push_back(P1[index1]);
				}
			}
			else if (event->type == '2') {
				index2++;
				if (index1 < 0 || (0 <= index1 && toLeft(P1[index1].first, P1[index1].second, *event))) {
					P.push_back(P2[index2]);
				}
			}
		}
		return P;
	}
public:
	std::vector<Halfplane> bruteForce(std::vector<Halfplane>& P1, std::vector<Halfplane>& P2) {
		std::vector<Halfplane> P;
		std::vector<Point> V;
		for (int i = 0; i < (int)P1.size() - 1; i++) {
			Point p = intersectionPoint(P1[i], P1[i + 1]);
			if (inConvexPolygon(P2, p)) {
				p.first.first = 1;
				p.first.second = i;
				p.second.first = 1;
				p.second.second = i + 1;
				V.push_back(p);
			}
		}
		if (P1.size() > 2) {
			Point p = intersectionPoint(P1[P1.size() - 1], P1[0]);
			if (inConvexPolygon(P1, p, 0, P1.size() - 1) && inConvexPolygon(P2, p)) {
				p.first.first = 1;
				p.first.second = P1.size() - 1;
				p.second.first = 1;
				p.second.second = 0;
				V.push_back(p);
			}
		}
		for (int i = 0; i < (int)P2.size() - 1; i++) {
			Point p = intersectionPoint(P2[i], P2[i + 1]);
			if (inConvexPolygon(P1, p)) {
				p.first.first = 2;
				p.first.second = i;
				p.second.first = 2;
				p.second.second = i + 1;
				V.push_back(p);
			}
		}
		if (P2.size() > 2) {
			Point p = intersectionPoint(P2[P2.size() - 1], P2[0]);
			if (inConvexPolygon(P2, p, 0, P2.size() - 1) && inConvexPolygon(P1, p)) {
				p.first.first = 2;
				p.first.second = P2.size() - 1;
				p.second.first = 2;
				p.second.second = 0;
				V.push_back(p);
			}
		}
		for (int i = 0; i < P1.size(); i++) {
			for (int j = 0; j < P2.size(); j++) {
				Point p = intersectionPoint(P1[i], P2[j]);
				if (inConvexPolygon(P1, p, i) && inConvexPolygon(P2, p, j)) {
					if (crossProduct(P1[i], P2[j]) > 0) {
						p.first.first = 1;
						p.first.second = i;
						p.second.first = 2;
						p.second.second = j;
					}
					else {
						p.first.first = 2;
						p.first.second = j;
						p.second.first = 1;
						p.second.second = i;
					}
					V.push_back(p);
				}
			}
		}
		if (!V.empty()) {
			int ltl = LTL(V);
			std::swap(V[0], V[ltl]);
			polarAngleQuickSort(V);
		}
		int index = -1;
		bool flag = isBounded(V, index);
		if (index != -1) {
			V.insert(V.end(), V.begin(), V.begin() + index);
			V.erase(V.begin(), V.begin() + index);
		}
		for (int i = 0; i < V.size(); i++) {
			if (V[i].first.first == 1) {
				P.push_back(P1[V[i].first.second]);
			}
			else if (V[i].first.first == 2) {
				P.push_back(P2[V[i].first.second]);
			}
		}
		if (!flag) {
			if (V[V.size() - 1].second.first == 1) {
				P.push_back(P1[V[V.size() - 1].second.second]);
			}
			else if (V[V.size() - 1].second.first == 2) {
				P.push_back(P2[V[V.size() - 1].second.second]);
			}
		}
		return P;
	}
	std::vector<Halfplane> planeSweeping(std::vector<Halfplane>& P1, std::vector<Halfplane>& P2) {
		std::vector<Halfplane> P, PL, PU, P1L, P1U, P2L, P2U;
		partition(P1, P1L, P1U);
		partition(P2, P2L, P2U);
		PL = planeSweepingLU(P1L, P2L);
		PU = planeSweepingLU(P1U, P2U);
		int lowerL = -1;
		int upperL = -1;
		int lowerR = -1;
		int upperR = -1;
		int lower = -1;
		int upper = -1;
		if (!PL.empty()) {
			lower++;
		}
		if (!PU.empty()) {
			upper++;
		}
		Point* event = NULL;
		Point q;
		while (true) {
			Point* p = NULL;
			Point r, s;
			if (0 <= lower && 0 <= upper) {
				r = intersectionPoint(PL[lower], PU[upper]);
				r.type = 'i';
				if ((event && event->x < r.x) || !event) {
					if ((p && r.x < p->x) || !p) {
						s = r;
						p = &s;
					}
				}
			}
			if (0 <= lower && lower < (int)PL.size() - 1) {
				r = intersectionPoint(PL[lower], PL[lower + 1]);
				r.type = 'l';
				if ((event && event->x < r.x) || !event) {
					if ((p && r.x < p->x) || !p) {
						s = r;
						p = &s;
					}
				}
			}
			if (0 <= upper && upper < (int)PU.size() - 1) {
				r = intersectionPoint(PU[upper], PU[upper + 1]);
				r.type = 'u';
				if ((event && event->x < r.x) || !event) {
					if ((p && r.x < p->x) || !p) {
						s = r;
						p = &s;
					}
				}
			}
			if (p) {
				q = s;
				event = &q;
			}
			else {
				break;
			}
			if (event->type == 'i') {
				if (crossProduct(PL[lower], PU[upper]) < 0) {
					lowerL = lower;
					upperL = upper;
				}
				else {
					lowerR = lower;
					upperR = upper;
				}
			}
			else if (event->type == 'l') {
				lower++;
			}
			else if (event->type == 'u') {
				upper++;
			}
		}
		if (0 <= lowerL && 0 <= upperL && 0 <= lowerR && 0 <= upperR) {
			P.insert(P.end(), PL.begin() + lowerL, PL.begin() + (lowerR + 1));
			P.insert(P.end(), PU.rend() - (upperR + 1), PU.rend() - upperL);
		}
		else if (0 <= lowerL && 0 <= upperL && lowerR < 0 && upperR < 0) {
			P.insert(P.end(), PU.rbegin(), PU.rend() - upperL);
			P.insert(P.end(), PL.begin() + lowerL, PL.end());
		}
		else if (lowerL < 0 && upperL < 0 && 0 <= lowerR && 0 <= upperR) {
			P.insert(P.end(), PL.begin(), PL.begin() + (lowerR + 1));
			P.insert(P.end(), PU.rend() - (upperR + 1), PU.rend());
		}
		else if (lowerL < 0 && upperL < 0 && lowerR < 0 && upperR < 0) {
			if (!PL.empty() && PU.empty()) {
				P.insert(P.end(), PL.begin(), PL.end());
			}
			else if (PL.empty() && !PU.empty()) {
				P.insert(P.end(), PU.rbegin(), PU.rend());
			}
		}
		return P;
	}
};
