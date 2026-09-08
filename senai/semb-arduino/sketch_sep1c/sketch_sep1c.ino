// ==========================================
// PROJETO: Pisca-Pisca Multi-Padrões
// ==========================================

// --- Pinos ---
// Array (lista) com os pinos dos 5 LEDs
const int pinosLeds[] = {8, 9, 10, 11, 12};
const int numLeds = 5;
const int pinoBotao = 2; // O botão está no pino digital 2

// --- Variáveis do Botão e Modo ---
int estadoBotao;
int ultimoEstadoBotao = LOW;
int modoAtual = 0;
const int maxModos = 5; // Modos vão de 0 a 4 (Total de 5 modos)

// --- Variáveis de Tempo e Animação ---
unsigned long tempoAnterior = 0;
bool estadoGeral = false; // Usado para piscar todos ao mesmo tempo
int indiceChase = 0;      // Controla a posição da luz no modo Scanner
int direcaoChase = 1;     // Direção: 1 (vai para a direita), -1 (volta para a esquerda)

void setup() {
  // Prepara os pinos dos LEDs como SAÍDA
  for (int i = 0; i < numLeds; i++) {
    pinMode(pinosLeds[i], OUTPUT);
  }
  
  // Prepara o pino do botão como ENTRADA
  // Assumimos que usou o resistor de 10k (pull-down) ligando o botão ao GND,
  // tal como ilustrado no mapa de montagem!
  pinMode(pinoBotao, INPUT); 
}

void loop() {
  unsigned long tempoAtual = millis(); // O nosso relógio principal
  
  // ==========================================
  // 1. LEITURA DO BOTÃO (Mudar de Modo)
  // ==========================================
  estadoBotao = digitalRead(pinoBotao);
  
  // Verifica se o botão foi pressionado agora (transição de LOW para HIGH)
  if (estadoBotao == HIGH && ultimoEstadoBotao == LOW) {
    modoAtual++; // Avança para o próximo modo
    
    // Se passar do limite, volta ao zero
    if (modoAtual >= maxModos) {
      modoAtual = 0; 
    }
    
    // Pequeno reset para que a nova animação comece limpa
    apagarTodos();
    tempoAnterior = tempoAtual;
    indiceChase = 0;
    direcaoChase = 1;
    
    delay(50); // Anti-bounce: pequena pausa para evitar que o Arduino leia cliques duplos por acidente
  }
  
  ultimoEstadoBotao = estadoBotao; // Guarda o estado para a próxima volta do loop

  // ==========================================
  // 2. A MÁQUINA DE PADRÕES (Switch Case)
  // ==========================================
  switch (modoAtual) {
    
    case 0: // MODO 0: Sistema Desligado
      apagarTodos();
      break;

    case 1: // MODO 1: Alerta (Pisca todos juntos)
      if (tempoAtual - tempoAnterior >= 400) { // Atualiza a cada 400ms
        tempoAnterior = tempoAtual;
        estadoGeral = !estadoGeral; // Inverte o estado (Acende/Apaga)
        
        for (int i = 0; i < numLeds; i++) {
          digitalWrite(pinosLeds[i], estadoGeral);
        }
      }
      break;

    case 2: // MODO 2: Scanner (Vai e Vem estilo Knight Rider)
      if (tempoAtual - tempoAnterior >= 100) { // Bem rápido (100ms)
        tempoAnterior = tempoAtual;
        apagarTodos(); // Apaga a luz anterior
        
        digitalWrite(pinosLeds[indiceChase], HIGH); // Acende a luz atual
        
        indiceChase += direcaoChase; // Move o índice para o lado
        
        // Se bater na última luz ou na primeira, inverte a direção!
        if (indiceChase >= numLeds - 1 || indiceChase <= 0) {
          direcaoChase = -direcaoChase;
        }
      }
      break;

    case 3: // MODO 3: Polícia (Alternado - Pares e Ímpares)
      if (tempoAtual - tempoAnterior >= 250) { // A cada 250ms
        tempoAnterior = tempoAtual;
        estadoGeral = !estadoGeral;
        
        for (int i = 0; i < numLeds; i++) {
          if (i % 2 == 0) { // Se o número do LED for Par (0, 2, 4)
            digitalWrite(pinosLeds[i], estadoGeral);
          } else {          // Se for Ímpar (1, 3)
            digitalWrite(pinosLeds[i], !estadoGeral);
          }
        }
      }
      break;

    case 4: // MODO 4: Festa / Caos (Aleatório)
      if (tempoAtual - tempoAnterior >= 100) { // A cada 100ms
        tempoAnterior = tempoAtual;
        
        for (int i = 0; i < numLeds; i++) {
          // A função random(2) gera os números 0 ou 1 (LOW ou HIGH) aleatoriamente
          digitalWrite(pinosLeds[i], random(2)); 
        }
      }
      break;
  }
}

// ==========================================
// FUNÇÕES AUXILIARES
// ==========================================

// Função simples para desligar todos os LEDs de uma vez
void apagarTodos() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(pinosLeds[i], LOW);
  }
}