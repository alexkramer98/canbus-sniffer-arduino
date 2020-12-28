int ids[50];
int allowedSpeeds[] = {5,10,20,25,33,50,80,95,100,125,200,250,500,666,1000};

void setup() {
  Serial.begin(115200);
  Serial.println("Ready.");
  randomSeed(analogRead(0));
  for (byte i = 0; i < 50; i++) {
    ids[i] = random(4096);
  }
}

void initCan(int speed) {
  int selectedSpeed;
  boolean found = false;
  for (int i = 0; i < 15; i++) {
      if (allowedSpeeds[i] == speed) {
        found = true;
        break;
      }
  }
  if (!found) {
     Serial.println("Incorrect CAN baudrate specified.");
     return;
  }
  Serial.println("Initializing CAN @ " + String(speed) + "Kbps.");
  Serial.println("CAN Initialized! Sniffing now.");
  sniffCan();
}

void sniffCan() {
  while(true) {
    int id = ids[random(50)];
    Serial.print(id, HEX);
    Serial.print(":");
    int msgLength = random(3, 9);
    for (int i = 0; i < msgLength; i++) {
      int randomInt = random(256);
      Serial.print(randomInt, HEX);
      if (i != msgLength-1) {
        Serial.print(",");
      }
    }
    Serial.println();
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