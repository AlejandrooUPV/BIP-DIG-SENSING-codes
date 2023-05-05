
const int Fan_pin = 14;  //multisensor board D7  
const int Fan_ch = 0;

const int BuiltInLed = 2; 
const int CO2_Input = 34; //multisensor board A2

int pwm_fan[3] = {0, 190, 255};
int co2 = 0;

void setup() {
  Serial.begin(9600);


  ledcSetup(Fan_ch, 5000, 8);
  ledcAttachPin(Fan_pin, Fan_ch);
}

// the loop function runs over and over again forever
void loop() {
int i;

co2 = analogRead(CO2_Input);
Serial.print("co2: ");
Serial.println(co2);
Serial.print("fan: ");

if(co2 < 100){
  ledcWrite(Fan_ch, pwm_fan[0]);
  Serial.println(pwm_fan[0]);
  delay(10000);
}
else if(co2 < 300){
        Serial.println(pwm_fan[1]);
        ledcWrite(Fan_ch, 255); //start up pulse
        delay(500);
        ledcWrite(Fan_ch, pwm_fan[1]);
        delay(10000);
        }
      else{
        Serial.println(pwm_fan[2]);
        ledcWrite(Fan_ch, pwm_fan[2]);
        delay(10000);
      }
}


