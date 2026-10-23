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

// PARTIDAS GUARDADAS
namespace {
	const char* archivo_partidas = "partidas.txt";

	bool leerRegistro(std::istream& input, registro_partida& registro, string entidades[max_filas][max_columnas]) {
		std::string linea;
		if (!std::getline(input, linea)) return false;
		if (linea != "#PARTIDA") return false;
		if (!std::getline(input, registro.pj.name)) return false;
		if (!std::getline(input, linea)) return false;
		registro.ultimo_guardado = std::stoll(linea);
		if (!std::getline(input, linea)) return false;
		registro.pj.oro = std::stoi(linea);
		if (!std::getline(input, linea)) return false;
		registro.pj.vida = std::stoi(linea);
		if (!std::getline(input, registro.pj.arma_equipada)) return false;
		if (!std::getline(input, registro.pj.armadura_equipada)) return false;
		if (!std::getline(input, linea)) return false;
		registro.pj.ataque = std::stoi(linea);
		if (!std::getline(input, linea)) return false;
		registro.pj.defensa = std::stoi(linea);
		if (!std::getline(input, linea)) return false;
		registro.pj.nivel_actual = std::stoi(linea);
		if (!std::getline(input, linea)) return false;
		registro.pj.posicion_x = std::stoi(linea);
		if (!std::getline(input, linea)) return false;
		registro.pj.posicion_y = std::stoi(linea);
		if (!std::getline(input, linea)) return false;
		registro.pj.cant_items = std::stoi(linea);
		for (int i = 0; i < registro.pj.cant_items; i++) {
			if (!std::getline(input, registro.pj.inventario[i])) return false;
		}
		if (!std::getline(input, linea)) return false;
		if (linea != "#ENTIDADES") return false;
		for (int i = 0; i < max_filas; i++) {
			for (int j = 0; j < max_columnas; j++) {
				if (!std::getline(input, entidades[i][j])) return false;
			}
		}
		return true;
	}

	void escribirregistro(std::ostream& output, const registro_partida& registro, const string (&entidades)[max_filas][max_columnas]) {
		output << "#PARTIDA\n";
		output << registro.pj.name << "\n";
		output << registro.ultimo_guardado << "\n";
		output << registro.pj.oro << "\n";
		output << registro.pj.vida << "\n";
		output << registro.pj.arma_equipada << "\n";
		output << registro.pj.armadura_equipada << "\n";
		output << registro.pj.ataque << "\n";
		output << registro.pj.defensa << "\n";
		output << registro.pj.nivel_actual << "\n";
		output << registro.pj.posicion_x << "\n";
		output << registro.pj.posicion_y << "\n";
		output << registro.pj.cant_items << "\n";
		for (int i = 0; i < registro.pj.cant_items; i++) {
			output << registro.pj.inventario[i] << "\n";
		}
		output << "#ENTIDADES\n";
		for (int i = 0; i < max_filas; i++) {
			for (int j = 0; j < max_columnas; j++) {
				output << entidades[i][j] << "\n";
			}
		}
	}

	long long tiempoAhora() {
		return static_cast<long long>(std::time(nullptr));
	}
}

std::vector<registro_partida> obtenerPartidas() {
	std::vector<registro_partida> partidas;
	std::ifstream archivo(archivo_partidas);
	if (!archivo.is_open()) {
		return partidas;
	}
	while (archivo.good()) {
		registro_partida registro;
		if (!leerRegistro(archivo, registro, registro.entidades)) {
			break;
		}
		partidas.push_back(registro);
	}
	return partidas;
}

void guardarPartida(const personaje& pj, string matriz_entidades[max_filas][max_columnas]) {
	std::vector<registro_partida> partidas = obtenerPartidas();
	bool actualizado = false;
	for (auto& registro : partidas) {
		if (registro.pj.name == pj.name) {
			registro.pj = pj;
			for (int i = 0; i < max_filas; i++) {
				for (int j = 0; j < max_columnas; j++) {
					registro.entidades[i][j] = matriz_entidades[i][j];
				}
			}
			registro.ultimo_guardado = tiempoAhora();
			actualizado = true;
			break;
		}
	}
	if (!actualizado) {
		registro_partida nuevo;
		nuevo.pj = pj;
		for (int i = 0; i < max_filas; i++) {
			for (int j = 0; j < max_columnas; j++) {
				nuevo.entidades[i][j] = matriz_entidades[i][j];
			}
		}
		nuevo.ultimo_guardado = tiempoAhora();
		partidas.push_back(nuevo);
	}
	std::ofstream archivo(archivo_partidas, std::ios::trunc);
	if (!archivo.is_open()) {
		return;
	}
	for (const auto& registro : partidas) {
		escribirregistro(archivo, registro, registro.entidades);
	}
}

bool cargarPartida(personaje& pj, string matriz_entidades[max_filas][max_columnas]) {
	std::vector<registro_partida> partidas = obtenerPartidas();
	if (partidas.empty()) {
		return false;
	}
	int indice_seleccion = 0;
	for (int i = 1; i < static_cast<int>(partidas.size()); i++) {
		if (partidas[i].ultimo_guardado > partidas[indice_seleccion].ultimo_guardado) {
			indice_seleccion = i;
		}
	}
	pj = partidas[indice_seleccion].pj;
	for (int i = 0; i < max_filas; i++) {
		for (int j = 0; j < max_columnas; j++) {
			matriz_entidades[i][j] = partidas[indice_seleccion].entidades[i][j];
		}
	}
	return true;
}

bool cargarPartidaPorIndice(personaje& pj, int indice, string matriz_entidades[max_filas][max_columnas]) {
	std::vector<registro_partida> partidas = obtenerPartidas();
	if (indice < 0 || indice >= static_cast<int>(partidas.size())) {
		return false;
	}
	pj = partidas[indice].pj;
	for (int i = 0; i < max_filas; i++) {
		for (int j = 0; j < max_columnas; j++) {
			matriz_entidades[i][j] = partidas[indice].entidades[i][j];
		}
	}
	return true;
}

bool eliminarPartidaPorIndice(int indice) {
	std::vector<registro_partida> partidas = obtenerPartidas();
	if (indice < 0 || indice >= static_cast<int>(partidas.size())) {
		return false;
	}
	partidas.erase(partidas.begin() + indice);
	std::ofstream archivo(archivo_partidas, std::ios::trunc);
	if (!archivo.is_open()) {
		return false;
	}
	for (const auto& registro : partidas) {
		escribirregistro(archivo, registro, registro.entidades);
	}
	return true;
}

// Elimina del archivo la partida guardada con el nombre dado.
// Se usa al ganar el juego, para que la partida "completada" no quede como cargable.
// Si el nombre esta vacio NO hace nada, asi evitamos borrar masivamente partidas
// viejas que tengan name vacio.
bool eliminarPartidaPorNombre(const std::string& nombre) {
	if (nombre.empty()) {
		return false;
	}
	std::vector<registro_partida> partidas = obtenerPartidas();
	bool elimino = false;
	for (int i = static_cast<int>(partidas.size()) - 1; i >= 0; i--) {
		if (partidas[i].pj.name == nombre) {
			partidas.erase(partidas.begin() + i);
			elimino = true;
		}
	}
	if (!elimino) return false;
	std::ofstream archivo(archivo_partidas, std::ios::trunc);
	if (!archivo.is_open()) {
		return false;
	}
	for (const auto& registro : partidas) {
		escribirregistro(archivo, registro, registro.entidades);
	}
	return true;
}

// Convierte un timestamp epoch en una cadena legible "dd/mm/aaaa hh:mm"
std::string formatearFecha(long long timestamp) {
	if (timestamp <= 0) return "Sin fecha";
	std::time_t t = static_cast<std::time_t>(timestamp);
	std::tm tm_local{};
#ifdef _WIN32
	localtime_s(&tm_local, &t);
#else
	tm_local = *std::localtime(&t);
#endif
	char buffer[32];
	std::strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", &tm_local);
	return std::string(buffer);
}

// PERSISTENCIA ALTERNATIVA
namespace persistencia {



namespace {
	const char* archivo_persistencia = "partidas.txt";

	long long tiempoActual() {
		return static_cast<long long>(std::time(nullptr));
	}

	bool leerUnaPartida(std::istream& entrada, partidaGuardada& registro) {
		string linea;
		getline(entrada, linea);
		if (linea != "#PARTIDA") return false;

		if (!getline(entrada, registro.pj.name)) return false;

		getline(entrada, linea);
		registro.ultimo_guardado = atoll(linea.c_str());

		getline(entrada, linea);
		registro.pj.oro = atoi(linea.c_str());

		getline(entrada, linea);
		registro.pj.vida = atoi(linea.c_str());

		getline(entrada, registro.pj.arma_equipada);
		getline(entrada, registro.pj.armadura_equipada);

		getline(entrada, linea);
		registro.pj.ataque = atoi(linea.c_str());

		getline(entrada, linea);
		registro.pj.defensa = atoi(linea.c_str());

		getline(entrada, linea);
		registro.pj.nivel_actual = atoi(linea.c_str());

		getline(entrada, linea);
		registro.pj.posicion_x = atoi(linea.c_str());

		getline(entrada, linea);
		registro.pj.posicion_y = atoi(linea.c_str());

		getline(entrada, linea);
		registro.pj.cant_items = atoi(linea.c_str());

		for (int i = 0; i < registro.pj.cant_items; i++) {
			getline(entrada, registro.pj.inventario[i]);
		}

		getline(entrada, linea);
		if (linea != "#ENTIDADES") return false;

		for (int i = 0; i < max_filas; i++) {
			for (int j = 0; j < max_columnas; j++) {
				getline(entrada, registro.entidades[i][j]);
			}
		}

		if (!entrada) return false;

		return true;
	}

	void escribirUnaPartida(std::ostream& salida, const partidaGuardada& registro) {
		salida << "#PARTIDA\n";
		salida << registro.pj.name << "\n";
		salida << registro.ultimo_guardado << "\n";
		salida << registro.pj.oro << "\n";
		salida << registro.pj.vida << "\n";
		salida << registro.pj.arma_equipada << "\n";
		salida << registro.pj.armadura_equipada << "\n";
		salida << registro.pj.ataque << "\n";
		salida << registro.pj.defensa << "\n";
		salida << registro.pj.nivel_actual << "\n";
		salida << registro.pj.posicion_x << "\n";
		salida << registro.pj.posicion_y << "\n";
		salida << registro.pj.cant_items << "\n";
		for (int i = 0; i < registro.pj.cant_items; i++) {
			salida << registro.pj.inventario[i] << "\n";
		}
		salida << "#ENTIDADES\n";
		for (int i = 0; i < max_filas; i++) {
			for (int j = 0; j < max_columnas; j++) {
				salida << registro.entidades[i][j] << "\n";
			}
		}
	}

	void reescribirArchivo(std::vector<partidaGuardada>& partidas) {
		std::ofstream salida(archivo_persistencia, std::ios::trunc);
		if (!salida.is_open()) {
			throw ErrorArchivo("no pude abrir partidas.txt para guardar");
		}
		for (int i = 0; i < static_cast<int>(partidas.size()); i++) {
			escribirUnaPartida(salida, partidas[i]);
		}
	}
}

std::vector<partidaGuardada> listarPartidas() {
	std::vector<partidaGuardada> partidas;
	std::ifstream entrada(archivo_persistencia);
	if (!entrada.is_open()) {
		return partidas;
	}
	while (entrada.good()) {
		partidaGuardada registro;
		if (!leerUnaPartida(entrada, registro)) break;
		partidas.push_back(registro);
	}
	return partidas;
}

void guardarPartidaPersistente(const personaje& pj, string entidades[max_filas][max_columnas]) {
	std::vector<partidaGuardada> partidas = listarPartidas();
	bool actualizado = false;

	for (int i = 0; i < static_cast<int>(partidas.size()); i++) {
		if (partidas[i].pj.name == pj.name) {
			partidas[i].pj = pj;
			for (int f = 0; f < max_filas; f++) {
				for (int c = 0; c < max_columnas; c++) {
					partidas[i].entidades[f][c] = entidades[f][c];
				}
			}
			partidas[i].ultimo_guardado = tiempoActual();
			actualizado = true;
			break;
		}
	}

	if (!actualizado) {
		partidaGuardada nueva;
		nueva.pj = pj;
		for (int f = 0; f < max_filas; f++) {
			for (int c = 0; c < max_columnas; c++) {
				nueva.entidades[f][c] = entidades[f][c];
			}
		}
		nueva.ultimo_guardado = tiempoActual();
		partidas.push_back(nueva);
	}

	reescribirArchivo(partidas);
}

void cargarUltimaPartida(personaje& pj, string entidades[max_filas][max_columnas]) {
	std::vector<partidaGuardada> partidas = listarPartidas();
	if (partidas.size() == 0) {
		throw ErrorPartidaNoEncontrada("no hay ninguna partida guardada");
	}

	int mejor = 0;
	for (int i = 1; i < static_cast<int>(partidas.size()); i++) {
		if (partidas[i].ultimo_guardado > partidas[mejor].ultimo_guardado) {
			mejor = i;
		}
	}

	pj = partidas[mejor].pj;
	for (int f = 0; f < max_filas; f++) {
		for (int c = 0; c < max_columnas; c++) {
			entidades[f][c] = partidas[mejor].entidades[f][c];
		}
	}
}

void cargarPartidaPorIndice(personaje& pj, int indice, string entidades[max_filas][max_columnas]) {
	std::vector<partidaGuardada> partidas = listarPartidas();
	if (indice < 0 || indice >= static_cast<int>(partidas.size())) {
		throw ErrorIndiceInvalido("ese indice de partida no existe");
	}

	pj = partidas[indice].pj;
	for (int f = 0; f < max_filas; f++) {
		for (int c = 0; c < max_columnas; c++) {
			entidades[f][c] = partidas[indice].entidades[f][c];
		}
	}
}

void eliminarPartidaPorNombre(string nombre) {
	if (nombre == "") {
		throw ErrorPartidaNoEncontrada("el nombre vino vacio");
	}

	std::vector<partidaGuardada> partidas = listarPartidas();
	bool elimino = false;
	for (int i = static_cast<int>(partidas.size()) - 1; i >= 0; i--) {
		if (partidas[i].pj.name == nombre) {
			partidas.erase(partidas.begin() + i);
			elimino = true;
		}
	}

	if (!elimino) {
		throw ErrorPartidaNoEncontrada("no encontre una partida con ese nombre");
	}

	reescribirArchivo(partidas);
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


