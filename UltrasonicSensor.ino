const int triggerPort = 4;
const int echoPort = 5;

long Ultrasonic_sensor_Distanza;

void Ultrasonic_sensor_Init(void)
{
  pinMode(triggerPort, OUTPUT);
  pinMode(echoPort, INPUT);
  //Serial.print( "Sensore Ultrasuoni: ");
}

void Ultrasonic_sensor_Task(void)
{
  long durata; 
  
  //porta bassa l'uscita del trigger
  digitalWrite( triggerPort, LOW );
  //invia un impulso di 10microsec su trigger
  digitalWrite( triggerPort, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( triggerPort, LOW );
  
  durata = pulseIn( echoPort, HIGH );
  Ultrasonic_sensor_Distanza = 0.034 * durata / 2;
}

int Ultrasonic_sensor_GetDistanza (long *distanza)
{
  *distanza = Ultrasonic_sensor_Distanza;
  return 0;
}
