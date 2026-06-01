#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#pragma once

int iniciarjuego();

const int max_items = 6;

// Funciones para manejar el dibujo y movimiento del menu
void inicializarmenu(std::vector<sf::Text>& opciones, const sf::Font& fuente, float width, float height);
void moverarriba(int& item_seleccionado, std::vector<sf::Text>& opciones);
void moverabajo(int& item_seleccionado, std::vector<sf::Text>& opciones);
void dibujarmenu(sf::RenderWindow& window, const std::vector<sf::Text>& opciones);