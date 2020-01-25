/**************************************************************
 * IoT Temperature Monitor with Blynk plus PIR sensor 
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 * 
 * Developed by Marcelo Rovai - 05 January 2017
 **************************************************************/

/* ESP & Blynk */
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
char auth[] = "9#########################################OG";

/* WiFi credentials */
char ssid[] = "MYSSID";
char pass[] = "PERPLEXINGWIFIPASSWORD";

BlynkTimer timer;

/* DS18B20 Temperature Sensor */
#include <OneWire.h>
#include<DallasTemperature.h> 
#define ONE_WIRE_BUS 2 // DS18B20 on arduino pin2 corresponds to D4 on physical board
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float temp;

int extraLED = 12;  //ESP8233 PIN D7
int PIRsensor = 13; //ESP8233 PIN D6 


void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  DS18B20.begin();
  pinMode(PIRsensor, INPUT); // declare sensor as input
  pinMode(extraLED, OUTPUT);  // declare LED as output
  timer.setInterval(1000L, getSendData);

}

void loop() 
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}

/***************************************************
 * Send Sensor data to Blynk
 **************************************************/
void getSendData()
{
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0);
  Serial.println(temp);
  Blynk.virtualWrite(10, temp); //virtual pin V10
  long state = digitalRead(PIRsensor);
  delay(200);
  if(state == HIGH){
     digitalWrite (extraLED, HIGH); //switch LED on
     Blynk.virtualWrite(11, 1);     //virtual pin 11
  }
  else {
    digitalWrite(extraLED, LOW);    //switch LED off
    Blynk.virtualWrite(11,0);       //virtual pin 11
  }
}
