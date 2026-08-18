// Definição dos pinos conforme o enunciado
const int pinoBotao = 5;
const int pinoVerde = 8;
const int pinoAmarelo = 9;
const int pinoVermelho = 10;

// Variável para guardar o estado do botão
int estadoBotao = 0; 

void setup() {
  // Configurando o botão como entrada
  pinMode(pinoBotao, INPUT);
  
  // Configurando os LEDs como saída
  pinMode(pinoVerde, OUTPUT);
  pinMode(pinoAmarelo, OUTPUT);
  pinMode(pinoVermelho, OUTPUT);
}

void loop() {
  // Faz a leitura de como está o botão naquele momento
  estadoBotao = digitalRead(pinoBotao);

  // Verifica se o botão está acionado (pressionado)
  if (estadoBotao == HIGH) {
    
    // SEMÁFORO NORMAL
    // Acende o Verde (VD = 3s)
    digitalWrite(pinoVermelho, LOW);
    digitalWrite(pinoAmarelo, LOW);
    digitalWrite(pinoVerde, HIGH);
    delay(3000); 

    // Acende o Amarelo (AM = 1s)
    digitalWrite(pinoVerde, LOW);
    digitalWrite(pinoAmarelo, HIGH);
    delay(1000); 

    // Acende o Vermelho (VM = 3s)
    digitalWrite(pinoAmarelo, LOW);
    digitalWrite(pinoVermelho, HIGH);
    delay(3000); 

  } else {
    
    // MODO DE ALERTA (Botão solto)
    // Garante que o verde e o vermelho fiquem apagados
    digitalWrite(pinoVerde, LOW);
    digitalWrite(pinoVermelho, LOW);
    
    // Faz o amarelo piscar a cada 1 segundo
    digitalWrite(pinoAmarelo, HIGH); // Liga
    delay(1000);                     // Espera 1s
    digitalWrite(pinoAmarelo, LOW);  // Desliga
    delay(1000);                     // Espera 1s
  }
}