// --- Pinos dos Componentes ---
const int pinoBotao = 1;       // Botão
const int pinoVermelho = 8;    // LED Vermelho
const int pinoAmarelo = 9;     // LED Amarelo
const int pinoVerde = 10;      // LED Verde
const int pinoSysLed = 11;     // LED de Sistema Ligado

// --- Variáveis do Botão (Efeito Liga/Desliga) ---
int estadoBotao;
int ultimoEstadoBotao = LOW;
bool sistemaLigado = false;    // Começa desligado

// --- Variáveis de Tempo (millis) ---
unsigned long tempoAnteriorSemaforo = 0;
unsigned long tempoAnteriorPisca = 0;

// --- Variáveis de Estado ---
int passoSemaforo = 0;         // 0=Vermelho, 1=Verde, 2=Amarelo
int estadoPiscaAmarelo = LOW;

void setup() {
  pinMode(pinoBotao, INPUT);
  pinMode(pinoVermelho, OUTPUT);
  pinMode(pinoAmarelo, OUTPUT);
  pinMode(pinoVerde, OUTPUT);
  pinMode(pinoSysLed, OUTPUT);
}

void loop() {
  unsigned long tempoAtual = millis(); // O relógio principal do Arduino

  // ==========================================
  // 1. LÓGICA DO BOTÃO (Liga / Desliga)
  // ==========================================
  estadoBotao = digitalRead(pinoBotao);
  
  // Verifica se o botão acabou de ser apertado (transição de LOW para HIGH)
  if (estadoBotao == HIGH && ultimoEstadoBotao == LOW) {
    sistemaLigado = !sistemaLigado; // Inverte o sistema (se estava falso, vira verdadeiro)
    
    // Zera os cronômetros e a sequência para começar certinho
    tempoAnteriorSemaforo = tempoAtual;
    tempoAnteriorPisca = tempoAtual;
    passoSemaforo = 0; 
    
    delay(50); // Pequeno atraso para evitar "bounce" (ruído metálico do botão)
  }
  ultimoEstadoBotao = estadoBotao; // Guarda o estado para a próxima leitura do loop


  // ==========================================
  // 2. SISTEMA LIGADO (Semáforo Normal)
  // ==========================================
  if (sistemaLigado == true) {
    digitalWrite(pinoSysLed, HIGH); // Acende o LED do sistema

    // Máquina de Estados do Semáforo
    if (passoSemaforo == 0) { 
      // PASSO 0: VERMELHO
      digitalWrite(pinoVermelho, HIGH);
      digitalWrite(pinoVerde, LOW);
      digitalWrite(pinoAmarelo, LOW);
      
      if (tempoAtual - tempoAnteriorSemaforo >= 3000) { // Fica 3s no vermelho
        passoSemaforo = 1; // Avança para o verde
        tempoAnteriorSemaforo = tempoAtual;
      }
    } 
    else if (passoSemaforo == 1) { 
      // PASSO 1: VERDE
      digitalWrite(pinoVermelho, LOW);
      digitalWrite(pinoVerde, HIGH);
      digitalWrite(pinoAmarelo, LOW);
      
      if (tempoAtual - tempoAnteriorSemaforo >= 3000) { // Fica 3s no verde
        passoSemaforo = 2; // Avança para o amarelo
        tempoAnteriorSemaforo = tempoAtual;
      }
    } 
    else if (passoSemaforo == 2) { 
      // PASSO 2: AMARELO
      digitalWrite(pinoVermelho, LOW);
      digitalWrite(pinoVerde, LOW);
      digitalWrite(pinoAmarelo, HIGH);
      
      if (tempoAtual - tempoAnteriorSemaforo >= 1000) { // Fica 1s no amarelo
        passoSemaforo = 0; // Volta para o vermelho
        tempoAnteriorSemaforo = tempoAtual;
      }
    }
  } 
  
  // ==========================================
  // 3. SISTEMA DESLIGADO (Amarelo Piscante)
  // ==========================================
  else {
    digitalWrite(pinoSysLed, LOW);   // Apaga o LED do sistema
    digitalWrite(pinoVermelho, LOW); // Garante que o vermelho apague
    digitalWrite(pinoVerde, LOW);    // Garante que o verde apague

    // Cronômetro exclusivo para fazer o amarelo piscar a cada 0,5s (500ms)
    if (tempoAtual - tempoAnteriorPisca >= 500) {
      tempoAnteriorPisca = tempoAtual;
      
      // Inverte o estado do LED amarelo
      if (estadoPiscaAmarelo == LOW) {
        estadoPiscaAmarelo = HIGH;
      } else {
        estadoPiscaAmarelo = LOW;
      }
      digitalWrite(pinoAmarelo, estadoPiscaAmarelo);
    }
  }
}