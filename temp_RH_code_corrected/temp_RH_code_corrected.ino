#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 9, 8, 7, 6);

#include "DHT.h"

#define DHTPIN 5     // what pin we're connected to

//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)

// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
/* NOTE: For working with a faster chip, like an Arduino Due or Teensy, you
   might need to increase the threshold for cycle counts considered a 1 or 0.
   You can do this by passing a 3rd parameter for this threshold.  It's a bit
   of fiddling to find the right value, but in general the faster the CPU the
   higher the value.  The default for a 16mhz AVR is a value of 6.  For an
   Arduino Due that runs at 84mhz a value of 30 works.
   Example to initialize DHT sensor for Arduino Due:
   DHT dht(DHTPIN, DHTTYPE, 30); */

#include <Wire.h>                                               //setup BMP180 sensor
#include <Adafruit_Sensor.h>                                    //BMP180 (A4, A5), (SDA, SCL)
#include <Adafruit_BMP085_U.h>
   
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

int tempPin = 0;           // Definimos la entrada de sensor LM35 en pin A1
float tempC;               // variable para el numero de grados centigrados

                                    //Setup para el modulo tiempo real
#include <DS1302.h>

                                    // Definir pines para el modulo tiempo real.
DS1302 rtc(2, 3, 4);                //2-RST, 3-IO, 4-SCK
Time ti;                             //t como variable de tiempo donde se va a almacenar las lecturas

void setup()
{
                           // Abre puerto serial y lo configura a 9600 baud
    Serial.begin(9600);
    dht.begin();           //comienza las lecturas de sensor DHT11
    lcd.begin(16,2);
    lcd.print("T=      Hr=");
    lcd.setCursor(0,1);
    lcd.print("P=");
  
  if(!bmp.begin())              // revisa sensor BMP180
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

}
void loop()
{
                           // Lee el valor desde el sensor
/*    tempC = analogRead(tempPin); 

                           // Convierte el valor a temperatura
    tempC = (5.0 * tempC * 100.0)/1024.0; 
    //float tempC4 = (tempC * 16); */

  /* Reading temperature or humidity takes about 250 milliseconds!
     Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)*/
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  ti = rtc.getTime();          // Obtencion de datos del reloj en tiempo real

  /* Get a new sensor event */ 
  sensors_event_t event;
  bmp.getEvent(&event);
 
  /* Display the results (barometric pressure is measure in hPa) 
  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
 
    /* First we get the current temperature from the BMP085
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C"); */

    /* Then convert the atmospheric pressure, SLP and temp to altitude    
    /* Update this next line with the current SLP for better results      
    float seaLevelPressure = 1029;
    Serial.print("Altitude:    "); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure,
                                        tempC)); 
    Serial.println(" m");
    Serial.println("");
  }
  else
  {
    Serial.println("Sensor error");
  } */
  
    // Envia el dato al puerto serial
  /*Serial.print("Temperatura2 ");
    Serial.print(t);
    Serial.print(", Humedad ");
    Serial.print(h);
    Serial.print(", grados Celsius ");
    Serial.println(tempC);
    */
    float seaLevelPressure = 1019;
        float temperature;
    bmp.getTemperature(&temperature);
   
  Serial.print(t);
  Serial.print(" C, ");
/*Serial.print(temperature);
  Serial.print(" C BMP180, ");
  Serial.print(t);
  Serial.print(" C DHT22, ");
*/Serial.print(h);
  Serial.print(" %Hr, ");
  Serial.print(event.pressure);
  Serial.print(" hPa, ");
  Serial.print(bmp.pressureToAltitude(seaLevelPressure,event.pressure,temperature));
  Serial.print(" msnm, ");
  Serial.print(ti.hour,DEC);
  Serial.print(":");
  Serial.println(ti.min, DEC);
  /*Serial.print(":");
  Serial.print(ti.sec, DEC);
  Serial.print(" ");
  Serial.print(ti.mon,DEC);
  Serial.print("/");
  Serial.print(ti.date, DEC);
  Serial.print("/");
  Serial.println(ti.year);*/
  
    
    lcd.setCursor(2,0);
    lcd.print(t);
    lcd.setCursor(11,0);
    lcd.print(h);  
    lcd.setCursor(2,1);
    lcd.print(event.pressure); 
    lcd.setCursor(10,1);
    lcd.print(ti.hour, DEC);
    lcd.setCursor(12,1);
    lcd.print(":");    
    lcd.setCursor(13,1);
    lcd.print(ti.min, DEC);
    
    delay(5000);                // Espera algún tiempo para repetir la medicion
}
