#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

#include <U8g2lib.h>

Adafruit_BME280 bme; // I2C

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

unsigned long delayTime;

void setup() {
    Serial.begin(9600);
    u8g2.begin();
    Serial.println(F("BME280 test"));
    bool status;
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 1000;
    Serial.println();
}

void loop() { 
    printValues();
    u8g2.setFont(u8g2_font_courR14_tf);
    u8g2.firstPage();
    do {
      u8g2.setCursor(0, 20);
      u8g2.print("Temperatur:");
      u8g2.setCursor(32, 50);
      u8g2.print(bme.readTemperature());

      } while ( u8g2.nextPage() );
    delay(delayTime);
}

void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    Serial.println();
}
