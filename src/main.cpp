#include <Arduino.h>
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
 
    #define SERIAL Serial
#endif
#define TEMP1 2
#define TEMP2 4

bool flag = 1;
float temp1, hum1;
float temp2, hum2;


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
    digitalWrite(TEMP1,flag);
    delay(1000);
}


void loop() {
  
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
           
        }
        
        SERIAL.print(temp1);
        SERIAL.print(',');
        SERIAL.println(hum1);
       
    }
    if(SERIAL.available()!=0)
    {
        if (SERIAL.read()=='1')
            sensor.change_heater_status(CMD_HEATER_ON);
        if (SERIAL.read()=='3')
            sensor.change_heater_status(CMD_HEATER_OFF);
    }
        
  
}
