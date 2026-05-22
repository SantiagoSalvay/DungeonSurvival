#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;


const int MAX_FILAS = 10;
const int MAX_COLUMNAS = 10;

void cargarNivel(int numeroNivel, string fondoDestino[MAX_FILAS][MAX_COLUMNAS], string entidadesDestino[MAX_FILAS][MAX_COLUMNAS]);


void dibujarmapa(
    sf::RenderWindow& ventana,
    string matrizFondo[MAX_FILAS][MAX_COLUMNAS],
    string matrizEntidades[MAX_FILAS][MAX_COLUMNAS],
    sf::Texture& texSuelo, sf::Texture& texParedLado, sf::Texture& texParedAbajo,
    sf::Texture& texProta, sf::Texture& texBoss, sf::Texture& texEnemigo,
    sf::Texture& texMercader, sf::Texture& texCofre, sf::Texture& texSalida
);