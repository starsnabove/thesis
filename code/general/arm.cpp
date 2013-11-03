//arm.cpp - library for managing an n DOF robotic arm

#include "arm.h"

Arm::Arm(void) {}

Arm::Arm(int degofree, vector<vector<double> > parameters, PWM pwm) {


    dof = degofree;
    kinemats = Kinematics(dof, parameters);

    servos.push_back(Servo(BASE, BASE_MIN, BASE_MAX, BASE_ANGLE, pwm, PWM0));
    servos.push_back(Servo(SHDR, SHDR_MIN, SHDR_MAX, SHDR_ANGLE, pwm, PWM1));
    servos.push_back(Servo(ELBW, ELBW_MIN, ELBW_MAX, ELBW_ANGLE, pwm, PWM2));
    servos.push_back(Servo(WRST, WRST_MIN, WRST_MAX, WRST_ANGLE, pwm, PWM3));
    claw = Claw(CLAW, CLAW_MIN, CLAW_MAX, pwm, PWM4);
}


/* Moves the arm to the given psotion
 */
vector<double> Arm::move(vector<double> position, 
        bool testing /*= false*/) {

    vector<double> angles = kinemats.inverse(position);

    if (testing) {
        for (int i = 0; i < 4; ++i) {
            angles[i] = radians(angles[i]);
        }
        vector<double> ret_pos = kinemats.forward(angles);
        cout << "(x, y, z) = (" << ret_pos[0] << ", " << ret_pos[1];
        cout << ", " << ret_pos[2] << ")\n";
    }

    set_angles(angles);

    return angles;
}

void Arm::set_angles(vector<double> angles) {

    for (int i = 0; i < dof; ++i) {
            cout << "Angle: "<< i << "--" << angles[i] << '\n';
            servos[i].set_angle(angles[i]);
    }

}

/* Moves the arm into its neutral position
 */
void Arm::neutral(void) {

    servos[BASE].set_angle(BASE_N);
    servos[SHDR].set_angle(SHDR_N);
    servos[ELBW].set_angle(ELBW_N);
    servos[WRST].set_angle(WRST_N);

}

void Arm::close_claw(void) {

    claw.close();

}

void Arm::open_claw(void) {

    claw.open();

}
