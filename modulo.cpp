#include "modulo.h"

// --- Responsabilidad 1: Datos del juego ---
personaje crearPersonajeVacio() {
	personaje pj;
	pj.name = "";
	pj.oro = 0;
	pj.vida = 0;
	pj.arma_equipada = "";
	pj.armadura_equipada = "";
	pj.ataque = 0;
	pj.defensa = 0;
	pj.nivel_actual = 0;
	pj.posicion_x = 0;
	pj.posicion_y = 0;
	pj.cant_items = 0;
	return pj;
}

// --- Responsabilidad 2: Inicializacion de las entidades ---
void inicializarEntidadesNivel(personaje& pj, mercader& vendedor, enemigo& en, bool es_boss) {
	protagonista(pj);
	inicializarmercader(vendedor);
	inicializarenemigo(en, es_boss);
}

// --- Responsabilidad 3: Mapas y dibujo ---
void cargarYDibujarNivel(
	int numero_nivel,
	string matriz_fondo[max_filas][max_columnas],
	string matriz_entidades[max_filas][max_columnas],
	sf::RenderWindow& ventana,
	sf::Texture& tex_suelo,
	sf::Texture& tex_pared_arriba, sf::Texture& tex_pared_abajo,
	sf::Texture& tex_pared_izq, sf::Texture& tex_pared_der,
	sf::Texture& tex_prota, sf::Texture& tex_boss, sf::Texture& tex_enemigo,
	sf::Texture& tex_mercader, sf::Texture& tex_cofre, sf::Texture& tex_salida
) {
	cargarnivel(numero_nivel, matriz_fondo, matriz_entidades);
	dibujarmapa(ventana, matriz_fondo, matriz_entidades,
		tex_suelo, tex_pared_arriba, tex_pared_abajo, tex_pared_izq, tex_pared_der,
		tex_prota, tex_boss, tex_enemigo, tex_mercader, tex_cofre, tex_salida);
}

// --- Responsabilidad 4: Movimiento e interaccion ---
char procesarTurno(
	personaje& pj, char direccion,
	string matriz_fondo[max_filas][max_columnas],
	string matriz_entidades[max_filas][max_columnas],
	cofre& cofre_resultado
) {
	moverpj(pj, direccion, matriz_fondo, matriz_entidades);
	return interactuar(pj, matriz_entidades, matriz_fondo, cofre_resultado);
}

// --- Responsabilidad 5: Guardado y carga de partidas ---
void guardarProgreso(const personaje& pj, string matriz_entidades[max_filas][max_columnas]) {
	guardarPartida(pj, matriz_entidades);
}

bool cargarProgreso(personaje& pj, string matriz_entidades[max_filas][max_columnas]) {
	return cargarPartida(pj, matriz_entidades);
}
