#include <Arduino.h>

/*    
    basic_demo.ino
    Example for MCP9600
    Copyright (c) 2018 Seeed Technology Co., Ltd.
    Website    : www.seeed.cc
    Author     : downey
    Create Time: May 2018
    Change Log :
    The MIT License (MIT)
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/   

#include "Seeed_SHT35.h"
  
     
/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SDAPIN  20
    #define SCLPIN  21
    #define RSTPIN  7
    #define SERIAL SerialUSB
#else
    #define SDAPIN  A4
    #define SCLPIN  A5
    //#define RSTPIN  4
    #define SERIAL Serial
#endif
#define TEMP1 2
#define TEMP2 4

bool flag = 0;
float temp1, hum1;
float temp2, hum2;
//unsigned long 

SHT35 sensor(SCLPIN);


void setup() {
    SERIAL.begin(9600);
    delay(10);
    SERIAL.println("serial start!!");
    if (sensor.init()) {
        SERIAL.println("sensor init failed!!!");
    }
    pinMode(TEMP1,OUTPUT);
    pinMode(TEMP2,OUTPUT);
    delay(1000);
}


void loop() {
   // u16 value = 0;
    //u8 data[6] = {0};

    flag = !flag;
    
    
    //delay(10);
    if (!(millis() % 1000))
    {
        
        
        if (flag)
        {
            
            if (NO_ERROR != sensor.read_meas_data_single_shot(HIGH_REP_WITH_STRCH, &temp1, &hum1))
            {
                SERIAL.println("read temp1 failed!!");
                SERIAL.println("   ");
                SERIAL.println("   ");
                SERIAL.println("   ");
            }
            else
            {
                //SERIAL.println("read data1 :");
                //SERIAL.print("temperature1 = ");
                // SERIAL.print(temp1);
                //SERIAL.println(" ℃ ");
                //SERIAL.print(',');

                //SERIAL.print("humidity1 = ");
                //SERIAL.print(hum1);
                //SERIAL.println(" % ");
                // SERIAL.print(',');
                //SERIAL.println("   ");
                //SERIAL.println("   ");
                //SERIAL.println("   ");
            }
        }
        else if (!flag)
        {
            
            if (NO_ERROR != sensor.read_meas_data_single_shot(HIGH_REP_WITH_STRCH, &temp2, &hum2))
            {
                SERIAL.println("read temp2 failed!!");
                SERIAL.println("   ");
                SERIAL.println("   ");
                SERIAL.println("   ");
            }
            else
            {
                //SERIAL.println("read data :");
                //SERIAL.print("temperature2 = ");
                // SERIAL.print(temp2);
                //SERIAL.println(" ℃ ");
                // SERIAL.print(',');
                //SERIAL.print("humidity2 = ");
                //  SERIAL.println(hum2);
                //SERIAL.println(" % ");

                //SERIAL.println("   ");
                //SERIAL.println("   ");
                //SERIAL.println("   ");
            }
        }
        SERIAL.print(temp1);
        SERIAL.print(',');
        SERIAL.print(hum1);
        SERIAL.print(',');
        SERIAL.print(temp2);
        SERIAL.print(',');
        SERIAL.println(hum2);

        digitalWrite(TEMP1,flag);
        digitalWrite(TEMP2,!flag);
    }
    //delay(488);
}
