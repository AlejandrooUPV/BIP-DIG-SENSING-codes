#include <Wire.h>               //Librería para comunicación I2C
#include <LiquidCrystal_I2C.h>  //Librería para controlar el LCD I2C

//Inicialización del objeto para controlar el LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); //Dirección del LCD, número de columnas y filas

void setup()
{
  Wire.begin();         //Inicialización del bus I2C
  lcd.init();           //Inicialización del LCD
  lcd.backlight();      //Encender la luz de fondo del LCD
  lcd.setCursor(0, 0);  //Colocar el cursor en la posición 0,0
  lcd.print("Hola mundo!"); //Escribir "Hola mundo!" en el LCD
}

void loop()
{
  //No hay nada que hacer en el loop
}