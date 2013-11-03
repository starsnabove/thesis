// drive.cpp - class for driving around


#include "../general/drive.h"

Drive::Drive(void) {}

Drive::Drive(PWM pwm_in) {

    pwm = pwm_in;

    rght_rvs = GPIO(1, 6, "out");
    rght_fwd = GPIO(1, 7, "out");
    left_fwd = GPIO(1, 2, "out");
    left_rvs = GPIO(1, 12, "out");

    enable = GPIO(1, 13, "out");

    left = Motor(1, pwm, left_fwd, left_rvs, enable);
    right = Motor(2, pwm, rght_fwd, rght_rvs, enable);

}

void Drive::forward(int speed) {

    left.forward(speed);
    right.forward(speed);

}

void Drive::reverse(int speed) {

    left.reverse(speed);
    right.reverse(speed);

}

void Drive::turn_left(int speed) {

    left.reverse(speed);
    right.forward(speed);

}

void Drive::turn_right(int speed) {

    left.forward(speed);
    right.reverse(speed);

}

void Drive::stop(void) {

    left.stop();
    right.stop();

}

void Drive::brake(void) {

    left.brake();
    right.brake();

}
