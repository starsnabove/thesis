//loader.h - library for running of the loader



#include "general/arm.h"
#include "general/drive.h"

//link lengths of the arm in mm
#define B_LEN 167
#define S_LEN 146
#define E_LEN 180
#define W_LEN 87

// offest of each joint is 0
#define OFFSET 0

//link twist of each joint
#define B_ALPHA -90
#define S_ALPHA -90
#define E_ALPHA 0
#define W_ALPHA 90

#define DOF 4

using namespace std;

class Loader {

    private:

        vector<vector<double> > parameters;
        PWM pwm;
        Arm arm;
        Drive drive;
        void setup_pwm();


    public:
        Loader(void);
        void load_blocks(void);
        void turn_left(int);
        void turn_right(int);
        void forward(int);
        void reverse(int);
        void set_angles(vector<double>);
        void close_claw(void);
        void open_claw(void);
        void move_to_point(vector<double>);

};
