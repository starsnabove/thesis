// motor.h - class for controlling a motor

#ifndef __MOTOR_H_INCLUDED__
#define __MOTOR_H_INCLUDED__

#include "../bbone/pwm.h"
#include "../bbone/gpio.h"
#include <iostream>

class Motor {

    private:
        PWM pwm;
        GPIO fwd_io;
        GPIO rvs_io;
        GPIO enbl;
        string pwm_str;

    public:

        Motor(void);
        Motor(int, PWM, GPIO, GPIO, GPIO);

        void forward(int);
        void reverse(int);
        void stop(void);
        void brake(void);

};

#endif
