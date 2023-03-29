#define LED_R 12
#define LED_G 14
#define LED_B 27


void setup() {
  // Configuramos los pines de los LEDs RGB como salidas
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() {
  // Encendemos el LED rojo
  digitalWrite(LED_R, HIGH);
  delay(1000);

  // Encendemos el LED verde y apagamos el LED rojo
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);
  delay(1000);

  // Encendemos el LED azul y apagamos el LED verde
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, HIGH);
  delay(1000);

  // Apagamos todos los LEDs
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_B, LOW);
  delay(1000);
}