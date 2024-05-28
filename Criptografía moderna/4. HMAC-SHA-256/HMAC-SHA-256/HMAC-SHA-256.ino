#include <Crypto.h>
#include <SHA256.h>
#include <string.h>

#define HASH_SIZE 32
#define BLOCK_SIZE 64

SHA256 sha256;
char frase[] = "APVCMSJ2024IOTTG"; // Define la frase como una variable global
char clave[] = "miClaveSecreta";

void printHash(uint8_t* hash) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hash[i] < 16) {
            Serial.print("0");
        }
        Serial.print(hash[i], HEX);
    }
    Serial.println();
}

void hmacData(const char* key, const char* data)
{
    uint8_t hmac[HASH_SIZE];
    unsigned long start = micros();
    for (int count = 0; count < 500; ++count) { // calcula el HMAC de la información 500 veces para saber tiempo promedio
    sha256.resetHMAC(key, strlen(key));
    sha256.update(data, strlen(data));
    sha256.finalizeHMAC(key, strlen(key), hmac, sizeof(hmac));
    }
    unsigned long elapsed = micros() - start;

    Serial.print(elapsed / (sizeof(frase) * 500.0)); // Tiempo promedio por byte hasheado
    Serial.print("us por byte hasheado, ");
    Serial.print((sizeof(frase) * 500.0 * 1000000.0) / elapsed);
    Serial.println(" bytes hasheados por segundo");

    printHash(hmac);
}

void setup()
{
    Serial.begin(115200); 
    while(!Serial){
    // Espera que el monitor serial se inicie
    }
    hmacData(clave, frase);
}

void loop(){
}
