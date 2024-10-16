#include "observer.h"
#include "crc.h"
#include <stdio.h>
#include <string.h>

// Registra um novo observador
void register_observer(Observable *observable, PacketHandler handler, uint8_t packet_type) {
    Observer *new_observer = (Observer *)malloc(sizeof(Observer));

    // Verifica se a alocação foi bem-sucedida
    if (new_observer) {
        // Inicializa o novo observador
        new_observer->handler = handler;
        new_observer->packet_type = packet_type;
        new_observer->next = observable->observers;
        observable->observers = new_observer;
    } else {
        printf("Erro: Falha na alocacao de memoria para um novo observador.\n");
    }
}

// Notifica os observadores registrados para o tipo de pacote recebido
void notify_observers(Observable *observable, Packet *packet) {
    Observer *current = observable->observers;
    while (current) {
        if (current->packet_type == packet->type) {
            printf("Notificando observador do tipo %d\n", current->packet_type);
            current->handler(packet);
        }
        current = current->next;
    }
}

// Extrai o pacote do buffer, verifica a integridade e notifica os observadores
void receive_packet(Observable *observable, uint8_t *buffer, uint16_t length) {

    printf("Pacote recebido: ");
    for (uint16_t i = 0; i < length; i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");

    // Verifica se o pacote tem pelo menos o tamanho do cabeçalho
    if (length < 7) {
        printf("Pacote muito curto.\n");
        return;
    }

    // Verifica o símbolo de start
    if (buffer[0] != START_SYMBOL) {
        printf("Simbolo de start incorreto.\n");
        return;
    }

    // Extrai o tipo e o comprimento do pacote
    uint8_t type = buffer[1];
    uint16_t data_length = (buffer[2] << 8) | buffer[3];

    // Verifica se o comprimento é consistente com o tamanho do pacote
    if (data_length + 6 != length) {
        printf("Comprimento inconsistente.\n");
        return;
    }

    // Calcula o CRC dos dados recebidos
    uint16_t received_crc = (buffer[length - 2] << 8) | buffer[length - 1];
    uint16_t calculated_crc = CRC_CalculateCRC16(buffer, length - 2);

    printf("CRC recebido: %04X\n", received_crc);
    printf("CRC calculado: %04X\n", calculated_crc);

    // Verifica a integridade dos dados
    if (received_crc != calculated_crc) {
        printf("Pacote invalido ou corrompido.\n");
        return;
    }

    // Cria um pacote para notificar os observadores
    Packet packet = {type, data_length, &buffer[4]};

    // Notifica os observadores interessados
    notify_observers(observable, &packet);
}

// Remove e libera todos os observadores
void unregister_all_observers(Observable *observable) {
    Observer *current = observable->observers;
    while (current) {
        Observer *to_free = current;
        current = current->next;
        free(to_free);
    }
    observable->observers = NULL;
}