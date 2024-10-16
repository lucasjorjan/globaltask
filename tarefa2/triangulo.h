#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "FormaGeometrica.h"
#include <stdbool.h>

typedef struct {
    FormaGeometrica base;
    float lado1, lado2, lado3;
} Triangulo;

Triangulo* criar_triangulo(float lado1, float lado2, float lado3);
bool triangulo_valido(Triangulo* t);

#endif
