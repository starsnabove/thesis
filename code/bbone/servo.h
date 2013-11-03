//Servo.h

#ifndef __SERVO_H_INCLUDED__
#define __SERVO_H_INCLUDED__


#include "pwm.h"
#include <iostream>
#include <stdlib.h>


#define WAIST 0
#define SHLDR 1
#define ELBOW 2
#define WRIST 3
#define CLAW 4

class Servo {

    private:

        PWM pwm;
        float convert; // the conversion between ns and angle
        int min; // the minimum range of servo in ns
        int max; // the maximum range of servo in ns
        int servo_no;
        string servo_nm;

    public:

        //constructor
        Servo(void);
        Servo(int, int, int, float, PWM, string);
        void set_angle(double);
        void open_claw(void);
        void close_claw(void);

};

#endif
