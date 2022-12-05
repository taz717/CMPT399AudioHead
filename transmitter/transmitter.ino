#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
// drive 12

// "/char incomingByte ; // for incoming serial data /"

char incomingByte;

RH_ASK driver;

void setup()
{
    Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
    if (!driver.init())
        Serial.println("init failed");
}

void loop()
{

    // send data only when you receive data:
    if (Serial.available() > 0)
    {
        // read the incoming byte:
        incomingByte = Serial.read();

        if (incomingByte == 'f')
        {
            driver.send((uint8_t *)"f", (1));
        }
        if (incomingByte == 'b')
        {
            driver.send((uint8_t *)"b", (1));
        }
        if (incomingByte == 'l')
        {
            driver.send((uint8_t *)"l", (1));
        }
        if (incomingByte == 'r')
        {
            driver.send((uint8_t *)"r", (1));
        }

        // say what you got:
        Serial.print("I received: ");
        Serial.println(incomingByte);
        // Serial.print(strlen(incomingByte));

        // Serial.println("works");
        // const char *msg = "Hello World!";
        // driver.send((uint8_t *)incomingByte, (6));
        driver.waitPacketSent();
        delay(5000);

        // driver.send((uint8_t *)stop, strlen(stop));
        // driver.waitPacketSent();
        // delay(5000);
    }

    // const char *msg = "Hello World!";
    //     driver.send((uint8_t *)msg, strlen(msg));
    //     driver.waitPacketSent();
    //     delay(5000);
}
