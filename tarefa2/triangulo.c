#include "Triangulo.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************************
 * Verifica se os lados fornecidos realmente formam um triângulo válido.
 * soma de dois lados deve ser sempre maior que o terceiro lado.
 ******************************************************************************/
bool triangulo_valido(Triangulo* t) {
    return (t->lado1 + t->lado2 > t->lado3) &&
           (t->lado1 + t->lado3 > t->lado2) &&
           (t->lado2 + t->lado3 > t->lado1);
}

/*******************************************************************************
 * Fórmula de Heron
 * S = (a+b+c)/2
 * Área = (s(s-a)(s-b)(s-c))^1/2
 * Onde:
 * a, b e c são os lados do triângulo.
 * s é o semi perímetro(metade dos três lados).
 ******************************************************************************/
void calcular_area_triangulo(FormaGeometrica* self) {
    Triangulo* t = (Triangulo*)self;
     if (!triangulo_valido(t)) {
        printf("Lados invalidos para um triangulo.\n");
        return;
    }
    float s = (t->lado1 + t->lado2 + t->lado3) / 2;
    float area = sqrt(s * (s - t->lado1) * (s - t->lado2) * (s - t->lado3));
    printf("Area: %.2f\n", area);
}

void calcular_perimetro_triangulo(FormaGeometrica* self) {
    Triangulo* t = (Triangulo*)self;
    if (!triangulo_valido(t)) {
        printf("Lados invalidos para um triangulo.\n");
        return;
    }
    float perimetro = t->lado1 + t->lado2 + t->lado3;
    printf("Perimetro: %.2f\n", perimetro);
}

void imprimir_triangulo(FormaGeometrica* self) {
    Triangulo* t = (Triangulo*)self;
    printf("Triangulo:\nLado 1: %.2f\nLado 2: %.2f\nLado 3: %.2f\n", t->lado1, t->lado2, t->lado3);
    if (triangulo_valido(t)) {
        t->base.calcular_area(self);
        t->base.calcular_perimetro(self);
    } else {
        printf("Triangulo invalido. Nao foi possivel calcular area ou perimetro.\n");
        printf("soma de dois lados menor que o terceiro lado.\n");
    }
}

Triangulo* criar_triangulo(float lado1, float lado2, float lado3) {
    Triangulo* t = (Triangulo*)malloc(sizeof(Triangulo));
    t->lado1 = lado1;
    t->lado2 = lado2;
    t->lado3 = lado3;
    t->base = *criar_forma(calcular_area_triangulo, calcular_perimetro_triangulo, imprimir_triangulo);
    return t;
}
