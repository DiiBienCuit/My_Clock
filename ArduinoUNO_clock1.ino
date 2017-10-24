#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremote.h>
#include <IRremoteInt.h>


int val;
int tempPin = 1; //lm35
int input_pin = 10; //set D10 as input signal pinir receiver
IRrecv irrecv(input_pin);
decode_results signals;

void setup()
{
Serial.begin(9600);
 irrecv.enableIRIn(); // enable input from IR receiver
}

void getTemperature()
{
val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float cel = mv/10;
float farh = (cel*9)/5 + 32;

Serial.print("TEMPRATURE = ");
Serial.print(cel);
Serial.print("*C");
Serial.println();
delay(1000);  
}

void loop()
{


if (irrecv.decode(&signals)) {
        Serial.println(signals.value, HEX);
        if(signals.value == 1){
          getTemperature();
        }
        irrecv.resume(); // get the next signal
    }
}




