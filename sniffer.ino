#include <SPI.h>
#include "mcp2515_can.h"
const int SPI_CS_PIN = 10;
mcp2515_can CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println("Ready.");
}

void initCan(int speed) {
  int selectedSpeed;
  switch (speed) {
    case 5:
      selectedSpeed = CAN_5KBPS;
      break;
    case 10:
      selectedSpeed = CAN_10KBPS;
      break;
    case 20:
      selectedSpeed = CAN_20KBPS;
      break;
    case 25:
      selectedSpeed = CAN_25KBPS;
      break;
    case 33:
      selectedSpeed = CAN_33KBPS;
      break;
    case 50:
      selectedSpeed = CAN_50KBPS;
      break;
    case 80:
      selectedSpeed = CAN_80KBPS;
      break;
    case 95:
      selectedSpeed = CAN_95KBPS;
      break;
    case 100:
      selectedSpeed = CAN_100KBPS;
      break;
    case 125:
      selectedSpeed = CAN_125KBPS;
      break;
    case 200:
      selectedSpeed = CAN_200KBPS;
      break;
    case 250:
      selectedSpeed = CAN_250KBPS;
      break;
    case 500:
      selectedSpeed = CAN_500KBPS;
      break;
    case 666:
      selectedSpeed = CAN_666KBPS;
      break;
    case 1000:
      selectedSpeed = CAN_1000KBPS;
      break;
    default:
      Serial.println("Incorrect CAN baudrate specified.");
      return;
  }
  Serial.println("Initializing CAN @ " + String(speed) + "Kbps.");
  int maxTries = 20;
  int tryCount = 0;
  while (CAN_OK != CAN.begin(selectedSpeed)) {
    if (tryCount < maxTries) {
      Serial.println("CAN not ready! Try count: " + String(++tryCount));
      delay(100);
    } else {
      Serial.println("CAN not initialized. Check settings!");
      return;
    }
  }
  Serial.println("CAN Initialized! Sniffing now.");
  delay(2000);
  sniffCan();
}

void sniffCan() {
  while(true) {
    unsigned char len = 0;
    unsigned char buf[8];

    if (CAN_MSGAVAIL == CAN.checkReceive()) {
        CAN.readMsgBuf(&len, buf);
        unsigned long canId = CAN.getCanId();
        Serial.print(canId, HEX);
        Serial.print(":");
        for (int i = 0; i < len; i++) {
            Serial.print(buf[i], HEX);
            if (i != len-1) {
               Serial.print(",");
            }
        }
        Serial.println();
    }
  }
}

void loop() {
  int speed;
  if (Serial.available() > 0) {
    speed = Serial.parseInt();
    if (speed <= 0) {
      Serial.println("Incorrect CAN baudrate specified.");
    } else {
      initCan(speed);
    }
  }
}