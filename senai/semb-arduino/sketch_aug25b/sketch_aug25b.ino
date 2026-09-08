// --- Variáveis do LED 1 ---
unsigned long tempoAnterior = 0; // Cronômetro do LED 1
const long intervalo = 1000;     // Tempo desejado (1 segundo)
int estadoLed = LOW;             // Estado atual do LED 1

// --- Variáveis do LED 2 ---
const int pinoLed2 = 14;           
unsigned long tempoAnterior2 = 0;  // O cronômetro exclusivo do LED 2
const long intervalo2 = 500;       // Tempo desejado (0,5 seg = 500 milissegundos)
int estadoLed2 = LOW;              // Estado atual do LED 2


void setup() {
  // Configura os dois pinos como saída de energia
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(pinoLed2, OUTPUT);    
}

void loop() {
  // Tira uma "foto" do tempo agora. Esse tempo serve para os dois LEDs!
  unsigned long tempoAtual = millis(); 

  // ==========================================
  // CONTROLE DO LED 1 (Pisca a cada 1 segundo)
  // ==========================================
  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual; // Salva o tempo atual para a próxima volta
    
    // Inverte o estado do LED 1
    if (estadoLed == LOW) {
      estadoLed = HIGH;
    } else {
      estadoLed = LOW;
    }
    digitalWrite(LED_BUILTIN, estadoLed);
  }

  // ==============================================
  // CONTROLE DO LED 2 (Pisca a cada 0,5 segundos)
  // ==============================================
  if (tempoAtual - tempoAnterior2 >= intervalo2) {
    tempoAnterior2 = tempoAtual; // Salva o tempo atual para a próxima volta
    
    // Inverte o estado do LED 2
    if (estadoLed2 == LOW) {
      estadoLed2 = HIGH;
    } else {
      estadoLed2 = LOW;
    }
    digitalWrite(pinoLed2, estadoLed2);
  }
}