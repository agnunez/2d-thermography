/*
 * =====================================================================================
 *
 *       Filename:  thermal-cam.ino
 *
 *    Description:  move and read an IR MLX90614 (ESF-DCI)
 *
 *        Version:  1.0
 *        Created:  26. 08. 14 16:59:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sebastien Chassot (sinux), sebastien.chassot@etu.hesge.ch
 *        Company:  HES-SO hepia section ITI (soir)
 *
 * =====================================================================================
 */


#include <i2cmaster.h>

#define DIRECTION_X     true
#define DIRECTION_Y     true
#define STP_X    2
#define DIR_X    3
#define MS1_X    4
#define MS2_X    5
#define STP_Y    6
#define DIR_Y    7
#define MS1_Y    8
#define MS2_Y    9

#define END_X    10
#define END_Y    11

int a = 0;     //  gen counter

void setup() 
{            
  Serial.begin(115200);
  
//  pinMode(STP_X, OUTPUT);       
//  pinMode(DIR_X, OUTPUT);
//  pinMode(MS1_X, OUTPUT);
//  pinMode(MS2_X, OUTPUT);
//  pinMode(STP_Y, OUTPUT);       
//  pinMode(DIR_Y, OUTPUT);
//  pinMode(MS1_Y, OUTPUT);
//  pinMode(MS2_Y, OUTPUT);
//  pinMode(END_X, INPUT);
//  pinMode(END_Y, INPUT);

  DDRD = B11111100;         // set pins 2-7 as OUTPUT
  DDRB = B00000011;         // set pins 8-11 as OUTPUT

 /* Set micro stepping 
  * pins 4,5,8,9 HIGH (1/8 step) */
  //PORTD = B00110000;        // pins 4,5 HIGH (1/8 X step)
  //PORTB = B00000011;        // pins 8,9 HIGH (1/8 Y step)

  if( DIRECTION_X )
      PORTD |= (1<<DIR_X);
  if( DIRECTION_Y )
      PORTD |= (1<<DIR_Y);

}


void loop(){
    if (a < 80){  //sweep 200 step in dir 1
    
        a++;
        PORTD |= (1<<STP_X);    // X step high
        PORTD |= (1<<STP_Y);
        delay(6);               
        PORTD &= ~(1<<STP_X);    // X step low
        PORTD &= ~(1<<STP_Y);
        delay(60);              
    }else{
        //PORTD &= ~(1<<DIR_X);    // toggle direction
        //PORTD &= ~(1<<DIR_Y);
        PORTD &= ~(1<<DIR_X);
        PORTD &= ~(1<<DIR_X);
        a++;
        PORTD |= (1<<STP_X);    // X step high
        PORTD |= (1<<STP_Y);
        delay(6);
        PORTD &= ~(1<<STP_X);    // X step low
        PORTD &= ~(1<<STP_Y);
        delay(60);
    
        if (a > 160){    //sweep 200 in dir 2
            delay(1000);
            a = 0;
            PORTD ^= (1<<DIR_X);    // toggle direction
            PORTD ^= (1<<DIR_Y);
      
            Serial.println("Fin du cycle");
        }
    }
}
