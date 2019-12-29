# esp8266-Dallas-DS18b20-Blynk
Blynk interface for ESP8266 with Dallas DS18b20 temperature sensor according to the: 
  https://www.hackster.io/mjrobot/iot-made-simple-monitoring-temperature-anywhere-76158c

DS18b20 data (middle) connected to D4 (GPIO2). The 4k7 ohm resistor between the data pin and Vcc (3.3V) 

Software developed by Marcelo Rovai - 05 January 2017

with only one small modification - instead of: 

```
  /* TIMER */
  #include <SimpleTimer.h>
  SimpleTimer timer;
```

Use *BlynkTimer*
