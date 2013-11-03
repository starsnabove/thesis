//kinematics.cpp - a library for performing forward and inverse kinematics


#include "kinematics.h"
#include "iostream"
Kinematics::Kinematics(void){}

/*The kinematics class constructor
 * parameters is an array of the DH parameters for each joint as an array of
 * {link twist, link length, link offset}
 */
Kinematics::Kinematics(int dof_in, vector<vector<double> > parameters) {

    dof = dof_in;
    params = parameters;

    for (int i = 0; i < dof; ++i) {

        square_lengths.push_back(params[i][A] * params[i][A]);

        DH_matrices.push_back(Matrix(4, 4));

        DH_matrices[i].insert(2, 0, 0);
        DH_matrices[i].insert(2, 1, sin(params[i][ALPHA]));
        DH_matrices[i].insert(2, 2, cos(params[i][ALPHA]));
        DH_matrices[i].insert(2, 3, params[i][D]);

        DH_matrices[i].insert(3, 0, 0);
        DH_matrices[i].insert(3, 1, 0);
        DH_matrices[i].insert(3, 2, 0);
        DH_matrices[i].insert(3, 3, 1);

    }

}

/* Performs forward kinematics returning the resultant position in a vector.
 * angles must be of length dof
 */
vector<double> Kinematics::forward(vector<double> angles) {

    for (int i = 0; i < dof; ++i ) {

        DH_matrices[i].insert(0, 0, cos(angles[i]));
        DH_matrices[i].insert(0, 1, -sin(angles[i]) * cos(params[i][ALPHA]));
        DH_matrices[i].insert(0, 2, sin(angles[i]) * sin(params[i][ALPHA]));
        DH_matrices[i].insert(0, 3, params[i][A] * cos(angles[i]));

        DH_matrices[i].insert(1, 0, sin(angles[i]));
        DH_matrices[i].insert(1, 1, cos(angles[i]) * cos(params[i][ALPHA]));
        DH_matrices[i].insert(1, 2, -cos(angles[i]) * sin(params[i][ALPHA]));
        DH_matrices[i].insert(1, 3, params[i][A] * sin(angles[i]));

    }

    Matrix res = DH_matrices[0] * DH_matrices[1];
    res *= DH_matrices[2];
    res *= DH_matrices[3];

    res.display();

    vector<double> position(3);

    position[X] = res[X][3];
    position[Y] = res[Y][3];
    position[Z] = res[Z][3];

    return position;
}

/* Performs inverse kinematics returning the resultant angles in degrees as
 * a vector. position must of length 3 in (x, y, z) order.
 */
vector<double> Kinematics::inverse(vector<double> position) {


    vector<double> angles(4);
    // Base rotator joint
    angles[BASE] =  180.0 - degrees(atan2(position[Y], position[X]));

    vector<double> wrst_loc(3);

    wrst_loc[X] = position[X];
    wrst_loc[Y] = position[Y];
    wrst_loc[Z] = position[Z] + params[WRST][A] - params[BASE][A];

    double s2w_sqrd = wrst_loc[Z] * wrst_loc[Z] + wrst_loc[Y] * wrst_loc[Y];
    double s2w = sqrt(s2w_sqrd);


    double elb_rad = acos((params[SHDR][A] * params[SHDR][A] +
                params[ELBW][A] * params[ELBW][A] - s2w_sqrd) / (2 *
                    params[SHDR][A] * params[ELBW][A]));

    double a1 = atan2(wrst_loc[Y], wrst_loc[Z]);

    double a2 = acos(((params[SHDR][A] * params[SHDR][A] - params[ELBW][A] *
                    params[ELBW][A]) + s2w_sqrd) / (2 * params[SHDR][A] * s2w));

    double shdr_rad = a1 + a2;
    angles[SHDR] = degrees(shdr_rad);

    angles[ELBW] = degrees(elb_rad);

    double wrst_1 = angles[ELBW] - angles[SHDR];
    double wrst_2 = atan2(wrst_loc[Z], wrst_loc[Y]);

    angles[WRST] = wrst_1 + degrees(wrst_2);

    angles[ELBW] = 180 - angles[ELBW];
    angles[WRST] = 180 - angles[WRST];

    return angles;

/*
    double s = wrst_loc[Z] - params[BASE][A];

    double d = (r_sqrd + (s * s) - (params[SHDR][A] * params[SHDR][A]) -
            (params[ELBW][A] * params[ELBW][A])) /
            (2 * params[SHDR][A] * params[ELBW][A]);

    double theta3_rad = atan2(-sqrt(1 - (d * d)), d); //-sqrt(...) for elbow up
                                            // +sqrt(...) for elbow down sol
    angles[THETA3] = -180 + degrees(theta3_rad);

    angles[THETA2] = degrees(atan2(s, r) - atan2(params[ELBW][A] *
            sin(theta3_rad), params[SHDR][A] + params[ELBW][A] *
            cos(theta3_rad)));

    angles[THETA4] = angles[THETA2] - angles[THETA3] - 90;

    return angles;
*/
/*
    double s_w = position[Y] * position[Y] + (position[Z] - params[WRST][A]) \
        * (position[Z] - params[WRST][A]);

    double s2w = sqrt(s_w);

    //angle first link to ground
    double a1 = atan2(position[Z] - params[BASE][A], position[Y]);
    // angle first link to 2nd link
    double a2 = acos((( square_lengths[SHDR] - square_lengths[ELBW] ) + s_w ) \
        / ( 2 * params[ELBW][A] * s2w )) + a1; // TODO check maybe have + a1

    // shoulder angle
    double shdr_a = a1 + a2;

    //elbow angle
    double elbw_a = acos(( square_lengths[SHDR] + square_lengths[ELBW] \
        - s_w ) / ( 2 * params[SHDR][A] * params[ELBW][A] ));

    double shdr_ad = degrees(shdr_a);
    double elbw_ad = degrees(elbw_a);

    double elbw_a_dn = -(180 - elbw_ad);

    //wrist angle

    double wrst_a = (-90 - elbw_a_dn) - shdr_ad;

    vector<double> angles(4);
    angles[BASE] = degrees(base_a);
    angles[SHDR] = shdr_ad;
    angles[ELBW] = elbw_ad;
    angles[WRST] = wrst_a;

    return angles;
*/
}

double Kinematics::degrees(double radian) {

    return radian * 180 / PI;
}

double radians(double degree) {

    return degree * PI / 180;

}
