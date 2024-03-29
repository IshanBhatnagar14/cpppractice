/*
 * File: example1.cpp
 * Project: Octo-Robot-GroundCrawler
 * File Created: Thursday, 22nd December 2022 10:26:54 am
 * Author: Ishan B (ishan.b@octobotics.tech)
 * -----
 * Last Modified: Thursday, 22nd December 2022 10:27:10 am
 * Modified By: Ishan B (ishan.b@octobotics.tech)
 * -----
 * Copyright 2022 - 2022 Octobotics Tech Pvt Ltd, Octobotics Tech Pvt Ltd
 */


#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()



int serial_port = open("/dev/ttyUSB0", O_RDWR);

// Check for errors
if (serial_port < 0) {
    printf("Error %i from open: %s\n", errno, strerror(errno));
}

// Create new termios struct, we call it 'tty' for convention
// No need for "= {0}" at the end as we'll immediately write the existing
// config to this struct

struct termios tty;


// Read in existing settings, and handle any error
// NOTE: This is important! POSIX states that the struct passed to tcsetattr()
// must have been initialized with a call to tcgetattr() overwise behaviour
// is undefined
if(tcgetattr(serial_port, &tty) != 0) {
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
}