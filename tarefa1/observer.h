#ifndef OBSERVER_H
#define OBSERVER_H

#include <stdint.h>
#include <stdlib.h>

// Definição do símbolo de start
#define START_SYMBOL 0xAA

// Estrutura de um pacote de dados
typedef struct {
    uint8_t type;
    uint16_t length;
    uint8_t *data;
} Packet;

// Tipo da função handler do observador
typedef void (*PacketHandler)(Packet *packet);

// Estrutura para representar um observador
typedef struct Observer {
    PacketHandler handler;
    uint8_t packet_type;
    struct Observer *next;
} Observer;

// Estrutura para o observável, que gerencia os observadores
typedef struct {
    Observer *observers;
} Observable;

// Funções para manipulação de observadores e pacotes
void register_observer(Observable *observable, PacketHandler handler, uint8_t packet_type);
void notify_observers(Observable *observable, Packet *packet);
void receive_packet(Observable *observable, uint8_t *buffer, uint16_t length);
void unregister_all_observers(Observable *observable);

#endif // OBSERVER_H
