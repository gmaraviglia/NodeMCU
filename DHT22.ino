#include "DHT.h"


#define DHTPIN 2     
#define DHTTYPE DHT22   
#define fan 4

DHT dht(DHTPIN, DHTTYPE);

float Humidity;
float Temperature;

void DHT22_Init() {
  dht.begin();
}

int DHT22_GetData (float *humidity, float* temperature)
{
  *humidity = Humidity;
  *temperature = Temperature;
  return 0;
}

void DHT22_Task() {
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();
  Serial.print("Umidita': "); 
  Serial.print(Humidity);
  Serial.print(" %\t");
  Serial.print("Temperatura: "); 
  Serial.print(Temperature);
  Serial.println(" *C ");
}
