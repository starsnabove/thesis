//matrix.h

#ifndef __MATRIX_H_INCLUDED__
#define __MATRIX_H_INCLUDED__

#include <vector>
using namespace std;

class Matrix {
    private:
        
        vector< vector<double> > mat;

    public:
        
        int rows;
        int cols;
        
        //constructor
        Matrix(int, int);
        void insert(int, int, double);
        //double get(int, int);
        void display(void);
        
        Matrix operator + (Matrix);
        void operator += (Matrix);
        Matrix operator - (Matrix);
        void operator -= (Matrix);
        Matrix operator * (Matrix);
        Matrix operator * (double);
        void operator *= (Matrix);
        void operator *= (double);
        void operator = (Matrix);
        bool operator == (Matrix);
        bool operator != (Matrix);
        
        vector<double> operator [] (int);
};

#endif
