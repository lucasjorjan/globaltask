#include <Arduino.h>

#define START_SYMBOL 0xAA
#define PACKET_LENGTH 10 // 8 bytes de dados + 2 bytes de CRC

uint16_t calculateCRC16(const uint8_t *data, uint16_t length) {
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        delay(100);
    }
}

void loop() {
    static uint8_t dataValue = 0;
    static uint8_t packetType = 0x01;  // Inicializa com o tipo 0x01

    // Simulação de envio de pacote
    uint8_t packet[PACKET_LENGTH] = {
        START_SYMBOL,  // Símbolo de início
        packetType,    // Tipo
        0x00,          // Comprimento (4 bytes de dados)
        0x04,          // Comprimento (4 bytes de dados)
        dataValue,     // Dados variáveis
        dataValue + 1, // Dados variáveis
        dataValue + 2, // Dados variáveis
        dataValue + 3, // Dados variáveis
        0x00, 0x00    // Espaço para CRC
    };

    // Calcular o CRC
    uint16_t crcValue = calculateCRC16(packet, 8);  // 8 bytes (start, type, length, data)
    packet[8] = (crcValue >> 8) & 0xFF;  // CRC alto
    packet[9] = crcValue & 0xFF;         // CRC baixo

    // Envia o pacote pela serial
    Serial.write(packet, sizeof(packet));

    // Alterna o tipo de pacote para a próxima iteração
    if (packetType == 0x01) {
        packetType = 0x02;
    } else {
        packetType = 0x01;
    }

    // Atualiza o valor dos dados para a próxima iteração
    dataValue++;

    // Reenvia o pacote a cada 2 segundos
    delay(2000);
}
