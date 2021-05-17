#include <Arduino.h>

//water temprature
#include <OneWire.h>
#include <DallasTemperature.h>

//waterflow
#include "SPIFFS.h"
#include <SPI.h>
#include <Wire.h>



//the relays connect to
int IN1 = 4;
//int IN2 = 5;
#define ON 0
#define OFF 1

//Water temprature
#define ONE_WIRE_BUS 15
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float Celcius=0;
float Fahrenheit=0;

//Pump
int is_pump_on = 0;
#define Button_Pump 14 // button is connected with gpio 14 (PURPLE WIRE)

//Waterflow
#define WATERFLOWpin 27
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned long flowMilliLitres;
unsigned int totalMilliLitres;
float flowLitres;
float totalLitres;

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void relay_init(void);
void relay_SetStatus( unsigned char status_1, unsigned char status_2);

void setup() {
  Serial.begin(115200);
  
  //Water temprature
  sensors.begin(); 

  //WaterFlow Sensor
  pinMode(WATERFLOWpin, INPUT_PULLUP);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(WATERFLOWpin), pulseCounter, FALLING);
  
  //Relay
  relay_init();//initialize the relay
  
  //Button Pump
  pinMode(Button_Pump, INPUT_PULLUP);
}


void loop() {

//Pump Button
  int ButtonStatePump = digitalRead(Button_Pump); // read the Button_Pump pin and store in ButtonStatePump variable
  if(ButtonStatePump == HIGH)  // if button is pressed
  {
    if(is_pump_on == 0){
      Serial.println("pump on");
      relay_SetStatus(ON, OFF);//turn on RELAY_1
      is_pump_on =1;
    }
    else{
      Serial.println("pump off");
      relay_SetStatus(OFF, OFF);//turn off RELAY_1
      is_pump_on =0;
    }
    Serial.println("pump buuton pressed");
  }
  
  
  // Water temprature
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  Fahrenheit=sensors.toFahrenheit(Celcius);
  Serial.print(" C  ");
  Serial.print(Celcius);
  Serial.print(" F  ");
  Serial.println(Fahrenheit);
  delay(1000);

   //Water Flow
  currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {

    pulse1Sec = pulseCount;
    pulseCount = 0;

    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();

    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;
    flowLitres = (flowRate / 60);

    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
    totalLitres += flowLitres;

    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(float(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space


    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalLitres);
    Serial.println("L");
  
  //delay(1000);
  }
}

void relay_init(void)//initialize the relay
{
 //set all the relays OUTPUT
 pinMode(IN1, OUTPUT);
// pinMode(IN2, OUTPUT);
 relay_SetStatus(OFF, OFF); //turn off all the relay
}

//set the status of relays
void relay_SetStatus( unsigned char status_1, unsigned char status_2)
{
 digitalWrite(IN1, status_1);
// digitalWrite(IN2, status_2);
}