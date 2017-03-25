#ifndef _RPI_UART_H
#define _RPI_UART_H

#include "rpi.h"
#include "gpio.h"

typedef union{
    struct{
    	uint32_t UARTEN:1;
	uint32_t SIREN: 1;
	uint32_t SIRLP: 1;
	uint32_t reserved: 4;
        uint32_t LBE :1;
        uint32_t TXE :1;
        uint32_t RXE :1;
        uint32_t DTR: 1;
        uint32_t RTS: 1;
        uint32_t OUT1: 1;
        uint32_t OUT2: 1;
        uint32_t RTSEN: 1;
        uint32_t CTSEN: 1;
        uint32_t reserved1: 16;
    } bit;
    uint32_t reg;
} RPI_UART_CR_REG;//control register
#define RPI_UART_CR_UARTEN_Pos 0
#define RPI_UART_CR_UARTEN_Msk 0x01 << RPI_UART_CR_UARTEN_pos
#define RPI_UART_CR_SIREN_Pos 1
#define RPI_UART_CR_SIREN_Msk 0x01 << RPI_UART_CR_SIREN_pos
#define RPI_UART_CR_SIRLP_Pos 2
#define RPI_UART_CR_SIRLP_Msk 0x01 << RPI_UART_CR_SIRLP_pos
#define RPI_UART_CR_LBE_Pos 7
#define RPI_UART_CR_LBE_Msk 0x01 << RPI_UART_CR_LBE_pos
#define RPI_UART_CR_TXE_Pos 8
#define RPI_UART_CR_TXE_Msk 0x01 << RPI_UART_CR_TXE_pos
#define RPI_UART_CR_RXE_Pos 9
#define RPI_UART_CR_RXE_Msk 0x01 << RPI_UART_CR_RXE_pos
#define RPI_UART_CR_DTR_Pos 10
#define RPI_UART_CR_DTR_Msk 0x01 << RPI_UART_CR_DTR_pos
#define RPI_UART_CR_RTS_Pos 11
#define RPI_UART_CR_RTS_Msk 0x01 << RPI_UART_CR_RTS_pos
#define RPI_UART_CR_OUT1_Pos 12
#define RPI_UART_CR_OUT1_Msk 0x01 << RPI_UART_CR_OUT1_pos
#define RPI_UART_CR_OUT2_Pos 13
#define RPI_UART_CR_OUT2_Msk 0x01 << RPI_UART_CR_OUT2_pos
#define RPI_UART_CR_RTSEN_Pos 14
#define RPI_UART_CR_RTSEN_Msk 0x01 << RPI_UART_CR_RTSEN_pos
#define RPI_UART_CR_CTSEN_Pos 15
#define RPI_UART_CR_CTSEN_Msk 0x01 << RPI_UART_CR_CTSEN_pos


typedef union{
    struct{
	uint32_t CTS :1;
	uint32_t DSR :1;
	uint32_t DCD :1;
	uint32_t BUSY:1;
	uint32_t RXFE:1;
	uint32_t TXFF:1;
        uint32_t RXFF:1;
        uint32_t TXFE:1;
        uint32_t RI:1;
        uint32_t reserved: 23;
    } bit;
    uint32_t reg;
} RPI_UART_FR_REG;//flag register

typedef union{
    struct{
	uint32_t DATA :8;
	uint32_t FE :1;
	uint32_t PE :1;
	uint32_t BE :1;
	uint32_t OE :1;
	uint32_t reserved: 20;	  } bit;
    uint32_t reg;
} RPI_UART_DR_REG;//data register


typedef union{
    struct{
	uint32_t IBRD: 16;
	uint32_t reserved: 16;
    } bit;
    uint32_t reg;
} RPI_UART_IBRD_REG; //integer part baudrate divisor


typedef union{
    struct{
	uint32_t FBRD: 6;
        uint32_t reserved: 26;
    } bit;
    uint32_t reg;
} RPI_UART_FBRD_REG;//fractional baud rate divisor

typedef union{
    struct{
        uint32_t BRK: 1;
        uint32_t PEN: 1;
        uint32_t EPS: 1;
        uint32_t STP2: 1;
        uint32_t FEN: 1;
        uint32_t WLEN: 2;
        uint32_t SPS: 1;
        uint32_t reserved: 24;
    } bit;
    uint32_t reg;
} RPI_UART_LCRH_REG; //line control register


typedef union{
    struct{
         uint32_t r0: 32;
    } bit;
    uint32_t reg;
} RPI_UART_SHARE_REG;

typedef enum
{
    RPI_UART_CLOCK_DIVIDER_4096 = 4096, //7627.53hz
    RPI_UART_CLOCK_DIVIDER_2048 = 2048 //15251.34hz

} RPI_UART_CLK_DIVIDER;

typedef struct{ 
    __IO RPI_UART_DR_REG DR;
    __IO RPI_UART_SHARE_REG reserved;
    __IO RPI_UART_FR_REG FR;
    __IO RPI_UART_SHARE_REG reserved1;
    __IO RPI_UART_IBRD_REG IBRD;
    __IO RPI_UART_FBRD_REG FBRD;
    __IO RPI_UART_LCRH_REG LCRH;
    __IO RPI_UART_CR_REG CR;
    __IO RPI_UART_SHARE_REG IFLS;
    __IO RPI_UART_SHARE_REG IMSC;
    __IO RPI_UART_SHARE_REG RIS;
    __IO RPI_UART_SHARE_REG MIS;
    __IO RPI_UART_SHARE_REG ICR;
    __IO RPI_UART_SHARE_REG DMACR;
    __IO RPI_UART_SHARE_REG ITCR;
    __IO RPI_UART_SHARE_REG ITIP;
    __IO RPI_UART_SHARE_REG ITOP;
    __IO RPI_UART_SHARE_REG TDR;

}rpi_uart_t;

extern volatile rpi_uart_t *rpi_uart;

int rpi_uart_init(volatile rpi_uart_t* rpi_uart);
void rpi_uart_set_clock(volatile rpi_uart_t* rpi_uart, uint16_t divider);
void rpi_uart_transmit(volatile rpi_uart_t* rpi_uart, char* tbuf, uint32_t len);
void rpi_uart_receive(volatile rpi_uart_t* rpi_uart, char* rbuf, uint32_t len);


#ifdef cplusplus
extern "C" {
#endif

#ifdef cplusplus
}
#endif

#endif
