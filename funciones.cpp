#include<iostream>
#include "funciones.h"
using namespace std;

void moverpj(Personaje& pj, char direccion, string matrizFondo[MAX_FILAS][MAX_COLUMNAS], string matrizEntidades[MAX_FILAS][MAX_COLUMNAS]) {

	int nuevaFila = pj.posicion_y;
	int nuevaColumna = pj.posicion_x;

	switch (direccion) {
	case 'W':
		nuevaFila = nuevaFila - 1;
		break;
	case 'S':
		nuevaFila = nuevaFila + 1;
		break;
	case 'A':
		nuevaColumna = nuevaColumna - 1;
		break;
	case 'D':
		nuevaColumna = nuevaColumna + 1;
		break;
	}

	// Colisioness de paredes y salida

	string bloqueDestino = matrizFondo[nuevaFila][nuevaColumna];

	if (bloqueDestino == "1" or bloqueDestino == "2" or bloqueDestino == "S") {
		// no hace nada si choca contra la pared
		return;
	}

	//coloisiones entidades

	string bloqueDestino2 = matrizEntidades[nuevaFila][nuevaColumna];

	if (bloqueDestino2 != "") {
		return;
	}

	matrizEntidades[pj.posicion_y][pj.posicion_x] = "";

	pj.posicion_y = nuevaFila;
	pj.posicion_x = nuevaColumna;

	matrizEntidades[pj.posicion_y][pj.posicion_x] = "P";

}

char interactuar(Personaje& pj, string matrizEntidades[MAX_FILAS][MAX_COLUMNAS], string matrizFondo[MAX_FILAS][MAX_COLUMNAS]) {

	int pj_x = pj.posicion_x;
	int pj_y = pj.posicion_y;

	// Deteccion de Objeto/Npc/Salida
	string deteccion = "";
	int det_x = -1, det_y = -1;



	// deteccion arriba
	
	if (pj_y - 1 >= 0 and (matrizEntidades[pj_y - 1][pj_x] != "" or matrizFondo[pj_y - 1][pj_x] == "S")) {

		if (matrizEntidades[pj_y - 1][pj_x] != "") {
			deteccion = matrizEntidades[pj_y - 1][pj_x];
		}
		else {
			deteccion = matrizFondo[pj_y - 1][pj_x];
		}

		det_y = pj_y - 1;
		det_x = pj_x;
	}

	
	// deteccion abajo
	
	else if (pj_y + 1 < MAX_FILAS and (matrizEntidades[pj_y + 1][pj_x] != "" or matrizFondo[pj_y + 1][pj_x] == "S")) {

		if (matrizEntidades[pj_y + 1][pj_x] != "") {
			deteccion = matrizEntidades[pj_y + 1][pj_x];
		}
		else {
			deteccion = matrizFondo[pj_y + 1][pj_x];
		}

		det_y = pj_y + 1;
		det_x = pj_x;
	}

	
	// deteccion derecha

	else if (pj_x + 1 < MAX_COLUMNAS and (matrizEntidades[pj_y][pj_x + 1] != "" or matrizFondo[pj_y][pj_x + 1] == "S")) {

		if (matrizEntidades[pj_y][pj_x + 1] != "") {
			deteccion = matrizEntidades[pj_y][pj_x + 1];
		}
		else {
			deteccion = matrizFondo[pj_y][pj_x + 1]; 
		}

		det_y = pj_y;
		det_x = pj_x + 1;
	}

	
	// deteccion izquierda 
	
	else if (pj_x - 1 >= 0 and (matrizEntidades[pj_y][pj_x - 1] != "" or matrizFondo[pj_y][pj_x - 1] == "S")) {

		if (matrizEntidades[pj_y][pj_x - 1] != "") {
			deteccion = matrizEntidades[pj_y][pj_x - 1];
		}
		else {
			deteccion = matrizFondo[pj_y][pj_x - 1];
		}

		det_y = pj_y;
		det_x = pj_x - 1;
	}

	// --- ACCIONES SEGÚN LO QUE ENCONTRÓ ---
	if (deteccion == "C") {
		cout << "¡Abriste un cofre en la fila " << det_y << " y columna " << det_x << "!" << endl;
		matrizEntidades[det_y][det_x] = "";
	}
	else if (deteccion == "S") {
		cout << "¡Encontraste la salida!" << endl;
		return 'S';


	}
	else if (deteccion == "M") {
		cout << "¡Hola, aventurero! ¿Qué vas a comprar?" << endl;
		return 'M';
	}
	else if (deteccion == "E" || deteccion == "B") {
		cout << "¡Empieza el combate!" << endl;
		return 'E';
	}
}