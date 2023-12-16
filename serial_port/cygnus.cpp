/*
 * File: cygnus.cpp
 * Project: Octo-Robot-GroundCrawler
 * File Created: Thursday, 22nd December 2022 11:22:07 am
 * Author: Ishan B (ishan.b@octobotics.tech)
 * -----
 * Last Modified: Thursday, 22nd December 2022 11:22:31 am
 * Modified By: Ishan B (ishan.b@octobotics.tech)
 * -----
 * Copyright 2022 - 2022 Octobotics Tech Pvt Ltd, Octobotics Tech Pvt Ltd
 */


/*-------------------------------------------------------------------------
    							HEADER FILE 
-------------------------------------------------------------------------*/

#include <errno.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <thread>
#include<algorithm>
#include <execinfo.h>
#include <future>


/*-------------------------------------------------------------------------
    							TYPEDEF 
-------------------------------------------------------------------------*/
typedef  unsigned char 		Uint8;
typedef  unsigned char 		BYTE;
typedef  short int 			Uint16;
typedef  unsigned short int 		Unit16;
typedef  char 				Int8;
typedef  unsigned int 			Uint32; 
typedef  unsigned short int 		WORD;
typedef  void				VOID;
/*-------------------------------------------------------------------------
									DEFINES 
-------------------------------------------------------------------------*/
#define DISPLAY_BY_BYTE
#define DEBUG_PRINT_ENABLE
#define ENABlE_WITH_GUI

#define SERIAL_FILE_PATH "/dev/ttyUSB0"
#define UNIT_MM "mm"
#define  UNIT_INCHES "inches"


/*-------------------------------------------------------------------------
    							MACROS 
-------------------------------------------------------------------------*/
#define GETBIT(var, bit)	(((var) >> (bit)) & 1)
#define NULL_CHECK(val)  \
	if (val == NULL) { \
		printf("%d >NULL",__LINE__);\
		return ;\
		}
	
#ifdef DEBUG_PRINT_ENABLE
#define DEBUG_PRINT(__X__) printf __X__
#else
#define DEBUG_PRINT(__X__) 
#endif

/*-------------------------------------------------------------------------
    							FUNCTION PROTOTYPES 
-------------------------------------------------------------------------*/
WORD CRC16 (const BYTE *nData, WORD wLength);
int serial_readermain();

VOID Parse_STATUS(Uint8 *pReceivedData, Uint16 ui16ReceivedLength);
VOID *serialWrite(void *vargp);
VOID Parse_STATUS_AS(Uint8 *pReceivedData, Uint16 ui16ReceivedLength);


/*-------------------------------------------------------------------------
    							STRUCTURE 
-------------------------------------------------------------------------*/
typedef struct status{
	Uint8 STX;
	Uint16 Preamble;
	Uint8 Ui8Reserved;
	
	Uint16 Command;
	Uint16 Size;
	
	Uint16 BITFIELD;
	Uint16 Ui16Reserved2;

	Uint32 SERIAL_NUMBER;
	
	Uint8 ID;
	Uint8 BATTERY;
	Uint16 VELOCITY;
	
	Uint8 ECHOES;
	Uint8 PROBE_INFO;
	Uint8 HVSETUP;
	Uint8 Ui8Reserved3;
	
	Uint16 RECORDS;
	Unit16 CMD_NUM;
	
	Uint16 LAST_CMD;
	Int8 THICKNESS[6];
	
	Uint16 CRC16;
	Uint16 Ui16Reserved4;
}STRUCT_STATUS;

typedef struct status_as{
Uint16	STX;
Uint16	Preamble;
Uint16	Command;
Uint16	Size;
Uint16	BITFIELD;
Uint32	SERIAL_NUMBER;
Uint8	ID;
Uint8	BATTERY;
Uint16	VELOCITY;
Uint8	ECHOES;
Uint8	PROBE_INFO;
Uint8	HVSETUP;
Uint16	RECORDS;
Unit16	CMD_NUM;
Uint16	LAST_CMD;
Int8	THICKNESS[6];
Uint16	XSIZE;
Uint16	HOLDOFF;
Uint8	XRANGE;
Uint8	TE_MATCH_POINTS[9];
Uint8	ASCAN[320];
Uint16		CRC16;
}STRUCT_STATUS_AS;

/*-------------------------------------------------------------------------
    							GLOBAL VARIABLES 
-------------------------------------------------------------------------*/
//User for testing purpose

Uint8 samplearray[] = {
	0x2,0x55,0x55,0x5,0x0,0x22,
	0x0,0x10,0x93,0xdc,0x30,0x0,
	0x0,0x1,0xb4,0x20,0x17,0x0,
	0x2,0xf,0xde,0x0,0x0,0x0,0x0,
	0x0,0x20,0x20,0x35,0x2e,0x30,
	0x0,0x5a,0x7d
};

static int counter = 0;

int fd;

/*-------------------------------------------------------------------------
								FUNCTION DEFINITION 
-------------------------------------------------------------------------*/  
WORD CRC16 (const BYTE *nData, WORD wLength)
{
	static const WORD wCRCTable[] = {
	0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
	0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
	0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
	0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
	0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
	0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
	0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
	0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
	0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
	0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
	0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
	0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
	0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
	0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
	0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
	0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
	0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
	0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
	0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
	0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
	0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
	0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
	0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
	0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
	0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
	0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
	0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
	0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
	0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
	0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
	0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
	0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

	BYTE nTemp;
	WORD wCRCWord = 0xFFFF;

	   while (wLength--)
	   {
	      nTemp = *nData++ ^ wCRCWord;
	      wCRCWord >>= 8;
	      wCRCWord ^= wCRCTable[nTemp];
	   }
	   return wCRCWord;
}

VOID printbuffer(int rdlen, unsigned char *buf)
{
		unsigned char *p;
		 
        if (rdlen > 0) {            
            printf("Read %d:", rdlen);
            for (p = buf; rdlen-- > 0; p++) {
                printf(" %d ,", *p);
            }
            printf("\n");
	}
}



int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}




VOID serialread()
{  
   while(1) {
   	serial_readermain();  
   	sleep(1);
   }

   return ; 		
}




int serial_readermain()
{
	const char *portname = SERIAL_FILE_PATH;
	int wlen;

	printf("Welcome to Serial Reader : version 1.0\n ");

	

	fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0) {
		printf("Error %i opening %s: %s\n",errno, portname, strerror(errno));
		return -1;
	}
	/*baudrate 115200, 8 bits, no parity, 1 stop bit */


	set_interface_attribs(fd, B115200);
	//set_mincount(fd, 0);                /* set to pure timed read */

	/* simple output 
	wlen = write(fd, xstr, xlen);
	if (wlen != xlen) {
	printf("Error from write: %d, %d\n", wlen, errno);
	}
	tcdrain(fd);    /* delay for output */

	/* simple noncanonical input */
	do {
	Uint8 buf[400];
	Uint32 rdlen,Backuplen;

	rdlen = read(fd, buf, sizeof(buf) - 1);
	Backuplen = rdlen;
	if (rdlen > 0) {
		  printbuffer(rdlen,buf);
	
		if(Backuplen == 34) {
			// Parse_STATUS(buf,Backuplen);
		} 
		else if(Backuplen == 368) {
			// Parse_STATUS_AS(buf,Backuplen);
		}

	} else if (rdlen < 0) {
		printf("Error from read: %d: %s\n", rdlen, strerror(errno));
	} else {  /* rdlen == 0 */
		printf("Timeout from read\n");
	}               
		/* repeat read to get full message */
	} while (1);
}





int main(int argc, char* argv[])
{	

     std::future<void> read_ (std::async(serialread));

     
    
    while(1) {
    	printf("\n Main running");
    	sleep(100000);
    }	
  
    return 0;
}