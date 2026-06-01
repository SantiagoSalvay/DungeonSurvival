#pragma once
#include "structs.h"
#include "mapa.h"

// inicio
void protagonista(personaje& pj);
void inicializarmercader(mercader& vendedor);

// Funciones de movimiento e interaccion en la matriz
void moverpj(personaje& pj, char direccion, string matriz_fondo[max_filas][max_columnas], string matriz_entidades[max_filas][max_columnas]);
char interactuar(personaje& pj, string matriz_entidades[max_filas][max_columnas], string matriz_fondo[max_filas][max_columnas]);

// Algoritmos
void completar(string v[], int tam, int pos, string c[], int& k);
int fusionar(string a[], int n, string b[], int m, string c[]);
int obtenerprecioventa(string nombre_item);
int buscaritem(string v[50], int n, string x);
void ordenarburbuja(string v[50], int n);
void ordenarmercader(string catalogo[6], int precios[6], int n);
//fucniones para las stats
int obtenerataque(string arma_nombre);
int obtenerdefensa(string armadura_nombre);