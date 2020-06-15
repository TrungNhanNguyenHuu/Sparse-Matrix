#pragma once
#include"Element.h"

class SparseMatrix {
private:
	// data member for dynamic array
	Element* storage;
	unsigned size;
	unsigned capacity;

	unsigned int nrow, ncol; // the size of matrix is nrow x ncol

	void rangeCheck(unsigned row, unsigned col) const{
		if(row < 0 || row >= nrow || col < 0 || col >=ncol)
			throw "MatrixSubscriptOutOfBoundsException";
	}

	void setCapacity(unsigned newCapacity) {
		Element *newStorage = new Element[newCapacity];
		memcpy(newStorage, storage, sizeof(Element) * size);
		capacity = newCapacity;
		delete[] storage;
		storage = newStorage;
	}

	void ensureCapacity(unsigned minCapacity) {
		if (minCapacity > capacity) {
			unsigned newCapacity = (capacity * 3) / 2 + 1;
			if (newCapacity < minCapacity)
				newCapacity = minCapacity;
			setCapacity(newCapacity);
		}
	}

	void pack() {
		if (size <= capacity / 2) {
			int newCapacity = (size * 3) / 2 + 1;
			setCapacity(newCapacity);
		}
	}

	void trim() {
		int newCapacity = size;
		setCapacity(newCapacity);
	}

	void insertAt(int index, Element val) {
		ensureCapacity(size + 1);
		memmove(storage + index + 1, storage + index, sizeof(Element)*(size - index));
		storage[index] = val;
		size++;
	}

	void add(Element val) {
		ensureCapacity(size + 1);
		storage[size] = val;
		size++;
	}

	void removeAt(int index) {
		memmove(storage + index, storage + index + 1, sizeof(Element)*(size - index - 1));
		size--;
		pack();
	}

public:
	SparseMatrix(unsigned int nr = 1, unsigned int nc = 1) {
		nrow = nr;
		ncol = nc;
		capacity = 10;
		size = 0;
		storage = new Element[capacity];
	}

	SparseMatrix(const SparseMatrix& a) {
		nrow = a.nrow;
		ncol = a.ncol;
		capacity = a.capacity;
		size = a.size;
		storage = new Element[capacity];
		memcpy(storage, a.storage, sizeof(Element)*size);
	}

	SparseMatrix& operator=(const SparseMatrix& a) {
		if (&a == this)
			return *this;
		if (storage != NULL) delete storage;
		nrow = a.nrow;
		ncol = a.ncol;
		capacity = a.capacity;
		size = a.size;
		storage = new Element[capacity];
		memcpy(storage, a.storage, sizeof(Element)*size);
		return (*this);
	}

	~SparseMatrix() {
		if (storage != NULL) {
			delete[] storage;
			storage = NULL;
		}
		size = 0;
	}

public:
	void printFull() {
		for (unsigned i = 0; i < nrow; i++) {
			for (unsigned j = 0; j < ncol; j++) {
				cout << getAt(i, j) << " ";
			}
			cout << endl;
		}
	}

	// Your tasks: complete the implementation of the below methods
	// in SparseMatrix.cpp
	void setAt(unsigned row, unsigned col, double val);
	double getAt(unsigned row, unsigned col);
	SparseMatrix* transpose();
	double trace();
	SparseMatrix* add(const SparseMatrix& b);
	SparseMatrix* multiplyPointWise(const SparseMatrix& b);

	friend ostream& operator<<(ostream& os, const SparseMatrix& a);
};


