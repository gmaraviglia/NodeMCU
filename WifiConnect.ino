#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define LIST_SIZE 5

#define FIREBASE_HOST "https://esp8266-42777.firebaseio.com/"
#define FIREBASE_AUTH "token_or_secret"
 
const char* ssid     = "LACASA";
const char* password = "peppemara";

char server[]  = "www.ic2pro.com";                          
int port       = 80;
String devId   = "6a16c5d7-7b96-4f51-b675-16786c15b9e1";              
String auth    = "cGVwcGVtYXJhODNAaG90bWFpbC5jb206c29za29kYXBwYTYy";  

WiFiClient client; 

typedef struct
{
  boolean Active;
  String  Variable_Name;
  int     Value;
}List_t;

List_t DataToCloud[LIST_SIZE];

void StartWiFi(void)
{
  // We start by connecting to a WiFi network 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void WifiConnect_Init(void)
{
  StartWiFi();
}

void WifiConnect_SendToCloud(String variable_name, int value, int pos)
{
  DataToCloud[pos].Active = true;
  DataToCloud[pos].Variable_Name = variable_name;
  DataToCloud[pos].Value = value;
  //Serial.println("DataToCloud[pos].Variable_Name = ");
  //Serial.print("Variable_Name = ");
}

void WifiConnect_Task ()
{
  int connection = 0;
  // Use WiFiClient class to create TCP connections
  const int httpPort = 80;
  //Serial.println(range);
  connection = client.connect(server, httpPort);
  //Serial.println(connection);
  if (!connection) {
    Serial.println("connection failed");
  }
  else
  {  
    //Serial.println("connection OK");
    client.println("GET http://" + String(server) + ":" + String(port) + "/Wire/connector/set?id=" + devId + 
                   "&DataToCloud[0].Variable_Name=" + DataToCloud[0].Value+ 
                   "&" + DataToCloud[0].Variable_Name + "=" + DataToCloud[0].Value+ 
                   "&" + DataToCloud[1].Variable_Name + "=" + DataToCloud[1].Value+ 
                   "&" + DataToCloud[2].Variable_Name + "=" + DataToCloud[2].Value+ 
                   "&" + DataToCloud[3].Variable_Name + "=" + DataToCloud[3].Value+ 
                   "&" + DataToCloud[4].Variable_Name + "=" + DataToCloud[4].Value+ 
                   " HTTP/1.1");   // submit HTTP request
    client.println("Authorization: Basic " + auth);
    client.println("Connection: close");
    client.println();
    client.stop();
    Firebase.setInt(DataToCloud[0].Variable_Name, DataToCloud[0].Value);
    Firebase.setInt(DataToCloud[1].Variable_Name, DataToCloud[1].Value);
    Firebase.setInt("prova", 22);
    
  }
}

//void WifiConnect_Task (String variable, int value)
//{
//  int connection = 0;
//  // Use WiFiClient class to create TCP connections
//  const int httpPort = 80;
//  //Serial.println(range);
//  connection = client.connect(server, httpPort);
//  //Serial.println(connection);
//  if (!connection) {
//    Serial.println("connection failed");
//  }
//  else
//  {  // connect to server
//    client.println("GET http://" + String(server) + ":" + String(port) + "/Wire/connector/set?id=" + devId + "&variable=" + value+ " HTTP/1.1");   // submit HTTP request
//    client.println("Authorization: Basic " + auth);
//    client.println("Connection: close");
//    client.println();
//    client.stop();
//  }
//}
