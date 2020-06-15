#include<fstream>
#include"SparseMatrix.h"


ostream& operator<<(ostream& out, const Element& e) {
	out << "(" << e.row << "," << e.col << ") = " << e.val;
	return out;
}

ostream& operator<<(ostream& os, const SparseMatrix& a) {
	os << "Sparse Matrix (" << a.nrow << " x " << a.ncol << "): \n";
	os << "----------------------\n";
	for (unsigned i = 0; i < a.size; i++)
		os << a.storage[i] << endl;
	os << "---------END----------";
	return os;
}

int main()
{
	// Assume that we only use 3 sparse matrix for testing purpose.
	const int MAX_NUM_SPARSE_MATRICES = 3;
	SparseMatrix* sm[MAX_NUM_SPARSE_MATRICES];
	for (int i = 0; i < MAX_NUM_SPARSE_MATRICES; i++)
		sm[i] = NULL;

	SparseMatrix* cm = NULL;
	ifstream ifs;
	ifs.open("input.txt");
	int row, col;
	int idx;
	double val;
	char command;
	try
	{
		while (ifs >> command) {
			switch (command) {
			case 'c': // create an object of SparseMatrix
				ifs >> row >> col >> idx;
				if (idx < 0 || idx > 1)
					throw "Wrong input format!";
				if (sm[idx] != NULL) {
					delete sm[idx];
				}
				sm[idx] = new SparseMatrix(row, col);
				cm = sm[idx];
				break;
			case 'g': // get the value of the element (row, col)
				ifs >> row >> col;
				cout << "Get (" << row << ", " << col << ") = " << cm->getAt(row, col) << endl;
				break;
			case 's': // set new value to the element (row, col)
				ifs >> row >> col >> val;
				cm->setAt(row, col, val);
				break;
			case 'r': // return trace of the matrix
				cout << "Trace = " << cm->trace() << endl;
				break;
			case 't': // return the transpose matrix of the current one
				if (sm[2] != NULL)
					delete sm[2];
				sm[2] = cm->transpose();
				cm = sm[2];
				cout << (*cm) << endl;
				break;
			case '+': // return the the sum of sm1 and sm2
				ifs >> idx;
				if (idx < 0 || idx > 1)
					throw "Wrong input format!";
				if (sm[2] != NULL)
					delete sm[2];
				sm[2] = cm->add(*sm[idx]);
				cm = sm[2];
				cout << (*cm) << endl;
				break;
			case '*': /// return the the point-wise multiplication of sm1 and sm2
				ifs >> idx;
				if (idx < 0 || idx > 1)
					throw "Wrong input format!";
				if (sm[2] != NULL)
					delete sm[2];
				sm[2] = cm->multiplyPointWise(*sm[idx]);
				cm = sm[2];
				cout << (*cm) << endl;
				break;
			case 'p': // print the content of the matrix sm1
				cout << (*cm) <<endl;
				break;
			case 'f': // print the full matrix sm1
				cm->printFull();
				break;
			default:
				throw "Wrong input format!";
			}
		}
	}
	catch (char const* s) {
		printf("An exception occurred. Exception type: %s\n", s);
	}

	for (int i = 0; i < MAX_NUM_SPARSE_MATRICES; i++) {
		if (sm[i] != NULL)
			delete sm[i];
	}
	ifs.close();
	return 0;
}
