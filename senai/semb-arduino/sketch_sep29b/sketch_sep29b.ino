#include <SPI.h>
#include <MFRC522.h>

// Pinos do RC522 na ESP32
#define SS_PIN   5
#define RST_PIN  22

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);

  // Inicializa comunicação SPI
  SPI.begin(18, 19, 23, 5);

  // Inicializa o RC522
  rfid.PCD_Init();

  Serial.println("RFID iniciado!");
  Serial.println("Aproxime um cartao ou tag...");
}

void loop() {

  // Verifica se existe um novo cartão
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Tenta ler o cartão
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Cartao detectado! UID:");

  // Mostra o UID do cartão
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(" ");

    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }

    Serial.print(rfid.uid.uidByte[i], HEX);
  }

  Serial.println();

  // Finaliza a comunicação com o cartão
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(1000);
} 
