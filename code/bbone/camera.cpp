//camera.cpp - library for interacting with the camera

#include "camera.h"


#define READ_SIZE 32
#define READ_WAIT 100 //nanoseconds

const struct timespec WAIT_TIME = {0, READ_WAIT};

const char GET_SIZE[5] = {0x56, 0x00, 0x34, 0x01, 0x00};
const char RESET[5] = {0x56, 0x00, 0x26, 0x00, 0x00};
const char CAPTURE[5] = {0x56, 0x00, 0x36, 0x01, 0x00};
const char STOP_CAPTURE[5] = {0x56, 0x00, 0x36, 0x01, 0x03};
const char READ_DATA[8] = {0x56, 0x00, 0x32, 0x0C, 0x00, 0x0A, 0x00, 0x00};
const char READ_START[2] = {0x00, 0x00};
const char READ_WAIT_CMD[2] = {0x00, 0x0A};
const char CHANGE_BAUD[5] = {0x56, 0x00, 0x24, 0x03, 0x01}; // Plus XX XX to
				// represent the desired baud rate

const char RESET_RET[5] = {0x76, 0x00, 0x26, 0x00, 0x00};
const char CAPTURE_RET[5] = {0x76, 0x00, 0x36, 0x00, 0x00};
const char SIZE_RET[7] = {0x76,  0x00, 0x34, 0x00, 0x04, 0x00, 0x00}; //XH XL
				// represent size
const char READ_RET[5] = {0x76, 0x00, 0x32, 0x00, 0x00};

/* Initilises the Camera Class
 */
Camera::Camera(void) {

    serial = Uart(5, DEFAULT_BAUD);

    struct timespec init_wait = {2, 0};
    nanosleep(&init_wait, 0);

    char ret;
    while (serial.receive(&ret, 1));


    //need to read for init_end
}

/* Sends the reset command to the camera
 * exits the program if fails
 */
void Camera::reset(void) {

    cout << "send camera reset\n";
    serial.transmit(RESET, 5);

    char ret[5];

    cout << "Reeive camera reset response\n";
    serial.receive(ret, 5);

    for (int i = 0; i < 5; ++i) {
        if (ret[i] != RESET_RET[i]) {
            cerr << "Error resetting camera\n";
            exit(1);
        }
    }
}

/* Send the capture command to the camera
 * exits the program if fails
 */
void Camera::capture(void) {

    cout << "sending capture to camera\n";
    serial.transmit(CAPTURE, 5);

    char ret[5];

    cout << "reading capture response\n";
    serial.receive(ret, 5);

    for (int i = 0; i < 5; ++i) {
        if (ret[i] != CAPTURE_RET[i]) {
            cerr << "Error sending capture to camera\n";
            exit(1);
        }
    }
}

/* Send the command to stop taking pictures to the camera
 * exits the program if fails
 */
void Camera::stop_capture(void) {


    cout << "sending stop capture to camera\n";
    serial.transmit(STOP_CAPTURE, 5);

    char ret[5];

    cout << "receiveing stop capture response\n";
    serial.receive(ret, 5);

    for (int i = 0; i < 5; ++i) {
        if (ret[i] != CAPTURE_RET[i]) {
            cerr << "Error sending stop capture to camera\n";
            exit(1);
        }
    }
}

/* gets the image size of the camera and stores it in the given 
 * size input. size must be an array of length at least 2
 */
void Camera::get_size(unsigned char * size) {

    cout << "sending get size to camera\n";
    serial.transmit(GET_SIZE, 5);

    char ret[9];

    cout << "reading get size response\n";
    serial.receive(ret, 9);
    int i;
    for (i = 0; i < 7; ++i) {
        if (ret[i] != SIZE_RET[i]) {
            cerr << "Error sending get size to camera\n";
            exit(1);
        }
    }

    size[0] = i++;
    size[1] = i;

}


/* Reads the image from the camera of the given size. sets the img
 * variable to the data from the camera. img needs to be an array of size.
 */
void Camera::read_img(char * img, unsigned char * size) {

    char zero[2] = {0x00, 0x00};
    char * data = &img[0];

//    WAIT_TIME.tv_sec = 0;
//    WAIT_TIME.tv_nsec = READ_WAIT:

    cout << "sending read data\n";
    while (serial.transmit(READ_DATA, 8));

    cout << "sending read start\n";
    while (serial.transmit(READ_START, 2));

    cout << "sending zero\n";
    while (serial.transmit(zero, 2));

    cout << "sending size\n";
    while (serial.transmit((const char *) size, 2));

    cout << "sending read wait\n";
    while (serial.transmit(READ_WAIT_CMD, 2));

    char ret[5];

    cout << "reading read response\n";
    while (serial.receive(ret, 5));

    for (int i = 0; i < 5; ++i) {
        if (ret[i] !=READ_RET[i]) {
            cerr << "Error Sending read\n";
            exit(1);
        }
    }

    nanosleep(&WAIT_TIME, 0); //wait for given interval

    cout << "receiving start of image\n";
    while (serial.receive(ret, 2));

    if ((ret[0] != 0xFF) && (ret[1] != 0xD8)) {
        cerr << "error Reading from camera\n";
        exit(1);
    }

    while (true) {
        cout << "receiving image part\n";
        while (serial.receive(ret, 2));

        if ((ret[0] == 0xFF) && (ret[1] == 0xD9)) break;

        *data++ = ret[0];
        *data++ = ret[1];
    }
}


void Camera::save_img(char * img, char * filename, int size) {


    fstream imgfile (filename, ofstream::binary);

    imgfile.write(img, size);

    imgfile.close();

}


/* converts a given hexadecimal number in an array to the corresponding
 * integer. ltl_endian specifies the endian order of the array
 */
int Camera::hex_to_int(unsigned char * array, int length, int ltl_endian) {

    int i, result = 0;

    if (ltl_endian) {
        for (i = 0; i < length; ++i) {

            result += (((int)array[i]) << (i * 8));
        }
    } else {
        for (i = length - 1; i > -1; --i) {
            result += (((int) array[i]) << ((length - 1 - i) * 8));
        }
    }
    return le32toh(result);
}

int main() {

    Camera cam = Camera();

    cam.capture();

    unsigned char size[2];
    cam.get_size(size);

    int isize = cam.hex_to_int(size, 2, 1);

    char * img = new char[isize];

    cam.read_img(img, size);

    char fname[] = "test.jpg";

    cam.save_img(img, fname, isize);

    delete img;

    return 0;
}
