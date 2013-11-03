// arm.h

#ifndef __ARM_H_INCLUDED__
#define __ARM_H_INCLUDED__

#include "../bbone/pwm.h"
#include "../bbone/servo.h"
#include "../bbone/claw.h"
#include "../general/kinematics.h"
#include <vector>


using namespace std;

#define CLAW 4

#define BASE_MIN 600000
#define BASE_MAX 2400000
#define BASE_ANGLE 180.0
#define SHDR_MIN 1500000
#define SHDR_MAX 2400000
#define SHDR_ANGLE 110.0
#define ELBW_MIN 700000
#define ELBW_MAX 2300000
#define ELBW_ANGLE 180.0
#define WRST_MIN 700000
#define WRST_MAX 2300000
#define WRST_ANGLE 180.0
#define CLAW_MIN 700000
#define CLAW_MAX 2200000

#define BASE_N 90
#define SHDR_N 80
#define ELBW_N 140
#define WRST_N 80

class Arm {

    private:

        int dof;

        vector<Servo> servos;
        Kinematics kinemats;
        Claw claw;

    public:

        Arm(void);
        Arm(int, vector<vector<double> >, PWM);
        vector<double> move(vector<double>, bool testing = false);
        void set_angles(vector<double>);
        void neutral(void);
        void close_claw(void);
        void open_claw(void);
};


#endif
