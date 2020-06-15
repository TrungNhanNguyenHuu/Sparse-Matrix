#include"SparseMatrix.h"

void SparseMatrix::setAt(unsigned row, unsigned col, double val) {
	rangeCheck(row, col);
	// YOUR CODE HERE
	Element *onething = new Element();
	(*onething).row = row;
	(*onething).col = col;
	(*onething).val = val;
	if (size == 0)
    {
        add(*onething);
        for (unsigned i = 0; i < size; i++)
        {
            if (storage[i].val == 0)
            {
                removeAt(i);
                return;
            }
        }
    }else
    {
        for (unsigned  i = 0; i < size; i++)
        {
            if (row == storage[i].row && col == storage[i].col)
            {
                storage[i].val = val;
                if (val == 0)
                {
                   removeAt(i);
                }
                return;
            }
            if (row < storage[i].row || (row == storage[i].row && col < storage[i].col))
            {
                insertAt(i,*onething);
                if (val == 0)
                {
                    removeAt(i);
                }
                return;
            }
        }
        add(*onething);
        for (unsigned i = 0; i < size; i++)
        {
            if (storage[i].val == 0)
            {
                removeAt(i);
                return;
            }
        }
    }
}

double SparseMatrix::getAt(unsigned row, unsigned col) {
	rangeCheck(row, col);
	// YOUR CODE HERE
    unsigned i = 0;
    while ( i < size)
    {
        if (storage[i].row == row && storage[i].col == col)
        {
            return storage[i].val;
        }
        i++;
    }
    return 0;
}

SparseMatrix* SparseMatrix::transpose() {
	SparseMatrix* result = NULL;
	// YOUR CODE HERE
	result = new SparseMatrix(ncol,nrow);
	for (unsigned i = 0; i < this->size; i++)
    {
        result->setAt(this->storage[i].col, this->storage[i].row, this->storage[i].val);
    }
    return result;
}

double SparseMatrix::trace() {
	if (nrow != ncol)
		throw "TraceOfNoneSquareMatrix";
	double result = 0;
	// YOUR CODE HERE
	for (unsigned i = 0; i < size ; i++)
    {
        if (storage[i].row == storage[i].col)
        {
            result = result + storage[i].val;
        }
    }
	return result;
}

SparseMatrix* SparseMatrix::add(const SparseMatrix& b) {
	if(nrow != b.nrow || ncol != b.ncol)
		throw "MismatchedDimensions";


	SparseMatrix* result = NULL;
	// YOUR CODE HERE
	result = new SparseMatrix(nrow, ncol);
	for (unsigned i = 0; i < size; i++)
    {
        result->setAt(this->storage[i].row, this->storage[i].col, this->storage[i].val);
    }

    SparseMatrix *b2;                       // create a clone version of SparseMatrix &b (B)
    b2 = new SparseMatrix(b.nrow, b.ncol);
    for (unsigned i = 0; i < b.size ; i++)
    {
        b2->setAt(b.storage[i].row, b.storage[i].col, b.storage[i].val);
    }                                       //

    for (unsigned i = 0; i < result->size ; i++)
    {
        for (unsigned j = 0; j < b2->size; j++)
        {
            if ( (result->storage[i].row == b2->storage[j].row) && (result->storage[i].col == b2->storage[j].col) )
            {
                result->storage[i].val = result->storage[i].val + b2->storage[j].val;
                b2->removeAt(j);
                if (result->storage[i].val == 0)
                {
                    result->removeAt(i);
                }
            }
        }
    }

    for (unsigned i = 0; i < b2->size; i++)
    {
        result->ensureCapacity((result->size) + 1);
        result->setAt(b2->storage[i].row, b2->storage[i].col, b2->storage[i].val);

    }
    delete b2; //
    b2 = NULL; // (B)
	return result;
}

SparseMatrix* SparseMatrix::multiplyPointWise(const SparseMatrix& b) {
	if (nrow != b.nrow || ncol != b.ncol)
		throw "MismatchedDimensions";


	SparseMatrix* result = NULL;
	// YOUR CODE HERE
    result = new SparseMatrix(b.nrow, b.ncol);
    for (unsigned i = 0; i< b.size; i++)
    {
        result->setAt(b.storage[i].row, b.storage[i].col, b.storage[i].val);
    }

    unsigned x, y;

    for (unsigned i =0; i < result->size; i++ )
    {
        x = result->storage[i].row;
        y = result->storage[i].col;
        result->storage[i].val = result->storage[i].val * this->getAt(x,y);
    }

    for (unsigned i = 0; i < result->size; i++)
    {
        if (result->storage[i].val == 0)
        {
            result->removeAt(i);
              i = i - 1;
        }
    }
	return result;
}
