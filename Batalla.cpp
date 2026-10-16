#include "Batalla.h"
#include <cstdlib>

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
