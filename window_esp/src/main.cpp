#include <Arduino.h>

#include "SPIFFS.h"
//#include <WiFiClientSecure.h>
//#include <PubSubClient.h>
#include <Servo_ESP32.h>
#include <string> 




// Enter your WiFi ssid and password
//const char* ssid = "Kilker"; //Provide your SSID
//const char* password = "0549932593"; // Provide Password
//const char* mqtt_server = "a3a4qqsp3xsqud-ats.iot.eu-west-1.amazonaws.com"; // Relace with your MQTT END point
//const int   mqtt_port = 8883;





//
//String Read_rootca;
//String Read_cert;
//String Read_privatekey;
//#define BUFFER_LEN 256
//long lastMsg = 0;
//char msg[BUFFER_LEN];
//char msg_2[BUFFER_LEN];
//char msg_3[BUFFER_LEN];
//int Value = 0;
//byte mac[6];
//char mac_Id[18];
//int count = 1;


//WiFiClientSecure espClient;
//PubSubClient client(espClient);

//LED
int LEDpin = 19; //connect to 3.3V

//PIR
int PIRpin = 12; //connect to 5V

//LIGHT
int LIGHTpin = 10; //connect to 3.3V

//Servo
static const int servoPin = 14; //printed G14 on the board - connect to 5V
Servo_ESP32 servo1;
//int i=0;
int angle =0;
int angleStep = 5;
int angleMin =0;
int angleMax = 180;


//void setup_wifi() {
//  delay(10);
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//
//
//  WiFi.begin(ssid, password);
//
//
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//
//
//  randomSeed(micros());
//
//
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
//}


//void callback(char* topic, byte* payload, unsigned int length) {
//  String topicStr = topic;
//  std::string payload_ =(char*)payload;
//  String m =mac_Id;
//  String pubTopic = "sensors/" + m;
//  String subWindowTopic ="jobs/" + m +"/window/state";
//  String subLightsTopic ="jobs/" + m+"/lights/state";
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
//  for (int i = 0; i < length; i++) {
//    Serial.print((char)payload[i]);
//  }
//  Serial.println();
//
//
//  if(topicStr==subWindowTopic){
//      //Servo   
//      if(payload_.find("open")!=std::string::npos){
//       for(int angle = 180; angle >= angleMin; angle -=angleStep) {
//       servo1.write(angle);
//       delay(20);}
//       Serial.println("open window");
//       pubTopic= "sensors/" + m+"/window/status";
//        snprintf(msg, BUFFER_LEN, "{\"mac_Id\" : \"%s\", \"type\" : \"window\", \"status\" : \"open\"}", m.c_str());
//       client.publish(pubTopic.c_str(), msg);
//      }
//      else{
//        for(int angle = 0; angle <= angleMax; angle +=angleStep) {
//       servo1.write(angle);
//       delay(20);}
//       Serial.println("close window");
//       
//       pubTopic= "sensors/" + m+"/window/status";
//        snprintf(msg, BUFFER_LEN, "{\"mac_Id\" : \"%s\", \"type\" : \"window\", \"status\" : \"close\"}", m.c_str());
//       client.publish(pubTopic.c_str(), msg);
//        
//      }}
//    
//  if(topicStr==subLightsTopic){
//    if(payload_.find("on")!=std::string::npos){
//      digitalWrite(LEDpin, LOW);
//  Serial.println("light on");
//  pubTopic= "sensors/" + m+"/lights/status";
//  snprintf(msg, BUFFER_LEN, "{\"mac_Id\" : \"%s\", \"type\" : \"light\", \"status\" : \"on\"}", m.c_str());
//  client.publish(pubTopic.c_str(), msg);
//      }
//      else{
//        digitalWrite(LEDpin, HIGH);
//  Serial.println("light off");
//  pubTopic= "sensors/" + m+"/lights/status";
//  snprintf(msg, BUFFER_LEN, "{\"mac_Id\" : \"%s\", \"type\" : \"light\", \"status\" : \"off\"}", m.c_str());
//  client.publish(pubTopic.c_str(), msg);
//        }
//    
//  
//  }
//  
//  }
//
//
// 
//
//
//void reconnect() {
//    String m =mac_Id;
//    String msg="";
//  String subWindowTopic ="jobs/" + m +"/window/state";
//  String subLightsTopic ="jobs/" + m+"/lights/state";
//  // Loop until we're reconnected
//  while (!client.connected()) {
//    Serial.print("Attempting MQTT connection...");
//    // Create a random client ID
//    String clientId = "ESP32-";
//    clientId += String(random(0xffff), HEX);
//    // Attempt to connect
//    if (client.connect(clientId.c_str())) {
//      Serial.println("connected");
//      // Once connected, publish an announcement...
//      client.publish("ei_out", "hello world");
//      // ... and resubscribe
//      client.subscribe("ei_in");
//    client.subscribe(subWindowTopic.c_str());
//    client.subscribe(subLightsTopic.c_str());
//    } else {
//      Serial.print("failed, rc=");
//      Serial.print(client.state());
//      Serial.println(" try again in 5 seconds");
//      // Wait 5 seconds before retrying
//      delay(5000);
//    }
//  }
//}


void setup() {
  Serial.begin(115200);
  
//PIR Sensor
  pinMode(PIRpin,INPUT);
    
//Servo
  servo1.attach(servoPin);

//Light sensor
  delay(1000);

//LED
  pinMode (LEDpin,OUTPUT);

  
//  setup_wifi();
//  delay(1000);
//  //=============================================================
//  if (!SPIFFS.begin(true)) {
//    Serial.println("An Error has occurred while mounting SPIFFS");
//    return;
//  }
//  //=======================================
//  //Root CA File Reading.
//  File file2 = SPIFFS.open("/AmazonRootCA1.pem", "r");
//  if (!file2) {
//    Serial.println("Failed to open file for reading");
//    return;
//  }
//  Serial.println("Root CA File Content:");
//  while (file2.available()) {
//    Read_rootca = file2.readString();
//    Serial.println(Read_rootca);
//  }
//  //=============================================
//  // Cert file reading
//  File file4 = SPIFFS.open("/0259afaea0-certificate.pem.crt", "r");
//  if (!file4) {
//    Serial.println("Failed to open file for reading");
//    return;
//  }
//  Serial.println("Cert File Content:");
//  while (file4.available()) {
//    Read_cert = file4.readString();
//    Serial.println(Read_cert);
//  }
//  //=================================================
//  //Privatekey file reading
//  File file6 = SPIFFS.open("/0259afaea0-private.pem.key", "r");
//  if (!file6) {
//    Serial.println("Failed to open file for reading");
//    return;
//  }
//  Serial.println("privateKey File Content:");
//  while (file6.available()) {
//    Read_privatekey = file6.readString();
//    Serial.println(Read_privatekey);
//  }
//  //=====================================================
//
//
//  char* pRead_rootca;
//  pRead_rootca = (char *)malloc(sizeof(char) * (Read_rootca.length() + 1));
//  strcpy(pRead_rootca, Read_rootca.c_str());
//
//
//  char* pRead_cert;
//  pRead_cert = (char *)malloc(sizeof(char) * (Read_cert.length() + 1));
//  strcpy(pRead_cert, Read_cert.c_str());
//
//
//  char* pRead_privatekey;
//  pRead_privatekey = (char *)malloc(sizeof(char) * (Read_privatekey.length() + 1));
//  strcpy(pRead_privatekey, Read_privatekey.c_str());
//
//
//  Serial.println("================================================================================================");
//  Serial.println("Certificates that passing to espClient Method");
//  Serial.println();
//  Serial.println("Root CA:");
//  Serial.write(pRead_rootca);
//  Serial.println("================================================================================================");
//  Serial.println();
//  Serial.println("Cert:");
//  Serial.write(pRead_cert);
//  Serial.println("================================================================================================");
//  Serial.println();
//  Serial.println("privateKey:");
//  Serial.write(pRead_privatekey);
//  Serial.println("================================================================================================");
//
//
//  espClient.setCACert(pRead_rootca);
//  espClient.setCertificate(pRead_cert);
//  espClient.setPrivateKey(pRead_privatekey);
//
//
//  client.setServer(mqtt_server, mqtt_port);
//  client.setCallback(callback);
//
//
//  //====================================================================================================================
//  WiFi.macAddress(mac);
//  snprintf(mac_Id, sizeof(mac_Id), "%02x:%02x:%02x:%02x:%02x:%02x",
//           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
//  Serial.print(mac_Id);
//  //=====================================================================================================================
//  delay(2000);
}




void loop() {
//  String m = mac_Id;
//  String pubTopic = "sensors/" +  m;
//  String pubTempTopic = pubTopic;

  //PIR Sensor
  int pir= digitalRead(PIRpin);
  Serial.println(pir);
  delay(1000);

  //Light sensor
  int LDR_val=analogRead(LIGHTpin);
  Serial.println(LDR_val);
  delay(100);

  //Servo
   for(int angle = 180; angle >= angleMin; angle -=angleStep) {
    servo1.write(angle);
    delay(20);
   }
   Serial.println("open window");
   for(int angle = 0; angle <= angleMax; angle +=angleStep) {
    servo1.write(angle);
    delay(20);
   }
   Serial.println("close window");

//  if (!client.connected()) {
//    reconnect();
//  }
//  client.loop();


//  long now = millis();
//  if (now - lastMsg > 2000) {
//    lastMsg = now;
//    //=============================================================================================
//    String macIdStr = mac_Id;
//    String Temprature = String(t);
//    String Humidity = String(h);
//    snprintf(msg, BUFFER_LEN, "{\"mac_Id\" : \"%s\", \"Temprature\" : %s, \"Humidity\" : \"%s\"}", macIdStr.c_str(), Temprature.c_str(), Humidity.c_str());
//    pubTempTopic= pubTopic+"/temp";
//    client.publish(pubTempTopic.c_str(), msg);
//    Serial.print("Publish message: ");
//    Serial.print(count);
//    Serial.println(msg);
//    delay(2000);
//     count = count + 1;
//    //==============================================================================================
//   snprintf(msg_2, BUFFER_LEN, "{\"mac_Id\" : \"%s\", \"motion\" : %d}", macIdStr.c_str(), pir);
//   pubTempTopic= pubTopic+"/motion";
//    client.publish(pubTempTopic.c_str(), msg_2);
//    Serial.print("Publish message: ");
//    Serial.print(count);
//    Serial.println(msg_2);
//    delay(2000);
// count = count + 1;
//    //==============================================================================================
////    char msg3[BUFFER_LEN];
//    snprintf(msg_3, BUFFER_LEN, "{\"mac_Id\" : \"%s\", \"LDR_val\" : %d}", macIdStr.c_str(), LDR_val);
//    pubTempTopic= pubTopic+"/LDR";
//    client.publish(pubTempTopic.c_str(), msg_3);
//    Serial.print("Publish message: ");
//    Serial.print(count);
//    Serial.println(msg_3);
//    count = count + 1;
//    //================================================================================================
//    
//  }
}
