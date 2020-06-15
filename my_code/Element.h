#pragma once
#include <stdio.h>
#include <string.h>
#include<iostream>
using namespace std;

class Element {
public:
	unsigned int row, col;
	double val;

	Element(unsigned int row = 0, unsigned int col = 0, double val = 0.0) {
		this->row = row;
		this->col = col;
		this->val = val;
	}

	friend ostream& operator<<(ostream& out, const Element& e);
};
