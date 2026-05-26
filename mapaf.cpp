#include <iostream>
#include <string>
#include "mapa.h"

using namespace std;

void cargarNivel(int numeroNivel, string fondoDestino[MAX_FILAS][MAX_COLUMNAS], string entidadesDestino[MAX_FILAS][MAX_COLUMNAS]) {



    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            fondoDestino[i][j] = "0";
            entidadesDestino[i][j] = "";
        }
    }

    switch (numeroNivel) {
    case 1: {

        string fondo[MAX_FILAS][MAX_COLUMNAS] = {
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

        string entidades[MAX_FILAS][MAX_COLUMNAS] = {
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

        for (int i = 0; i < MAX_FILAS; i++) {
            for (int j = 0; j < MAX_COLUMNAS; j++) {
                fondoDestino[i][j] = fondo[i][j];
                entidadesDestino[i][j] = entidades[i][j];
            }
        }
        break;
    }

    case 2: {
        string fondo[MAX_FILAS][MAX_COLUMNAS] = {
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

        string entidades[MAX_FILAS][MAX_COLUMNAS] = {
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

        for (int i = 0; i < MAX_FILAS; i++) {
            for (int j = 0; j < MAX_COLUMNAS; j++) {
                fondoDestino[i][j] = fondo[i][j];
                entidadesDestino[i][j] = entidades[i][j];
            }
        }
        break;
    }

    case 3: {

        string fondo[MAX_FILAS][MAX_COLUMNAS] = {
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

        string entidades[MAX_FILAS][MAX_COLUMNAS] = {
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

        for (int i = 0; i < MAX_FILAS; i++) {
            for (int j = 0; j < MAX_COLUMNAS; j++) {
                fondoDestino[i][j] = fondo[i][j];
                entidadesDestino[i][j] = entidades[i][j];
            }
        }
        break;
    }

    case 4: {

        string fondo[MAX_FILAS][MAX_COLUMNAS] = {
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

        string entidades[MAX_FILAS][MAX_COLUMNAS] = {
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

        for (int i = 0; i < MAX_FILAS; i++) {
            for (int j = 0; j < MAX_COLUMNAS; j++) {
                fondoDestino[i][j] = fondo[i][j];
                entidadesDestino[i][j] = entidades[i][j];
            }
        }
        break;
    }

    case 5: {
        string fondo[MAX_FILAS][MAX_COLUMNAS] = {
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

        string entidades[MAX_FILAS][MAX_COLUMNAS] = {
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

        for (int i = 0; i < MAX_FILAS; i++) {
            for (int j = 0; j < MAX_COLUMNAS; j++) {
                fondoDestino[i][j] = fondo[i][j];
                entidadesDestino[i][j] = entidades[i][j];
            }
        }
        break;
    }
    }
}


void dibujarmapa(
    sf::RenderWindow& ventana,
    string matrizFondo[MAX_FILAS][MAX_COLUMNAS],
    string matrizEntidades[MAX_FILAS][MAX_COLUMNAS],
    sf::Texture& texSuelo, sf::Texture& texParedLado, sf::Texture& texParedAbajo,
    sf::Texture& texProta, sf::Texture& texBoss, sf::Texture& texEnemigo,
    sf::Texture& texMercader, sf::Texture& texCofre, sf::Texture& texSalida) {

    sf::Sprite rectangulo(texSuelo);

    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {

           
            float posX = j * 254.f;
            float posY = i * 254.f;

            // IMPORTANTE: Resetear el origen y la rotación para que el piso y 
            // los personajes no salgan rotados por culpa de la pared anterior.
            rectangulo.setOrigin(sf::Vector2f(0.f, 0.f));
            rectangulo.setRotation(sf::degrees(0.f));
            rectangulo.setPosition({ posX, posY });

            if (matrizFondo[i][j] == "0") {
                rectangulo.setTexture(texSuelo);
                ventana.draw(rectangulo);
            }
            else if (matrizFondo[i][j] == "1") {

                // Paredes LATERALES (Izquierda o Derecha)
                rectangulo.setTexture(texParedLado); // Usás tu única textura de pared

                // 1. Movemos el eje al centro de la imagen de 254x254
                rectangulo.setOrigin(sf::Vector2f(127.f, 127.f));
                // 2. Ajustamos la posición sumando la mitad para que no se desfase
                rectangulo.setPosition({ posX + 127.f, posY + 127.f });

                if (j == 0) {
                    // Si la columna es 0, es la pared izquierda
                    rectangulo.setRotation(sf::degrees(90.f));
                }
                else {
                    // Si no es 0, es la pared derecha (columna 9)
                    rectangulo.setRotation(sf::degrees(270.f));
                }
                ventana.draw(rectangulo);
            }
            else if (matrizFondo[i][j] == "2") {
                // Paredes SUPERIOR o INFERIOR (Arriba o Abajo)
                rectangulo.setTexture(texParedLado); // Seguimos reciclando la misma textura

                rectangulo.setOrigin(sf::Vector2f(127.f, 127.f));
                rectangulo.setPosition({ posX + 127.f, posY + 127.f });

                if (i == 0) {
                    // Si la fila es 0, es el techo
                    rectangulo.setRotation(sf::degrees(180.f));
                }
                else {
                    // Si la fila es 9, es el piso
                    rectangulo.setRotation(sf::degrees(0.f));
                }
                ventana.draw(rectangulo);
            }
            else if (matrizFondo[i][j] == "S") {
                rectangulo.setTexture(texSuelo);
                ventana.draw(rectangulo);
                rectangulo.setTexture(texSalida);
                ventana.draw(rectangulo);
            }


            if (matrizEntidades[i][j] != "") {
                if (matrizEntidades[i][j] == "P") {
                    rectangulo.setTexture(texProta);
                }
                else if (matrizEntidades[i][j] == "E") {
                    rectangulo.setTexture(texEnemigo);
                }
                else if (matrizEntidades[i][j] == "M") {
                    rectangulo.setTexture(texMercader);
                }
                else if (matrizEntidades[i][j] == "B") {
                    rectangulo.setTexture(texBoss);
                }
                else if (matrizEntidades[i][j] == "C") {
                    rectangulo.setTexture(texCofre);
                }
                ventana.draw(rectangulo);
            }
        }
    }
}