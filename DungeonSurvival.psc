// Dungeon Survival
// Programacion I
// Autores del proyecto
// Profesora



// -------------------------
// ALGORITMO PRINCIPAL
// -------------------------
// -------------------------
Algoritmo DungeonSurvival
	
// --- Limites del mapa y del inventario ---
// del mapa (8 filas x 12 columnas), el maximo de items que puede cargar
// Se definen una sola vez al inicio y no se modifican durante el juego.
	Definir FILAS_MAPA, COLS_MAPA Como Entero
	Definir MAX_INV, MAX_TIENDA Como Entero
	FILAS_MAPA  <- 8
	COLS_MAPA   <- 12
	MAX_INV     <- 15
	MAX_TIENDA  <- 5
	
// --- Datos del jugador
// PSeInt no tiene registros (structs), entonces simulamos uno usando
// variables separadas que juntas describen el estado completo del
// personaje: nombre, vida actual y maxima, ataque, defensa, oro,
// nivel actual, posicion en el mapa, intentos y mazmorras superadas.
// "vivoJugador" es un indicador logico: Verdadero mientras tenga vida.
	Definir nombreJugador Como Cadena
	Definir vidaJugador, vidaMaxJugador Como Entero
	Definir ataqueJugador, defensaJugador Como Entero
	Definir oroJugador, nivelJugador Como Entero
	Definir posXJugador, posYJugador Como Entero
	Definir intentosJugador, mazmorrasPasadas Como Entero
	Definir vivoJugador Como Logico
	
// --- Inventario
// El inventario es un arreglo de cadenas de texto de 15 posiciones.
// Cada posicion guarda el nombre de un item (ej: "Pocion menor").
	Definir inventario Como Cadena
	Dimension inventario[15]
	Definir cantidadItems Como Entero
	
// --- Mapa
// El mapa es una matriz de 8 filas por 12 columnas de caracteres.
// Cada celda contiene un simbolo que representa lo que hay en ese lugar:
// '#' = pared, '.' = piso libre, 'P' = jugador, 'E' = enemigo, etc.
	Definir mapa Como Caracter
	Dimension mapa[8,12]
	
// su efecto numerico (indice 1) son del mismo articulo. Este patron se
	Definir nombresTienda Como Cadena
	Dimension nombresTienda[5]
	Definir preciosTienda Como Entero
	Dimension preciosTienda[5]
	Definir efectoTienda Como Entero
	Dimension efectoTienda[5]
	
// --- Guardado
// En PSeInt estandar no se pueden usar archivos reales facilmente,
// entonces simulamos el guardado guardando los datos en variables
// que persisten mientras el programa esta abierto. "saveExiste" indica
// si hay una partida guardada disponible para cargar.
	Definir saveExiste Como Logico
	Definir saveNombre Como Cadena
	Definir saveVida, saveAtaque, saveOro Como Entero
	Definir saveNivel, saveIntentos Como Entero
	Definir saveInventario Como Cadena
	Dimension saveInventario[15]
	Definir saveCantidadItems Como Entero
	saveExiste <- Falso
	
// --- Control del menu
// "seguirJugando" controla el bucle principal: mientras sea Verdadero,
// el menu se sigue mostrando. "resultadoPartida" guarda el resultado
	Definir opcionMenu Como Entero
	Definir seguirJugando Como Logico
	Definir resultadoPartida Como Entero
	
	seguirJugando <- Verdadero
	
// La tienda se inicializa una sola vez al arrancar el programa.
	inicializarTienda(nombresTienda, preciosTienda, efectoTienda)
	
// Mostramos la pantalla de bienvenida antes de entrar al menu.
	mostrarBienvenida()
	pausar()
	
// elija la opcion "Salir" (opcion 6), que pone "seguirJugando" en Falso.
	Repetir
		mostrarMenuPrincipal()
		Escribir Sin Saltar "  Tu eleccion: "
		Leer opcionMenu
		
// Cada numero lleva a una rama diferente del juego.
		Segun opcionMenu Hacer
			1:
// El jugador elige empezar desde cero.
// Primero se inicializan todos los datos del jugador con "nuevaPartida",
// y luego se lanza el bucle de juego con "jugarAventura".
				nuevaPartida(nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, nivelJugador, posXJugador, posYJugador, intentosJugador, mazmorrasPasadas, vivoJugador, inventario, cantidadItems)
				resultadoPartida <- jugarAventura(nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, nivelJugador, posXJugador, posYJugador, intentosJugador, mazmorrasPasadas, vivoJugador, inventario, cantidadItems, mapa, FILAS_MAPA, COLS_MAPA, nombresTienda, preciosTienda, efectoTienda, MAX_TIENDA, MAX_INV, saveExiste, saveNombre, saveVida, saveAtaque, saveOro, saveNivel, saveIntentos, saveInventario, saveCantidadItems)
				
				Si resultadoPartida = 1 Entonces
					mostrarVictoria(nombreJugador, oroJugador, mazmorrasPasadas)
				FinSi
				Si resultadoPartida = 2 Entonces
					mostrarGameOver(nombreJugador, mazmorrasPasadas, intentosJugador)
				FinSi
				pausar()
			2:
// El jugador quiere continuar una partida que guardo antes.
// Primero verificamos si existe un guardado (saveExiste = Verdadero).
// Si no hay guardado, avisamos al jugador.
				Si saveExiste Entonces
					cargarPartida(saveNombre, saveVida, saveAtaque, saveOro, saveNivel, saveIntentos, saveInventario, saveCantidadItems, nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, nivelJugador, posXJugador, posYJugador, intentosJugador, mazmorrasPasadas, vivoJugador, inventario, cantidadItems)
					Escribir ""
					Escribir " >> Partida cargada. Continuando aventura..."
					pausar()
					resultadoPartida <- jugarAventura(nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, nivelJugador, posXJugador, posYJugador, intentosJugador, mazmorrasPasadas, vivoJugador, inventario, cantidadItems, mapa, FILAS_MAPA, COLS_MAPA, nombresTienda, preciosTienda, efectoTienda, MAX_TIENDA, MAX_INV, saveExiste, saveNombre, saveVida, saveAtaque, saveOro, saveNivel, saveIntentos, saveInventario, saveCantidadItems)
					Si resultadoPartida = 1 Entonces
						mostrarVictoria(nombreJugador, oroJugador, mazmorrasPasadas)
					FinSi
					Si resultadoPartida = 2 Entonces
						mostrarGameOver(nombreJugador, mazmorrasPasadas, intentosJugador)
					FinSi
				SiNo
					Escribir ""
					Escribir " >> No hay ninguna partida guardada en partida.txt."
				FinSi
				pausar()
			3:
// Muestra la pantalla con las reglas del juego.
				mostrarReglas()
				pausar()
			4:
// Muestra el manual de controles con todas las teclas disponibles.
				mostrarManual()
				pausar()
			5:
// Muestra quienes desarrollaron el juego.
				mostrarCreditos()
				pausar()
			6:
// El jugador decide salir. Ponemos el flag en Falso para
// que el bucle DO-WHILE termine en su proxima evaluacion.
				seguirJugando <- Falso
				Escribir ""
				Escribir " >> Hasta la proxima, aventurero!"
			De Otro Modo:
// Si el jugador escribe un numero fuera del rango 1-6, se le avisa.
				Escribir ""
				Escribir " >> Opcion invalida. Elegi un numero entre 1 y 6."
				pausar()
		FinSegun
	Hasta Que NO seguirJugando
	
FinAlgoritmo


// -------------------------
// SUBPROCESOS SIN PARAMETROS (solo muestran informacion)
// -------------------------
// Estos subprocesos no reciben ni devuelven datos. Su unica funcion es
// Son equivalentes a funciones "void" sin argumentos en otros lenguajes.
// -------------------------

// Muestra la pantalla de titulo al abrir el programa por primera vez.
SubProceso mostrarBienvenida
	Borrar Pantalla
	Escribir "=========================================="
	Escribir "             DUNGEON SURVIVAL             "
	Escribir "=========================================="
	Escribir ""
	Escribir "      Una aventura de fantasia y peligro  "
	Escribir ""
	Escribir "          [ Paolo el Aventurero ]         "
	Escribir ""
	Escribir "  Atraviesa 3 mazmorras, vence enemigos,  "
	Escribir "    comercia con el mercader y derrota    "
	Escribir "            al boss final.                "
	Escribir ""
	Escribir "  -- 1 vida -- 1 oportunidad --           "
	Escribir "=========================================="
FinSubProceso


// Muestra las opciones del menu principal para que el jugador elija.
SubProceso mostrarMenuPrincipal
	Escribir ""
	Escribir "------------- MENU PRINCIPAL -------------"
	Escribir "  1. Nueva partida"
	Escribir "  2. Cargar partida"
	Escribir "  3. Reglas"
	Escribir "  4. Manual de controles"
	Escribir "  5. Creditos"
	Escribir "  6. Salir"
	Escribir "------------------------------------------"
FinSubProceso


SubProceso mostrarReglas
	Borrar Pantalla
	Escribir "================= REGLAS ================="
	Escribir ""
	Escribir " 1) Sos Paolo, un aventurero con 1 sola vida."
	Escribir " 2) Debes atravesar 3 mazmorras (niveles)."
	Escribir " 3) En cada mazmorra hay enemigos, cofres y"
	Escribir "    un comerciante (excepto el ultimo nivel)."
	Escribir " 4) Si tu vida llega a 0, perdes el juego."
	Escribir " 5) Para ganar, derrota al boss final del"
	Escribir "    nivel 3."
	Escribir " 6) Empezas con un Palo y poco oro."
	Escribir " 7) Podes comprar pociones y mejoras."
	Escribir " 8) Cada enemigo derrotado deja oro y/o loot."
	Escribir "=========================================="
FinSubProceso


// junto con el significado de cada simbolo que aparece en el mapa.
SubProceso mostrarManual
	Borrar Pantalla
	Escribir "============ MANUAL DE CONTROLES ============"
	Escribir ""
	Escribir " EXPLORACION (en la mazmorra):"
	Escribir "   1 = Mover arriba"
	Escribir "   2 = Mover abajo"
	Escribir "   3 = Mover izquierda"
	Escribir "   4 = Mover derecha"
	Escribir "   5 = Abrir inventario"
	Escribir "   6 = Ordenar inventario (A-Z)"
	Escribir "   7 = Ver estado del personaje"
	Escribir "   8 = Guardar partida"
	Escribir "   9 = Volver al menu principal"
	Escribir ""
	Escribir " COMBATE (por turnos):"
	Escribir "   1 = Atacar"
	Escribir "   2 = Usar pocion"
	Escribir "   3 = Defender (reduce el dano recibido)"
	Escribir "   4 = Huir (50% de exito)"
	Escribir ""
	Escribir " SIMBOLOS DEL MAPA:"
	Escribir "   P = Paolo (vos)"
	Escribir "   E = Enemigo"
	Escribir "   M = Comerciante"
	Escribir "   C = Cofre"
	Escribir "   S = Escaleras (siguiente nivel)"
	Escribir "   B = Boss final"
	Escribir "   # = Pared"
	Escribir "   . = Piso"
	Escribir "============================================="
FinSubProceso


SubProceso mostrarCreditos
	Borrar Pantalla
	Escribir "================ CREDITOS ================"
	Escribir ""
	Escribir "  Proyecto Parcial 2 - Programacion I"
	Escribir ""
	Escribir "  Desarrollado por:"
	Escribir "    - Ignacio Gonzalez"
	Escribir "    - Santiago Oviedo"
	Escribir "    - Santiago Salvay"
	Escribir ""
	Escribir "  Profesora: Monica Liliana Nano"
	Escribir ""
	Escribir "  Carrera:"
	Escribir "    Ingenieria en Informatica"
	Escribir "    Ingenieria en Telecomunicaciones"
	Escribir "=========================================="
FinSubProceso


SubProceso mostrarMenuCombate
	Escribir ""
	Escribir " --- COMBATE ---"
	Escribir "  1. Atacar"
	Escribir "  2. Usar pocion"
	Escribir "  3. Defender"
	Escribir "  4. Huir"
FinSubProceso


// Muestra el menu de acciones durante la exploracion de la mazmorra.
SubProceso mostrarMenuExploracion
	Escribir ""
	Escribir " --- ACCIONES ---"
	Escribir "  1.Arriba  2.Abajo  3.Izq.  4.Der."
	Escribir "  5.Inventario  6.Ordenar  7.Estado"
	Escribir "  8.Guardar  9.Salir al menu"
FinSubProceso


// Detiene la ejecucion hasta que el jugador presione ENTER.
// Se usa para dar tiempo a leer los mensajes antes de continuar.
SubProceso pausar
	Definir dummy Como Cadena
	Escribir ""
	Escribir "(Presiona ENTER para continuar...)"
	Leer dummy
FinSubProceso


// -------------------------
// SUBPROCESOS CON PARAMETROS QUE NO DEVUELVEN VALOR
// -------------------------
// Estos subprocesos reciben datos a traves de sus parametros y realizan
// un valor de retorno como tal. Los parametros "Por Referencia" permiten
// -------------------------

// Muestra en pantalla todos los datos actuales del personaje:
// vida, ataque, defensa, oro, nivel y estadisticas de partida.
SubProceso mostrarEstado(nombre, vida, vidaMax, ataque, defensa, oro, nivel, intentos, mazmorras)
	Escribir ""
	Escribir "+-------------- ESTADO --------------+"
	Escribir "| Aventurero: ", nombre
	Escribir "| Vida: ", vida, " / ", vidaMax
	Escribir "| Ataque: ", ataque, "   Defensa: ", defensa
	Escribir "| Oro: ", oro, "        Mazmorra: ", nivel
	Escribir "| Mazmorras pasadas: ", mazmorras
	Escribir "| Intentos: ", intentos
	Escribir "+------------------------------------+"
FinSubProceso


// Muestra el contenido del inventario recorriendo el vector con un FOR.
SubProceso mostrarInventario(inv, cant)
	Definir i Como Entero
	Escribir ""
	Escribir "+----------- INVENTARIO -----------+"
	Si cant = 0 Entonces
		Escribir "| (vacio)"
	SiNo
		Para i <- 1 Hasta cant Con Paso 1 Hacer
			Escribir "| ", i, ". ", inv[i]
		FinPara
	FinSi
	Escribir "+----------------------------------+"
FinSubProceso


// Muestra el mapa de la mazmorra en pantalla.
SubProceso mostrarMapa(mapa, filas, cols)
	Definir i, j Como Entero
	Escribir ""
	Escribir "  --- MAPA DE LA MAZMORRA ---"
// El FOR exterior recorre las filas (de arriba a abajo).
// El FOR interior recorre las columnas (de izquierda a derecha).
	Para i <- 1 Hasta filas Con Paso 1 Hacer
		Escribir Sin Saltar "   "
		Para j <- 1 Hasta cols Con Paso 1 Hacer
			Escribir Sin Saltar mapa[i,j], " "
		FinPara
		Escribir ""
	FinPara
FinSubProceso


// Construye el mapa de una mazmorra desde cero segun el nivel actual.
// Primero rellena toda la matriz: los bordes se marcan con '#' (pared)
// superior izquierda y ubica los elementos del nivel con un SWITCH.
SubProceso inicializarMapa(mapa, filas, cols, nivel, posXJugador Por Referencia, posYJugador Por Referencia)
	Definir i, j Como Entero
// Dos FOR anidados rellenan toda la matriz.
// Si esta en el borde, pone pared; si no, pone piso.
	Para i <- 1 Hasta filas Con Paso 1 Hacer
		Para j <- 1 Hasta cols Con Paso 1 Hacer
			Si i = 1 O i = filas O j = 1 O j = cols Entonces
				mapa[i,j] <- '#'
			SiNo
				mapa[i,j] <- '.'
			FinSi
		FinPara
	FinPara
	
// Ubicamos al jugador en la posicion inicial (fila 2, columna 2)
// y marcamos esa celda con 'P' en el mapa.
	posYJugador <- 2
	posXJugador <- 2
	mapa[posYJugador, posXJugador] <- 'P'
	
// Nivel 1 y 2 tienen comerciante ('M') y escaleras ('S').
// Nivel 3 reemplaza las escaleras por el boss final ('B').
	Segun nivel Hacer
		1:
			mapa[3, 6]  <- 'C'   // cofre
			mapa[5, 4]  <- 'M'   // comerciante
			mapa[4, 9]  <- 'E'   // enemigo 1
			mapa[6, 7]  <- 'E'   // enemigo 2
			mapa[7, 11] <- 'S'   // escaleras al nivel 2
		2:
			mapa[3, 5]  <- 'E'
			mapa[4, 10] <- 'C'
			mapa[5, 7]  <- 'M'
			mapa[6, 4]  <- 'E'
			mapa[6, 9]  <- 'E'
			mapa[7, 11] <- 'S'
		3:
			mapa[3, 6]  <- 'E'
			mapa[4, 4]  <- 'C'
			mapa[5, 10] <- 'E'
			mapa[6, 7]  <- 'E'
			mapa[7, 11] <- 'B'   // boss final
	FinSegun
FinSubProceso


// Ejecuta un ataque de un personaje a otro.
SubProceso atacar(ataqueOrigen, vidaDestino Por Referencia, nombreOrigen, nombreDestino)
	Definir dano Como Entero
	dano <- calcularDanio(ataqueOrigen)
	vidaDestino <- vidaDestino - dano
	Si vidaDestino < 0 Entonces
		vidaDestino <- 0
	FinSi
	Escribir "  >> ", nombreOrigen, " ataca a ", nombreDestino, " e inflige ", dano, " de dano."
FinSubProceso


// Otorga la recompensa al jugador cuando derrota a un enemigo.
// El oro ganado depende del nivel del enemigo (mas nivel = mas oro).
// Ademas hay una probabilidad de obtener items: se usa azar(4) para
// decidir que loot cae (0-2 items segun el resultado), y luego se
// llama a "fusionarLoot" para agregarlo al inventario del jugador.
SubProceso recompensaEnemigo(oro Por Referencia, inv Por Referencia, cant Por Referencia, maxInv, nivelEnemigo)
	Definir oroGanado, idx Como Entero
	Definir loot Como Cadena
	Dimension loot[3]
	Definir cantLoot Como Entero
	
	oroGanado <- 5 + azar(10) + (nivelEnemigo * 3)
	oro <- oro + oroGanado
	Escribir "  >> Ganas ", oroGanado, " de oro."
	
// Decidimos el tipo de loot con un numero aleatorio entre 0 y 3.
// Cada valor del resultado corresponde a un conjunto diferente de items.
// Si el resultado es 3, no cae ningun item (es posible no obtener loot).
	idx <- azar(4)
	cantLoot <- 0
	Si idx = 0 Entonces
		loot[1] <- "Pocion menor"
		cantLoot <- 1
	FinSi
	Si idx = 1 Entonces
		loot[1] <- "Antorcha"
		cantLoot <- 1
	FinSi
	Si idx = 2 Entonces
		loot[1] <- "Pocion menor"
		loot[2] <- "Daga oxidada"
		cantLoot <- 2
	FinSi
// Si idx resulto 3, cantLoot queda en 0 y no se agrega nada.
	
	Si cantLoot > 0 Entonces
// Agregamos los items obtenidos al inventario del jugador.
		fusionarLoot(inv, cant, maxInv, loot, cantLoot)
	FinSi
FinSubProceso


// Maneja un combate completo por turnos entre el jugador y un enemigo.
// luego actua el enemigo automaticamente si sigue vivo.
SubProceso combate(nombreEnemigo, vidaEnemigoIni, ataqueEnemigo, nivelEnemigo, nombreJugador, vidaJugador Por Referencia, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador Por Referencia, inventario Por Referencia, cantidadItems Por Referencia, maxInv, victoria Por Referencia, huida Por Referencia)
	Definir vidaEnemigo Como Entero
	Definir opcion Como Entero
	Definir defendiendo Como Logico
	Definir danoRecibido Como Entero
	Definir exitoHuida Como Entero
	
// Inicializamos la vida del enemigo y los estados del combate.
	vidaEnemigo <- vidaEnemigoIni
	defendiendo <- Falso
	victoria    <- Falso
	huida       <- Falso
	
	Escribir ""
	Escribir " ============================================"
	Escribir "    Un ", nombreEnemigo, " salvaje aparece!"
	Escribir "    Vida: ", vidaEnemigo, "  Ataque: ", ataqueEnemigo
	Escribir " ============================================"
	
// Esta es una condicion compuesta con tres partes unidas por Y logico.
	Mientras estaVivo(vidaJugador) Y estaVivo(vidaEnemigo) Y NO huida Hacer
		Escribir ""
		Escribir "  Tu vida: ", vidaJugador, "/", vidaMaxJugador, "   |   ", nombreEnemigo, ": ", vidaEnemigo
		mostrarMenuCombate()
		Escribir Sin Saltar "  Tu accion: "
		Leer opcion
		
		Segun opcion Hacer
			1:
				defendiendo <- Falso
				atacar(ataqueJugador, vidaEnemigo, nombreJugador, nombreEnemigo)
			2:
// El jugador intenta usar una pocion del inventario.
// "usarPocion" busca la mejor pocion disponible y la consume.
				defendiendo <- Falso
				usarPocion(inventario, cantidadItems, vidaJugador, vidaMaxJugador)
			3:
// El jugador adopta postura defensiva: el flag "defendiendo" se activa.
				defendiendo <- Verdadero
				Escribir "  >> ", nombreJugador, " se cubre con su defensa."
			4:
// Intento de huida: hay un 50% de probabilidad (azar(2) devuelve 0 o 1).
				defendiendo <- Falso
				exitoHuida <- azar(2)
				Si exitoHuida = 0 Entonces
					Escribir "  >> Lograste huir del combate!"
					huida <- Verdadero
				SiNo
					Escribir "  >> Fallaste al huir. Perdes 5 de vida."
					vidaJugador <- vidaJugador - 5
					Si vidaJugador < 0 Entonces
						vidaJugador <- 0
					FinSi
				FinSi
			De Otro Modo:
// Si el jugador ingresa algo invalido, pierde el turno sin hacer nada.
				Escribir "  >> Accion invalida. Pierdes el turno."
				defendiendo <- Falso
		FinSegun
		
// pero siempre recibe al menos 1 punto de dano.
		Si estaVivo(vidaEnemigo) Y NO huida Entonces
			danoRecibido <- calcularDanio(ataqueEnemigo)
			Si defendiendo Entonces
				danoRecibido <- danoRecibido - defensaJugador
				Si danoRecibido < 1 Entonces
					danoRecibido <- 1
				FinSi
				Escribir "  >> Defiendes! Solo recibes ", danoRecibido, " de dano."
			SiNo
				Escribir "  >> ", nombreEnemigo, " te golpea por ", danoRecibido, " de dano."
			FinSi
			vidaJugador <- vidaJugador - danoRecibido
			Si vidaJugador < 0 Entonces
				vidaJugador <- 0
			FinSi
		FinSi
	FinMientras
	
// y se entregan las recompensas correspondientes.
	Si NO estaVivo(vidaEnemigo) Y NO huida Entonces
		Escribir ""
		Escribir "  >> Has derrotado a ", nombreEnemigo, "!"
		victoria <- Verdadero
		recompensaEnemigo(oroJugador, inventario, cantidadItems, maxInv, nivelEnemigo)
	FinSi
FinSubProceso


// Busca una pocion en el inventario y la usa para recuperar vida.
// Una vez usada la pocion, se elimina del inventario "corriendo" todos
SubProceso usarPocion(inv Por Referencia, cant Por Referencia, vida Por Referencia, vidaMax)
	Definir indice, curacion, i Como Entero
// Primero buscamos si hay una Pocion mayor disponible.
// Si no hay, buscamos una Pocion menor. Si no hay ninguna, avisamos.
	indice <- buscarItem(inv, cant, "Pocion mayor")
	curacion <- 0
	Si indice > 0 Entonces
		curacion <- 50
	SiNo
		indice <- buscarItem(inv, cant, "Pocion menor")
		Si indice > 0 Entonces
			curacion <- 20
		FinSi
	FinSi
	
	Si indice > 0 Entonces
// Aplicamos la curacion sin superar el maximo de vida.
		vida <- vida + curacion
		Si vida > vidaMax Entonces
			vida <- vidaMax
		FinSi
		Escribir "  >> Usaste ", inv[indice], ". Recuperas ", curacion, " de vida."
// Eliminamos la pocion del inventario desplazando todos los items
// que estan a su derecha una posicion a la izquierda.
// Luego vaciamos la ultima posicion y reducimos el contador.
		Para i <- indice Hasta cant - 1 Con Paso 1 Hacer
			inv[i] <- inv[i+1]
		FinPara
		inv[cant] <- ""
		cant <- cant - 1
	SiNo
		Escribir "  >> No tenes pociones en el inventario!"
	FinSi
FinSubProceso


// Permite al jugador interactuar con el comerciante de la mazmorra.
// vender un item del inventario, o comparar el inventario con la tienda.
// Los efectos de las armas y armaduras se aplican directamente sobre los
SubProceso comerciante(oro Por Referencia, inv Por Referencia, cant Por Referencia, maxInv, ataqueJugador Por Referencia, defensaJugador Por Referencia, vidaMaxJugador Por Referencia, nombresTienda, preciosTienda, efectoTienda, maxTienda)
	Definir opcion, i Como Entero
	Definir salir Como Logico
	salir <- Falso
	
	Repetir
		Borrar Pantalla
		Escribir "=========== COMERCIANTE ==========="
		Escribir " -Bienvenido aventurero! Que necesitas?-"
		Escribir " Tu oro: ", oro
		Escribir " ---------------------------------"
		Escribir " === TIENDA ==="
		Para i <- 1 Hasta maxTienda Con Paso 1 Hacer
			Escribir "  ", i, ". ", nombresTienda[i], " - ", preciosTienda[i], " oro"
		FinPara
		Escribir "  ", maxTienda + 1, ". Vender items del inventario"
		Escribir "  ", maxTienda + 2, ". Comparar inventario con la tienda (apareo)"
		Escribir "  0. Salir de la tienda"
		Escribir " ---------------------------------"
		Escribir Sin Saltar " Tu eleccion: "
		Leer opcion
		
// Si eligio un numero entre 1 y maxTienda, intenta comprar ese producto.
		Si opcion >= 1 Y opcion <= maxTienda Entonces
			Si oro >= preciosTienda[opcion] Entonces
				Si cant < maxInv Entonces
// Le descontamos el precio y aplicamos el efecto segun el tipo de item.
// Armas y armaduras modifican atributos permanentes del jugador.
					oro <- oro - preciosTienda[opcion]
					Si nombresTienda[opcion] = "Espada de hierro" Entonces
						ataqueJugador <- ataqueJugador + efectoTienda[opcion]
						Escribir " >> Compraste ", nombresTienda[opcion], "! Ataque +", efectoTienda[opcion]
					SiNo
						Si nombresTienda[opcion] = "Escudo de madera" Entonces
							defensaJugador <- defensaJugador + efectoTienda[opcion]
							Escribir " >> Compraste ", nombresTienda[opcion], "! Defensa +", efectoTienda[opcion]
						SiNo
							Si nombresTienda[opcion] = "Armadura ligera" Entonces
								vidaMaxJugador <- vidaMaxJugador + efectoTienda[opcion]
								Escribir " >> Compraste ", nombresTienda[opcion], "! Vida maxima +", efectoTienda[opcion]
							SiNo
								Escribir " >> Compraste ", nombresTienda[opcion], "!"
							FinSi
						FinSi
					FinSi
// En todos los casos, el item queda registrado en el inventario.
					cant <- cant + 1
					inv[cant] <- nombresTienda[opcion]
				SiNo
					Escribir " >> Inventario lleno!"
				FinSi
			SiNo
				Escribir " >> No tenes suficiente oro!"
			FinSi
			pausar()
		SiNo
			Si opcion = maxTienda + 1 Entonces
// El jugador quiere vender un item de su inventario.
				venderItems(inv, cant, oro)
				pausar()
			SiNo
				Si opcion = maxTienda + 2 Entonces
					aparearTiendaInventario(inv, cant, nombresTienda, maxTienda)
					pausar()
				SiNo
					Si opcion = 0 Entonces
// El jugador cierra la tienda y vuelve a explorar la mazmorra.
						salir <- Verdadero
					SiNo
						Escribir " >> Opcion invalida."
						pausar()
					FinSi
				FinSi
			FinSi
		FinSi
	Hasta Que salir
FinSubProceso


// Permite al jugador elegir un item de su inventario para venderlo.
// El precio de venta es aleatorio (entre 5 y 14 de oro).
SubProceso venderItems(inv Por Referencia, cant Por Referencia, oro Por Referencia)
	Definir opcion, i, precio Como Entero
	Si cant = 0 Entonces
		Escribir " >> No tenes items para vender."
	SiNo
		mostrarInventario(inv, cant)
		Escribir Sin Saltar " Numero del item a vender (0 cancelar): "
		Leer opcion
		Si opcion >= 1 Y opcion <= cant Entonces
// El precio de venta varia aleatoriamente entre 5 y 14 de oro.
			precio <- 5 + azar(10)
			oro <- oro + precio
			Escribir " >> Vendiste ", inv[opcion], " por ", precio, " de oro."
			Para i <- opcion Hasta cant - 1 Con Paso 1 Hacer
				inv[i] <- inv[i+1]
			FinPara
			inv[cant] <- ""
			cant <- cant - 1
		SiNo
			Si opcion <> 0 Entonces
				Escribir " >> Numero invalido."
			FinSi
		FinSi
	FinSi
FinSubProceso


SubProceso aparearTiendaInventario(inv, cant, nombresTienda, maxTienda)
	Definir i, j Como Entero
	Definir encontrados Como Entero
	Escribir ""
	Escribir " >> APAREO inventario / tienda <<"
	Escribir " Items que ya tenes y que vende la tienda:"
	encontrados <- 0
	Para i <- 1 Hasta cant Con Paso 1 Hacer
		Para j <- 1 Hasta maxTienda Con Paso 1 Hacer
			Si inv[i] = nombresTienda[j] Entonces
				Escribir "   * ", inv[i], " (tambien en la tienda)"
				encontrados <- encontrados + 1
			FinSi
		FinPara
	FinPara
	Si encontrados = 0 Entonces
		Escribir "   (no hay coincidencias)"
	FinSi
FinSubProceso


// Abre un cofre en la mazmorra y entrega su contenido al jugador.
// depende del nivel actual de la mazmorra: cuanto mas avanzado, mas oro.
// El loot se agrega al inventario usando "fusionarLoot".
SubProceso abrirCofre(inv Por Referencia, cant Por Referencia, maxInv, oro Por Referencia, nivel)
	Definir tipoLoot, cantLoot Como Entero
	Definir loot Como Cadena
	Dimension loot[3]
	Definir oroEncontrado Como Entero
	
	Escribir ""
	Escribir " >> Abres el cofre... que habra adentro?"
	
	tipoLoot <- azar(4)
	cantLoot <- 0
	
	Segun tipoLoot Hacer
		0:
			loot[1] <- "Pocion menor"
			loot[2] <- "Antorcha"
			cantLoot <- 2
		1:
			loot[1] <- "Pocion mayor"
			cantLoot <- 1
		2:
			loot[1] <- "Daga oxidada"
			loot[2] <- "Pocion menor"
			loot[3] <- "Antorcha"
			cantLoot <- 3
		3:
			loot[1] <- "Amuleto magico"
			cantLoot <- 1
	FinSegun
	
// El oro encontrado en el cofre aumenta segun el nivel de la mazmorra.
	oroEncontrado <- 10 + azar(15) + (nivel * 5)
	oro <- oro + oroEncontrado
	Escribir "   + ", oroEncontrado, " de oro"
	
// Agregamos los items del cofre al inventario del jugador.
	fusionarLoot(inv, cant, maxInv, loot, cantLoot)
FinSubProceso


// Si el inventario esta lleno, descarta el item y avisa al jugador.
SubProceso fusionarLoot(inv Por Referencia, cant Por Referencia, maxInv, loot, cantLoot)
	Definir i Como Entero
// Intentamos agregar cada item del loot al inventario.
// Si la cantidad actual es menor al maximo, hay lugar para agregar.
	Para i <- 1 Hasta cantLoot Con Paso 1 Hacer
		Si cant < maxInv Entonces
			cant <- cant + 1
			inv[cant] <- loot[i]
			Escribir "   + ", loot[i]
		SiNo
			Escribir "   - Inventario lleno, descartas: ", loot[i]
		FinSi
	FinPara
FinSubProceso


SubProceso ordenarInventario(inv Por Referencia, cant)
	Definir i, j Como Entero
	Definir aux Como Cadena
// porque los ultimos elementos ya estan en su lugar correcto.
	Para i <- 1 Hasta cant - 1 Con Paso 1 Hacer
		Para j <- 1 Hasta cant - i Con Paso 1 Hacer
			Si inv[j] > inv[j+1] Entonces
// Intercambiamos los dos elementos usando una variable auxiliar.
				aux       <- inv[j]
				inv[j]    <- inv[j+1]
				inv[j+1]  <- aux
			FinSi
		FinPara
	FinPara
FinSubProceso


// Carga los productos fijos de la tienda en los arreglos paralelos.
// Se ejecuta una sola vez al inicio del programa. Los cinco productos
// de tres arreglos distintos (la tecnica de arreglos paralelos).
SubProceso inicializarTienda(nombresTienda Por Referencia, preciosTienda Por Referencia, efectoTienda Por Referencia)
// Pocion menor: cura 20 de vida, cuesta 15 de oro.
	nombresTienda[1] <- "Pocion menor"
	preciosTienda[1] <- 15
	efectoTienda[1]  <- 20
	
// Pocion mayor: cura 50 de vida, cuesta 35 de oro.
	nombresTienda[2] <- "Pocion mayor"
	preciosTienda[2] <- 35
	efectoTienda[2]  <- 50
	
// Espada de hierro: aumenta el ataque en 5, cuesta 50 de oro.
	nombresTienda[3] <- "Espada de hierro"
	preciosTienda[3] <- 50
	efectoTienda[3]  <- 5
	
// Escudo de madera: aumenta la defensa en 3, cuesta 30 de oro.
	nombresTienda[4] <- "Escudo de madera"
	preciosTienda[4] <- 30
	efectoTienda[4]  <- 3
	
// Armadura ligera: aumenta la vida maxima en 25, cuesta 60 de oro.
	nombresTienda[5] <- "Armadura ligera"
	preciosTienda[5] <- 60
	efectoTienda[5]  <- 25
FinSubProceso


// Configura todos los datos del jugador para comenzar una partida nueva.
// Pide el nombre al jugador (si deja vacio, usa "Paolo" por defecto).
// El inventario inicial tiene dos items: un Palo y una Pocion menor.
SubProceso nuevaPartida(nombreJugador Por Referencia, vidaJugador Por Referencia, vidaMaxJugador Por Referencia, ataqueJugador Por Referencia, defensaJugador Por Referencia, oroJugador Por Referencia, nivelJugador Por Referencia, posXJugador Por Referencia, posYJugador Por Referencia, intentosJugador Por Referencia, mazmorrasPasadas Por Referencia, vivoJugador Por Referencia, inventario Por Referencia, cantidadItems Por Referencia)
	Borrar Pantalla
	Escribir "============= NUEVA PARTIDA ============="
	Escribir Sin Saltar " Ingresa el nombre de tu aventurero (ENTER = Paolo): "
	Leer nombreJugador
	Si nombreJugador = "" Entonces
		nombreJugador <- "Paolo"
	FinSi
	
// Esto permite cambiar los valores iniciales del juego en un solo lugar.
	vidaMaxJugador  <- generarVidaInicial
	vidaJugador     <- vidaMaxJugador
	oroJugador      <- generarOroInicial
	ataqueJugador   <- 8
	defensaJugador  <- 1
	nivelJugador    <- 1
	posXJugador     <- 2
	posYJugador     <- 2
	intentosJugador <- 1
	mazmorrasPasadas <- 0
	vivoJugador     <- Verdadero
	
// El inventario empieza con dos items en las posiciones 1 y 2.
	cantidadItems    <- 2
	inventario[1]    <- "Palo"
	inventario[2]    <- "Pocion menor"
	
	Escribir ""
	Escribir " >> Hola ", nombreJugador, "! Tu aventura comienza..."
	Escribir " >> Empezas con un Palo y una Pocion menor."
	pausar()
FinSubProceso


// Controla el recorrido del jugador dentro de una mazmorra.
// el inventario, el guardado y la salida al menu.
// no haya pasado de nivel y no haya elegido salir al menu.
SubProceso explorarMazmorra(nombreJugador, vidaJugador Por Referencia, vidaMaxJugador Por Referencia, ataqueJugador Por Referencia, defensaJugador Por Referencia, oroJugador Por Referencia, nivelJugador Por Referencia, posXJugador Por Referencia, posYJugador Por Referencia, intentosJugador Por Referencia, mazmorrasPasadas Por Referencia, vivoJugador Por Referencia, inventario Por Referencia, cantidadItems Por Referencia, mapa Por Referencia, FILAS_MAPA, COLS_MAPA, nombresTienda, preciosTienda, efectoTienda, MAX_TIENDA, MAX_INV, resultado Por Referencia, saveExiste Por Referencia, saveNombre Por Referencia, saveVida Por Referencia, saveAtaque Por Referencia, saveOro Por Referencia, saveNivel Por Referencia, saveIntentos Por Referencia, saveInventario Por Referencia, saveCantidadItems Por Referencia)
	Definir accion Como Entero
	Definir nuevaX, nuevaY Como Entero
	Definir destino Como Caracter
	Definir avanzaNivel, salirAlMenu Como Logico
	Definir vidaEnemigo, ataqueEnemigo Como Entero
	Definir nombreEnemigo Como Cadena
	Definir victoriaCombate, huidaCombate Como Logico
	
	inicializarMapa(mapa, FILAS_MAPA, COLS_MAPA, nivelJugador, posXJugador, posYJugador)
	
	avanzaNivel  <- Falso
	salirAlMenu  <- Falso
	resultado    <- 0
	
	Escribir ""
	Escribir " ============================================"
	Escribir "         MAZMORRA NIVEL ", nivelJugador
	Escribir " ============================================"
	Si nivelJugador = 3 Entonces
		Escribir "   Atencion! Aqui se esconde el BOSS FINAL."
	FinSi
	pausar()
	
// no haya pasado de nivel y no haya pedido salir al menu.
	Mientras estaVivo(vidaJugador) Y NO avanzaNivel Y NO salirAlMenu Hacer
		Borrar Pantalla
		mostrarEstado(nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, nivelJugador, intentosJugador, mazmorrasPasadas)
		mostrarMapa(mapa, FILAS_MAPA, COLS_MAPA)
		mostrarMenuExploracion()
		Escribir Sin Saltar "  Accion: "
		Leer accion
		
// Calculamos la nueva posicion tentativa segun la direccion elegida.
		nuevaX <- posXJugador
		nuevaY <- posYJugador
		
		Segun accion Hacer
			1:
// Mover arriba significa disminuir la fila (Y - 1).
				nuevaY <- posYJugador - 1
			2:
// Mover abajo significa aumentar la fila (Y + 1).
				nuevaY <- posYJugador + 1
			3:
// Mover a la izquierda significa disminuir la columna (X - 1).
				nuevaX <- posXJugador - 1
			4:
// Mover a la derecha significa aumentar la columna (X + 1).
				nuevaX <- posXJugador + 1
			5:
// Mostrar el inventario sin moverse.
				mostrarInventario(inventario, cantidadItems)
				pausar()
			6:
// Ordenar el inventario alfabeticamente y mostrarlo.
				ordenarInventario(inventario, cantidadItems)
				Escribir "  >> Inventario ordenado alfabeticamente."
				mostrarInventario(inventario, cantidadItems)
				pausar()
			7:
// Ver el estado completo del personaje.
				mostrarEstado(nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, nivelJugador, intentosJugador, mazmorrasPasadas)
				pausar()
			8:
// Guardar el estado actual de la partida en memoria.
				guardarPartida(nombreJugador, vidaJugador, ataqueJugador, oroJugador, nivelJugador, intentosJugador, inventario, cantidadItems, saveExiste, saveNombre, saveVida, saveAtaque, saveOro, saveNivel, saveIntentos, saveInventario, saveCantidadItems)
				pausar()
			9:
// El jugador decide volver al menu principal.
				salirAlMenu <- Verdadero
				resultado   <- 3
			De Otro Modo:
					pausar()
					Escribir "  >> Accion invalida."
		FinSegun
		
		
		
		
		
		
		
		
		
		
		
		
		
		
// Si la accion fue un movimiento (1 a 4), validamos la nueva posicion y
// procesamos lo que hay en la celda destino.
		Si accion >= 1 Y accion <= 4 Entonces
// Verificamos que la nueva posicion este dentro de los limites del mapa.
			Si nuevaY >= 1 Y nuevaY <= FILAS_MAPA Y nuevaX >= 1 Y nuevaX <= COLS_MAPA Entonces
				destino <- mapa[nuevaY, nuevaX]
				Si destino = '#' Entonces
// No se puede atravesar paredes.
					Escribir "  >> Hay una pared en esa direccion."
					pausar()
				SiNo
					Si destino = '.' Entonces
// La celda esta libre: movemos al jugador actualizando
// la posicion anterior a '.' y la nueva a 'P'.
						mapa[posYJugador, posXJugador] <- '.'
						posYJugador <- nuevaY
						posXJugador <- nuevaX
						mapa[posYJugador, posXJugador] <- 'P'
					SiNo
						Si destino = 'E' Entonces
// Hay un enemigo en esa celda: generamos sus estadisticas
// segun el nivel actual y lanzamos el combate.
// Si el jugador gana, ocupa la celda del enemigo.
							generarEnemigo(nivelJugador, nombreEnemigo, vidaEnemigo, ataqueEnemigo)
							combate(nombreEnemigo, vidaEnemigo, ataqueEnemigo, nivelJugador, nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, inventario, cantidadItems, MAX_INV, victoriaCombate, huidaCombate)
							Si victoriaCombate Entonces
								mapa[posYJugador, posXJugador] <- '.'
								posYJugador <- nuevaY
								posXJugador <- nuevaX
								mapa[posYJugador, posXJugador] <- 'P'
							FinSi
							pausar()
						SiNo
							Si destino = 'B' Entonces
// Es el boss final del juego.
// Tiene estadisticas fijas y muy superiores a los enemigos normales.
								nombreEnemigo <- "BOSS - Senor de la Mazmorra"
								vidaEnemigo   <- 80
								ataqueEnemigo <- 14
								combate(nombreEnemigo, vidaEnemigo, ataqueEnemigo, nivelJugador + 2, nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, inventario, cantidadItems, MAX_INV, victoriaCombate, huidaCombate)
								Si victoriaCombate Entonces
									resultado   <- 1
									avanzaNivel <- Verdadero
								FinSi
								pausar()
							SiNo
								Si destino = 'M' Entonces
// Hay un comerciante: abrimos el menu de la tienda.
// El jugador no se mueve a esa celda, solo interactua.
									comerciante(oroJugador, inventario, cantidadItems, MAX_INV, ataqueJugador, defensaJugador, vidaMaxJugador, nombresTienda, preciosTienda, efectoTienda, MAX_TIENDA)
								SiNo
									Si destino = 'C' Entonces
// Hay un cofre: lo abrimos, recibimos el loot
// y reemplazamos la celda del cofre por piso libre.
										abrirCofre(inventario, cantidadItems, MAX_INV, oroJugador, nivelJugador)
										mapa[nuevaY, nuevaX] <- '.'
										mapa[posYJugador, posXJugador] <- '.'
										posYJugador <- nuevaY
										posXJugador <- nuevaX
										mapa[posYJugador, posXJugador] <- 'P'
										pausar()
									SiNo
										Si destino = 'S' Entonces
// Son las escaleras al siguiente nivel.
// Marcamos que se paso de nivel y sumamos al contador de mazmorras.
											Escribir "  >> Encuentras las escaleras! Avanzas al siguiente nivel."
											avanzaNivel <- Verdadero
											mazmorrasPasadas <- mazmorrasPasadas + 1
											pausar()
										FinSi
									FinSi
								FinSi
							FinSi
						FinSi
					FinSi
				FinSi
			SiNo
// La posicion calculada esta fuera de los bordes del mapa.
				Escribir "  >> Esa direccion esta fuera del mapa."
				pausar()
			FinSi
		FinSi
	FinMientras
	
// Al salir del bucle, verificamos si el jugador murio.
	Si NO estaVivo(vidaJugador) Entonces
		vivoJugador <- Falso
		resultado   <- 2
	FinSi
FinSubProceso


// -------------------------
// SUBPROCESOS CON RETORNO Y CON PARAMETROS (funciones de tipo)
// -------------------------
// En PSeInt, un subproceso "con retorno" se declara con la sintaxis
// -------------------------

// Bucle principal del juego: recorre los niveles 1, 2 y 3 en secuencia.
SubProceso retorno <- jugarAventura(nombreJugador Por Referencia, vidaJugador Por Referencia, vidaMaxJugador Por Referencia, ataqueJugador Por Referencia, defensaJugador Por Referencia, oroJugador Por Referencia, nivelJugador Por Referencia, posXJugador Por Referencia, posYJugador Por Referencia, intentosJugador Por Referencia, mazmorrasPasadas Por Referencia, vivoJugador Por Referencia, inventario Por Referencia, cantidadItems Por Referencia, mapa Por Referencia, FILAS_MAPA, COLS_MAPA, nombresTienda, preciosTienda, efectoTienda, MAX_TIENDA, MAX_INV, saveExiste Por Referencia, saveNombre Por Referencia, saveVida Por Referencia, saveAtaque Por Referencia, saveOro Por Referencia, saveNivel Por Referencia, saveIntentos Por Referencia, saveInventario Por Referencia, saveCantidadItems Por Referencia)
	Definir resultado Como Entero
	resultado <- 0
// y la partida no haya terminado (resultado = 0 significa "en curso").
	Mientras estaVivo(vidaJugador) Y nivelJugador <= 3 Y resultado = 0 Hacer
		explorarMazmorra(nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, nivelJugador, posXJugador, posYJugador, intentosJugador, mazmorrasPasadas, vivoJugador, inventario, cantidadItems, mapa, FILAS_MAPA, COLS_MAPA, nombresTienda, preciosTienda, efectoTienda, MAX_TIENDA, MAX_INV, resultado, saveExiste, saveNombre, saveVida, saveAtaque, saveOro, saveNivel, saveIntentos, saveInventario, saveCantidadItems)
		Si resultado = 0 Entonces
			nivelJugador <- nivelJugador + 1
		FinSi
	FinMientras
	retorno <- resultado
FinSubProceso


// Genera las estadisticas de un enemigo segun el nivel de la mazmorra.
// Los valores se devuelven por referencia a traves de los parametros.
SubProceso generarEnemigo(nivel, nombreEnemigo Por Referencia, vidaEnemigo Por Referencia, ataqueEnemigo Por Referencia)
	Definir tipo Como Entero
	tipo <- azar(3)
	Segun nivel Hacer
		1:
// Nivel 1: enemigos debiles para introducir al jugador al combate.
			Segun tipo Hacer
				0:
					nombreEnemigo <- "Goblin"
					vidaEnemigo   <- 20
					ataqueEnemigo <- 5
				1:
					nombreEnemigo <- "Rata gigante"
					vidaEnemigo   <- 15
					ataqueEnemigo <- 4
				2:
					nombreEnemigo <- "Esqueleto"
					vidaEnemigo   <- 25
					ataqueEnemigo <- 6
			FinSegun
		2:
// Nivel 2: enemigos de dificultad intermedia con mas vida y ataque.
			Segun tipo Hacer
				0:
					nombreEnemigo <- "Orco"
					vidaEnemigo   <- 35
					ataqueEnemigo <- 8
				1:
					nombreEnemigo <- "Mago oscuro"
					vidaEnemigo   <- 30
					ataqueEnemigo <- 10
				2:
					nombreEnemigo <- "Hombre lobo"
					vidaEnemigo   <- 40
					ataqueEnemigo <- 9
			FinSegun
		3:
// Nivel 3: enemigos duros que preceden al boss final.
			Segun tipo Hacer
				0:
					nombreEnemigo <- "Caballero negro"
					vidaEnemigo   <- 55
					ataqueEnemigo <- 12
				1:
					nombreEnemigo <- "Demonio menor"
					vidaEnemigo   <- 50
					ataqueEnemigo <- 13
				2:
					nombreEnemigo <- "Wyvern"
					vidaEnemigo   <- 60
					ataqueEnemigo <- 11
			FinSegun
		De Otro Modo:
// Valor de seguridad por si el nivel estuviera fuera del rango esperado.
			nombreEnemigo <- "Sombra"
			vidaEnemigo   <- 20
			ataqueEnemigo <- 5
	FinSegun
FinSubProceso


// Definir archivo Como Archivo
// Abrir archivo Como Escritura "partida.txt"
// Escribir archivo, nombre
// Escribir archivo, vida
// ...
// Cerrar archivo
// Aca lo simulamos en memoria para que no de error en perfil estandar.
SubProceso guardarPartida(nombre, vida, ataque, oro, nivel, intentos, inv, cant, saveExiste Por Referencia, saveNombre Por Referencia, saveVida Por Referencia, saveAtaque Por Referencia, saveOro Por Referencia, saveNivel Por Referencia, saveIntentos Por Referencia, saveInventario Por Referencia, saveCantidadItems Por Referencia)
	Definir i Como Entero
	saveNombre        <- nombre
	saveVida          <- vida
	saveAtaque        <- ataque
	saveOro           <- oro
	saveNivel         <- nivel
	saveIntentos      <- intentos
	saveCantidadItems <- cant
// Copiamos el inventario item por item usando un FOR.
	Para i <- 1 Hasta cant Con Paso 1 Hacer
		saveInventario[i] <- inv[i]
	FinPara
// Marcamos que ya existe un guardado disponible para cargar.
	saveExiste <- Verdadero
	
	Escribir ""
	Escribir " >> Partida guardada en partida.txt (en memoria)"
	Escribir "    Nombre: ", nombre
	Escribir "    Vida: ", vida, "  Ataque: ", ataque, "  Oro: ", oro
	Escribir "    Nivel: ", nivel, "  Intentos: ", intentos
	Escribir "    Items guardados: ", cant
FinSubProceso


// Recupera los datos de un guardado anterior y los carga en el jugador.
// Restaura todos los atributos del personaje a los valores guardados.
// a sus valores base por seguridad.
SubProceso cargarPartida(saveNombre, saveVida, saveAtaque, saveOro, saveNivel, saveIntentos, saveInventario, saveCantidadItems, nombreJugador Por Referencia, vidaJugador Por Referencia, vidaMaxJugador Por Referencia, ataqueJugador Por Referencia, defensaJugador Por Referencia, oroJugador Por Referencia, nivelJugador Por Referencia, posXJugador Por Referencia, posYJugador Por Referencia, intentosJugador Por Referencia, mazmorrasPasadas Por Referencia, vivoJugador Por Referencia, inventario Por Referencia, cantidadItems Por Referencia)
	Definir i Como Entero
	nombreJugador     <- saveNombre
	vidaJugador       <- saveVida
	vidaMaxJugador    <- 100           // La vida maxima base siempre es 100 al cargar.
	ataqueJugador     <- saveAtaque
	defensaJugador    <- 1             // La defensa base se reinicia al cargar.
	oroJugador        <- saveOro
	nivelJugador      <- saveNivel
	intentosJugador   <- saveIntentos + 1  // Sumamos 1 porque es un nuevo intento.
	posXJugador       <- 2             // La posicion se reinicia al inicio del nivel.
	posYJugador       <- 2
	mazmorrasPasadas  <- saveNivel - 1
	vivoJugador       <- Verdadero
	cantidadItems     <- saveCantidadItems
	Para i <- 1 Hasta saveCantidadItems Con Paso 1 Hacer
		inventario[i] <- saveInventario[i]
	FinPara
FinSubProceso


SubProceso mostrarVictoria(nombre, oro, mazmorras)
	Borrar Pantalla
	Escribir "******************************************"
	Escribir "*             VICTORIA!!!                *"
	Escribir "******************************************"
	Escribir ""
	Escribir "  Felicitaciones ", nombre, "!"
	Escribir "  Has derrotado al BOSS FINAL y completado"
	Escribir "  todas las mazmorras de Dungeon Survival."
	Escribir ""
	Escribir "  Mazmorras pasadas: ", mazmorras
	Escribir "  Oro acumulado: ", oro
	Escribir ""
	Escribir "         Eres una leyenda!"
	Escribir "******************************************"
FinSubProceso


// Muestra la pantalla de game over cuando la vida del jugador llega a 0.
SubProceso mostrarGameOver(nombre, mazmorras, intentos)
	Borrar Pantalla
	Escribir "##########################################"
	Escribir "#              GAME OVER                 #"
	Escribir "##########################################"
	Escribir ""
	Escribir "  ", nombre, " ha caido en combate..."
	Escribir ""
	Escribir "  Mazmorras superadas: ", mazmorras
	Escribir "  Intentos: ", intentos
	Escribir ""
	Escribir "  La mazmorra se cobra otra alma."
	Escribir "  Volve a intentarlo desde el menu principal!"
	Escribir "##########################################"
FinSubProceso


// -------------------------
// SUBPROCESOS CON RETORNO Y CON PARAMETROS (funciones de tipo)
// -------------------------

// al ataque base del atacante. El dano minimo posible siempre es 1.
SubProceso dano <- calcularDanio(ataqueBase)
	Definir variacion Como Entero
	variacion <- azar(5)  // Genera un numero entre 0 y 4 inclusive.
	dano <- ataqueBase + variacion
	Si dano < 1 Entonces
		dano <- 1
	FinSi
FinSubProceso


// Verifica si un personaje sigue vivo segun su vida actual.
SubProceso vivo <- estaVivo(vida)
	Si vida > 0 Entonces
		vivo <- Verdadero
	SiNo
		vivo <- Falso
	FinSi
FinSubProceso


// Busca un item especifico dentro del inventario usando busqueda lineal.
// guarda su posicion y detiene la busqueda usando el flag "encontrado".
// Si el item no esta en el inventario, devuelve 0 (posicion invalida).
SubProceso indice <- buscarItem(inv, cant, item)
	Definir i Como Entero
	Definir encontrado Como Logico
	indice     <- 0
	encontrado <- Falso
// Busqueda lineal: recorremos el vector de izquierda a derecha.
// Cuando encontramos el item, guardamos su indice y usamos el flag
// para no seguir comparando en las iteraciones restantes del FOR.
	Para i <- 1 Hasta cant Con Paso 1 Hacer
		Si NO encontrado Entonces
			Si inv[i] = item Entonces
				indice     <- i
				encontrado <- Verdadero
			FinSi
		FinSi
	FinPara
FinSubProceso


// -------------------------
// SUBPROCESOS CON RETORNO SIN PARAMETROS (funciones de tipo simples)
// -------------------------
// Estos subprocesos devuelven un valor fijo o calculado sin necesitar
// ningun dato de entrada. Son utiles para centralizar valores iniciales:
// si queremos cambiar la vida o el oro de inicio, solo editamos aqui.
// -------------------------

// Devuelve la cantidad de oro con la que empieza el jugador: un valor
// aleatorio entre 20 y 30 inclusive.
SubProceso oro <- generarOroInicial
	oro <- 20 + azar(11)  // azar(11) genera entre 0 y 10, sumado a 20 da entre 20 y 30.
FinSubProceso


SubProceso vida <- generarVidaInicial
	vida <- 100
FinSubProceso