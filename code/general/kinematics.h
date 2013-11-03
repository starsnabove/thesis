// kinematics.h

#ifndef __KINEMATICS_H_INCLUDED__
#define __KINEMATICS_H_INCLUDED__

#include "matrix.h"
#include <math.h>
#include <vector>

#define PI 3.141592653589793238462643383
#define ALPHA 0
#define A 1
#define D 2

#define X 0
#define Y 1
#define Z 2

#define THETA1 0
#define THETA2 1
#define THETA3 2
#define THETA4 3

//defines for 4DOF
#define BASE 0
#define SHDR 1
#define ELBW 2
#define WRST 3


double radians(double);

class Kinematics {

    private:
        int dof; // no of degrees of freedom
        vector<Matrix>DH_matrices;
        vector<vector<double> > params; // the DH parameters
        vector<double> square_lengths; //square of the link lengths
        double degrees(double);

    public:

        Kinematics(void);
        Kinematics(int, vector<vector<double> >);
        vector<double> forward(vector<double>);
		vector<double> inverse(vector<double>);

};


#endif
