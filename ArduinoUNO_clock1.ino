#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>



int val;
int tempPin = 1; //lm35
int input_pin = 10; //set D10 as input signal pinir receiver
IRrecv irrecv(input_pin);
decode_results signals;

/*FF30CF
FF18E7
FF7A85
FF10EF
*/

static const long int modeTemperature = 0xFF30CF;
static const long int modeTime = 0xFF18E7;
static const long int modeLight = 0xFF7A85;
static const long int modeHumidity = 0xFF10EF;


void setup()
{
Serial.begin(9600);
 irrecv.enableIRIn(); // enable input from IR receiver
}

void notFinish(){
  Serial.print("This command is coming! ");
}
void getTime(){
  Serial.print("This command is coming! ");
}
void getLight(){
  int valeur = analogRead(A0);
  
  Serial.println(valeur);
  if(valeur <= 673){
    Serial.print("Night! ");
  }else{
    Serial.print(" Good morning! ");
  }
  delay(250);
   
}
void getTemperature()
{
val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
int cel = mv/10;
float farh = (cel*9)/5 + 32;

Serial.print(" Now: ");
Serial.print(cel);
Serial.print("°C");
Serial.println();
delay(1000);  
}

void loop()
{


if (irrecv.decode(&signals)) {
        Serial.println(signals.value, HEX);
        switch(signals.value){
          case modeTemperature: 
              getTemperature();
              break;
           case modeTime:
              getTime();
              break;
           case modeLight:
              getLight();
              break;
           
           default: 
              notFinish();
              break;
        }
        /*if(signals.value == modeTemperature){
          getTemperature();
        }*/
        irrecv.resume(); // get the next signal
    }
}


