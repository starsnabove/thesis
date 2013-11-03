//gpio.cpp - library for interacting with beaglebone gpio ports

#include "../bbone/gpio.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define MUXADDR "/sys/kernel/debug/omap_mux/"
#define GPIO_PATH "/sys/class/gpio/gpio"
#define EXPORT "/sys/class/gpio/export"

#define GPIO_OUT 7
#define GPIO_IN 27

//so far have defined the ones that I am using
#define GPIO1_2MUX "gpmc_ad2"
#define GPIO1_3MUX "gpmc_ad3" // unavailable as beaglebone uses it
#define GPIO1_6MUX "gpmc_ad6"
#define GPIO1_7MUX "gpmc_ad7"
#define GPIO1_12MUX "gpmc_ad12"
#define GPIO1_13MUX "gpmc_ad13"

GPIO::GPIO(void){}


/* Constructor for beaglebone GPIO ports. num is the GPIO number you wish 
 * to activate. direction sets the gpio port as input(in) or output(out)
 */
GPIO::GPIO(int gpio_bank, int gpio_num, string direction ) {

    bank = gpio_bank;
    num = gpio_num;

    ofstream export_file;
    export_file.open(EXPORT);

    port = bank * 32 + num; // 4 banks of 32 GPIOs

    export_file << port;

    export_file.close();

    //convert num into a string
    ostringstream port2str;
    port2str << port;
    string port_str = port2str.str();

    path = GPIO_PATH + port_str + "/";

    set_direction(direction);
}

/* sets the GPIO port to the given level (0/1 -- low/high). only works
 * if the GPIO is set as an output
 */
void GPIO::set(int level) {

    if (direc != "out") {
        cerr << "Cannot set GPIO " << bank << '-' << num;
        cerr << " as it is set as input\n";
        exit(1);
    }

    if (level != 0 && level != 1) {
        cerr << "Cannot only set GPIO to high(1) or low(0) - GPIO";
        cerr << bank << '_' << num << endl;
        exit(1);
    }

    ofstream out;
    out.open((path + "value").c_str());

    out << level << endl;

    out.close();
}

/* reads the value on the GPIO port. only works if the GPIO port is set as
 * an input
 */
int GPIO::get(void) {

    if (direc != "in") {
        cerr << "Cannot get fromGPIO " << bank << '-' << num;
        cerr << " as it is an output\n";
        exit(1);
    }

    ifstream in;
    in.open((path + "value").c_str());

    string input;

    getline(in, input, '\n');

    if (!input.length()) {
        cerr << "error reading from GPIO " << bank << '-' << num << endl;
        exit(1);
    }

    in.close();

    stringstream ins(input);
    int in_int;
    ins >> in_int;

    return in_int;
}

void GPIO::set_direction(string direction) {

    ofstream muxfile;

    if (bank == 1) {
        switch (num) {
            case 2: muxfile.open(MUXADDR GPIO1_2MUX); break;
            case 3: muxfile.open(MUXADDR GPIO1_3MUX); break;// gpio1_3 unavailable
            case 6: muxfile.open(MUXADDR GPIO1_6MUX); break;
            case 7: muxfile.open(MUXADDR GPIO1_7MUX); break;
            case 12: muxfile.open(MUXADDR GPIO1_12MUX); break;
            case 13: muxfile.open(MUXADDR GPIO1_13MUX); break;
        }
    }

    if (muxfile.is_open()) {
        if (direction == "out") {
            muxfile << GPIO_OUT;
        }
        else if (direction == "in") {
            muxfile << GPIO_IN;
        }
        else {
            cerr << "bad direction given to gpio" << bank << num <<endl;
            exit(1);
        }
        muxfile.close();
    }
    else {
        cerr << "invalid GPIO port given: " << bank << '_' << num << endl;
        exit(1);
    }

    direc = direction;

    string direc_path = path + "direction";

    ofstream direc_file;
    direc_file.open(direc_path.c_str());

    direc_file << direc;

    direc_file.close();

}

/*
int main (int argc, char ** argv) {

    GPIO gp(atoi(argv[1]), atoi(argv[2]), "out");
    gp.set(1);

    return 0;
}
*/
