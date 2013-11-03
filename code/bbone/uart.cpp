//uart.cpp - uart interaction library

#include "uart.h"

Uart::Uart(void){}

Uart::Uart(int uart_no, int baud) {

    uart = uart_no;

    struct termios tio;

    switch (uart) {
        case 1:
            tx_mux = string(MUX_DIR) + string(UART1_TX_MUX);
            rx_mux = string(MUX_DIR) + string(UART1_RX_MUX);
            ct_mux = string(MUX_DIR) + string(UART1_CT_MUX);
            rt_mux = string(MUX_DIR) + string(UART1_RT_MUX);
            tx_mode = UART1_MODE;
            rx_mode = UART1_MODE;
            ct_mode = UART1_MODE;
            rt_mode = UART1_MODE;
            file = UART1_FILE;
            break;

        case 2:
            tx_mux = string(MUX_DIR) + string(UART2_TX_MUX);
            rx_mux = string(MUX_DIR) + string(UART2_RX_MUX);
            tx_mode = UART2_MODE;
            rx_mode = UART2_MODE;
            file = UART2_FILE;
            break;

        case 5:
            tx_mux = string(MUX_DIR) + string(UART5_TX_MUX);
            rx_mux = string(MUX_DIR) + string(UART5_RX_MUX);
            tx_mode = UART5_MODE;
            rx_mode = UART5_MODE;
            file = UART5_FILE;
            break;

	//default:
        //    cerr << "invalid uart no.: " << uart_no << '\n'; 
    }

    ofstream fd;

    fd.open(tx_mux.c_str());
    fd << tx_mode;
    fd.close();

    fd.open(rx_mux.c_str());
    fd << rx_mode;
    fd.close();

    if (uart != 5 && uart != 2) {
    	fd.open(ct_mux.c_str());
    	fd << ct_mode;
    	fd.close();

    	fd.open(rt_mux.c_str());
    	fd << rt_mode;
    	fd.close();

    }


    com_fd = open(file.c_str(), O_RDWR | O_NOCTTY | O_SYNC | O_NONBLOCK);

    if (com_fd < 0) {
        cerr << "Cannot open serial port\n";
        exit(1);
    }

    fcntl(com_fd, F_SETFL, 0);

    if (tcgetattr(com_fd, &tio) != 0) {
        cerr << "error getting tio attr\n";
        exit(1);
    }


    // ste speed
    int br = select_baud(baud);
    cfsetospeed(&tio, br);
    cfsetispeed(&tio, br);

    //input flags
    tio.c_iflag &= ~IGNBRK; // ignore break
    tio.c_iflag &= ~(IGNPAR | PARMRK); // siable parity checks
    tio.c_iflag &= ~INPCK; // disable parity checking
    tio.c_iflag &= ~ISTRIP; // disable stripping 8th bit
    tio.c_iflag &= ~(INLCR | ICRNL); // disable translating NL <-> CR
    tio.c_iflag &= ~IGNCR; // disable ignoring CR
    tio.c_iflag &= ~(IXON | IXOFF); //disable XON/XOFF for control

    //output flags
    tio.c_oflag &= ~OPOST; // disblae output processing
    tio.c_oflag &= ~(ONLCR | OCRNL); // disable translating NL <-> CR

    // control flags
    tio.c_cflag |= CLOCAL; // prevent ownership changing
    tio.c_cflag |= CREAD; // enable reviever
    tio.c_cflag &= ~PARENB; // disable parity
    tio.c_cflag &= ~CSTOPB; // disblae 2 stop bits
    tio.c_cflag &= ~ CSIZE; // remove size flag
    tio.c_cflag |= CS8; // enable 8 bit characters
    tio.c_cflag |= HUPCL; // enable lower control lines on close
    tio.c_cflag &= ~CRTSCTS; // disable hardware CTS/RTS flow control
    
    //local flags    
    tio.c_lflag &= ~ISIG; // disable generating signals
    tio.c_lflag &= ~ICANON; // disable canonical (line by line) mode
    tio.c_lflag &= ~ECHO; // disable echoing characters
    tio.c_lflag &= ~ECHONL; // as above
    tio.c_lflag &= ~NOFLSH; //disable flushing on sigint
    tio.c_lflag &= ~IEXTEN; // disable input processing

    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 0;

    if (tcsetattr(com_fd, TCSAFLUSH, &tio) != 0) {
        cerr << "error setting uart tio attr\n";
	exit(1);
    }
    
    tcflow(com_fd, TCOON | TCION); // enable input & output transmission

    fcntl(com_fd, F_SETFL, 0);
}

Uart::~Uart(void) {

    close(com_fd);

}

int Uart::select_baud(int rate) {

    switch (rate) {
        case 1200: return B1200;
        case 2400: return B2400;
        case 4800: return B4800;
        case 9600: return B9600;
        case 19200: return B19200;
        case 38400: return B38400;
        case 57600: return B57600;
        case 115200: return B115200;
        default: return 0;
    }
}

bool Uart::transmit(const char * message, int length) {
    
    int wr = write(com_fd, message, length);

    if (wr < 0) {
        cerr << "Error transmitting to uart" << uart << '\n';
        return false;
    }
    return true;
}

bool Uart::receive(char * message, int length) {
    
    
    int rd = read(com_fd, message, length);

    if (rd < 0) {
        cerr << "Error receiving from uart" << uart << '\n';
        return false;
    }
    return true;
}



/*
int main() {
    char buf[10] = {'h', 'e', 'l', 'l', 'o'};
    char in;
    Uart test = Uart(5, 38400);
    test.transmit(buf, 5);

    while (1) {
    cout << "receiving\n";
    test.receive(&in, 1);
    cout << "recevied -> " << in << " <- now transmit\n";
    test.transmit(&in, 1);
    }

}*/
