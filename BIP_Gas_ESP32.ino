#include "BluetoothSerial.h"

BluetoothSerial BT;

String slaveName = "My_ESP32_Bluetooth";

const int BuiltInLed = 2; 
const int CO2_Input = 34; //multisensor board A2

int pwm_fan[3] = {0, 190, 255};
int co2 = 0;

void setup() {
   
  BT.begin("ESP32_BT_Master", true); //Name and Master configuration
  Serial.begin(9600);
  Serial.print("Connecting to Bluetooth slave ESP32...");
  while (!BT.connect(slaveName))
  Serial.print("...");
  Serial.println("...connected!");
  
}

// the loop function runs over and over again forever
void loop() {
int i;

co2 = analogRead(CO2_Input);
Serial.print("co2: ");
Serial.println(co2);
Serial.print("fan: ");

if(co2 < 100){
  Serial.println(pwm_fan[0]);
  BT.write('1');
  delay(10000);
}
else if(co2 < 300){
        Serial.println(pwm_fan[1]);
        BT.write('2');
         delay(10000);
        }
      else{
        Serial.println(pwm_fan[2]);
        BT.write('3');
        delay(10000);
      }
}
