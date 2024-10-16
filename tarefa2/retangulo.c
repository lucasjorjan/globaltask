#include "Retangulo.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Função para calcular a área de um retângulo
 * @param self Ponteiro para a forma base (Retângulo)
 ******************************************************************************/

void calcular_area_retangulo(FormaGeometrica* self) {
    Retangulo* r = (Retangulo*)self;
    float area = r->largura * r->altura;
    printf("Area: %.2f\n", area);
}

void calcular_perimetro_retangulo(FormaGeometrica* self) {
    Retangulo* r = (Retangulo*)self;
    float perimetro = 2 * (r->largura + r->altura);
    printf("Perimetro: %.2f\n", perimetro);
}

void imprimir_retangulo(FormaGeometrica* self) {
    Retangulo* r = (Retangulo*)self;
    printf("Retangulo:\nLargura: %.2f\nAltura: %.2f\n", r->largura, r->altura);
    r->base.calcular_area(self);
    r->base.calcular_perimetro(self);
}

Retangulo* criar_retangulo(float largura, float altura) {
    Retangulo* r = (Retangulo*)malloc(sizeof(Retangulo));
    r->largura = largura;
    r->altura = altura;
    r->base = *criar_forma(calcular_area_retangulo, calcular_perimetro_retangulo, imprimir_retangulo);
    return r;
}
