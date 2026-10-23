#pragma once
#include <string>
#include <exception>
#include <SFML/Graphics.hpp>
#include <vector>

// ESTRUCTURAS
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

// CONSTANTES DEL MAPA
using namespace std;
// Tamano mapa
const int max_filas = 10;
const int max_columnas = 10;

// Carga la matriz de fondo y de entidades del nivel pedido
void cargarnivel(int numero_nivel, string fondo_destino[max_filas][max_columnas], string entidades_destino[max_filas][max_columnas]);

// EXCEPCIONES
class ErrorDungeon : public std::exception {
public:
	explicit ErrorDungeon(const std::string& mensaje) : mensaje(mensaje) {}
	const char* what() const noexcept override { return mensaje.c_str(); }
private:
	std::string mensaje;
};

class ErrorArchivo : public ErrorDungeon {
public:
	explicit ErrorArchivo(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};

class ErrorPartidaNoEncontrada : public ErrorDungeon {
public:
	explicit ErrorPartidaNoEncontrada(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};

class ErrorIndiceInvalido : public ErrorDungeon {
public:
	explicit ErrorIndiceInvalido(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};

class ErrorItemNoEncontrado : public ErrorDungeon {
public:
	explicit ErrorItemNoEncontrado(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};

// PARTIDAS GUARDADAS
struct registro_partida {
	personaje pj;
	string entidades[max_filas][max_columnas];
	long long ultimo_guardado = 0;
};

std::vector<registro_partida> obtenerPartidas();
void guardarPartida(const personaje& pj, string matriz_entidades[max_filas][max_columnas]);
bool cargarPartida(personaje& pj, string matriz_entidades[max_filas][max_columnas]);
bool cargarPartidaPorIndice(personaje& pj, int indice, string matriz_entidades[max_filas][max_columnas]);
bool cargarPartidaPorIndice(personaje& pj, int indice);
bool eliminarPartidaPorIndice(int indice);
bool eliminarPartidaPorNombre(const std::string& nombre);

std::string formatearFecha(long long timestamp);

// ESTADO DEL JUEGO
// Pantallas posibles del juego
enum estado_pantalla { menu_principal, jugando, cargar, controles, reglas, creditos, en_tienda, en_batalla, en_inventario, confirmar_guardado, aviso_guardado, pedir_nombre, intro_historia };

// Fases del combate por turnos (incluye las cinematicas del boss)
enum class fase_batalla {
    cinematica_boss,
    espera_input,
    anim_pj_ataca,
    anim_enemigo_ataca,
    anim_pocion,
    cinematica_curacion_boss,
    cinematica_ataque_especial_boss,
    cinematica_golpe_devastador,
    ganada,
    victoria_final,
    perdida,
    huida
};

// Cuantas partidas guardadas se muestran a la vez en la pantalla de carga
constexpr int MAX_PARTIDAS_VISIBLES = 5;

// Duraciones (en segundos) de las animaciones y cinematicas de combate.
// Compartidas entre la logica de turnos y el dibujado.
constexpr float DURACION_ANIM_BATALLA = 0.55f;
constexpr float DURACION_CURACION_BOSS = 4.5f;
constexpr float DURACION_ATAQUE_ESPECIAL_BOSS = 4.0f;
constexpr float DURACION_GOLPE_DEVASTADOR = 3.8f;
constexpr float DURACION_DERROTA = 4.5f;

// --- Estado de la batalla por turnos ---
struct EstadoBatalla {
    fase_batalla fase = fase_batalla::espera_input;
    sf::Clock reloj_anim;
    enemigo enemigo_actual;
    int enemigo_pos_x = -1;
    int enemigo_pos_y = -1;
    int enemigo_vida_max = 0;
    bool es_boss_actual = false;
    bool defendiendo = false;
    bool boss_se_curo = false;
    std::string mensaje;
};

// --- Estado de navegacion/overlays de la UI (menu, pausa, guardado, tienda, inventario, etc.) ---
struct EstadoUI {
    // Menu principal
    int item_seleccionado = 0;

    // Pedir nombre / intro de historia
    std::string nombre_input;
    sf::Clock reloj_intro;
    sf::Clock reloj_cursor_nombre; // solo para el parpadeo del cursor del campo de nombre

    // Pausa (durante "jugando")
    bool en_pausa = false;
    int item_pausa = 0;

    // Confirmar guardado
    int item_confirmacion = 0;
    bool salir_despues_confirmacion = false;

    // Aviso de guardado y navegacion pendiente tras cerrarlo
    bool guardado_reciente = false;
    bool controles_desde_pausa = false;
    estado_pantalla estado_pendiente = jugando;

    // Cargar partida
    std::vector<registro_partida> partidas_guardadas;
    std::vector<sf::Text> opciones_carga;
    int item_carga = 0;
    int scroll_carga = 0;

    // Avisos en exploracion (puerta sellada, boss cercano, cofre abierto)
    bool aviso_puerta = false;
    bool aviso_cofre = false;
    bool aviso_boss = false;
    cofre cofre_resultado;
    std::string mensaje_cofre;

    // Tienda / inventario
    int cursor_tienda = 0;
    int cursor_inventario = 0;
    bool en_modo_compra = true;
};

// PERSISTENCIA ALTERNATIVA CON EXCEPCIONES
namespace persistencia {


struct partidaGuardada {
	personaje pj;
	string entidades[max_filas][max_columnas];
	long long ultimo_guardado = 0;
};

std::vector<partidaGuardada> listarPartidas();
void guardarPartidaPersistente(const personaje& pj, string entidades[max_filas][max_columnas]);
void cargarUltimaPartida(personaje& pj, string entidades[max_filas][max_columnas]);
void cargarPartidaPorIndice(personaje& pj, int indice, string entidades[max_filas][max_columnas]);
void eliminarPartidaPorNombre(string nombre);

}
