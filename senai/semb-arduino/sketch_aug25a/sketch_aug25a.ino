// Definição dos pinos conforme o enunciado
const int BOT1 = 1;
const int pinVM = 8;
const int pinAM = 9;
const int pinVD = 10;

// Variável para guardar o estado do botão
int estadoBOT1 = 0;

void setup() {
  // Configurando o botão como entrada
  pinMode(BOT1, INPUT);
 
  // Configurando os LEDs como saída
  pinMode(pinVD, OUTPUT);
  pinMode(pinAM, OUTPUT);
  pinMode(pinVM, OUTPUT);
}

void loop() {
  // Faz a leitura de como está o botão naquele momento
  estadoBOT1 = digitalRead(BOT1);

  // Verifica se o botão está acionado (pressionado)
  if (estadoBOT1 == HIGH) {
   
    // SEMÁFORO NORMAL
    // Acende o Verde (VD = 3s)
    digitalWrite(pinVM, LOW);
    digitalWrite(pinAM, LOW);
    digitalWrite(pinVD, HIGH);
    delay(3000);

    // Acende o Amarelo (AM = 1s)
    digitalWrite(pinVD, LOW);
    digitalWrite(pinAM, HIGH);
    delay(1000);

    // Acende o Vermelho (VM = 3s)
    digitalWrite(pinAM, LOW);
    digitalWrite(pinVM, HIGH);
    delay(3000);

  } else {
   
    // MODO DE ALERTA (Botão solto)
    // Garante que o verde e o vermelho fiquem apagados
    digitalWrite(pinVD, LOW);
    digitalWrite(pinVM, LOW);
   
    // Faz o amarelo piscar a cada 1 segundo
    digitalWrite(pinAM, HIGH); // Liga
    delay(1000);                     // Espera 1s
    digitalWrite(pinAM, LOW);  // Desliga
    delay(1000);                     // Espera 1s
  }
}