/********* Libraries needed ***********/
// GFX Library (Adafruit)
// SSD1306 (Adafruit)
// BusIO (Adafruit)
// DHT (Adafruit)
// LiquidCrystal_I2C (Frank de Brabander)




void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);  //(x,y)
  lcd.print("     DISCA      ");
  lcd.setCursor(0, 1);
  lcd.print("0123456789ABCDEF");
  ledcSetup(R_Led_ch, 5000, 12);  //12 bit resolution PWM @5KHz
  ledcAttachPin(R_Led_pin, R_Led_ch);
  ledcSetup(G_Led_ch, 5000, 12);
  ledcAttachPin(G_Led_pin, G_Led_ch);
  ledcSetup(B_Led_ch, 5000, 12);
  ledcAttachPin(B_Led_pin, B_Led_ch);
  pinMode(SW1, INPUT); //Pull-up resistor, so "1" is read by default (not pressed)
  pinMode(SW2, INPUT); //Pull-up resistor, so "1" is read by default (not pressed)
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(DHTpin, INPUT);
  pinMode(ROT, INPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(LM35, INPUT);
  pinMode(IR, INPUT);
   lcd.setCursor(11,0);
  if(!Backlight)
    lcd.print("Off");
  else
    lcd.print("On ");
}

void loop() {
 

}
