//A matrix class for use with calculations
#include "matrix.h"
#include <iostream>
#include <stdlib.h>


#define FILLING 10 //the horizontal filling for pretty printing the matrix



/* Overrides the != operrator
 */
bool Matrix::operator!= (Matrix param) {
    if (rows != param.rows || cols != param.cols) return true;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (mat[i][j] != param[i][j]) return true;
        }
    }
    return false;
}

/* Overrides the == operater enabling comparing of matrices
 */
bool Matrix::operator== (Matrix param) {
    if (rows != param.rows || cols != param.cols) return false;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (mat[i][j] != param[i][j]) return false;
        }
    }
    return true;
}

/* Overrides the equals operator enabling the equating of matrices
 */
void Matrix::operator= (Matrix param) {
    rows = param.rows;
    cols = param.cols;
    mat = param.mat;
}

/* Overrides the *= operator performing matrix scalar multiplication
 */
void Matrix::operator*= (double param) {

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i][j] = mat[i][j] * param;
        }
    }
}

/* Overrides the *= operator performing matrix dot product
 */
void Matrix::operator*= (Matrix param) {
    if (rows != param.cols || cols != param.rows) {
        cerr << "Invalid Matrix dimensions in dot product\n";
        cerr << "Rows of LHM must equal Columns of RHM\n";
        cerr << "and Columns of LHM must equal Rows of RHM\n";
        exit(EXIT_FAILURE);
    }
    Matrix temp(rows, param.cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < param.cols; ++j) {
            double sum = 0;
            for (int k = 0; k < cols; ++k) {
                sum += mat[i][k] * param[k][j];
            }
            temp.insert(i, j, sum);
        }
    }
    cols = param.cols;
    mat = temp.mat;
}

/* Overrides the * operator performing matrix times scalar
 */
Matrix Matrix::operator* (double param) {

    Matrix temp(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            temp.insert(i, j, mat[i][j] * param);
        }
    }
    return temp;
}

/* Overrides the * operator performing matrix dot product
 */
Matrix Matrix::operator* (Matrix param) {
    if (rows != param.cols || cols != param.rows) {
        cerr << "Invalid Matrix dimensions in dot product\n";
        cerr << "Rows of LHM must equal Columns of RHM\n";
        cerr << "and Columns of LHM must equal Rows of RHM\n";
        exit(EXIT_FAILURE);
    }

    Matrix temp(rows, param.cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < param.cols; ++j) {
            double sum = 0;
            for (int k = 0; k < cols; ++k) {
                sum += mat[i][k] * param[k][j];
            }
            temp.insert(i, j, sum);
        }
    }
    return temp;
}

/* Overrides the -= operator performing matrix addition
 */
void Matrix::operator-= (Matrix param) {
    if (rows != param.rows || cols != param.cols) {
        cerr << "Matrix Dimensions must be the same for subtraction\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i][j] = mat[i][j] - param[i][j];
        }
    }
}


/* Overrides the - operator performing matrix addition
 */
Matrix Matrix::operator- (Matrix param) {
    if (rows != param.rows || cols != param.cols) {
        cerr << "Matrix Dimensions must be the same for subtraction\n";
        exit(EXIT_FAILURE);
    }
    Matrix temp(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            temp.insert(i, j, mat[i][j] - param[i][j]);
        }
    }
    return temp;
}


/* Overrides the += operator performing matrix addition
 */
void Matrix::operator+= (Matrix param) {
    if (rows != param.rows || cols != param.cols) {
        cerr << "Matrix Dimensions must be the same for addition\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i][j] = mat[i][j] + param[i][j];
        }
    }
}


/* Overrides the + operator performing matrix addition
 */
Matrix Matrix::operator+ (Matrix param) {
    if (rows != param.rows || cols != param.cols) {
        cerr << "Matrix Dimensions must be the same for addition\n";
        exit(EXIT_FAILURE);
    }
    Matrix temp(rows, cols);
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            temp.insert(i, j, mat[i][j] + param[i][j]);
        }
    }
    return temp;
}

/* Overrides the indexing operator
 */
vector<double> Matrix::operator[] (int param) {
    return mat[param];
}

/* Matrix Class constructor
 */
Matrix::Matrix (int num_rows, int num_cols) {
    rows = num_rows; cols = num_cols;

    for (int i = 0; i < rows; ++i) {
        vector<double> row; //new empty row
        for (int j = 0; j < cols; ++j) {
            row.push_back(0); // add zero for every column
        }
        mat.push_back(row); // add row into matrix
    }
}

/* inserts value into the row, col coordinate.
 */
void Matrix::insert(int row, int col, double value) {

    if (row >= rows || col >= cols) {
        cerr << "Invalid row or column in insert\n";
        exit(EXIT_FAILURE);
    }
    mat[row][col] = value;
}

/* Pretty Prints the matix with horizontal filling - beware large matrices
 * can end up off screen.
 */
void Matrix::display(void) {

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout.width(FILLING);
            cout << mat[i][j];
        }
        cout << '\n';
    }

}

/*
int main(int argc, char ** argv) {

    Matrix m (4, 4);
    m.insert(2,2,2);
    m.insert(2,1,2);
    m.insert(1, 2, 2);
    m.insert(1,1,1);
    Matrix n(4, 4);
    n.insert(2,2,2);
    n.insert(2,1,2);
    n.insert(1,1,1);
    n.insert(1,2,2);
    Matrix d(4,4);
    //m*=10;
    //d = m * 10;
    cout << (m != n) << '\n';
    m.display();
    cout << '\n';
    n.display();
    cout << '\n';
    d.display();

}
*/
