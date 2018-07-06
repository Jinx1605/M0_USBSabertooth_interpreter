#include <Arduino.h>   // required before wiring_private.h
#include "wiring_private.h" // pinPeripheral() function
#include <USBSabertooth.h>

Uart Serial2 (&sercom2, 2, 0, SERCOM_RX_PAD_1, UART_TX_PAD_0);
 
void SERCOM2_Handler() {
  Serial2.IrqHandler();
}

USBSabertoothSerial C(Serial2);             // Use SWSerial as the serial port.
USBSabertooth       ST(C, 128);              // Use address 128.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  Serial2.begin(19200);

  // Assign pins 3 & 4 SERCOM functionality
  pinPeripheral(0, PIO_SERCOM_ALT);
  pinPeripheral(2, PIO_SERCOM_ALT);
}

uint8_t i=0;
void loop() {
  // put your main code here, to run repeatedly:
  int power;
  
  // Ramp motor 1 from -2047 to 2047 (full reverse to full forward),
  // waiting 20 ms (1/50th of a second) per step.
  for (power = -2047; power <= 2047; power += 16) {
    ST.motor(1, power);
    Serial.println(power);
    delay(20);
  }
  
  // Now go back the way we came.
  for (power = 2047; power >= -2047; power -= 16) {
    ST.motor(1, power);
    Serial.println(power);
    delay(20);
  }
}
