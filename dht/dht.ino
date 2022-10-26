#include <TroykaDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;   
DHT dht11(pinDHT11, DHT11);
int lampu = 3;
int kipas = 4;

void setup() {
  Serial.begin(115200);
  dht11.begin();
}

void loop() {
  dht11.read();
  int h = dht11.getHumidity();
  int t = dht11.getTemperatureC();
  
    Serial.print("Temperature = ");
      Serial.print(t);
      Serial.print(" C \t");

    Serial.print("Humidity = ");
      Serial.print(h);
      Serial.println(" % \t");

  delay(100);
  
  }
