#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
// Tamano mapa
const int max_filas = 10;
const int max_columnas = 10;

void cargarnivel(int numero_nivel, string fondo_destino[max_filas][max_columnas], string entidades_destino[max_filas][max_columnas]);

// Texturas Mapa
void dibujarmapa(
    sf::RenderWindow& ventana,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    sf::Texture& tex_suelo,
    sf::Texture& tex_pared_arriba, sf::Texture& tex_pared_abajo,
    sf::Texture& tex_pared_izq, sf::Texture& tex_pared_der,
    sf::Texture& tex_prota, sf::Texture& tex_boss, sf::Texture& tex_enemigo,
    sf::Texture& tex_mercader, sf::Texture& tex_cofre, sf::Texture& tex_salida
);