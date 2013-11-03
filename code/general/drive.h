// drive.h - class for driving around


#include "../bbone/pwm.h"
#include "../bbone/motor.h"

class Drive {

    private:

        PWM pwm;
        GPIO left_fwd;
        GPIO left_rvs;
        GPIO rght_fwd;
        GPIO rght_rvs;

        GPIO enable;

        Motor left;
        Motor right;

    public:

        Drive(void);
        Drive(PWM);

        void forward(int);
        void reverse(int);
        void turn_left(int);
        void turn_right(int);
        void stop(void);
        void brake(void);

};
