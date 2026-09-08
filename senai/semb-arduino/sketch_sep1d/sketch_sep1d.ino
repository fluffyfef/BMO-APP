// ==========================================
// SEMÁFORO: CRUZAMENTO DE DUAS VIAS
// ==========================================

// --- Pinos da Via 1 ---
const int ledVermelho1 = 8;
const int ledAmarelo1  = 9;
const int ledVerde1    = 10;

// --- Pinos da Via 2 ---
const int ledVermelho2 = 11;
const int ledAmarelo2  = 12;
const int ledVerde2    = 13;

// --- Controle de Estado e Tempo ---
int estado = 0;
unsigned long tempoAnterior = 0;

void setup() {
pinMode(ledVermelho1, OUTPUT);
pinMode(ledAmarelo1, OUTPUT);
pinMode(ledVerde1, OUTPUT);
pinMode(ledVermelho2, OUTPUT);
pinMode(ledAmarelo2, OUTPUT);
pinMode(ledVerde2, OUTPUT);
}

void loop() {
unsigned long tempoAtual = millis();

switch (estado) {
case 0: // VIA 1 Verde | VIA 2 Vermelho
digitalWrite(ledVerde1, HIGH);
digitalWrite(ledVermelho1, LOW);
digitalWrite(ledAmarelo1, LOW);
digitalWrite(ledVermelho2, HIGH);
digitalWrite(ledAmarelo2, LOW);
digitalWrite(ledVerde2, LOW);

if (tempoAtual - tempoAnterior >= 4000) {
tempoAnterior = tempoAtual;
estado = 1;
}
break;

case 1: // VIA 1 Amarelo | VIA 2 Vermelho
digitalWrite(ledVerde1, LOW);
digitalWrite(ledAmarelo1, HIGH);
// Via 2 continua vermelho, não mexe

if (tempoAtual - tempoAnterior >= 1500) {
tempoAnterior = tempoAtual;
estado = 2;
}
break;

case 2: // VIA 1 Vermelho | VIA 2 Verde
digitalWrite(ledAmarelo1, LOW);
digitalWrite(ledVermelho1, HIGH);
digitalWrite(ledVermelho2, LOW);
digitalWrite(ledVerde2, HIGH);

if (tempoAtual - tempoAnterior >= 4000) {
tempoAnterior = tempoAtual;
estado = 3;
}
break;

case 3: // VIA 1 Vermelho | VIA 2 Amarelo
digitalWrite(ledVerde2, LOW);
digitalWrite(ledAmarelo2, HIGH);
// Via 1 continua vermelho

if (tempoAtual - tempoAnterior >= 1500) {
tempoAnterior = tempoAtual;
estado = 0;
}
break;
}
}