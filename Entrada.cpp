#include "Entrada.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>

// TECLADO
void manejarTextoNombre(std::string& nombre_input, std::uint32_t code) {
    if (code == 8) { // Backspace
        if (!nombre_input.empty()) {
            nombre_input.pop_back();
        }
    }
    else if (code >= 32 && code < 127) { // ASCII imprimible
        if (nombre_input.length() < 15) {
            nombre_input += static_cast<char>(code);
        }
    }
}

void manejarTeclaMenuPrincipal(
    EstadoUI& ui,
    RecursosVisuales& recursos,
    sf::RenderWindow& window,
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
) {
    if (tecla == sf::Keyboard::Key::W || tecla == sf::Keyboard::Key::Up) {
        moverarriba(ui.item_seleccionado, recursos.opciones_menu);
    }
    else if (tecla == sf::Keyboard::Key::S || tecla == sf::Keyboard::Key::Down) {
        moverabajo(ui.item_seleccionado, recursos.opciones_menu);
    }
    else if (tecla == sf::Keyboard::Key::Enter) {
        switch (ui.item_seleccionado) {
        case 0:
            // Nueva partida: primero pedimos el nombre del personaje
            ui.nombre_input = "";
            estado_actual = pedir_nombre;
            break;
        case 1:
            ui.partidas_guardadas = obtenerPartidas();
            std::sort(ui.partidas_guardadas.begin(), ui.partidas_guardadas.end(), [](const registro_partida& a, const registro_partida& b) {
                return a.ultimo_guardado > b.ultimo_guardado;
            });
            ui.opciones_carga.clear();
            ui.item_carga = 0;
            ui.scroll_carga = 0;
            for (int i = 0; i < static_cast<int>(ui.partidas_guardadas.size()); i++) {
                const registro_partida& registro = ui.partidas_guardadas[i];
                std::string nombre_mostrado = registro.pj.name.empty() ? std::string("Paolo") : registro.pj.name;
                std::ostringstream linea;
                linea << (i + 1) << ") " << nombre_mostrado
                    << " - Nivel " << registro.pj.nivel_actual
                    << " - Oro " << registro.pj.oro << "\n"
                    << "      " << formatearFecha(registro.ultimo_guardado);
                sf::Text texto(recursos.alagard);
                texto.setString(linea.str());
                texto.setCharacterSize(22);
                texto.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
                texto.setLineSpacing(1.2f);
                auto bounds = texto.getLocalBounds();
                texto.setOrigin({ bounds.size.x / 2.0f, 0.0f });
                texto.setPosition({ window.getSize().x / 2.0f, 160.0f + (i * 70.0f) });
                ui.opciones_carga.push_back(texto);
            }
            estado_actual = cargar;
            break;
        case 2: estado_actual = controles; break;
        case 3: estado_actual = reglas; break;
        case 4: estado_actual = creditos; break;
        case 5: window.close(); break;
        }
    }
}

void manejarTeclaPedirNombre(
    EstadoUI& ui,
    personaje& paolo,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
) {
    if (tecla == sf::Keyboard::Key::Enter) {
        // Si el campo esta vacio, dejamos el nombre por defecto
        std::string nombre_final = ui.nombre_input.empty() ? std::string("Paolo") : ui.nombre_input;
        // Quitamos espacios al inicio/final
        while (!nombre_final.empty() && nombre_final.front() == ' ') nombre_final.erase(0, 1);
        while (!nombre_final.empty() && nombre_final.back() == ' ') nombre_final.pop_back();
        if (nombre_final.empty()) nombre_final = "Paolo";

        // Reseteamos el protagonista y el mapa para arrancar una partida limpia
        mercader vendedor_descartable;
        enemigo enemigo_descartable;
        paolo = crearPersonajeVacio();
        inicializarEntidadesNivel(paolo, vendedor_descartable, enemigo_descartable, false);
        paolo.name = nombre_final;
        cargarnivel(paolo.nivel_actual, matriz_fondo, matriz_entidades);
        // Antes de empezar, mostramos la cinematica de introduccion
        ui.reloj_intro.restart();
        estado_actual = intro_historia;
    }
    else if (tecla == sf::Keyboard::Key::Escape) {
        // Cancelar: vuelve al menu
        estado_actual = menu_principal;
    }
}

void manejarTeclaIntro(estado_pantalla& estado_actual, sf::Keyboard::Key tecla) {
    // Solo aceptamos E (o ENTER) para empezar el juego
    if (tecla == sf::Keyboard::Key::E || tecla == sf::Keyboard::Key::Enter) {
        estado_actual = jugando;
    }
}

void manejarTeclaReglasControlesCreditos(EstadoUI& ui, estado_pantalla& estado_actual, sf::Keyboard::Key tecla) {
    if (estado_actual == controles && ui.controles_desde_pausa) {
        // Si vinimos desde la pausa, ESC vuelve al juego (no al menu)
        if (tecla == sf::Keyboard::Key::Escape || tecla == sf::Keyboard::Key::Enter) {
            ui.controles_desde_pausa = false;
            estado_actual = jugando;
        }
    }
    else if (tecla == sf::Keyboard::Key::Enter || tecla == sf::Keyboard::Key::Escape) {
        estado_actual = menu_principal;
    }
}

void manejarTeclaCargar(
    EstadoUI& ui,
    personaje& paolo,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
) {
    if (ui.opciones_carga.empty()) {
        if (tecla == sf::Keyboard::Key::Enter || tecla == sf::Keyboard::Key::Escape) {
            estado_actual = menu_principal;
        }
        return;
    }

    if (tecla == sf::Keyboard::Key::Escape) {
        estado_actual = menu_principal;
    }
    else if (tecla == sf::Keyboard::Key::W || tecla == sf::Keyboard::Key::Up) {
        // Navegacion arriba con auto-scroll: si el cursor sale del rango visible, ajustamos scroll
        if (ui.item_carga - 1 >= 0) {
            ui.opciones_carga[ui.item_carga].setFillColor(sf::Color::White);
            ui.item_carga--;
            ui.opciones_carga[ui.item_carga].setFillColor(sf::Color::Red);
            if (ui.item_carga < ui.scroll_carga) {
                ui.scroll_carga = ui.item_carga;
            }
        }
    }
    else if (tecla == sf::Keyboard::Key::S || tecla == sf::Keyboard::Key::Down) {
        // Navegacion abajo con auto-scroll: si el cursor sale del rango visible, ajustamos scroll
        if (ui.item_carga + 1 < static_cast<int>(ui.opciones_carga.size())) {
            ui.opciones_carga[ui.item_carga].setFillColor(sf::Color::White);
            ui.item_carga++;
            ui.opciones_carga[ui.item_carga].setFillColor(sf::Color::Red);
            if (ui.item_carga >= ui.scroll_carga + MAX_PARTIDAS_VISIBLES) {
                ui.scroll_carga = ui.item_carga - MAX_PARTIDAS_VISIBLES + 1;
            }
        }
    }
    else if (tecla == sf::Keyboard::Key::Enter) {
        if (ui.item_carga >= 0 && ui.item_carga < static_cast<int>(ui.partidas_guardadas.size())) {
            // Cargamos DIRECTO desde la lista ya ordenada por fecha.
            // La primera de la lista es la mas reciente, que es justo la que carga cargarProgreso.
            bool cargada = false;
            if (ui.item_carga == 0) {
                cargada = cargarProgreso(paolo, matriz_entidades);
            }
            if (!cargada) {
                const registro_partida& partida_seleccionada = ui.partidas_guardadas[ui.item_carga];
                paolo = partida_seleccionada.pj;
                for (int i = 0; i < max_filas; i++) {
                    for (int j = 0; j < max_columnas; j++) {
                        matriz_entidades[i][j] = partida_seleccionada.entidades[i][j];
                    }
                }
            }
            // Si la partida guardada tiene nombre vacio, le ponemos uno por defecto
            if (paolo.name.empty()) {
                paolo.name = "Paolo";
            }
            // Reconstruimos el mapa visual del nivel guardado
            string matriz_entidades_base[max_filas][max_columnas];
            cargarnivel(paolo.nivel_actual, matriz_fondo, matriz_entidades_base);
            // Aseguramos que la "P" del jugador este en la posicion exacta guardada
            for (int i = 0; i < max_filas; i++) {
                for (int j = 0; j < max_columnas; j++) {
                    if (matriz_entidades[i][j] == "P") {
                        matriz_entidades[i][j] = "";
                    }
                }
            }
            if (paolo.posicion_y >= 0 && paolo.posicion_y < max_filas &&
                paolo.posicion_x >= 0 && paolo.posicion_x < max_columnas) {
                matriz_entidades[paolo.posicion_y][paolo.posicion_x] = "P";
            }
            // Si el nivel cargado tiene Boss, advertimos al jugador
            ui.aviso_boss = false;
            for (int i = 0; i < max_filas && !ui.aviso_boss; i++) {
                for (int j = 0; j < max_columnas && !ui.aviso_boss; j++) {
                    if (matriz_entidades[i][j] == "B") {
                        ui.aviso_boss = true;
                    }
                }
            }
            estado_actual = jugando;
        }
    }
}

bool manejarTeclaConfirmarGuardado(
    EstadoUI& ui,
    RecursosVisuales& recursos,
    const personaje& paolo,
    string matriz_entidades[max_filas][max_columnas],
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
) {
    if (tecla == sf::Keyboard::Key::W || tecla == sf::Keyboard::Key::Up) {
        moverarriba(ui.item_confirmacion, recursos.opciones_confirmacion);
    }
    else if (tecla == sf::Keyboard::Key::S || tecla == sf::Keyboard::Key::Down) {
        moverabajo(ui.item_confirmacion, recursos.opciones_confirmacion);
    }
    else if (tecla == sf::Keyboard::Key::Enter) {
        if (ui.item_confirmacion == 0) {
            guardarProgreso(paolo, matriz_entidades);
            ui.guardado_reciente = true;
            estado_actual = aviso_guardado;
            return true;
        }
        estado_actual = ui.estado_pendiente;
        if (ui.salir_despues_confirmacion) {
            estado_actual = menu_principal;
            ui.en_pausa = false;
        }
    }
    return false;
}

void manejarTeclaAvisoGuardado(EstadoUI& ui, estado_pantalla& estado_actual, sf::Keyboard::Key tecla) {
    if (tecla == sf::Keyboard::Key::Enter || tecla == sf::Keyboard::Key::Escape) {
        estado_actual = ui.estado_pendiente;
        if (ui.salir_despues_confirmacion) {
            estado_actual = menu_principal;
            ui.en_pausa = false;
            ui.salir_despues_confirmacion = false;
        }
    }
}

void manejarTeclaJugando(
    EstadoUI& ui,
    EstadoBatalla& batalla,
    RecursosVisuales& recursos,
    personaje& paolo,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
) {
    if (ui.en_pausa) {
        // --- CONTROL CON EL JUEGO PAUSADO ---
        if (tecla == sf::Keyboard::Key::W || tecla == sf::Keyboard::Key::Up) {
            moverarriba(ui.item_pausa, recursos.opciones_pausa);
        }
        else if (tecla == sf::Keyboard::Key::S || tecla == sf::Keyboard::Key::Down) {
            moverabajo(ui.item_pausa, recursos.opciones_pausa);
        }
        else if (tecla == sf::Keyboard::Key::Enter) {
            switch (ui.item_pausa) {
            case 0: // Seguir Jugando
                ui.en_pausa = false;
                break;
            case 1: // Guardar Partida
                guardarProgreso(paolo, matriz_entidades);
                ui.guardado_reciente = true;
                ui.estado_pendiente = jugando;
                estado_actual = aviso_guardado;
                break;
            case 2: // Ver Controles (desde la pausa)
                estado_actual = controles;
                ui.en_pausa = false;
                ui.controles_desde_pausa = true;
                break;
            case 3: // Volver al Menu
                if (ui.guardado_reciente) {
                    estado_actual = menu_principal;
                    ui.en_pausa = false;
                    ui.guardado_reciente = false;
                }
                else {
                    ui.item_confirmacion = 0;
                    recursos.opciones_confirmacion[0].setFillColor(sf::Color::Red);
                    recursos.opciones_confirmacion[1].setFillColor(sf::Color::White);
                    ui.estado_pendiente = jugando;
                    ui.salir_despues_confirmacion = true;
                    estado_actual = confirmar_guardado;
                }
                break;
            }
        }
        else if (tecla == sf::Keyboard::Key::Escape) {
            ui.en_pausa = false; // Despausar tambien con Escape
        }
    }
    else {
        // --- CONTROL DE EXPLORACION NORMAL ---
        if (tecla == sf::Keyboard::Key::Num9) {
            estado_actual = menu_principal;
        }
        else if (tecla == sf::Keyboard::Key::Escape) {
            ui.en_pausa = true; // Escape activa la pausa en lugar de salir directo
        }
        else if (tecla == sf::Keyboard::Key::Num5) {
            estado_actual = en_inventario;
            ui.cursor_inventario = 0;
        }
        else if (tecla == sf::Keyboard::Key::Num6) {
            ordenarburbuja(paolo.inventario, paolo.cant_items);
            std::cout << "Inventario Ordenado!" << std::endl;
        }
        else if (tecla == sf::Keyboard::Key::Num8) {
            guardarProgreso(paolo, matriz_entidades);
        }
        else if (tecla == sf::Keyboard::Key::W) {
            procesarTurno(paolo, 'W', matriz_fondo, matriz_entidades, ui.cofre_resultado);
            ui.aviso_puerta = false;
            ui.aviso_cofre = false;
            ui.aviso_boss = false;
        }
        else if (tecla == sf::Keyboard::Key::S) {
            procesarTurno(paolo, 'S', matriz_fondo, matriz_entidades, ui.cofre_resultado);
            ui.aviso_puerta = false;
            ui.aviso_cofre = false;
            ui.aviso_boss = false;
        }
        else if (tecla == sf::Keyboard::Key::A) {
            procesarTurno(paolo, 'A', matriz_fondo, matriz_entidades, ui.cofre_resultado);
            ui.aviso_puerta = false;
            ui.aviso_cofre = false;
            ui.aviso_boss = false;
        }
        else if (tecla == sf::Keyboard::Key::D) {
            procesarTurno(paolo, 'D', matriz_fondo, matriz_entidades, ui.cofre_resultado);
            ui.aviso_puerta = false;
            ui.aviso_cofre = false;
            ui.aviso_boss = false;
        }
        else if (tecla == sf::Keyboard::Key::E) {
            // Limpiamos el resultado para no arrastrar datos viejos
            ui.cofre_resultado.oro = 0;
            ui.cofre_resultado.cant_loot = 0;

            char resultado = procesarTurno(paolo, 'E', matriz_fondo, matriz_entidades, ui.cofre_resultado);

            if (resultado == 'S') {
                paolo.nivel_actual = paolo.nivel_actual + 1;
                cargarnivel(paolo.nivel_actual, matriz_fondo, matriz_entidades);
                paolo.posicion_x = 1;
                paolo.posicion_y = 1;
                ui.aviso_puerta = false;
                ui.aviso_cofre = false;
                // Si el nuevo nivel tiene un Boss, advertimos al jugador
                ui.aviso_boss = false;
                for (int i = 0; i < max_filas && !ui.aviso_boss; i++) {
                    for (int j = 0; j < max_columnas && !ui.aviso_boss; j++) {
                        if (matriz_entidades[i][j] == "B") {
                            ui.aviso_boss = true;
                        }
                    }
                }
            }
            else if (resultado == 'L') {
                ui.aviso_puerta = true;
                ui.aviso_cofre = false;
            }
            else if (resultado == 'C') {
                // Armamos el cartel con las recompensas aleatorias del cofre
                std::ostringstream oss;
                oss << "Encontraste un cofre!\n\n";
                oss << "  +" << ui.cofre_resultado.oro << " de oro\n\n";
                oss << "  Loot obtenido:\n";
                for (int i = 0; i < ui.cofre_resultado.cant_loot; i++) {
                    oss << "    - " << ui.cofre_resultado.loot[i] << "\n";
                }
                ui.mensaje_cofre = oss.str();
                ui.aviso_cofre = true;
                ui.aviso_puerta = false;
            }
            else if (resultado == 'M') {
                estado_actual = en_tienda;
                ui.cursor_tienda = 0;
                ui.cursor_inventario = 0;
                ui.en_modo_compra = true;
                ui.aviso_puerta = false;
                ui.aviso_cofre = false;
            }
            else if (resultado == 'E' || resultado == 'B') {
                // Busca al enemigo adyacente (mismo orden que la funcion interactuar)
                int px = paolo.posicion_x;
                int py = paolo.posicion_y;
                int enemigo_pos_x = -1;
                int enemigo_pos_y = -1;
                bool es_boss = false;
                int dxs[4] = { 0, 0, 1, -1 };
                int dys[4] = { -1, 1, 0, 0 };
                for (int d = 0; d < 4; d++) {
                    int nx = px + dxs[d];
                    int ny = py + dys[d];
                    if (nx >= 0 && nx < max_columnas && ny >= 0 && ny < max_filas) {
                        if (matriz_entidades[ny][nx] == "E" || matriz_entidades[ny][nx] == "B") {
                            enemigo_pos_x = nx;
                            enemigo_pos_y = ny;
                            es_boss = (matriz_entidades[ny][nx] == "B");
                            break;
                        }
                    }
                }
                iniciarBatalla(batalla, enemigo_pos_x, enemigo_pos_y, es_boss);
                estado_actual = en_batalla;
                ui.aviso_puerta = false;
                ui.aviso_cofre = false;
            }
        }
    }
}

void manejarTeclaInventario(EstadoUI& ui, personaje& paolo, estado_pantalla& estado_actual, sf::Keyboard::Key tecla) {
    // Helpers: calculo de grupos del inventario ordenado
    auto contar_grupos = [&]() -> int {
        int c = 0;
        for (int i = 0; i < paolo.cant_items; ) {
            int j = i;
            while (j < paolo.cant_items && paolo.inventario[j] == paolo.inventario[i]) j++;
            c++;
            i = j;
        }
        return c;
    };
    auto indice_plano_grupo = [&](int idx_grupo) -> int {
        int c = 0;
        for (int i = 0; i < paolo.cant_items; ) {
            int j = i;
            while (j < paolo.cant_items && paolo.inventario[j] == paolo.inventario[i]) j++;
            if (c == idx_grupo) return i;
            c++;
            i = j;
        }
        return -1;
    };

    if (tecla == sf::Keyboard::Key::Escape || tecla == sf::Keyboard::Key::Num5) {
        estado_actual = jugando;
    }
    else if (tecla == sf::Keyboard::Key::W || tecla == sf::Keyboard::Key::Up) {
        if (ui.cursor_inventario > 0) ui.cursor_inventario--;
    }
    else if (tecla == sf::Keyboard::Key::S || tecla == sf::Keyboard::Key::Down) {
        int n_grupos = contar_grupos();
        if (ui.cursor_inventario < n_grupos - 1) ui.cursor_inventario++;
    }
    else if (tecla == sf::Keyboard::Key::Num6) {
        // Ordenamos el inventario alfabeticamente (selection sort)
        ordenarburbuja(paolo.inventario, paolo.cant_items);
        ui.cursor_inventario = 0;
        std::cout << "Inventario ya ordenado" << std::endl;
    }
    else if (tecla == sf::Keyboard::Key::Enter) {
        if (paolo.cant_items > 0) {
            int idx_plano = indice_plano_grupo(ui.cursor_inventario);
            if (idx_plano < 0) idx_plano = 0;
            string item_sel = paolo.inventario[idx_plano];

            if (item_sel == "Palo" || item_sel == "Daga Rota" || item_sel == "Espada de Hierro") {
                paolo.arma_equipada = item_sel;
                paolo.ataque = 8 + obtenerataque(item_sel);
            }
            else if (item_sel == "Armadura Ligera" || item_sel == "Armadura Pesada") {
                int defensa_vieja = paolo.defensa;
                paolo.armadura_equipada = item_sel;
                paolo.defensa = obtenerdefensa(item_sel);

                // Ajustamos la vida actual segun el nuevo maximo
                paolo.vida += (paolo.defensa - defensa_vieja);
            }
            else if (item_sel == "Pocion Chica" || item_sel == "Pocion Pequena" || item_sel == "Pocion Grande") {
                if (item_sel == "Pocion Grande") paolo.vida += 50;
                else paolo.vida += 20;

                // El tope de vida depende de la armadura
                int vida_maxima = 100 + paolo.defensa;
                if (paolo.vida > vida_maxima) paolo.vida = vida_maxima;

                for (int i = idx_plano; i < paolo.cant_items - 1; i++) {
                    paolo.inventario[i] = paolo.inventario[i + 1];
                }
                paolo.cant_items--;

                // Si el grupo quedo vacio, ajustamos el cursor
                int n_grupos_nuevos = contar_grupos();
                if (ui.cursor_inventario >= n_grupos_nuevos && ui.cursor_inventario > 0) {
                    ui.cursor_inventario--;
                }
            }
        }
    }
}

void manejarTeclaTienda(EstadoUI& ui, personaje& paolo, const mercader& vendedor, estado_pantalla& estado_actual, sf::Keyboard::Key tecla) {
    if (tecla == sf::Keyboard::Key::Escape) {
        estado_actual = jugando;
    }
    else if (tecla == sf::Keyboard::Key::A || tecla == sf::Keyboard::Key::Left) {
        ui.en_modo_compra = true;
    }
    else if (tecla == sf::Keyboard::Key::D || tecla == sf::Keyboard::Key::Right) {
        if (paolo.cant_items > 0) {
            ui.en_modo_compra = false;
        }
    }
    else if (tecla == sf::Keyboard::Key::W || tecla == sf::Keyboard::Key::Up) {
        if (ui.en_modo_compra && ui.cursor_tienda > 0) ui.cursor_tienda--;
        else if (!ui.en_modo_compra && ui.cursor_inventario > 0) ui.cursor_inventario--;
    }
    else if (tecla == sf::Keyboard::Key::S || tecla == sf::Keyboard::Key::Down) {
        if (ui.en_modo_compra && ui.cursor_tienda < 5) ui.cursor_tienda++;
        else if (!ui.en_modo_compra && ui.cursor_inventario < paolo.cant_items - 1) ui.cursor_inventario++;
    }
    else if (tecla == sf::Keyboard::Key::Enter) {
        if (ui.en_modo_compra) {
            int precio_item = vendedor.precios[ui.cursor_tienda];
            if (paolo.oro >= precio_item && paolo.cant_items < 50) {
                paolo.oro -= precio_item;
                paolo.inventario[paolo.cant_items] = vendedor.catalogo[ui.cursor_tienda];
                paolo.cant_items++;

                ordenarburbuja(paolo.inventario, paolo.cant_items);
            }
        }
        else {
            if (paolo.cant_items > 0) {
                std::string item_a_vender = paolo.inventario[ui.cursor_inventario];
                try {
                    // La busqueda binaria necesita el inventario ordenado
                    ordenarburbuja(paolo.inventario, paolo.cant_items);
                    int pos = busquedaBinaria(paolo.inventario, paolo.cant_items, item_a_vender);

                    paolo.oro += obtenerprecioventa(item_a_vender);

                    for (int i = pos; i < paolo.cant_items - 1; i++) {
                        paolo.inventario[i] = paolo.inventario[i + 1];
                    }
                    paolo.cant_items--;

                    if (ui.cursor_inventario >= paolo.cant_items && ui.cursor_inventario > 0) {
                        ui.cursor_inventario--;
                    }
                    if (paolo.cant_items == 0) {
                        ui.en_modo_compra = true;
                    }
                }
                catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }
}

// BUCLE PRINCIPAL
int iniciarjuego() {
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Dungeon Survival");
    window.setFramerateLimit(60);

    RecursosVisuales recursos;
    cargarRecursosVisuales(recursos, window);

    estado_pantalla estado_actual = menu_principal;

    string matriz_fondo[max_filas][max_columnas];
    string matriz_entidades[max_filas][max_columnas];
    cargarnivel(1, matriz_fondo, matriz_entidades);

    EstadoBatalla batalla;

    personaje paolo = crearPersonajeVacio();
    mercader vendedor;
    enemigo enemigo_inicial;
    inicializarEntidadesNivel(paolo, vendedor, enemigo_inicial, false);
    ordenarmercader(vendedor.catalogo, vendedor.precios, 6);

    EstadoUI ui;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* text_event = event->getIf<sf::Event::TextEntered>()) {
                // Capturamos los caracteres tipeados cuando estamos pidiendo el nombre del personaje
                if (estado_actual == pedir_nombre) {
                    manejarTextoNombre(ui.nombre_input, text_event->unicode);
                }
            }
            else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {

                if (estado_actual == menu_principal) {
                    manejarTeclaMenuPrincipal(ui, recursos, window, estado_actual, key_pressed->code);
                }
                else if (estado_actual == pedir_nombre) {
                    manejarTeclaPedirNombre(ui, paolo, matriz_fondo, matriz_entidades, estado_actual, key_pressed->code);
                }
                else if (estado_actual == intro_historia) {
                    manejarTeclaIntro(estado_actual, key_pressed->code);
                }
                else if (estado_actual == aviso_guardado) {
                    manejarTeclaAvisoGuardado(ui, estado_actual, key_pressed->code);
                }
                else if (estado_actual == reglas || estado_actual == controles || estado_actual == creditos) {
                    manejarTeclaReglasControlesCreditos(ui, estado_actual, key_pressed->code);
                }
                else if (estado_actual == cargar) {
                    manejarTeclaCargar(ui, paolo, matriz_fondo, matriz_entidades, estado_actual, key_pressed->code);
                }
                else if (estado_actual == confirmar_guardado) {
                    if (manejarTeclaConfirmarGuardado(ui, recursos, paolo, matriz_entidades, estado_actual, key_pressed->code)) {
                        break;
                    }
                }
                else if (estado_actual == jugando) {
                    manejarTeclaJugando(ui, batalla, recursos, paolo, matriz_fondo, matriz_entidades, estado_actual, key_pressed->code);
                }
                else if (estado_actual == en_inventario) {
                    manejarTeclaInventario(ui, paolo, estado_actual, key_pressed->code);
                }
                else if (estado_actual == en_tienda) {
                    manejarTeclaTienda(ui, paolo, vendedor, estado_actual, key_pressed->code);
                }
                else if (estado_actual == en_batalla) {
                    manejarEntradaBatalla(batalla, paolo, matriz_fondo, matriz_entidades, estado_actual, key_pressed->code);
                }
            }
        }

        // --- ACTUALIZACION DEL TURNO Y ANIMACIONES DE BATALLA ---
        if (estado_actual == en_batalla) {
            actualizarTurnoBatalla(batalla, paolo, matriz_entidades);
        }

        window.clear();

        if (estado_actual == en_batalla) {
            dibujarBatalla(window, recursos, batalla, paolo);
            window.display();
            continue;
        }

        dibujarFondoMenu(window, recursos);

        if (estado_actual == menu_principal) {
            dibujarMenuPrincipal(window, recursos);
        }
        else if (estado_actual == pedir_nombre) {
            dibujarPedirNombre(window, recursos, ui);
        }
        else if (estado_actual == intro_historia) {
            dibujarIntroHistoria(window, recursos, ui);
            window.display();
            continue;
        }
        else {
            if (estado_actual == jugando || estado_actual == en_tienda || estado_actual == en_inventario) {
                dibujarMapaConCamara(window, matriz_fondo, matriz_entidades, recursos);
            }

            if (estado_actual != jugando) {
                window.draw(recursos.panel_oscuro);
            }

            if (estado_actual == reglas) {
                window.draw(recursos.texto_reglas);
            }
            else if (estado_actual == controles) {
                window.draw(recursos.texto_controles);
            }
            else if (estado_actual == creditos) {
                window.draw(recursos.texto_creditos);
            }
            else if (estado_actual == jugando) {
                dibujarPantallaJuego(window, recursos, ui);
            }
            else if (estado_actual == cargar) {
                dibujarCargarPartida(window, recursos, ui);
            }
            else if (estado_actual == confirmar_guardado) {
                dibujarConfirmarGuardado(window, recursos);
            }
            else if (estado_actual == aviso_guardado) {
                dibujarAvisoGuardado(window, recursos);
            }
            else if (estado_actual == en_inventario) {
                dibujarInventario(window, recursos, paolo, ui);
            }
            else if (estado_actual == en_tienda) {
                dibujarTienda(window, recursos, paolo, vendedor, ui);
            }
        }

        window.display();
    }

    return 0;
}
