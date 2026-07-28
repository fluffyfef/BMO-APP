const int BOT1 = 1;
const int BOT2 = 2;
const int BOT3 = 3;

const int LED8 = 8;
const int LED9 = 9;
const int LED10 = 10;
const int LED11 = 11;

void setup() {
  pinMode(BOT1,INPUT);
  pinMode(BOT2,INPUT);
  pinMode(BOT3,INPUT);

  pinMode(LED8,OUTPUT);
  pinMode(LED9,OUTPUT);
  pinMode(LED10,OUTPUT);
  pinMode(LED11,OUTPUT);

}

void loop() {
  if(digitalRead(BOT1) && digitalRead(BOT2))
  {digitalWrite(LED8, HIGH);}

  else{digitalWrite(LED8,LOW);}

  if(digitalRead(BOT1) || digitalRead(BOT2))
  {digitalWrite(LED9, HIGH);}

  else{digitalWrite(LED9,LOW);}

  if(!digitalRead(BOT3))
    {digitalWrite(LED10, HIGH);}
    
    else{digitalWrite(LED10,LOW);}


}
