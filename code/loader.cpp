//loader.cpp  - This file runs the program for the loader.

#include "loader.h"


Loader::Loader(void) {

    int i = 0;
    for (i = 0; i < DOF; ++i) {
        vector<double> parameter(3);

        parameter[D] = OFFSET;

        switch (i) {

            case BASE:
                parameter[ALPHA] = radians(B_ALPHA);
                parameter[A] = B_LEN;

            case SHDR:
                parameter[ALPHA] = radians(S_ALPHA);
                parameter[A] = S_LEN;

            case ELBW:
                parameter[ALPHA] = radians(E_ALPHA);
                parameter[A] = E_LEN;

            case WRST:
                parameter[ALPHA] = radians( W_ALPHA);
                parameter[A] = W_LEN;
        }

        parameters.push_back(parameter);
    }

    setup_pwm();

    arm = Arm(DOF, parameters, pwm);
    arm.neutral();
    arm.open_claw();

    drive = Drive(pwm);

}

void Loader::setup_pwm() {

    pwm = PWM();
    pwm.init_mux();
    pwm.request();
    pwm.run();

}

void Loader::load_blocks(void) {

    //locate hauler
    //
    // Get image from camera
    // Get points from image
    // Move arm to centre-most point
    // control loop with above till arm reaches block
    //
    // grab block
    // move to hauler location
    // release block
    //
    // repeat
    //

    vector<double> point(3);
    point.push_back(50);
    point.push_back(50);
    point.push_back(50);

    arm.move(point);
/*
    for (int i = 0; i < 3; ++i) {
        arm.move(points[i], true);
    }
*/
}

void Loader::move_to_point(vector<double> point) {

    arm.move(point);

}

void Loader::turn_left(int speed) {

    drive.turn_left(speed);
}

void Loader::turn_right(int speed) {

    drive.turn_right(speed);

}

void Loader::forward(int speed) {

    drive.forward(speed);

}

void Loader::reverse(int speed) {

    drive.reverse(speed);

}

void Loader::set_angles(vector<double> angles) {

    arm.set_angles(angles);

}

void Loader::close_claw(void) {

    arm.close_claw();

}

void Loader::open_claw(void) {

    arm.open_claw();

}

/*
int main(int argc, char ** argv) {

    Loader l = Loader();

    vector<double> angles(4);
    angles.push_back(0);
    angles.push_back(0);
    angles.push_back(0);
    angles.push_back(0);
    angles[0] = 90.0;
    angles[1] = 50.0;
    angles[2] = 180 - 140.0;
    angles[3] = 180 - 110.0;
    for (int i = 0; i < 4; ++i) {
        cout << angles[i] << endl;
    }
    l.set_angles(angles);


//    l.load_blocks();
    //
//    l.reverse(50);

    return 0;
}*/
