

void WifiConnect_Init();
void WifiConnect_Task();
void WifiConnect_SendToCloud(String variable_name, int value, int pos);
void Ultrasonic_sensor_Init();
void Ultrasonic_sensor_Task(void);
int DHT22_GetData (float *humidity, float* temperature);

void DHT22_Init();


void setup() 
{
  // start serial monitoring
  Serial.begin(115200);
  WifiConnect_Init();
  DHT22_Init();
  //Ultrasonic_sensor_Init();
  
}

void loop()
{
  //long DistanzaCalc;
  float humidity, temperature;
  //Ultrasonic_sensor_Task();
  //Ultrasonic_sensor_GetDistanza(&DistanzaCalc);
  Serial.println();
  //Serial.print("Ultrasonic_sensor_Distanza: ");
  //Serial.print(DistanzaCalc);
  //WifiConnect_SendToCloud("Distanza", DistanzaCalc, 1);
  DHT22_GetData(&humidity, &temperature);
  WifiConnect_SendToCloud("Umidita", humidity*10, 0);
  WifiConnect_SendToCloud("Temperatura", temperature*10, 1);
  WifiConnect_Task();
  DHT22_Task();
  delay(1000);
}
