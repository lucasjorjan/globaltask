#ifndef RETANGULO_H
#define RETANGULO_H

#include "FormaGeometrica.h"

typedef struct {
    FormaGeometrica base;
    float largura, altura;
} Retangulo;

Retangulo* criar_retangulo(float largura, float altura);

#endif
