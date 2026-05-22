#include <iostream>
#include <SFML/Graphics.hpp>
#include "structs.h"

void Protagonista(Personaje& pj) {
	pj.oro = 100;
	pj.vida = 100;
	pj.cantidad_pociones_m = 1;
	pj.cantidad_pociones_g = 0;
	pj.ataque = 8;
	pj.defensa = 0;
	pj.arma_equipada = "Palo";
	pj.armadura_equipada = "";
}

void InicializarMercader(Mercader& vendedor) {
	vendedor.catalogo[0] = "Pocion Pequena";
	vendedor.precios[0] = 15;
	vendedor.catalogo[1] = "Pocion Grande";
	vendedor.catalogo[1] = 35;
	vendedor.catalogo[2] = "Espada de madera";
	vendedor.precios[2] = 30;
	vendedor.catalogo[3] = "Espada de Hierro";
	vendedor.catalogo[3] = 50;
	vendedor.catalogo[4] = "Armadura Ligera";
	vendedor.precios[4] = 35;
	vendedor.catalogo[5] = "Armadura Pesada";
	vendedor.catalogo[5] = 60;
}

void AbrirCofre() {
}
