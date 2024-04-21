//Libraries
#include <MQ135.h>
#include <DHT.h>
//Sensors
#define GAS_SENSOR A0 //MQ-135
#define TEMP_SENSOR 2 //DHT11
#define LDR_SENSOR A2 //LDR Photo resistor
#define DHTTYPE DHT11
//LED & Fan
#define RED_LED 3
#define YELLOW_LED 5
#define GREEN_LED 6
#define FAN 9

MQ135 mq135_sensor(GAS_SENSOR);
DHT dht(TEMP_SENSOR, DHTTYPE);

float temperature, humidity; // Temp and Humid floats, will be measured by the DHT
int brightness = 0;
void setup() {

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  // Wait a few seconds between measurements.
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
  float hic = dht.computeHeatIndex(temperature, humidity, false);

  Serial.print("MQ135 RZero: ");
  Serial.print(rzero);
  Serial.print("\t Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print("\t Resistance: ");
  Serial.print(resistance);
  Serial.print("\t PPM: ");
  Serial.print(ppm);
  Serial.print("ppm");
  Serial.print("\t Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm");

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.print(F("°C  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));

  Serial.println();
  Serial.println();

  int ldrValue = analogRead(LDR_SENSOR); // Read LDR sensor value
  adjust_Brightness(ldrValue, RED_LED);
  
  delay(300);
}
void adjust_Brightness(int ldrValue, int LED_PIN) {
  


  // Map the LDR sensor value from range 400 to 1023 to the range 0 to 255
  brightness = map(ldrValue, 400, 1023, 0, 255);

  // Limit the brightness value to 0-255 range
  brightness = constrain(brightness, 0, 255);

  // Set the brightness of the LED
  digitalWrite(LED_PIN, brightness);

  //delay(50); // Add a small delay for stability
}
