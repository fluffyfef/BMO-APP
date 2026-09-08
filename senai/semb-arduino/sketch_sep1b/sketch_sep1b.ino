// ==========================================
// PROJETO: BarLED Mágico (Bargraph)
// ==========================================

// --- Pinos dos Componentes ---
// Guardamos os pinos numa "Array" (uma lista) para facilitar.
// Estes são os pinos digitais onde os LEDs estão ligados (D8 ao D12).
const int pinosLeds[] = {8, 9, 10, 11, 12};
const int numLeds = 5; // Quantidade total de LEDs na nossa barra

const int pinoPot = A0; // Pino Analógico 0 onde o Potenciómetro está ligado

void setup() {
  // Prepara todos os 5 pinos de LED como saída de energia rapidamente 
  // usando um laço de repetição "for". Magia pura para poupar linhas de código!
  for (int i = 0; i < numLeds; i++) {
    pinMode(pinosLeds[i], OUTPUT);
  }
}

void loop() {
  // 1. Lê a energia que passa pelo potenciómetro
  // O valor lido pelo pino analógico será sempre entre 0 e 1023
  int leituraPot = analogRead(pinoPot);

  // 2. Função MAP: A magia da proporção!
  // Transforma a escala gigante do potenciómetro (0 a 1023) 
  // na nossa escala pequena de LEDs (0 a 5).
  int nivel = map(leituraPot, 0, 1023, 0, numLeds);

  // 3. Acende ou apaga os LEDs conforme o nível de energia
  for (int i = 0; i < numLeds; i++) {
    if (i < nivel) {
      // Se a posição do LED for menor que o nível atual, ele ACENDE
      digitalWrite(pinosLeds[i], HIGH); 
    } else {
      // Se a posição do LED for maior ou igual ao nível, ele APAGA
      digitalWrite(pinosLeds[i], LOW);  
    }
  }
}