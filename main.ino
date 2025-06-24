#include <DHT.h>

#define MQ2_PIN A0
#define MQ7_PIN A1
#define MQ135_PIN A2

#define DHT_PIN 2
#define DHT_TYPE DHT11

#define LED_GREEN 10
#define LED_RED 11

#define MQ_THRESHOLD 300
#define TEMP_MIN 18
#define TEMP_MAX 30
#define HUM_MIN 30
#define HUM_MAX 60

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop() {
  int mq2 = analogRead(MQ2_PIN);
  int mq7 = analogRead(MQ7_PIN);
  int mq135 = analogRead(MQ135_PIN);

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  bool alert = false;

  if (mq2 > MQ_THRESHOLD || mq7 > MQ_THRESHOLD || mq135 > MQ_THRESHOLD) {
    alert = true;
  }

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Error!");
    alert = true;
  } else if (temp < TEMP_MIN || temp > TEMP_MAX || hum < HUM_MIN || hum > HUM_MAX) {
    alert = true;
  }

  if (alert) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
  } else {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  }

  Serial.print("MQ2: "); Serial.print(mq2);
  Serial.print(" | MQ7: "); Serial.print(mq7);
  Serial.print(" | MQ135: "); Serial.print(mq135);
  Serial.print(" | Temp: "); Serial.print(temp);
  Serial.print(" | Hum: "); Serial.println(hum);

  delay(2000); 
}
