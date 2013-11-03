//claw.h

#ifndef __CLAW_H_included__
#define __CLAW_H_included__

#include "servo.h"

#define CLAW_OPEN 0
#define CLAW_CLOSE 100

class Claw: public Servo{

    public:

        Claw(void);
        Claw(int, int, int, PWM, string);
        void open(void);
        void close(void);
};




#endif
