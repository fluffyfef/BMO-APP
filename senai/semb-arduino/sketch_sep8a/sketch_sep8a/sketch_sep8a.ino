// ==========================================
// PROJETO: BarLED (Bargraph) UM POR VEZ
// ==========================================

const int pinosLeds[] = {4, 5, 6, 7, 8, 9, 10, 11, 12};
const int numLeds = 9;
const int pinoPot = A0;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(pinosLeds[i], OUTPUT);
  }
}

void loop() {
  int leituraPot = analogRead(pinoPot);
  int nivel = map(leituraPot, 0, 1023, 0, numLeds - 1);

  for (int i = 0; i < numLeds; i++) {
    if (i == nivel) {
      digitalWrite(pinosLeds[i], HIGH);
    } else {
      digitalWrite(pinosLeds[i], LOW);
    }
  }
}