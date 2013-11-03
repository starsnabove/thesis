//uart.h

#ifndef __UART_H_INCLUDED__
#define __UART_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MUX_DIR "/sys/kernel/debug/omap_mux/"
#define UART1_TX_MUX "uart1_txd"
#define UART1_RX_MUX "uart1_rxd"
#define UART1_CT_MUX "uart1_ctsn"
#define UART1_RT_MUX "uart1_rtsn"

#define UART2_TX_MUX "spi0_d0"
#define UART2_RX_MUX "spi0_sclk"

#define UART5_TX_MUX "lcd_data8"
#define UART5_RX_MUX "lcd_data9"

#define UART1_MODE 20
#define UART1_FILE "/dev/ttyO1"

#define UART2_MODE 21
#define UART2_FILE "/dev/ttyO2"

#define UART5_MODE 24
#define UART5_FILE "/dev/ttyO5"

class Uart {

    private:

        int select_baud(int);

        string tx_mux;
        string rx_mux;
        string ct_mux;
        string rt_mux;
        int tx_mode;
        int rx_mode;
        int ct_mode;
        int rt_mode;

        string file;
        int com_fd;
        int uart;



    public:
        Uart(void);
        Uart(int, int);
        ~Uart(void);
        bool transmit(const char *, int);
        bool receive(char *, int);

};

#endif
