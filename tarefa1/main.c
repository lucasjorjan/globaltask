/******************************************************************************
                Implementação em C Interpretação de Pacotes de Dados 
                            Lucas Jorjan Alves 
                          Criado em 05 de Setembro de 2024
******************************************************************************/

#include "observer.h"
#include "crc.h"
#include <stdio.h>
#include <windows.h> //// Inclui a biblioteca específica do Windows para manipulação de portas seriais e threads.
#include <process.h> /// Inclui a biblioteca para uso de threads (_beginthreadex) no Windows.

// Definições de macros para facilitar a configuração da porta serial e a taxa de transmissão.
#define COM_PORT "COM7"  // Ajuste para a porta serial correta do seu dispositivo 
#define BAUD_RATE CBR_9600 //// Define a taxa de transmissão em 9600 bauds

// Função executada por uma thread que realiza a leitura contínua da porta serial
// e verifica a integridade dos pacotes recebidos.
unsigned __stdcall serial_read_task(void *param) {
    Observable *observable = (Observable *)param;

    HANDLE hSerial;
    DCB dcbSerialParams = {0}; // Estrutura para configurar os parâmetros da porta serial
    COMMTIMEOUTS timeouts = {0}; // Estrutura para configurar os timeouts da porta serial

    hSerial = CreateFile(COM_PORT, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Erro ao abrir a porta serial\n");
        return 1;
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Erro ao obter parâmetros da porta serial\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = BAUD_RATE;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Erro ao configurar a porta serial\n");
        CloseHandle(hSerial);
        return 1;
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    uint8_t buffer[256];
    DWORD bytesRead;
    while (1) {
        if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) { //Verifica se recebeu algum dado serial
            if (bytesRead > 0) {
                receive_packet(observable, buffer, bytesRead);
            }
        }
        Sleep(100); // Evita consumo excessivo de CPU
    }

    CloseHandle(hSerial);
    return 0;
}

// Handler para pacotes do tipo 1
void packet_handler_1(Packet *packet) {
    printf("Handler 1: Pacote do tipo %d recebido com %d bytes de dados.\n", packet->type, packet->length);
    for (uint16_t i = 0; i < packet->length; i++) {
        printf("%02X ", packet->data[i]);
    }
    printf("\n");
    printf("|||||||||||||||||||||||||||\n");
}

// Handler para pacotes do tipo 2
void packet_handler_2(Packet *packet) {
    printf("Handler 2: Pacote do tipo %d recebido com %d bytes de dados.\n", packet->type, packet->length);
      for (uint16_t i = 0; i < packet->length; i++) {
        printf("%02X ", packet->data[i]);
    }
    printf("\n");
    printf("|||||||||||||||||||||||||||\n");
}


int main() {
    Observable observable = {0};

    // Registrando observadores
    register_observer(&observable, packet_handler_1, 0x01);
    register_observer(&observable, packet_handler_2, 0x02);

    // Iniciar task para leitura da serial
    _beginthreadex(NULL, 0, &serial_read_task, &observable, 0, NULL);

    // Mantém o programa principal ativo
    while (1) {
        Sleep(1000);
    }

    // Como melhoria fazer uma lógica para sair do loop infinito e liberar a mémoria de forma controlada
    unregister_all_observers(&observable); // Limpa todos os observadores antes de sair

    return 0;
}
