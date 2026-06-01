#include<iostream>
#include <cstdlib>
#include "funciones.h"
using namespace std;

// --- LOGICA DE MOVIMIENTO EN LA MATRIZ ---
void moverpj(personaje& pj, char direccion, string matriz_fondo[max_filas][max_columnas], string matriz_entidades[max_filas][max_columnas]) {

	int nueva_fila = pj.posicion_y;
	int nueva_columna = pj.posicion_x;

	switch (direccion) {
	case 'W': nueva_fila = nueva_fila - 1; break;
	case 'S': nueva_fila = nueva_fila + 1; break;
	case 'A': nueva_columna = nueva_columna - 1; break;
	case 'D': nueva_columna = nueva_columna + 1; break;
	}

	// 1. Verificamos choque con la pared del fondo
	string bloque_destino = matriz_fondo[nueva_fila][nueva_columna];
	if (bloque_destino == "1" or bloque_destino == "2" or bloque_destino == "S") {
		return; // Frena el movimiento
	}

	// 2. Verificamos choque con una entidad (cofre, enemigo, etc)
	string bloque_destino2 = matriz_entidades[nueva_fila][nueva_columna];
	if (bloque_destino2 != "") {
		return; // Frena el movimiento
	}

	// 3. Si esta libre, vaciamos la celda vieja y movemos la 'P' a la nueva
	matriz_entidades[pj.posicion_y][pj.posicion_x] = "";
	pj.posicion_y = nueva_fila;
	pj.posicion_x = nueva_columna;
	matriz_entidades[pj.posicion_y][pj.posicion_x] = "P";
}

// --- LOGICA DE INTERACCION EN LAS 4 DIRECCIONES ---
char interactuar(personaje& pj, string matriz_entidades[max_filas][max_columnas], string matriz_fondo[max_filas][max_columnas]) {

	int pj_x = pj.posicion_x;
	int pj_y = pj.posicion_y;

	string deteccion = "";
	int det_x = -1, det_y = -1;

	// Mira arriba
	if (pj_y - 1 >= 0 and (matriz_entidades[pj_y - 1][pj_x] != "" or matriz_fondo[pj_y - 1][pj_x] == "S")) {
		if (matriz_entidades[pj_y - 1][pj_x] != "") deteccion = matriz_entidades[pj_y - 1][pj_x];
		else deteccion = matriz_fondo[pj_y - 1][pj_x];
		det_y = pj_y - 1;
		det_x = pj_x;
	}
	// Mira abajo
	else if (pj_y + 1 < max_filas and (matriz_entidades[pj_y + 1][pj_x] != "" or matriz_fondo[pj_y + 1][pj_x] == "S")) {
		if (matriz_entidades[pj_y + 1][pj_x] != "") deteccion = matriz_entidades[pj_y + 1][pj_x];
		else deteccion = matriz_fondo[pj_y + 1][pj_x];
		det_y = pj_y + 1;
		det_x = pj_x;
	}
	// Mira a la derecha
	else if (pj_x + 1 < max_columnas and (matriz_entidades[pj_y][pj_x + 1] != "" or matriz_fondo[pj_y][pj_x + 1] == "S")) {
		if (matriz_entidades[pj_y][pj_x + 1] != "") deteccion = matriz_entidades[pj_y][pj_x + 1];
		else deteccion = matriz_fondo[pj_y][pj_x + 1];
		det_y = pj_y;
		det_x = pj_x + 1;
	}
	// Mira a la izquierda
	else if (pj_x - 1 >= 0 and (matriz_entidades[pj_y][pj_x - 1] != "" or matriz_fondo[pj_y][pj_x - 1] == "S")) {
		if (matriz_entidades[pj_y][pj_x - 1] != "") deteccion = matriz_entidades[pj_y][pj_x - 1];
		else deteccion = matriz_fondo[pj_y][pj_x - 1];
		det_y = pj_y;
		det_x = pj_x - 1;
	}

	// --- ACCIONES SEGUN LO QUE TOCO ---

	if (deteccion == "C") {
		cofre cofre_local;
		cofre_local.oro = rand() % 15 + 1; // 1 a 15 de oro

		int random_loot = rand() % 3;
		if (random_loot == 0) {
			cofre_local.loot[0] = "Daga Rota";
			cofre_local.loot[1] = "Basura Premium";
			cofre_local.cant_loot = 2;
		}
		else if (random_loot == 1) {
			cofre_local.loot[0] = "Armadura Ligera";
			cofre_local.loot[1] = "Pocion Grande";
			cofre_local.cant_loot = 2;
		}
		else {
			cofre_local.loot[0] = "Pocion Chica";
			cofre_local.loot[1] = "Pocion Chica";
			cofre_local.cant_loot = 2;
		}

		pj.oro = pj.oro + cofre_local.oro;

		string inventario_temporal[100];

		int nueva_cantidad = fusionar(pj.inventario, pj.cant_items, cofre_local.loot, cofre_local.cant_loot, inventario_temporal);

		for (int i = 0; i < nueva_cantidad; i++) {
			pj.inventario[i] = inventario_temporal[i];
		}
		pj.cant_items = nueva_cantidad;

		matriz_entidades[det_y][det_x] = ""; // Borramos el cofre del mapa
		return 'C';
	}

	else if (deteccion == "S") {
		bool quedan_enemigos = false;

		for (int i = 0; i < max_filas; i++) {
			for (int j = 0; j < max_columnas; j++) {
				if (matriz_entidades[i][j] == "E" || matriz_entidades[i][j] == "B") {
					quedan_enemigos = true;
				}
			}
		}

		if (quedan_enemigos == true) {
			return 'L'; // 'L' de Locked (Bloqueado)
		}
		else {
			return 'S'; // 'S' de Salida libre
		}
	}

	else if (deteccion == "M") {
		return 'M';
	}

	else if (deteccion == "E" || deteccion == "B") {
		return 'E';
	}

	return '0';
}

void completar(string v[], int tam, int pos, string c[], int& k) {
	while (pos < tam) {
		c[k] = v[pos];
		pos++;
		k++;
	}
}

int fusionar(string a[], int n, string b[], int m, string c[]) {
	int i = 0, j = 0, k = 0;

	while (i < n && j < m) {
		if (a[i] < b[j]) {
			c[k] = a[i];
			i++;
		}
		else {
			c[k] = b[j];
			j++;
		}
		k++;
	}

	if (i < n) completar(a, n, i, c, k);
	else completar(b, m, j, c, k);

	return n + m;
}

int obtenerprecioventa(string nombre_item) {
	if (nombre_item == "Pocion Chica") return 7;
	if (nombre_item == "Pocion Grande") return 17;
	if (nombre_item == "Daga Rota") return 15;
	if (nombre_item == "Espada de Hierro") return 25;
	if (nombre_item == "Armadura Ligera") return 17;
	if (nombre_item == "Armadura Pesada") return 30;
	if (nombre_item == "Basura Premium") return 2;
	return 1;
}

int buscaritem(string v[], int n, string x) {
	int posicion = 0;
	for (int i = 0; i < n; i++) {
		if (x == v[i]) {
			posicion = i;
		}
	}
	return posicion;
}

void ordenarburbuja(string v[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (v[i] > v[j]) {
				string aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}

void ordenarmercader(string catalogo[], int precios[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (catalogo[i] > catalogo[j]) {
				string aux1 = catalogo[i];
				catalogo[i] = catalogo[j];
				catalogo[j] = aux1;

				int aux2 = precios[i];
				precios[i] = precios[j];
				precios[j] = aux2;
			}
		}
	}
}

int obtenerataque(string arma_nombre) {
	if (arma_nombre == "Palo") return 2;
	if (arma_nombre == "Daga Rota") return 4;
	if (arma_nombre == "Espada de Hierro") return 12;
	return 0;
}

int obtenerdefensa(string armadura_nombre) {
	if (armadura_nombre == "Armadura Ligera") return 25; 
	if (armadura_nombre == "Armadura Pesada") return 50; 
	return 0;
}