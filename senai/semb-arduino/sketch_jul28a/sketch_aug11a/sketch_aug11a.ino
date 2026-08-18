const int entrada1 = 1;
const int entrada2 = 2;
const int saida = 10;

void setup() {
  pinMode(entrada1,INPUT);
  pinMode(entrada2,INPUT);
  pinMode(saida,OUTPUT);

}

void loop() {
  int estadoEntrada1 = digitalRead(entrada1);
  int estadoEntrada2 = digitalRead(entrada2);

  //int resultado = estadoEntrada1 ^ estadoEntrada2; OR EXCLUSIVO

  int resultado = (estadoEntrada1 == estadoEntrada2) ? HIGH : LOW;

  digitalWrite(saida, resultado);

  delay(10);

}
