#include <TroykaDHT.h>
DHT dht(4, DHT11);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  
      Serial.print("****************************************\n");
      Serial.print("*Sensor Suhu dan Kelembaban\n*Berbasis Arduino dan DHT11\n*BY RizkyX12\n");
      Serial.print("*****************************************\n\n");
      delay(1000);
}

void loop()
{

  dht.read();
  
  switch(dht.getState()) {
    
    case DHT_OK:
      Serial.print("Temperatur = ");
      Serial.print(dht.getTemperatureC());
      Serial.println(" C \t");
      Serial.print("Temperatur = ");
      Serial.print(dht.getTemperatureK());
      Serial.println(" K \t");
      Serial.print("Temperatur = ");
      Serial.print(dht.getTemperatureF());
      Serial.println(" F \t");
      Serial.print("Kelembaban = ");
      Serial.print(dht.getHumidity());
      Serial.println(" %\n\n");
      break;
    
    case DHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    
    case DHT_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    
    case DHT_ERROR_NO_REPLY:
      Serial.println("Sensor not connected");
      break;
  }
  
  
  delay(2000);
}
