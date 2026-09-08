// ==========================================
// PROJETO: BarLED LDR
// ==========================================

const int pinosLeds[] = {4, 5, 6, 7, 8, 9, 10, 11, 12};
const int numLeds = 9;
const int pinoLDR = A0;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(pinosLeds[i], OUTPUT);
  }
}

void loop() {
  int leituraLDR = analogRead(pinoLDR);
  int nivel = map(leituraLDR, 300, 700, 0, numLeds - 1);

  for (int i = 0; i < numLeds; i++) {
    if (i == nivel) {
      digitalWrite(pinosLeds[i], HIGH);
    } else {
      digitalWrite(pinosLeds[i], LOW);
    }
  }
}
