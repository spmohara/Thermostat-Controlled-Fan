float temp_in_celsius = 0, temp_in_fahrenheit = 0;
const int TxPin = 6;

#include <SoftwareSerial.h>
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);  //LCD settings

void setup()
{
    Serial.begin(9600);
    pinMode(TxPin, OUTPUT);
    digitalWrite(TxPin, HIGH);
    mySerial.begin(9600);
}

void loop()
{
    int fan = 2;
    pinMode(fan, OUTPUT);
  
    //Reads input in mV and converts to Fahrenheit with 500mV offset
    temp_in_fahrenheit = (analogRead(0) - .5) * 100 * 5 / 1024;
    temp_in_celsius = (temp_in_fahrenheit - 32) * 5 / 9;

    //Prints temperature in Fahrenheit to serial port
    Serial.print("temp_in_fahrenheit: ");
    Serial.println(temp_in_fahrenheit);

    //Prints temperature in Celsius to serial port
    Serial.print("temp_in_celsius: ");
    Serial.println(temp_in_celsius);
    Serial.println();

    //If temp in fahrenheit is > 85 deg: fan = on, if temp is < 84 deg: fan = off
    if(temp_in_fahrenheit > 85)
    {
        digitalWrite(fan, HIGH);  //Fan on
    }
    else
    {
        if(temp_in_fahrenheit < 84)  //Fan off
            {
                digitalWrite(fan, LOW);
            }
    }

    //Prints serial data to LCD
    mySerial.write(17);
    mySerial.print("         Fahrenheit   ");
    mySerial.print(13);
    mySerial.print(temp_in_fahrenheit);
    delay(3000);  //3 second delay before program loops
}
