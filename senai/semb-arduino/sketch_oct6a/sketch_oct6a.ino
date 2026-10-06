#include <Keypad.h>

//definir senha
char senha[] = "987564";

//configuração do teclado//
const byte LINHAS = 4;
const byte COLUNAS = 3;

char digitos[LINHAS][COLUNAS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pinosLinha[LINHAS] = {11,10,9,8};
byte pinosColuna[COLUNAS] = {7,6,5};

Keypad keypad = Keypad(makeKeymap(digitos), pinosLinha, pinosColuna, LINHAS, COLUNAS);

//Variáveis Auxiliares//
int position = 0;
int ledVermelho = 12;
int ledVerde = 13;
int releFechadura = 4;
int buzzer = 2;
int tempoBuzzer = 50;
int tempoAberto = 2000;

void setup() {
  //definição do estado da porta, aberta ou fechada//
  estadodaporta(true);

  //definição dos pinos de saída do arduino//
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(releFechadura, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  //leitura das teclas//
  char digito = keypad.getKey();

  if (digito != 0) { //buzzer é acionado ao pressionar qualquer tecla//
    digitalWrite(buzzer, HIGH);
    delay(tempoBuzzer);
    digitalWrite(buzzer, LOW);

    if (digito == senha[position]) { //verificação se o número digitado corresponde a senha definida//
      position++; //se o número digitado for equivalente à senha, ele vai retornar ao início, na primeira posição//
    }
    else { //se o número digitado não for equivalente à senha
      position = 0;
    }

    if (position == 6) {
      estadodaporta(false);
    }
  }

  delay(100);
}

void estadodaporta(int trancado) {
  if (trancado) { //trancamento da porta//
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(releFechadura, HIGH);
  }
  else {
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(releFechadura, LOW);
    digitalWrite(buzzer, HIGH);
    delay(tempoBuzzer*10);
    digitalWrite(buzzer, LOW); //acerto da senha//
    delay(tempoAberto);
    position = 0;

    digitalWrite(releFechadura, LOW);
    estadodaporta(true); //trancamento da porta//
  }
}
