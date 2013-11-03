//gpio.h - - gpio lib

#ifndef __GPIO_H_INCLUDED__
#define __GPIO_H_INCLUDED__

#include <string>
#include <stdlib.h>

using namespace std;

class GPIO {

    private:

        string path;
        int bank;
        int num;
        int port;
        string direc;

    public:

        GPIO(void);
        GPIO(int, int, string);

        void set(int);
        int get(void);
        void set_direction(string);

};

#endif
