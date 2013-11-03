//pwm.h

#ifndef __PWM_H_INCLUDED__
#define __PWM_H_INCLUDED__


#include <string>
using namespace std;

// The sub-directories for each PWM
#define PWM0 "ehrpwm.0:0/"
#define PWM1 "ehrpwm.0:1/"
#define PWM2 "ehrpwm.1:0/"
#define PWM3 "ehrpwm.1:1/"
#define PWM4 "ehrpwm.2:0/"
#define PWM5 "ehrpwm.2:1/"
#define PWM6 "ecap.0/"
#define PWM7 "ecap.2/"

/*class for interactions with the PWM ports of the beaglebone
 */
class PWM {
    
    public:

    void init_mux(void);
  void request(void);
	void release(void);
	void run(void);
	void set_prd_frq(string, int);
	void set_prd_ns(string, int);
	void set_duty_pc(string, int);
	void set_duty_ns(string, int);

};

#endif
