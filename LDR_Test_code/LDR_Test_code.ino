// Incluir las librerías necesarias
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// Definir los pines que se utilizarán
#define LDR_PIN A0
#define MOTOR_PIN 9

// Crear el objeto del sensor de luz
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void setup() {
  // Iniciar la comunicación serial a una velocidad de 9600 baudios
  Serial.begin(9600);
  
  // Iniciar el sensor de luz
  if(!tsl.begin()) {
    Serial.println("No se pudo iniciar el sensor de luz");
    while(1);
  }
  
  // Configurar el rango dinámico del sensor de luz (valores posibles: TSL2561_GAIN_0X, TSL2561_GAIN_16X)
  tsl.setGain(TSL2561_GAIN_16X);
  
  // Configurar el tiempo de integración del sensor de luz (valores posibles: TSL2561_INTEGRATIONTIME_13MS, TSL2561_INTEGRATIONTIME_101MS, TSL2561_INTEGRATIONTIME_402MS)
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);

  // Configurar el pin del motor como salida
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  // Leer el valor del LDR
  int ldrValue = analogRead(LDR_PIN);
  
  // Leer el valor de luz del sensor de luz
  sensors_event_t event;
  tsl.getEvent(&event);
  float light = event.light;
  
  // Si el valor de luz es menor que el valor del LDR, encender el motor
  if (light < ldrValue) {
    digitalWrite(MOTOR_PIN, HIGH);
  } else {
    digitalWrite(MOTOR_PIN, LOW);
  }
  
  // Imprimir los valores en el monitor serial
  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.print(", Luz: ");
  Serial.print(light);
  Serial.println();
  
  // Esperar 500ms antes de volver a leer los valores
  delay(500);
}
