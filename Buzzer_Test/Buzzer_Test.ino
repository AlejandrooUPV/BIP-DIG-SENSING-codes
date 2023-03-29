long DO = 523.25,  //definimos las frecuencias de las notas
  DoS = 554.37,
     RE = 587.33,
     RES = 622.25,
     MI = 659.26,
     FA = 698.46,
     FAS = 739.99,
     SOL = 783.99,
     SOLS = 830.61,
     LA = 880,
     LAS = 932.33,
     SI = 987.77,
     RE2 = 1174.66,
     FAS2 = 1479.98;

DHT dht(DHTpin, DHT11);
int Button1_Count = 0;
int Button1_State, Button1_Old = 1;  //Switch pull down, so press button will read 0
bool Backlight=true;

void setup() {

}

void loop() {
  // put your main code here, to run repeatedly:

}

void doTest(){
 Serial.println("Pasive buzzer test.");
  tone(BUZZ, DO, 500);  // A4
  delay(100);
  tone(BUZZ, RE, 500);  // B4
  delay(100);
  tone(BUZZ, MI, 500);  // C4
  delay(100);
  tone(BUZZ, FA, 500);  // D4
  delay(100);
  tone(BUZZ, SOL, 500);  // E4
  delay(100);
  tone(BUZZ, LA, 500);  // F4
  delay(100);
  tone(BUZZ, SI, 500);  // G4
  delay(100);
}