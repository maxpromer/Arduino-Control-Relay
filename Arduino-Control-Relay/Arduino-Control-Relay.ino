byte relay_pin[] = { A3, A2, A1, A0 };
#define RELAY_ACTIVE LOW

void setup() {
  for (byte i = 0; i < sizeof relay_pin; i++) {
    pinMode(relay_pin[i], OUTPUT);
    digitalWrite(relay_pin[i], !RELAY_ACTIVE);
  }

  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  while(Serial1.available()) {
    char c = Serial1.read();
    Serial.print("R: ");
    Serial.println(c);
    if (c >= '1' && c <= '4') {
      digitalWrite(relay_pin[c - '1'], RELAY_ACTIVE);
      Serial.println("Relay ON!");
    } else if (c >= 'A' && c <= 'D') {
      digitalWrite(relay_pin[c - 'A'], !RELAY_ACTIVE);
      Serial.println("Relay OFF!");
    } else if (c == '9' || c == 'I') {
      for (byte i = 0; i < sizeof relay_pin; i++) {
        digitalWrite(relay_pin[i], c == '9' ? RELAY_ACTIVE : !RELAY_ACTIVE);
      }
      Serial.print(c == '9' ? String("ON") : String("OFF"));
      Serial.println("All!");
    }
  }
  delay(1);
}
