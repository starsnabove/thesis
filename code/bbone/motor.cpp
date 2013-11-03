// motor.cpp - class for controlling a motor


#include "motor.h"

#define MTR_FRQ 300

Motor::Motor(){}

Motor::Motor(int id, PWM pwm_in, GPIO fwd_gpio, GPIO rvs_gpio, GPIO enable) {

    pwm = pwm_in;
    fwd_io = fwd_gpio;
    rvs_io = rvs_gpio;
    enbl = enable;

    stop();

    if (id == 1) {
        pwm_str = PWM6;
    }
    else if (id == 2) {
        pwm_str = PWM7;
    }
    else {
        cerr << "bad motor id given - needs to be 1 or 2\n";
        exit(1);
    }

    pwm.set_prd_frq(pwm_str, MTR_FRQ);

}

/* turns the motor forward at the given speed. speed is the percentage
 * of full speed between 0 and 100. if a number outside this range is 
 * given it will be set at the closest bound.
 */
void Motor::forward(int speed) {

    enbl.set(1);
    rvs_io.set(0);
    fwd_io.set(1);
    pwm.set_duty_pc(pwm_str, speed);

}


/* turns the motor backward at the given speed. speed is the percentage
 * of full speed between 0 and 100. if a number outside this range is 
 * given it will be set at the closest bound.
 */
void Motor::reverse(int speed) {

    enbl.set(1);
    rvs_io.set(1);
    fwd_io.set(0);
    pwm.set_duty_pc(pwm_str, speed);

}

/* lets the motors roll to a stop
 */
void Motor::stop(void) {

    enbl.set(0);
    fwd_io.set(0);
    rvs_io.set(0);

}

/* makes the motors brake to stop
 */
void Motor::brake(void) {

    enbl.set(1);
    fwd_io.set(1);
    rvs_io.set(1);

}
