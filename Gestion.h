#pragma once
#include "structs.h"
#include "mapa.h"

void ordenarBurbuja(string v[], int n);
void ordenarParalelo(string claves[], int valores[], int n);
int busquedaBinaria(const string v[], int n, const string& x);
int busquedaBinariaParalelo(const string claves[], int n, const string& x);
