//camera.h - library for dealing with camera


#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_h_INCLUDED__

#include "../bbone/uart.h"
#include <time.h>
#include <endian.h>
#include <fstream>

using namespace std;

#define DEFAULT_BAUD 38400

class Camera {

    public:

        Camera(void);
        void reset(void);
        void capture(void);
        void stop_capture(void);
        void get_size(unsigned char *);
        void read_img(char *, unsigned char *);
        void save_img(char * , char *, int);

        int hex_to_int(unsigned char *, int, int);

    private:

        Uart serial;

};


#endif
