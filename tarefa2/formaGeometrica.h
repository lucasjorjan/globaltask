#ifndef FORMA_GEOMETRICA_H
#define FORMA_GEOMETRICA_H

typedef struct FormaGeometrica {
    void (*calcular_area)(struct FormaGeometrica* self);
    void (*calcular_perimetro)(struct FormaGeometrica* self);
    void (*imprimir)(struct FormaGeometrica* self);
} FormaGeometrica;

FormaGeometrica* criar_forma(void (*calcular_area)(FormaGeometrica*),
                             void (*calcular_perimetro)(FormaGeometrica*),
                             void (*imprimir)(FormaGeometrica*));

void destruir_forma(FormaGeometrica* forma);

#endif
