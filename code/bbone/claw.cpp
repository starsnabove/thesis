// claw.cpp - class for controlling the claw

#include "claw.h"

Claw::Claw(void){}

Claw::Claw(int servo_number, int min_range, int max_range, PWM pwm_in, 
        string servo_name) : Servo(servo_number, min_range, max_range, 
            180.0, pwm_in, servo_name) {}

/* Opens the claw
 */
void Claw::open(void) {
    set_angle(CLAW_OPEN);
}

/* Closes the claw
 */
void Claw::close(void) {
    set_angle(CLAW_CLOSE);
}

