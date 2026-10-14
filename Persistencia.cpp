#include "Persistencia.h"
#include "ErroresMios.h"
#include <fstream>
#include <ctime>
#include <cstdlib>

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
