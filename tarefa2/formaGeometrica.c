#include "FormaGeometrica.h"
#include <stdlib.h>
#include <stdio.h>

/*******************************************************************************
 * Função para criar uma nova FormaGeometrica
 * @param calcular_area Função para calcular a área da forma
 * @param calcular_perimetro Função para calcular o perímetro da forma
 * @param imprimir Função para imprimir os dados da forma
 * @return Ponteiro para a nova FormaGeometrica criada
 ******************************************************************************/

FormaGeometrica* criar_forma(void (*calcular_area)(FormaGeometrica*),
                             void (*calcular_perimetro)(FormaGeometrica*),
                             void (*imprimir)(FormaGeometrica*)) {
    // Aloca memória para uma nova FormaGeometrica
    FormaGeometrica* forma = (FormaGeometrica*)malloc(sizeof(FormaGeometrica));
    
    // Verifica se a alocação de memória falhou
    if (!forma) {
        printf("Erro ao alocar memoria para FormaGeometrica\n");
        return NULL;
    }
    
    // Atribui as funções para cálculo e impressão
    forma->calcular_area = calcular_area;
    forma->calcular_perimetro = calcular_perimetro;
    forma->imprimir = imprimir;

    return forma;
}

/*******************************************************************************
 * Função para destruir uma FormaGeometrica, liberando a memória alocada
 * @param forma Ponteiro para a forma que será destruída
 ******************************************************************************/
void destruir_forma(FormaGeometrica* forma) {
    if (forma != NULL) {
        free(forma);
    }
}

