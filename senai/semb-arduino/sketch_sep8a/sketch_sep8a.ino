#define AnalogLDR A0 //define a entrada analógica A0
#define Limiar 1.7
#define ledPin 8

int Leitura = 0; // variavel inteiro igual a zero
float voltage;     // variável número fracionário
float ResLDR;

void setup()
{ 
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  // monitor serial - velocidade 9600Bps
  delay(500);         // atraso de 100 milisegundos
}

void loop()
{
  Leitura = analogRead(AnalogLDR);  // leitura da entrada analógica A0
  voltage = Leitura * (5.0/1024);    // calculo tensao

  Serial.print("Leitura sensor LDR = "); // imprime no monitor serial
  Serial.println (voltage);    //imprime a tensão
  if(voltage > Limiar)
  digitalWrite(ledPin, HIGH);
    else
  digitalWrite(ledPin, LOW);
  delay(500); //atraso de 500 milisegundos
}
