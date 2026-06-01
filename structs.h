#pragma once
#include <string>

// Estructura principal del jugador
struct personaje {
	std::string name;
	int oro;
	int vida;
	std::string arma_equipada;
	std::string armadura_equipada;
	int ataque;
	int defensa;
	int nivel_actual;
	int posicion_x;
	int posicion_y;
	std::string inventario[50]; // Vector para la mochila
	int cant_items = 0;
};

// Estructura de los enemigos
struct enemigo {
	std::string nombre;
	int vida;
	int ataque;
	int defensa;
};

// Estructura de la tienda para el apaero
struct mercader {
	std::string nombre;
	std::string catalogo[6]; 
	int precios[6];          
};


struct cofre {
	int oro;
	int cant_loot;
	std::string loot[3];     // Vector temp para fusion
};