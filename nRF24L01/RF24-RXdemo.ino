/* ------------------------------------------------------------------------- *
- Connections
   - nRF24L01 to Arduino
     1 GND   	  -> GND
     2 VCC	    -> 3V3
     3 CE	      -> D9
     4 CSN/CE	  -> D10
     5 SCK/SDK	-> D13
     6 MOSI/MQ	-> D11
     7 MISO/M1	-> D12
     8 IRQ UNUSED	
 * ---------------------------------------------------------------------------*/

/* Libraries ------------------------------------------------------------------*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/* Ports ---------------------------------------------------------------------*/
#define CE_PIN   9
#define CSN_PIN 10

/* nRF24l01 ------------------------------------------------------------------*/
// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

/* Joystick ------------------------------------------------------------------*/
int joystick[2]; // 2 element array holding Joystick readings
/* ---------------------------------------------------------------------------*/

void setup() {
// Si invita il lettore a utilizzare un display esterno OLED o LCD
  Serial.begin(9600);
  delay(1000);
  Serial.println("nRF24l01 Receiver Starting");
  radio.begin();
  radio.setRetries(0, 15);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1,pipe);                        
  radio.startListening();;
}


void loop() {
  if ( radio.available() ) {
    // Read the data payload until we've received everything
    bool done = false;
    while (!done) {
      // Fetch the data payload
      done = radio.read( joystick, sizeof(joystick));
      Serial.print("X = ");
      Serial.print(joystick[0]);
      Serial.print(" Y = ");      
      Serial.println(joystick[1]);
    }
  }
  else {    
    Serial.println("No radio available");
  }
}