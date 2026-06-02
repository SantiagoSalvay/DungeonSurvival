#include <iostream>
#include <SFML/Graphics.hpp>
#include "structs.h"

// Carga de las stats principales de paolo
void protagonista(personaje& pj) {
	pj.oro = 10; 
	pj.vida = 100;
	pj.ataque = 8;
	pj.defensa = 0;
	pj.arma_equipada = "Palo";
	pj.armadura_equipada = "";
	pj.posicion_x = 1;
	pj.posicion_y = 1;
	pj.nivel_actual = 1;

	// Inventario
	pj.inventario[0] = "Pocion Chica";
	pj.inventario[1] = "Palo";
	pj.cant_items = 2;
}

// Carga los vectores del mercader
void inicializarmercader(mercader& vendedor) {
	vendedor.catalogo[0] = "Pocion Pequena";
	vendedor.precios[0] = 15;

	vendedor.catalogo[1] = "Pocion Grande";
	vendedor.precios[1] = 35;

	vendedor.catalogo[2] = "Daga Rota";
	vendedor.precios[2] = 25;

	vendedor.catalogo[3] = "Espada de Hierro";
	vendedor.precios[3] = 50;

	vendedor.catalogo[4] = "Armadura Ligera";
	vendedor.precios[4] = 35;

	vendedor.catalogo[5] = "Armadura Pesada";
	vendedor.precios[5] = 60;
}

void abrircofre() {
}

// Inicializa las stats del enemigo segun si es jefe o enemigo comun
void inicializarenemigo(enemigo& en, bool es_boss) {
	if (es_boss) {
		en.nombre = "Guardian de la Mazmorra";
		en.vida = 200;
		en.ataque = 26;
		en.defensa = 10;
	}
	else {
		en.nombre = "Enemigo";
		en.vida = 45;
		en.ataque = 10;
		en.defensa = 3;
	}
}