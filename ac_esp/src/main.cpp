#include <Arduino.h>

//lcd
#include <LiquidCrystal_I2C.h>
//DHT
#include <DHT.h>  // library for getting data from DHT

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//LCD and Buttons
#define Button_Plus 13 // button is connected with gpio 22 (PURPLE WIRE)
#define Button_Minus 9 // button is connected with gpio 10 (PURPLE WIRE)
int count =0;

//LED
#define LED 12  

//FAN
const int FanPin = 10;  // corresponds to GPIO9
  // setting PWM properties
const int freq = 5000;
const int FanChannel = 0;
const int resolution = 8;

//DHT
#define DHTPIN 4        //pin where the DHT11 is connected - connect to 5V
DHT dht(DHTPIN, DHT11);


void setup() {
  Serial.begin(115200);
  //LED
  pinMode(LED, OUTPUT);
  
  //LCD and buttons
  pinMode(Button_Plus, INPUT_PULLUP);
  pinMode(Button_Minus, INPUT_PULLUP);
  lcd.begin();  
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("econHOMEic");
  lcd.setCursor(4,1);
  lcd.print("welcome");
  delay(1500);
  lcd.clear();// clear previous values from screen

  //DHT 
  dht.begin();

  //FAN
    // configure LED PWM functionalitites
  ledcSetup(FanChannel, freq, resolution);
    // attach the channel to the GPIO to be controlled
  ledcAttachPin(FanPin, FanChannel);
}


void loop() {
  //LCD and buttons
  int ButtonStatePlus = digitalRead(Button_Plus); // read the button pin and store in ButtonState variable
  int ButtonStateMinus = digitalRead(Button_Minus); // read the button pin and store in ButtonState variable
  if(ButtonStatePlus == HIGH)  // if button plus is pressed
  {
    lcd.clear();// clear previous values from screen
    count++;
    lcd.print(count);
    delay(500);
    digitalWrite(LED,LOW); // led will be ON
    Serial.print("PLUS if Loop -> Count: ");
    Serial.print(count);
    Serial.println(" HIGH");
  }
  else   // otherwise
  {
    digitalWrite(LED, HIGH); // LED will be OFF
    Serial.print("PLUS else Loop -> Count: ");
    Serial.print(count);
    Serial.println(" LOW");
  }
  
  if(ButtonStateMinus == HIGH)  // if button minnus is pressed
  {
    lcd.clear();// clear previous values from screen
    count--;
    lcd.print(count);
    delay(500);
    digitalWrite(LED,LOW); // led will be ON
    Serial.print("MINUS if Loop -> Count: ");
    Serial.print(count);
    Serial.println(" HIGH");
  }
  else   // otherwise
  {
    digitalWrite(LED, HIGH); // LED will be OFF
    Serial.print("MINUS else Loop -> Count: ");
    Serial.print(count);
    Serial.println(" LOW");
  }

  //FAN
   ledcWrite(FanChannel, 150);
   delay(3000);
   ledcWrite(FanChannel, 255);
   delay(3000);

  //DHT
//  float h = dht.readHumidity();   // Reading Temperature form DHT sensor
//  float t = dht.readTemperature();      // Reading Humidity form DHT sensor
//  float tF = (t * 1.8) + 32;
//  if (isnan(h) || isnan(t))
//  {
//    Serial.println("Failed to read from DHT sensor!");
//  }
//  else{
//    Serial.println("Temprature: %f \n Humidity: %f", t, h);
//  }


  //DHT Temrature sensor
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}