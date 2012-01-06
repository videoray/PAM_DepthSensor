#ifndef _PAM_H_
#define _PAM_H_

#define UART_RS485_TXE_PORT PORTA
#define UART_RS485_TXE_PORT_DIR DDRA
#define UART_RS485_RXE_PORT PORTA
#define UART_RS485_RXE_PORT_DIR DDRA

#define UART_0_RS485_TXE_MASK (1<<1)
#define UART_1_RS485_TXE_MASK (1<<0)
#define UART_0_RS485_TXE_MASK (1<<1)
#define UART_1_RS485_TXE_MASK (1<<0)
#define UART_1_RS485_RS232_SW (1<<2) //Device RS-485/RS-232 Switch (1=RS485,0=RS232)
#define UART_1_RS485_RXE_MASK (1<<3) //Device RS-485 Receive Enable

#define COMM_PORT_TETHER     0
#define COMM_PORT_ACCESSORY  1

#endif
