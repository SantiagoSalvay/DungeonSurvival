#pragma once
#include <string>
#include "ErroresMios.h"

// GESTION: ORDENAMIENTOS Y BUSQUEDAS
// Ordenamientos (burbuja, de menor a mayor alfabeticamente)
void ordenarburbuja(std::string v[], int n);
void ordenarBurbuja(std::string v[], int n);

// Ordena el catalogo del mercader y mueve los precios junto con cada nombre
void ordenarmercader(std::string catalogo[], int precios[], int n);

// Ordena claves y arrastra los valores paralelos para que sigan emparejados
void ordenarParalelo(std::string claves[], int valores[], int n);

// Busquedas binarias: el vector tiene que estar ORDENADO.
// Devuelven la posicion o lanzan ErrorItemNoEncontrado si no esta.
int busquedaBinaria(const std::string v[], int n, const std::string& x);
int busquedaBinariaParalelo(const std::string claves[], int n, const std::string& x);
