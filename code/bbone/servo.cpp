// servo.cpp - Servo class

#include "servo.h"

#define NEUTRAL 1500000 // ns pulse width for servo neutral position
#define SIG_FREQ 250 // frequency (Hz) of the pwm signal
#define MAX 2400000 // maximum pulse width in ns
#define MIN 600000 // minimum pulse width in ms
#define ANGLE 180.0 // the movement angle in degrees

Servo::Servo(void){}


/* Servo class constructor. min_range & max_range specify the movement range
* of the servo in ns. this range can not be outside the movement range of the
* servo
*/
Servo::Servo (int servo_number, int min_range, int max_range, float angle, 
        PWM pwm_in, string servo_name) {

    if (min_range < MIN || max_range > MAX) {
        cerr << "Invalid servo movement range\n";
        exit(EXIT_FAILURE);
    }
    min = min_range; max = max_range;
    convert = (max - min) / angle;

    pwm = pwm_in;
    servo_no = servo_number;
    servo_nm = servo_name;

    pwm.set_prd_frq(servo_nm, SIG_FREQ);
    pwm.set_duty_ns(servo_nm, NEUTRAL);

    pwm.run();

}

/* Sets the joint angle of the given joint
 */
void Servo::set_angle(double angle) {

    if (angle < 0 || angle > ANGLE) {
        cerr << "Invalid angle into servos.set_angle\n";
        return;
    }

    int ns = (int)(min + angle * convert) / 10;
    ns *= 10;
    cout << "ns into servo: " << servo_no << "--" << ns << endl;
    pwm.set_duty_ns(servo_nm, ns);
}
