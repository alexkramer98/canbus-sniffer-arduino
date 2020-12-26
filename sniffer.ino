#include <SPI.h>
#include "mcp2515_can.h"
const int SPI_CS_PIN = 10;
mcp2515_can CAN(SPI_CS_PIN);

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing.");
    while (CAN_OK != CAN.begin(CAN_50KBPS)) {}
    Serial.println("Intialized.");
}


void loop() {
    unsigned char length = 0;
    unsigned char buffer[8];

    if (CAN_MSGAVAIL == CAN.checkReceive()) {
        CAN.readMsgBuf(&length, buffer);
        unsigned long canId = CAN.getCanId();
        Serial.print(canId, HEX);
        Serial.print(":");
        for (int i = 0; i < length; i++) {
            Serial.print(buffer[i], HEX);
            if (i != length-1) {
               Serial.print(",");
            }
        }
        Serial.println();
    }
}
