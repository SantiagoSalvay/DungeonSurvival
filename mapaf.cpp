#include <iostream>
#include <string>
#include "mapa.h"

using namespace std;

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


void dibujarmapa(
    sf::RenderWindow& ventana,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    sf::Texture& tex_suelo,
    sf::Texture& tex_pared_arriba, sf::Texture& tex_pared_abajo,
    sf::Texture& tex_pared_izq, sf::Texture& tex_pared_der,
    sf::Texture& tex_prota, sf::Texture& tex_boss, sf::Texture& tex_enemigo,
    sf::Texture& tex_mercader, sf::Texture& tex_cofre, sf::Texture& tex_salida) {

    sf::Sprite rectangulo(tex_suelo);

    for (int i = 0; i < max_filas; i++) {
        for (int j = 0; j < max_columnas; j++) {

            float pos_x = j * 254.f;
            float pos_y = i * 254.f;

            // Ya no hace falta rotar ni desfasar nada, lo dejamos limpito
            rectangulo.setOrigin(sf::Vector2f(0.f, 0.f));
            rectangulo.setRotation(sf::degrees(0.f));
            rectangulo.setPosition({ pos_x, pos_y });

            if (matriz_fondo[i][j] == "0") {
                rectangulo.setTexture(tex_suelo);
                ventana.draw(rectangulo);
            }
<<<<<<< HEAD
            else if (matrizFondo[i][j] == "1") {

=======
            else if (matriz_fondo[i][j] == "1") {
>>>>>>> Oviedo
                // Paredes LATERALES (Izquierda o Derecha)
                if (j == 0) {
                    rectangulo.setTexture(tex_pared_izq);
                }
                else {
                    rectangulo.setTexture(tex_pared_der);
                }
                ventana.draw(rectangulo);
            }
            else if (matriz_fondo[i][j] == "2") {
                // Paredes SUPERIOR o INFERIOR (Arriba o Abajo)
                if (i == 0) {
                    rectangulo.setTexture(tex_pared_arriba);
                }
                else {
                    rectangulo.setTexture(tex_pared_abajo);
                }
                ventana.draw(rectangulo);
            }
            else if (matriz_fondo[i][j] == "S") {
                rectangulo.setTexture(tex_suelo);
                ventana.draw(rectangulo);
                rectangulo.setTexture(tex_salida);
                ventana.draw(rectangulo);
            }

            if (matriz_entidades[i][j] != "") {
                if (matriz_entidades[i][j] == "P") {
                    rectangulo.setTexture(tex_prota);
                }
                else if (matriz_entidades[i][j] == "E") {
                    rectangulo.setTexture(tex_enemigo);
                }
                else if (matriz_entidades[i][j] == "M") {
                    rectangulo.setTexture(tex_mercader);
                }
                else if (matriz_entidades[i][j] == "B") {
                    rectangulo.setTexture(tex_boss);
                }
                else if (matriz_entidades[i][j] == "C") {
                    rectangulo.setTexture(tex_cofre);
                }
                ventana.draw(rectangulo);
            }
        }
    }
}