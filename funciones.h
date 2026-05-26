#pragma once
#include "structs.h"
#include "mapa.h"

void Protagonista(Personaje& pj);
void InicializarMercader(Mercader& vendedor);
void AbrirCofre();


void moverpj(Personaje& pj, char direccion, string matrizFondo[MAX_FILAS][MAX_COLUMNAS], string matrizEntidades[MAX_FILAS][MAX_COLUMNAS]);
bool cofreabrir(Cofre& cofrepj);

char interactuar(Personaje& pj, string matrizEntidades[MAX_FILAS][MAX_COLUMNAS], string matrizFondo[MAX_FILAS][MAX_COLUMNAS]);