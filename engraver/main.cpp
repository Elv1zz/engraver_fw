//
//    COPYRIGHT 2012 Elv1zz
//    based on code from Christian Nolte
//    Arduino firmware for laser engraver project
//    
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "MSMotorShield.h"

// define default pin for laser
#ifndef LASERPIN
// pin 13 is connected to a LED on most Arduino boards, so it is a nice default
#define LASERPIN 13
#endif

//// define default pin for warning LED
//#ifndef WARNPIN
//// no useful default yet
//#define WARNPIN xx
//#endif

// used for decoding protocol messages
#define BIT_LASER 0x30

// define default length for receive buffer
#ifndef RECBUFFER_LEN
#define RECBUFFER_LEN 256
#endif

// steppers
// stepper for x-axis is connected to motor port 2 and can do 48 steps per full rotation
// (information about steps/rotation is not really required here)
MS_Stepper motorX (48, 2);
// stepper for y-axis is connected to motor port 1 and can do 48 steps per full rotation
// (information about steps/rotation is not really required here)
MS_Stepper motorY (48, 1);

// receive buffer
unsigned char receiveBuffer[RECBUFFER_LEN];
unsigned int bufferPos = 0;

void setup (void) {
  // serial communication with 9600 bps
  Serial.begin (9600);

  // declare pin to be an output for laser 
  pinMode (LASERPIN, OUTPUT);

  // make sure, laser is off
  digitalWrite (LASERPIN, LOW);
  
  // declare pin to be an output for warnings 
  //pinMode (WARNPIN, OUTPUT);

  // make sure, warning LED is off
  //digitalWrite (WARNPIN, LOW);
 
} 

void sendData (unsigned char data) {
  Serial.write (data);
} 

unsigned char receiveData (void) {
  unsigned char data = 0;

  // TODO: There might be a better way of doing this than busy waiting...
  while (Serial.readBytes ((char *) &data, 1) <= 0) {
    delay (5);
  }
  return data;
}

unsigned char check_crc (unsigned char b2, unsigned char b3, unsigned char crc) {
  unsigned char mycrc;

  mycrc = b2 + b3;
  if (crc == mycrc) {
    return 1;
  } else {
    return 0;
  }
}

void loop (void) {
  unsigned char received_char, received_char_2, received_char_3, received_char_crc;

  received_char = receiveData ();
  if (received_char == 'a') {
    //digitalWrite (WARNPIN, LOW);
    received_char_2 = receiveData ();   // b1
    received_char_3 = receiveData ();   // b2 
    received_char_crc = receiveData (); // b4   (CRC)
    if (check_crc (received_char_2, received_char_3, received_char_crc)) {
      //CRC OK

      // motor X
      if ((received_char_3 & 0x03) == 0x03) {
        // negative step
        motorX.onestep (-1, INTERLEAVE);
      } else if ((received_char_3 & 0x0C) == 0x0C) {
        // positive step
        motorX.onestep (1, INTERLEAVE);
      }
      // motor Y
      if ((received_char_3 & 0x30) == 0x30) {
        // negative step
        motorY.onestep (-1, INTERLEAVE);
      } else if ((received_char_3 & 0xC0) == 0xC0) {
        // positive step
        motorY.onestep (1, INTERLEAVE);
      }
      // laser
      if ((received_char_2 & BIT_LASER) == BIT_LASER) {
        // on
        digitalWrite (LASERPIN, HIGH);
      } else {
        // off
        digitalWrite (LASERPIN, LOW);
      }
      sendData ('O');
    } else {
      sendData ('C');
      //digitalWrite (WARNPIN, HIGH);
    }
  } else if (received_char == 'r') {
    // go to (0,0):
    // - register interrupts for 0-position switches
    // - start motors
  } else {
    //digitalWrite (WARNPIN, HIGH);
    sendData ('F');
  }
}

//indent --braces-on-if-line --braces-on-func-def-line --braces-on-struct-decl-line --honour-newlines --line-length120 --comment-line-length120 --cuddle-else --no-tabs --blank-lines-after-declarations --blank-lines-after-procedures --dont-break-procedure-type --no-blank-lines-before-block-comments main.cpp.ind.tr -o main.cpp.ind

