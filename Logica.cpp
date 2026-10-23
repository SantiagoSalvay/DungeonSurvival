#include "Logica.h"
#include <cstdlib>
#include <ctime>

// REGLAS DEL JUEGO
#include<iostream>


using namespace std;

// --- LOGICA DE MOVIMIENTO EN LA MATRIZ ---
void moverpj(personaje& pj, char direccion, string matriz_fondo[max_filas][max_columnas], string matriz_entidades[max_filas][max_columnas]) {

	int nueva_fila = pj.posicion_y;
	int nueva_columna = pj.posicion_x;

	switch (direccion) {
	case 'W': nueva_fila = nueva_fila - 1; break;
	case 'S': nueva_fila = nueva_fila + 1; break;
	case 'A': nueva_columna = nueva_columna - 1; break;
	case 'D': nueva_columna = nueva_columna + 1; break;
	}

	// 1. Verificamos choque con la pared del fondo
	string bloque_destino = matriz_fondo[nueva_fila][nueva_columna];
	if (bloque_destino == "1" or bloque_destino == "2" or bloque_destino == "S") {
		return; // Frena el movimiento
	}

	// 2. Verificamos choque con una entidad (cofre, enemigo, etc)
	string bloque_destino2 = matriz_entidades[nueva_fila][nueva_columna];
	if (bloque_destino2 != "") {
		return; // Frena el movimiento
	}

	// 3. Si esta libre, vaciamos la celda vieja y movemos la 'P' a la nueva
	matriz_entidades[pj.posicion_y][pj.posicion_x] = "";
	pj.posicion_y = nueva_fila;
	pj.posicion_x = nueva_columna;
	matriz_entidades[pj.posicion_y][pj.posicion_x] = "P";
}

// --- LOGICA DE INTERACCION EN LAS 4 DIRECCIONES ---
char interactuar(personaje& pj, string matriz_entidades[max_filas][max_columnas], string matriz_fondo[max_filas][max_columnas], cofre& cofre_resultado) {

	int pj_x = pj.posicion_x;
	int pj_y = pj.posicion_y;

	string deteccion = "";
	int det_x = -1, det_y = -1;

	// Mira arriba
	if (pj_y - 1 >= 0 and (matriz_entidades[pj_y - 1][pj_x] != "" or matriz_fondo[pj_y - 1][pj_x] == "S")) {
		if (matriz_entidades[pj_y - 1][pj_x] != "") deteccion = matriz_entidades[pj_y - 1][pj_x];
		else deteccion = matriz_fondo[pj_y - 1][pj_x];
		det_y = pj_y - 1;
		det_x = pj_x;
	}
	// Mira abajo
	else if (pj_y + 1 < max_filas and (matriz_entidades[pj_y + 1][pj_x] != "" or matriz_fondo[pj_y + 1][pj_x] == "S")) {
		if (matriz_entidades[pj_y + 1][pj_x] != "") deteccion = matriz_entidades[pj_y + 1][pj_x];
		else deteccion = matriz_fondo[pj_y + 1][pj_x];
		det_y = pj_y + 1;
		det_x = pj_x;
	}
	// Mira a la derecha
	else if (pj_x + 1 < max_columnas and (matriz_entidades[pj_y][pj_x + 1] != "" or matriz_fondo[pj_y][pj_x + 1] == "S")) {
		if (matriz_entidades[pj_y][pj_x + 1] != "") deteccion = matriz_entidades[pj_y][pj_x + 1];
		else deteccion = matriz_fondo[pj_y][pj_x + 1];
		det_y = pj_y;
		det_x = pj_x + 1;
	}
	// Mira a la izquierda
	else if (pj_x - 1 >= 0 and (matriz_entidades[pj_y][pj_x - 1] != "" or matriz_fondo[pj_y][pj_x - 1] == "S")) {
		if (matriz_entidades[pj_y][pj_x - 1] != "") deteccion = matriz_entidades[pj_y][pj_x - 1];
		else deteccion = matriz_fondo[pj_y][pj_x - 1];
		det_y = pj_y;
		det_x = pj_x - 1;
	}

	// --- ACCIONES SEGUN LO QUE TOCO ---

	if (deteccion == "C") {
		cofre cofre_local;
		cofre_local.oro = rand() % 15 + 1; // 1 a 15 de oro

		int random_loot = rand() % 3;
		if (random_loot == 0) {
			// El loot DEBE quedar ordenado alfabeticamente para que fusionar() funcione bien
			cofre_local.loot[0] = "Basura Premium";
			cofre_local.loot[1] = "Daga Rota";
			cofre_local.cant_loot = 2;
		}
		else if (random_loot == 1) {
			cofre_local.loot[0] = "Armadura Ligera";
			cofre_local.loot[1] = "Pocion Grande";
			cofre_local.cant_loot = 2;
		}
		else {
			cofre_local.loot[0] = "Pocion Chica";
			cofre_local.loot[1] = "Pocion Chica";
			cofre_local.cant_loot = 2;
		}

		pj.oro = pj.oro + cofre_local.oro;

		string inventario_temporal[100];

		int nueva_cantidad = fusionar(pj.inventario, pj.cant_items, cofre_local.loot, cofre_local.cant_loot, inventario_temporal);

		for (int i = 0; i < nueva_cantidad; i++) {
			pj.inventario[i] = inventario_temporal[i];
		}
		pj.cant_items = nueva_cantidad;

		// Red de seguridad: garantizamos que el inventario quede ordenado tras fusionar el loot
		ordenarburbuja(pj.inventario, pj.cant_items);

		// Devolvemos las recompensas para que el menu pueda mostrar el cartel
		cofre_resultado.oro = cofre_local.oro;
		cofre_resultado.cant_loot = cofre_local.cant_loot;
		for (int i = 0; i < cofre_local.cant_loot; i++) {
			cofre_resultado.loot[i] = cofre_local.loot[i];
		}

		matriz_entidades[det_y][det_x] = ""; // Borramos el cofre del mapa
		return 'C';
	}

	else if (deteccion == "S") {
		bool quedan_enemigos = false;

		for (int i = 0; i < max_filas; i++) {
			for (int j = 0; j < max_columnas; j++) {
				if (matriz_entidades[i][j] == "E" || matriz_entidades[i][j] == "B") {
					quedan_enemigos = true;
				}
			}
		}

		if (quedan_enemigos == true) {
			return 'L'; // 'L' de Locked (Bloqueado)
		}
		else {
			return 'S'; // 'S' de Salida libre
		}
	}

	else if (deteccion == "M") {
		return 'M';
	}

	else if (deteccion == "E" || deteccion == "B") {
		return 'E';
	}

	return '0';
}

void completar(string v[], int tam, int pos, string c[], int& k) {
	while (pos < tam) {
		c[k] = v[pos];
		pos++;
		k++;
	}
}

int fusionar(string a[], int n, string b[], int m, string c[]) {
	int i = 0, j = 0, k = 0;

	while (i < n && j < m) {
		if (a[i] < b[j]) {
			c[k] = a[i];
			i++;
		}
		else {
			c[k] = b[j];
			j++;
		}
		k++;
	}

	if (i < n) completar(a, n, i, c, k);
	else completar(b, m, j, c, k);

	return n + m;
}

int obtenerprecioventa(string nombre_item) {
	if (nombre_item == "Pocion Chica") return 7;
	if (nombre_item == "Pocion Grande") return 17;
	if (nombre_item == "Daga Rota") return 15;
	if (nombre_item == "Espada de Hierro") return 25;
	if (nombre_item == "Armadura Ligera") return 17;
	if (nombre_item == "Armadura Pesada") return 30;
	if (nombre_item == "Basura Premium") return 2;
	return 1;
}

int buscaritem(string v[], int n, string x) {
	int posicion = 0;
	for (int i = 0; i < n; i++) {
		if (x == v[i]) {
			posicion = i;
		}
	}
	return posicion;
}

void ordenarburbuja(string v[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (v[i] > v[j]) {
				string aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}

void ordenarmercader(string catalogo[], int precios[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (catalogo[i] > catalogo[j]) {
				string aux1 = catalogo[i];
				catalogo[i] = catalogo[j];
				catalogo[j] = aux1;

				int aux2 = precios[i];
				precios[i] = precios[j];
				precios[j] = aux2;
			}
		}
	}
}

int obtenerataque(string arma_nombre) {
	if (arma_nombre == "Palo") return 2;
	if (arma_nombre == "Daga Rota") return 4;
	if (arma_nombre == "Espada de Hierro") return 12;
	return 0;
}

int obtenerdefensa(string armadura_nombre) {
	if (armadura_nombre == "Armadura Ligera") return 25; 
	if (armadura_nombre == "Armadura Pesada") return 50; 
	return 0;
}

// BUSQUEDAS Y ORDENAMIENTOS
void ordenarBurbuja(string v[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (v[i] > v[j]) {
				string aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}

void ordenarParalelo(string claves[], int valores[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (claves[i] > claves[j]) {
				string auxc = claves[i];
				claves[i] = claves[j];
				claves[j] = auxc;

				int auxv = valores[i];
				valores[i] = valores[j];
				valores[j] = auxv;
			}
		}
	}
}

int busquedaBinaria(const string v[], int n, const string& x) {
	int izq = 0, der = n - 1;
	while (izq <= der) {
		int medio = (izq + der) / 2;
		if (v[medio] == x) return medio;
		if (v[medio] < x) izq = medio + 1;
		else der = medio - 1;
	}
	throw ErrorItemNoEncontrado("No se encontro el item: " + x);
}

int busquedaBinariaParalelo(const string claves[], int n, const string& x) {
	int izq = 0, der = n - 1;
	while (izq <= der) {
		int medio = (izq + der) / 2;
		if (claves[medio] == x) return medio;
		if (claves[medio] < x) izq = medio + 1;
		else der = medio - 1;
	}
	throw ErrorItemNoEncontrado("No se encontro la clave: " + x);
}

// BATALLA POR TURNOS
void iniciarBatalla(EstadoBatalla& batalla, int pos_x, int pos_y, bool es_boss) {
    batalla.enemigo_pos_x = pos_x;
    batalla.enemigo_pos_y = pos_y;
    batalla.es_boss_actual = es_boss;
    inicializarenemigo(batalla.enemigo_actual, es_boss);
    batalla.enemigo_vida_max = batalla.enemigo_actual.vida;
    batalla.defendiendo = false;
    batalla.boss_se_curo = false;
    if (es_boss) {
        batalla.fase = fase_batalla::cinematica_boss;
        batalla.mensaje = "";
    }
    else {
        batalla.fase = fase_batalla::espera_input;
        batalla.mensaje = "Un enemigo se cruza en tu camino!";
    }
    batalla.reloj_anim.restart();
}

void iniciarTurnoEnemigo(EstadoBatalla& batalla) {
    if (batalla.es_boss_actual && batalla.boss_se_curo && (std::rand() % 100) < 25) {
        batalla.fase = fase_batalla::cinematica_golpe_devastador;
    }
    else {
        batalla.fase = fase_batalla::anim_enemigo_ataca;
    }
}

void actualizarTurnoBatalla(EstadoBatalla& batalla, personaje& paolo, string matriz_entidades[max_filas][max_columnas]) {
    float t_anim = batalla.reloj_anim.getElapsedTime().asSeconds();

    if (batalla.fase == fase_batalla::anim_pj_ataca && t_anim >= DURACION_ANIM_BATALLA) {
        // Si peleamos contra el boss, hay 33% de chance de fallar el ataque por miedo
        bool fallo_por_miedo = false;
        if (batalla.es_boss_actual && (std::rand() % 100) < 33) {
            fallo_por_miedo = true;
        }

        if (fallo_por_miedo) {
            batalla.mensaje = "Te paralizas de miedo y fallas el ataque!";
            batalla.reloj_anim.restart();
            iniciarTurnoEnemigo(batalla);
        }
        else {
            // El jugador hace ~150% del dano base (ventaja clara contra enemigos)
            int dano_base = (paolo.ataque * 3) / 2 + (std::rand() % 6);
            int dano_real = dano_base - batalla.enemigo_actual.defensa;
            if (dano_real < 2) dano_real = 2;
            batalla.enemigo_actual.vida -= dano_real;

            if (batalla.enemigo_actual.vida <= 0) {
                batalla.enemigo_actual.vida = 0;
                // Recompensa segun tipo de enemigo
                int recompensa = batalla.es_boss_actual ? (60 + std::rand() % 41) : (10 + std::rand() % 16);
                paolo.oro += recompensa;
                // Borramos al enemigo del mapa
                if (batalla.enemigo_pos_x >= 0 && batalla.enemigo_pos_y >= 0 &&
                    batalla.enemigo_pos_y < max_filas && batalla.enemigo_pos_x < max_columnas) {
                    matriz_entidades[batalla.enemigo_pos_y][batalla.enemigo_pos_x] = "";
                }
                if (batalla.es_boss_actual) {
                    batalla.mensaje = "Ganaste " + std::to_string(recompensa) + " de oro!";
                    batalla.fase = fase_batalla::victoria_final;
                    batalla.reloj_anim.restart();
                    // La partida fue ganada: la borramos del archivo para que no quede como cargable
                    eliminarPartidaPorNombre(paolo.name);
                }
                else {
                    batalla.mensaje = "Victoria! Causaste " + std::to_string(dano_real) +
                        " de dano final. Ganaste " + std::to_string(recompensa) + " de oro. (ENTER)";
                    batalla.fase = fase_batalla::ganada;
                    // Solo guardamos automaticamente tras vencer enemigos normales
                    guardarPartida(paolo, matriz_entidades);
                }
            }
            // Si es el boss, esta debilitado y nunca se curo, gatillamos la cinematica de regeneracion
            else if (batalla.es_boss_actual && !batalla.boss_se_curo &&
                     batalla.enemigo_actual.vida <= (batalla.enemigo_vida_max * 30) / 100) {
                batalla.boss_se_curo = true;
                batalla.mensaje = "El Guardian se enfurece y libera su poder!";
                batalla.reloj_anim.restart();
                batalla.fase = fase_batalla::cinematica_curacion_boss;
            }
            else {
                batalla.mensaje = "Causaste " + std::to_string(dano_real) + " de dano al " + batalla.enemigo_actual.nombre + ".";
                batalla.reloj_anim.restart();
                iniciarTurnoEnemigo(batalla);
            }
        }
    }
    else if (batalla.fase == fase_batalla::anim_enemigo_ataca && t_anim >= DURACION_ANIM_BATALLA) {
        // Multiplicadores de dano:
        //   - enemigo comun: 70%
        //   - boss antes de regenerarse: 80%
        //   - boss tras regenerarse (modo enfurecido): 160% + bonus de aleatoriedad mayor
        int multiplicador;
        int rango_random;
        if (batalla.es_boss_actual && batalla.boss_se_curo) {
            multiplicador = 160;
            rango_random = 8;
        }
        else if (batalla.es_boss_actual) {
            multiplicador = 80;
            rango_random = 4;
        }
        else {
            multiplicador = 70;
            rango_random = 3;
        }
        int dano_base = (batalla.enemigo_actual.ataque * multiplicador) / 100 + (std::rand() % rango_random);
        int dano_real = dano_base - (paolo.defensa / 10);
        if (batalla.defendiendo) {
            dano_real = dano_real / 2;
            batalla.defendiendo = false;
        }
        if (dano_real < 1) dano_real = 1;
        paolo.vida -= dano_real;

        if (paolo.vida <= 0) {
            paolo.vida = 0;
            batalla.mensaje = "Has caido en batalla...";
            batalla.reloj_anim.restart();
            batalla.fase = fase_batalla::perdida;
        }
        else {
            if (batalla.es_boss_actual && batalla.boss_se_curo) {
                batalla.mensaje = "El " + batalla.enemigo_actual.nombre + " enfurecido te golpea por " +
                    std::to_string(dano_real) + "! Tu turno (1/2/3/4)";
            }
            else {
                batalla.mensaje = "El " + batalla.enemigo_actual.nombre + " te causa " +
                    std::to_string(dano_real) + " de dano. Tu turno! (1/2/3/4)";
            }
            batalla.fase = fase_batalla::espera_input;
        }
    }
    else if (batalla.fase == fase_batalla::anim_pocion && t_anim >= DURACION_ANIM_BATALLA) {
        // Tras curarse, ataca el enemigo
        batalla.reloj_anim.restart();
        iniciarTurnoEnemigo(batalla);
    }
    else if (batalla.fase == fase_batalla::cinematica_curacion_boss && t_anim >= DURACION_CURACION_BOSS) {
        // El boss recupera el 50% de su HP maxima
        batalla.enemigo_actual.vida += batalla.enemigo_vida_max / 2;
        if (batalla.enemigo_actual.vida > batalla.enemigo_vida_max) batalla.enemigo_actual.vida = batalla.enemigo_vida_max;

        batalla.mensaje = "El Guardian se prepara para un ATAQUE DEVASTADOR!";
        batalla.reloj_anim.restart();
        batalla.fase = fase_batalla::cinematica_ataque_especial_boss;
    }
    else if (batalla.fase == fase_batalla::cinematica_ataque_especial_boss && t_anim >= DURACION_ATAQUE_ESPECIAL_BOSS) {
        // Aplica un ataque especial: doble dano contra el jugador
        int dano_base = (batalla.enemigo_actual.ataque * 80) / 100 + (std::rand() % 4);
        int dano_real = (dano_base * 2) - (paolo.defensa / 10);
        if (batalla.defendiendo) {
            dano_real = dano_real / 2;
            batalla.defendiendo = false;
        }
        if (dano_real < 1) dano_real = 1;
        paolo.vida -= dano_real;

        if (paolo.vida <= 0) {
            paolo.vida = 0;
            batalla.mensaje = "El ataque especial te derroto...";
            batalla.reloj_anim.restart();
            batalla.fase = fase_batalla::perdida;
        }
        else {
            batalla.mensaje = "El ataque especial te causa " + std::to_string(dano_real) +
                " de dano! Tu turno. (1/2/3)";
            batalla.fase = fase_batalla::espera_input;
        }
    }
    else if (batalla.fase == fase_batalla::cinematica_golpe_devastador && t_anim >= DURACION_GOLPE_DEVASTADOR) {
        // Golpe devastador: 1.5x del ataque base del boss
        int dano_base = (batalla.enemigo_actual.ataque * 80) / 100 + (std::rand() % 4);
        int dano_real = (dano_base * 3) / 2 - (paolo.defensa / 10);
        if (batalla.defendiendo) {
            dano_real = dano_real / 2;
            batalla.defendiendo = false;
        }
        if (dano_real < 1) dano_real = 1;
        paolo.vida -= dano_real;

        if (paolo.vida <= 0) {
            paolo.vida = 0;
            batalla.mensaje = "El golpe devastador te derroto...";
            batalla.reloj_anim.restart();
            batalla.fase = fase_batalla::perdida;
        }
        else {
            batalla.mensaje = "El golpe devastador te causa " + std::to_string(dano_real) +
                " de dano! Tu turno. (1/2/3)";
            batalla.fase = fase_batalla::espera_input;
        }
    }
}

void manejarEntradaBatalla(
    EstadoBatalla& batalla,
    personaje& paolo,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
) {
    // Si la batalla termino, ENTER vuelve al juego o al menu
    if (batalla.fase == fase_batalla::ganada || batalla.fase == fase_batalla::huida) {
        if (tecla == sf::Keyboard::Key::Enter) {
            estado_actual = jugando;
        }
    }
    else if (batalla.fase == fase_batalla::victoria_final) {
        // Tras vencer al boss, ENTER lleva al menu principal con la partida terminada
        if (tecla == sf::Keyboard::Key::Enter) {
            estado_actual = menu_principal;
        }
    }
    else if (batalla.fase == fase_batalla::perdida) {
        // Solo aceptamos ENTER tras la cinematica de derrota
        if (tecla == sf::Keyboard::Key::Enter &&
            batalla.reloj_anim.getElapsedTime().asSeconds() >= DURACION_DERROTA) {
            // Resetea al protagonista y vuelve al menu
            protagonista(paolo);
            cargarnivel(paolo.nivel_actual, matriz_fondo, matriz_entidades);
            estado_actual = menu_principal;
        }
    }
    else if (batalla.fase == fase_batalla::cinematica_boss) {
        // Permite saltear la cinematica con ENTER o ESC
        if (tecla == sf::Keyboard::Key::Enter || tecla == sf::Keyboard::Key::Escape) {
            batalla.fase = fase_batalla::espera_input;
            batalla.mensaje = "El Guardian de la Mazmorra te desafia! Que haces?";
            batalla.reloj_anim.restart();
        }
    }
    // Solo aceptamos input cuando es el turno del jugador
    else if (batalla.fase == fase_batalla::espera_input) {
        if (tecla == sf::Keyboard::Key::Num1) {
            batalla.reloj_anim.restart();
            batalla.fase = fase_batalla::anim_pj_ataca;
            batalla.mensaje = "Atacas al " + batalla.enemigo_actual.nombre + "!";
        }
        else if (tecla == sf::Keyboard::Key::Num2) {
            // Busca una pocion en el inventario
            int idx_poc = -1;
            for (int i = 0; i < paolo.cant_items; i++) {
                if (paolo.inventario[i] == "Pocion Chica" ||
                    paolo.inventario[i] == "Pocion Pequena" ||
                    paolo.inventario[i] == "Pocion Grande") {
                    idx_poc = i;
                    break;
                }
            }
            if (idx_poc >= 0) {
                std::string nombre_poc = paolo.inventario[idx_poc];
                int curar = (nombre_poc == "Pocion Grande") ? 50 : 20;
                paolo.vida += curar;
                int vida_max = 100 + paolo.defensa;
                if (paolo.vida > vida_max) paolo.vida = vida_max;
                for (int i = idx_poc; i < paolo.cant_items - 1; i++) {
                    paolo.inventario[i] = paolo.inventario[i + 1];
                }
                paolo.cant_items--;
                batalla.mensaje = "Usaste " + nombre_poc + " (+" + std::to_string(curar) + " HP)";
                batalla.reloj_anim.restart();
                batalla.fase = fase_batalla::anim_pocion;
            }
            else {
                batalla.mensaje = "No tienes pociones para usar!";
            }
        }
        else if (tecla == sf::Keyboard::Key::Num3) {
            batalla.defendiendo = true;
            batalla.mensaje = "Te preparas para defender el proximo ataque.";
            batalla.reloj_anim.restart();
            iniciarTurnoEnemigo(batalla);
        }
        else if (tecla == sf::Keyboard::Key::Num4) {
            if (batalla.es_boss_actual) {
                batalla.mensaje = "No puedes huir del Boss!";
            }
            else {
                int chance = std::rand() % 100;
                if (chance < 55) {
                    batalla.mensaje = "Lograste huir del combate! (ENTER)";
                    batalla.fase = fase_batalla::huida;
                }
                else {
                    batalla.mensaje = "Fallaste la huida! El enemigo aprovecha y ataca!";
                    batalla.reloj_anim.restart();
                    iniciarTurnoEnemigo(batalla);
                }
            }
        }
    }
}

// ORQUESTACION DE TURNOS
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
