#include "Datos.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>

// ENTIDADES
// Carga de las stats principales de paolo
void protagonista(personaje& pj) {
	pj.oro = 10;
	pj.vida = 100;
	pj.ataque = 8;
	pj.defensa = 0;
	pj.arma_equipada = "";
	pj.armadura_equipada = "";
	pj.posicion_x = 1;
	pj.posicion_y = 1;
	pj.nivel_actual = 1;

	// Inventario: el palo viene en la mochila para que el jugador decida equiparlo
	pj.inventario[0] = "Palo";
	pj.inventario[1] = "Pocion Chica";
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
		en.nombre = "Guardian";
		en.vida = 200;
		en.ataque = 11;
		en.defensa = 10;
	}
	else {
		en.nombre = "Enemigo";
		en.vida = 45;
		en.ataque = 10;
		en.defensa = 3;
	}
}

// NIVELES
void cargarnivel(int numero_nivel, string fondo_destino[max_filas][max_columnas], string entidades_destino[max_filas][max_columnas]) {

    for (int i = 0; i < max_filas; i++) {
        for (int j = 0; j < max_columnas; j++) {
            fondo_destino[i][j] = "0";
            entidades_destino[i][j] = "";
        }
    }

    switch (numero_nivel) {
    case 1: {

        string fondo[max_filas][max_columnas] = {
            {"2", "2", "2", "2", "2", "2", "2", "2", "2", "2"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "S", "1"},
            {"2", "2", "2", "2", "2", "2", "2", "2", "2", "2"}
        };

        string entidades[max_filas][max_columnas] = {
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "P", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "C", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "M", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""}
        };

        for (int i = 0; i < max_filas; i++) {
            for (int j = 0; j < max_columnas; j++) {
                fondo_destino[i][j] = fondo[i][j];
                entidades_destino[i][j] = entidades[i][j];
            }
        }
        break;
    }

    case 2: {
        string fondo[max_filas][max_columnas] = {
            {"2", "2", "2", "2", "2", "2", "2", "2", "2", "2"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "1", "0", "0", "0", "0", "1", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "1", "0", "0", "0", "0", "1", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "S", "1"},
            {"2", "2", "2", "2", "2", "2", "2", "2", "2", "2"}
        };

        string entidades[max_filas][max_columnas] = {
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "P", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "E", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "E", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "C", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""}
        };

        for (int i = 0; i < max_filas; i++) {
            for (int j = 0; j < max_columnas; j++) {
                fondo_destino[i][j] = fondo[i][j];
                entidades_destino[i][j] = entidades[i][j];
            }
        }
        break;
    }

    case 3: {

        string fondo[max_filas][max_columnas] = {
            {"2", "2", "2", "2", "2", "2", "2", "2", "2", "2"},
            {"1", "0", "0", "0", "1", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "1", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "1", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "1", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "1", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "1", "0", "0", "0", "S", "1"},
            {"2", "2", "2", "2", "2", "2", "2", "2", "2", "2"}
        };

        string entidades[max_filas][max_columnas] = {
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "P", "", "", "", "", "", "", "", ""},
            {"", "", "E", "", "", "", "E", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "M", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "E", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""}
        };

        for (int i = 0; i < max_filas; i++) {
            for (int j = 0; j < max_columnas; j++) {
                fondo_destino[i][j] = fondo[i][j];
                entidades_destino[i][j] = entidades[i][j];
            }
        }
        break;
    }

    case 4: {

        string fondo[max_filas][max_columnas] = {
            {"2", "2", "2", "2", "2", "2", "2", "2", "2", "2"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "1", "2", "2", "1", "0", "0", "1"},
            {"1", "0", "0", "1", "0", "0", "1", "0", "0", "1"},
            {"1", "0", "0", "1", "0", "0", "1", "0", "0", "1"},
            {"1", "0", "0", "1", "2", "2", "1", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "S", "1"},
            {"2", "2", "2", "2", "2", "2", "2", "2", "2", "2"}
        };

        string entidades[max_filas][max_columnas] = {
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "P", "", "", "", "", "", "", "", ""},
            {"", "", "", "E", "", "", "E", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "E", "", "", "", "", "", "", "C", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "E", "", "", "", ""},
            {"", "C", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""}
        };

        for (int i = 0; i < max_filas; i++) {
            for (int j = 0; j < max_columnas; j++) {
                fondo_destino[i][j] = fondo[i][j];
                entidades_destino[i][j] = entidades[i][j];
            }
        }
        break;
    }

    case 5: {
        string fondo[max_filas][max_columnas] = {
            {"2", "2", "2", "2", "2", "2", "2", "2", "2", "2"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
            {"2", "2", "2", "2", "2", "2", "2", "2", "2", "2"}
        };

        string entidades[max_filas][max_columnas] = {
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "P", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "B", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "C", "", "", "", "", "", "", "C", ""},
            {"", "", "", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", "", "", ""}
        };

        for (int i = 0; i < max_filas; i++) {
            for (int j = 0; j < max_columnas; j++) {
                fondo_destino[i][j] = fondo[i][j];
                entidades_destino[i][j] = entidades[i][j];
            }
        }
        break;
    }
    }
}


