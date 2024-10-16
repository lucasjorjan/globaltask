/******************************************************************************
                        hierarquia de formas geométricas em C
                            Lucas Jorjan Alves 
                          Criado em 05 de Setembro de 2024
******************************************************************************/

#include "Triangulo.h"
#include "Retangulo.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    FormaGeometrica* formas[4];
    
    Triangulo* t = criar_triangulo(3, 4, 5);
    Retangulo* r = criar_retangulo(5, 3);

    Triangulo* t2 = criar_triangulo(6, 4, 15);
    Retangulo* r2 = criar_retangulo(25, 10);

    formas[0] = (FormaGeometrica*)t;
    formas[1] = (FormaGeometrica*)r;
    formas[2] = (FormaGeometrica*)t2;
    formas[3] = (FormaGeometrica*)r2;

    for (int i = 0; i < 4; i++) {
        formas[i]->imprimir(formas[i]);
        printf("\n");
    }

    // Libera a memória utilizando a função destruir_forma
    for (int i = 0; i < 4; i++) {
        destruir_forma(formas[i]);
    }

    return 0;
}
