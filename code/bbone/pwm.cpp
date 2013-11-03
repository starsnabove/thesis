#include "pwm.h"
#include <iostream>
#include <fstream>
//#include <string>
//using namespace std;

// the directory the multiplexing files are stored
#define MUXADDR "/sys/kernel/debug/omap_mux/"

//Modes for activating multiplexing the pwm clock to the pwm port
#define PWM0MODE 1 // ehrpwm.0:0 - port 9-31
#define PWM1MODE 1 // ehrpwm.0:1 - port 9-29
#define PWM2MODE 6 // ehrpwm.1:0 - port 9-14
#define PWM3MODE 6 // ehrpwm.1:1 - port 9-16
#define PWM4MODE 4 // ehrpwm.2:0 - port 8-19
#define PWM5MODE 4 // ehrpwm.2:1 - port 8-13
#define PWM6MODE 0 // ecap.0 - port 9-42
#define PWM7MODE 4 // ecap.2 - port 9-28

//Multiplexing files for each mode
#define PWM0MUX "mcasp0_aclkx"
#define PWM1MUX "mcasp0_fsx"
#define PWM2MUX "gpmc_a2"
#define PWM3MUX "gpmc_a3"
#define PWM4MUX "gpmc_ad8"
#define PWM5MUX "gpmc_ad9"
#define PWM6MUX "ecap0_in_pwm0_out"
#define PWM7MUX "mcasp0_ahclkr"

// The directory that the PWM files are stored
#define PWMADDR "/sys/class/pwm/"

/*
// The sub-directories for each PWM
#define PWM0 "ehrpwm.0:0/"
#define PWM1 "ehrpwm.0:1/"
#define PWM2 "ehrpwm.1:0/"
#define PWM3 "ehrpwm.1:1/"
#define PWM4 "ehrpwm.2:0/"
#define PWM5 "ehrpwm.2:1/"
#define PWM6 "ecap.0/"
#define PWM7 "ecap.2/"
*/

//access files
#define REQUEST "request" //request the clock
#define P_FREQ "period_freq" // set the period in frequency (Hz)
#define P_NS "period_ns" // set the period in nanoseconds
#define DUTY_PC "duty_percent" //set the duty cycle in %
#define DUTY_NS "duty_ns" // set the duty in ns
#define RUN "run" // start the pwm


/* sets the pwm duty as a percentage  for the specified port
 */
void PWM::set_duty_pc(string  pwm_port, int percentage) {

    ofstream duty_file;

    string fout;
    fout =  PWMADDR + pwm_port + DUTY_PC;

    duty_file.open(fout.c_str());
    duty_file << percentage << '\n';
    duty_file.close();
}

/* sets the pwm duty in nano seconds  for the specified port
 */
void PWM::set_duty_ns(string  pwm_port, int ns) {

    ofstream duty_file;

    string fout;
    fout =  PWMADDR + pwm_port + DUTY_NS;

    duty_file.open(fout.c_str());
    duty_file << ns << '\n';
    duty_file.close();
}

/* sets the pwm period frequency for the specified port
 * NOTE: the way the beaglebone is set up the paired pwm ports will have the 
 * same frequency - if you change one theother will change
 */
void PWM::set_prd_frq(string  pwm_port, int freq) {

    ofstream freq_file;

    string fout;
    fout =  PWMADDR + pwm_port + P_FREQ;

    freq_file.open(fout.c_str());
    freq_file << freq << '\n';
    freq_file.close();
}


/* sets the pwm period in nano seconds for the specified port
 * NOTE: the way the beaglebone is set up the paired pwm ports will have the 
 * same period - if you change one theother will change
 */
void PWM::set_prd_ns(string  pwm_port, int ns) {

    ofstream freq_file;

    string fout;
    fout =  PWMADDR + pwm_port + P_NS;

    freq_file.open(fout.c_str());
    freq_file << ns << '\n';
    freq_file.close();
}

/* sets up the multiplexing of the ports to the correct pins for PWM
 * these pins however are dependant on the ports specified above
 * they can be change by reassessing the mux table
 */
void PWM::init_mux(void) {

    ofstream muxfile;
    muxfile.open(MUXADDR PWM0MUX);
    muxfile << PWM0MODE;
    muxfile.close();

    muxfile.open(MUXADDR PWM1MUX);
    muxfile << PWM1MODE;
    muxfile.close();

    muxfile.open(MUXADDR PWM2MUX);
    muxfile << PWM2MODE;
    muxfile.close();

    muxfile.open(MUXADDR PWM3MUX);
    muxfile << PWM3MODE;
    muxfile.close();

    muxfile.open(MUXADDR PWM4MUX);
    muxfile << PWM4MODE;
    muxfile.close();

    muxfile.open(MUXADDR PWM5MUX);
    muxfile << PWM5MODE;
    muxfile.close();

    muxfile.open(MUXADDR PWM6MUX);
    muxfile << PWM6MODE;
    muxfile.close();

    muxfile.open(MUXADDR PWM7MUX);
    muxfile << PWM7MODE;
    muxfile.close();

}

/* requests access to all the PWM clocks
 */
void PWM::request(void) {

    ofstream req_file;

    req_file.open(PWMADDR PWM0 REQUEST);
    req_file << 1 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM1 REQUEST);
    req_file << 1 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM2 REQUEST);
    req_file << 1 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM3 REQUEST);
    req_file << 1 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM4 REQUEST);
    req_file << 1 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM5 REQUEST);
    req_file << 1 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM6 REQUEST);
    req_file << 1 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM7 REQUEST);
    req_file << 1 << '\n';
    req_file.close();

}

/* Releases all PWM clocks from use
 */
void PWM::release(void) {

     ofstream req_file;

    req_file.open(PWMADDR PWM0 REQUEST);
    req_file << 0 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM1 REQUEST);
    req_file << 0 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM2 REQUEST);
    req_file << 0 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM3 REQUEST);
    req_file << 0 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM4 REQUEST);
    req_file << 0 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM5 REQUEST);
    req_file << 0 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM6 REQUEST);
    req_file << 0 << '\n';
    req_file.close();

    req_file.open(PWMADDR PWM7 REQUEST);
    req_file << 0 << '\n';
    req_file.close();
   
}

/* Sets the PWM clocks to run - therfore activating the PWM signals
 */
void PWM::run(void) {

    ofstream run_file;

    run_file.open(PWMADDR PWM0 RUN);
    run_file << 1 << '\n';
    run_file.close();

    run_file.open(PWMADDR PWM1 RUN);
    run_file << 1 << '\n';
    run_file.close();

    run_file.open(PWMADDR PWM2 RUN);
    run_file << 1 << '\n';
    run_file.close();

    run_file.open(PWMADDR PWM3 RUN);
    run_file << 1 << '\n';
    run_file.close();

    run_file.open(PWMADDR PWM4 RUN);
    run_file << 1 << '\n';
    run_file.close();

    run_file.open(PWMADDR PWM5 RUN);
    run_file << 1 << '\n';
    run_file.close();

    run_file.open(PWMADDR PWM6 RUN);
    run_file << 1 << '\n';
    run_file.close();

    run_file.open(PWMADDR PWM7 RUN);
    run_file << 1 << '\n';
    run_file.close();

}
/*
int main(int argc, char ** argv) {

    PWM pwm;
    pwm.init_mux();
    pwm.request();
    pwm.run();
    pwm.set_prd_ns(PWM0, 1000000000);
    //pwm.release();
    return 0;

}
*/
