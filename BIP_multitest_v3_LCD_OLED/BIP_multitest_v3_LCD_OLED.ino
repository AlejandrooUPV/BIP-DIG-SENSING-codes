/********* Libraries needed ***********/
// GFX Library (Adafruit)
// SSD1306 (Adafruit)
// BusIO (Adafruit)
// DHT (Adafruit)
// LiquidCrystal_I2C (Frank de Brabander)

/*************** OLED *************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 32     // OLED display height, in pixels
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
LiquidCrystal_I2C lcd(0x27, 16, 2);             // LCD at address 0x27 (also 0x3F is possible) 16x2 chars
#define SOUND_RESOLUTION 8                      // 8 bit resolution
#define SOUND_ON (1 << (SOUND_RESOLUTION - 1))  // 50% duty cycle
#define SOUND_OFF 0                             // 0% duty cycle

/**************** Multifunction + wemos board *********************/
const int SW1 = 26;        //D2
const int SW2 = 25;        //D3
const int LED1 = 18;       //D13
const int LED2 = 19;       //D12
const int DHTpin = 17;     //D4
const int ROT = 2;         //A0 NOTE: Unable to upload program if potentiometer HIGH. It must be to 0
const int BUZZ = 16;       //D5
const int LM35 = 35;       //A2
const int IR = 27;         //D6
const int R_Led_pin = 13;  //D9
const int G_Led_pin = 23;  //D11
const int B_Led_pin = 5;   //D10
const int R_Led_ch = 1;    //PWM red channel
const int G_Led_ch = 2;    //PWM green channel
const int B_Led_ch = 3;    //PWM blue channel
const int BUZZ_ch = 4;

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
  Serial.begin(9600);

  dht.begin();

/**************** Only OLED ******************/
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
/*********************************************/


/**************** Only LCD ******************/
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);  //(x,y)
  lcd.print("     DISCA      ");
  lcd.setCursor(0, 1);
  lcd.print("0123456789ABCDEF");
/********************************************/

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
  pinMode(LM35, INPUT);
  pinMode(IR, INPUT);


/**************** Only OLED ******************/
  display.clearDisplay();
  // fill rectangle fillRect(xinit, yinit, xend, yend, color)
  display.fillRect(0, 0, display.width(), display.height(), SSD1306_INVERSE);
  display.display();
  delay(1000);
  display.fillRect(4, 4, display.width() - 8, display.height() - 8, SSD1306_INVERSE);
  display.display();  // Update screen with each newly-drawn rectangle
  delay(2000);

  //display.clearDisplay();
  display.setTextSize(2);  // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 8);
  display.println(F("DISCA"));
  display.display();
  delay(100);
/*********************************************/

  Serial.println("Starting the test");
  doTest();

/**************** Only LCD ******************/
  lcd.setCursor(11,0);
  if(!Backlight)
    lcd.print("Off");
  else
    lcd.print("On ");
/********************************************/

}

void loop() {


/**************** Only LCD ******************/
  Button1_State = digitalRead(SW1);
  if ((Button1_State == 0) && (Button1_Old == 1)) {
    Button1_Count++;
    lcd.setCursor(15,0);
    lcd.print(Button1_Count);
  }
  Button1_Old = Button1_State;

  
  lcd.setCursor(11,0);

  if (Button1_Count == 3){
    Backlight=!Backlight;
    if(Backlight){
      lcd.print("On ");
      lcd.backlight();
    }
    else{
      lcd.print("Off");
      lcd.noBacklight();
    }
    Button1_Count=0;
  }
/*************************************************/

  if (Button1_State == 0)
    digitalWrite(LED1, HIGH);

  else
    digitalWrite(LED1, LOW);

  if (!digitalRead(SW2))
    digitalWrite(LED2, HIGH);
  else
    digitalWrite(LED2, LOW);


  int rot = analogRead(ROT);

  if (rot <= 650) {
    ledcWrite(R_Led_ch, 4095);
    ledcWrite(G_Led_ch, rot * 6);
    ledcWrite(B_Led_ch, 0);
  }

  if ((rot > 650) && (rot <= 1300)) {
    ledcWrite(R_Led_ch, 4095 - (rot - 650) * 6);
    ledcWrite(G_Led_ch, 4095);
    ledcWrite(B_Led_ch, 0);
  }

  if ((rot > 1300) && (rot <= 1950)) {
    ledcWrite(R_Led_ch, 0);
    ledcWrite(G_Led_ch, 4095);
    ledcWrite(B_Led_ch, (rot - 1300) * 6);
  }

  if ((rot > 1950) && (rot <= 2600)) {
    ledcWrite(R_Led_ch, 0);
    ledcWrite(G_Led_ch, 4095 - (rot - 1950) * 6);
    ledcWrite(B_Led_ch, 4095);
  }

  if ((rot > 2600) && (rot <= 3250)) {
    ledcWrite(R_Led_ch, (rot - 2600) * 6);
    ledcWrite(G_Led_ch, 0);
    ledcWrite(B_Led_ch, 4095);
  }

  if ((rot > 3250) && (rot <= 3900)) {
    ledcWrite(R_Led_ch, 4095);
    ledcWrite(G_Led_ch, 0);
    ledcWrite(B_Led_ch, 4095 - (rot - 3250) * 6);
  }


  delay(1);
}

void doTest() {
  Serial.println("LED1 test");
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  delay(1000);
  Serial.println("LED2 test");
  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED2, LOW);
  delay(1000);

  Serial.println("RGB test: Red");
  ledcWrite(R_Led_ch, 255);  //test RED
  ledcWrite(G_Led_ch, 0);
  ledcWrite(B_Led_ch, 0);
  delay(1000);

  Serial.println("RGB test: Green");
  ledcWrite(R_Led_ch, 0);
  ledcWrite(G_Led_ch, 255);  //test GREEN
  ledcWrite(B_Led_ch, 0);
  delay(1000);

  Serial.println("RGB test: Blue");
  ledcWrite(R_Led_ch, 0);
  ledcWrite(G_Led_ch, 0);
  ledcWrite(B_Led_ch, 255);  //test BLUE
  delay(1000);
 
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

  Serial.print("LM35 (temperature) test:");
  Serial.println(analogRead(LM35));

  Serial.println("DHT11 (temperature and humidity) test");
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  } else {
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("% Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));
  }
}

void tone(int pin, int frequency, int duration) {
  ledcSetup(BUZZ_ch, frequency, SOUND_RESOLUTION);  // Set up PWM channel
  ledcAttachPin(pin, BUZZ_ch);                      // Attach channel to pin
  ledcWrite(BUZZ_ch, SOUND_ON);
  delay(duration);
  ledcWrite(BUZZ_ch, SOUND_OFF);
}
