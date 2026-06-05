Algoritmo DungeonSurvival
	
// tamano de inv y mapa
	Definir FILAS_MAPA, COLS_MAPA Como Entero
	Definir MAX_INV, MAX_TIENDA Como Entero
	FILAS_MAPA  <- 10
	COLS_MAPA   <- 10
	MAX_INV     <- 15
	MAX_TIENDA  <- 5
	
// stats del jugador
	Definir nombreJugador Como Cadena
	Definir vidaJugador, vidaMaxJugador Como Entero
	Definir ataqueJugador, defensaJugador Como Entero
	Definir oroJugador, nivelJugador Como Entero
	Definir posXJugador, posYJugador Como Entero
	Definir intentosJugador, mazmorrasPasadas Como Entero
	Definir vivoJugador Como Logico
	
// inventario
	Definir inventario Como Cadena
	Dimension inventario[15]
	Definir cantidadItems Como Entero
	

	Definir mapa Como Caracter
	Dimension mapa[8,12]
	

	Definir nombresTienda Como Cadena
	Dimension nombresTienda[5]
	Definir preciosTienda Como Entero
	Dimension preciosTienda[5]
	Definir efectoTienda Como Entero
	Dimension efectoTienda[5]
	
// Guardado
	Definir saveExiste Como Logico
	Definir saveNombre Como Cadena
	Definir saveVida, saveAtaque, saveOro Como Entero
	Definir saveNivel, saveIntentos Como Entero
	Definir saveInventario Como Cadena
	Dimension saveInventario[15]
	Definir saveCantidadItems Como Entero
	saveExiste <- Falso
	
// Control del menu
	Definir opcionMenu Como Entero
	Definir seguirJugando Como Logico
	Definir resultadoPartida Como Entero
	
	seguirJugando <- Verdadero
	

	inicializarTienda(nombresTienda, preciosTienda, efectoTienda)
	

	mostrarBienvenida()
	pausar()
	
	Repetir
		mostrarMenuPrincipal()
		Escribir Sin Saltar "  Tu eleccion: "
		Leer opcionMenu
		

		Segun opcionMenu Hacer
			1:
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
				mostrarReglas()
				pausar()
			4:
				mostrarManual()
				pausar()
			5:
				mostrarCreditos()
				pausar()
			6:
				seguirJugando <- Falso
				Escribir ""
				Escribir " >> Hasta la proxima, aventurero!"
			De Otro Modo:
				Escribir ""
				Escribir " >> Opcion invalida. Elegi un numero entre 1 y 6."
				pausar()
		FinSegun
	Hasta Que NO seguirJugando
	
FinAlgoritmo


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


SubProceso mostrarMenuExploracion
	Escribir ""
	Escribir " --- ACCIONES ---"
	Escribir "  1.Arriba  2.Abajo  3.Izq.  4.Der."
	Escribir "  5.Inventario  6.Ordenar  7.Estado"
	Escribir "  8.Guardar  9.Salir al menu"
FinSubProceso


SubProceso pausar
	Definir dummy Como Cadena
	Escribir ""
	Escribir "(Presiona ENTER para continuar...)"
	Leer dummy
FinSubProceso


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


SubProceso mostrarMapa(mapa, filas, cols)
	Definir i, j Como Entero
	Escribir ""
	Escribir "  --- MAPA DE LA MAZMORRA ---"
	Para i <- 1 Hasta filas Con Paso 1 Hacer
		Escribir Sin Saltar "   "
		Para j <- 1 Hasta cols Con Paso 1 Hacer
			Escribir Sin Saltar mapa[i,j], " "
		FinPara
		Escribir ""
	FinPara
FinSubProceso


SubProceso inicializarMapa(mapa, filas, cols, nivel, posXJugador Por Referencia, posYJugador Por Referencia)
	Definir i, j Como Entero
	Para i <- 1 Hasta filas Con Paso 1 Hacer
		Para j <- 1 Hasta cols Con Paso 1 Hacer
			Si i = 1 O i = filas O j = 1 O j = cols Entonces
				mapa[i,j] <- '#'
			SiNo
				mapa[i,j] <- '.'
			FinSi
		FinPara
	FinPara
	
	posYJugador <- 2
	posXJugador <- 2
	mapa[posYJugador, posXJugador] <- 'P'
	
	Segun nivel Hacer
		1:
			mapa[3, 6]  <- 'C'   
			mapa[5, 4]  <- 'M'   
			mapa[4, 9]  <- 'E'   
			mapa[6, 7]  <- 'E'   
			mapa[7, 11] <- 'S'   
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
			mapa[7, 11] <- 'B'   
	FinSegun
FinSubProceso



SubProceso atacar(ataqueOrigen, vidaDestino Por Referencia, nombreOrigen, nombreDestino)
	Definir dano Como Entero
	dano <- calcularDanio(ataqueOrigen)
	vidaDestino <- vidaDestino - dano
	Si vidaDestino < 0 Entonces
		vidaDestino <- 0
	FinSi
	Escribir "  >> ", nombreOrigen, " ataca a ", nombreDestino, " e inflige ", dano, " de dano."
FinSubProceso


SubProceso recompensaEnemigo(oro Por Referencia, inv Por Referencia, cant Por Referencia, maxInv, nivelEnemigo)
	Definir oroGanado, idx Como Entero
	Definir loot Como Cadena
	Dimension loot[3]
	Definir cantLoot Como Entero
	
	oroGanado <- 5 + azar(10) + (nivelEnemigo * 3)
	oro <- oro + oroGanado
	Escribir "  >> Ganas ", oroGanado, " de oro."
	
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
	
	Si cantLoot > 0 Entonces
		fusionarLoot(inv, cant, maxInv, loot, cantLoot)
	FinSi
FinSubProceso


SubProceso combate(nombreEnemigo, vidaEnemigoIni, ataqueEnemigo, nivelEnemigo, nombreJugador, vidaJugador Por Referencia, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador Por Referencia, inventario Por Referencia, cantidadItems Por Referencia, maxInv, victoria Por Referencia, huida Por Referencia)
	Definir vidaEnemigo Como Entero
	Definir opcion Como Entero
	Definir defendiendo Como Logico
	Definir danoRecibido Como Entero
	Definir exitoHuida Como Entero
	
	vidaEnemigo <- vidaEnemigoIni
	defendiendo <- Falso
	victoria    <- Falso
	huida       <- Falso
	
	Escribir ""
	Escribir " ============================================"
	Escribir "    Un ", nombreEnemigo, " aparece!"
	Escribir "    Vida: ", vidaEnemigo, "  Ataque: ", ataqueEnemigo
	Escribir " ============================================"
	
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
				defendiendo <- Falso
				usarPocion(inventario, cantidadItems, vidaJugador, vidaMaxJugador)
			3:
				defendiendo <- Verdadero
				Escribir "  >> ", nombreJugador, " se cubre con su defensa."
			4:
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
				Escribir "  >> Accion invalida. Pierdes el turno."
				defendiendo <- Falso
		FinSegun
		
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
	
	Si NO estaVivo(vidaEnemigo) Y NO huida Entonces
		Escribir ""
		Escribir "  >> Has derrotado a ", nombreEnemigo, "!"
		victoria <- Verdadero
		recompensaEnemigo(oroJugador, inventario, cantidadItems, maxInv, nivelEnemigo)
	FinSi
FinSubProceso


SubProceso usarPocion(inv Por Referencia, cant Por Referencia, vida Por Referencia, vidaMax)
	Definir indice, curacion, i Como Entero
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
		vida <- vida + curacion
		Si vida > vidaMax Entonces
			vida <- vidaMax
		FinSi
		Escribir "  >> Usaste ", inv[indice], ". Recuperas ", curacion, " de vida."
		Para i <- indice Hasta cant - 1 Con Paso 1 Hacer
			inv[i] <- inv[i+1]
		FinPara
		inv[cant] <- ""
		cant <- cant - 1
	SiNo
		Escribir "  >> No tenes pociones en el inventario!"
	FinSi
FinSubProceso


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
		
		Si opcion >= 1 Y opcion <= maxTienda Entonces
			Si oro >= preciosTienda[opcion] Entonces
				Si cant < maxInv Entonces
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
				venderItems(inv, cant, oro)
				pausar()
			SiNo
				Si opcion = maxTienda + 2 Entonces
					aparearTiendaInventario(inv, cant, nombresTienda, maxTienda)
					pausar()
				SiNo
					Si opcion = 0 Entonces
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


SubProceso venderItems(inv Por Referencia, cant Por Referencia, oro Por Referencia)
	Definir opcion, i, precio Como Entero
	Si cant = 0 Entonces
		Escribir " >> No tenes items para vender."
	SiNo
		mostrarInventario(inv, cant)
		Escribir Sin Saltar " Numero del item a vender (0 cancelar): "
		Leer opcion
		Si opcion >= 1 Y opcion <= cant Entonces
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
	
	oroEncontrado <- 10 + azar(15) + (nivel * 5)
	oro <- oro + oroEncontrado
	Escribir "   + ", oroEncontrado, " de oro"
	
	fusionarLoot(inv, cant, maxInv, loot, cantLoot)
FinSubProceso


SubProceso fusionarLoot(inv Por Referencia, cant Por Referencia, maxInv, loot, cantLoot)
	Definir i Como Entero
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
	Para i <- 1 Hasta cant - 1 Con Paso 1 Hacer
		Para j <- 1 Hasta cant - i Con Paso 1 Hacer
			Si inv[j] > inv[j+1] Entonces
				aux       <- inv[j]
				inv[j]    <- inv[j+1]
				inv[j+1]  <- aux
			FinSi
		FinPara
	FinPara
FinSubProceso


SubProceso inicializarTienda(nombresTienda Por Referencia, preciosTienda Por Referencia, efectoTienda Por Referencia)
	nombresTienda[1] <- "Pocion menor"
	preciosTienda[1] <- 15
	efectoTienda[1]  <- 20
	
	nombresTienda[2] <- "Pocion mayor"
	preciosTienda[2] <- 35
	efectoTienda[2]  <- 50
	
	nombresTienda[3] <- "Espada de hierro"
	preciosTienda[3] <- 50
	efectoTienda[3]  <- 5
	
	nombresTienda[4] <- "Escudo de madera"
	preciosTienda[4] <- 30
	efectoTienda[4]  <- 3
	
	nombresTienda[5] <- "Armadura ligera"
	preciosTienda[5] <- 60
	efectoTienda[5]  <- 25
FinSubProceso


SubProceso nuevaPartida(nombreJugador Por Referencia, vidaJugador Por Referencia, vidaMaxJugador Por Referencia, ataqueJugador Por Referencia, defensaJugador Por Referencia, oroJugador Por Referencia, nivelJugador Por Referencia, posXJugador Por Referencia, posYJugador Por Referencia, intentosJugador Por Referencia, mazmorrasPasadas Por Referencia, vivoJugador Por Referencia, inventario Por Referencia, cantidadItems Por Referencia)
	Borrar Pantalla
	Escribir "============= NUEVA PARTIDA ============="
	Escribir Sin Saltar " Ingresa el nombre de tu aventurero (ENTER = Paolo): "
	Leer nombreJugador
	Si nombreJugador = "" Entonces
		nombreJugador <- "Paolo"
	FinSi
	
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
	
	cantidadItems    <- 2
	inventario[1]    <- "Palo"
	inventario[2]    <- "Pocion menor"
	
	Escribir ""
	Escribir " >> Hola ", nombreJugador, "! Tu aventura comienza..."
	Escribir " >> Empezas con un Palo y una Pocion menor."
	pausar()
FinSubProceso


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
	
	Mientras estaVivo(vidaJugador) Y NO avanzaNivel Y NO salirAlMenu Hacer
		Borrar Pantalla
		mostrarEstado(nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, nivelJugador, intentosJugador, mazmorrasPasadas)
		mostrarMapa(mapa, FILAS_MAPA, COLS_MAPA)
		mostrarMenuExploracion()
		Escribir Sin Saltar "  Accion: "
		Leer accion
		
		nuevaX <- posXJugador
		nuevaY <- posYJugador
		
		Segun accion Hacer
			1:
				nuevaY <- posYJugador - 1
			2:
				nuevaY <- posYJugador + 1
			3:
				nuevaX <- posXJugador - 1
			4:
				nuevaX <- posXJugador + 1
			5:
				mostrarInventario(inventario, cantidadItems)
				pausar()
			6:
				ordenarInventario(inventario, cantidadItems)
				Escribir "  >> Inventario ordenado alfabeticamente."
				mostrarInventario(inventario, cantidadItems)
				pausar()
			7:
				mostrarEstado(nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, nivelJugador, intentosJugador, mazmorrasPasadas)
				pausar()
			8:
				guardarPartida(nombreJugador, vidaJugador, ataqueJugador, oroJugador, nivelJugador, intentosJugador, inventario, cantidadItems, saveExiste, saveNombre, saveVida, saveAtaque, saveOro, saveNivel, saveIntentos, saveInventario, saveCantidadItems)
				pausar()
			9:
				salirAlMenu <- Verdadero
				resultado   <- 3
			De Otro Modo:
					pausar()
					Escribir "  >> Accion invalida."
		FinSegun
		Si accion >= 1 Y accion <= 4 Entonces
			Si nuevaY >= 1 Y nuevaY <= FILAS_MAPA Y nuevaX >= 1 Y nuevaX <= COLS_MAPA Entonces
				destino <- mapa[nuevaY, nuevaX]
				Si destino = '#' Entonces
					Escribir "  >> Hay una pared en esa direccion."
					pausar()
				SiNo
					Si destino = '.' Entonces
						mapa[posYJugador, posXJugador] <- '.'
						posYJugador <- nuevaY
						posXJugador <- nuevaX
						mapa[posYJugador, posXJugador] <- 'P'
					SiNo
						Si destino = 'E' Entonces
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
									comerciante(oroJugador, inventario, cantidadItems, MAX_INV, ataqueJugador, defensaJugador, vidaMaxJugador, nombresTienda, preciosTienda, efectoTienda, MAX_TIENDA)
								SiNo
									Si destino = 'C' Entonces
										abrirCofre(inventario, cantidadItems, MAX_INV, oroJugador, nivelJugador)
										mapa[nuevaY, nuevaX] <- '.'
										mapa[posYJugador, posXJugador] <- '.'
										posYJugador <- nuevaY
										posXJugador <- nuevaX
										mapa[posYJugador, posXJugador] <- 'P'
										pausar()
									SiNo
										Si destino = 'S' Entonces
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
				Escribir "  >> Esa direccion esta fuera del mapa."
				pausar()
			FinSi
		FinSi
	FinMientras
	
	Si NO estaVivo(vidaJugador) Entonces
		vivoJugador <- Falso
		resultado   <- 2
	FinSi
FinSubProceso
SubProceso retorno <- jugarAventura(nombreJugador Por Referencia, vidaJugador Por Referencia, vidaMaxJugador Por Referencia, ataqueJugador Por Referencia, defensaJugador Por Referencia, oroJugador Por Referencia, nivelJugador Por Referencia, posXJugador Por Referencia, posYJugador Por Referencia, intentosJugador Por Referencia, mazmorrasPasadas Por Referencia, vivoJugador Por Referencia, inventario Por Referencia, cantidadItems Por Referencia, mapa Por Referencia, FILAS_MAPA, COLS_MAPA, nombresTienda, preciosTienda, efectoTienda, MAX_TIENDA, MAX_INV, saveExiste Por Referencia, saveNombre Por Referencia, saveVida Por Referencia, saveAtaque Por Referencia, saveOro Por Referencia, saveNivel Por Referencia, saveIntentos Por Referencia, saveInventario Por Referencia, saveCantidadItems Por Referencia)
	Definir resultado Como Entero
	resultado <- 0
	Mientras estaVivo(vidaJugador) Y nivelJugador <= 3 Y resultado = 0 Hacer
		explorarMazmorra(nombreJugador, vidaJugador, vidaMaxJugador, ataqueJugador, defensaJugador, oroJugador, nivelJugador, posXJugador, posYJugador, intentosJugador, mazmorrasPasadas, vivoJugador, inventario, cantidadItems, mapa, FILAS_MAPA, COLS_MAPA, nombresTienda, preciosTienda, efectoTienda, MAX_TIENDA, MAX_INV, resultado, saveExiste, saveNombre, saveVida, saveAtaque, saveOro, saveNivel, saveIntentos, saveInventario, saveCantidadItems)
		Si resultado = 0 Entonces
			nivelJugador <- nivelJugador + 1
		FinSi
	FinMientras
	retorno <- resultado
FinSubProceso


SubProceso generarEnemigo(nivel, nombreEnemigo Por Referencia, vidaEnemigo Por Referencia, ataqueEnemigo Por Referencia)
	Definir tipo Como Entero
	tipo <- azar(3)
	Segun nivel Hacer
		1:
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
			nombreEnemigo <- "Sombra"
			vidaEnemigo   <- 20
			ataqueEnemigo <- 5
	FinSegun
FinSubProceso
SubProceso guardarPartida(nombre, vida, ataque, oro, nivel, intentos, inv, cant, saveExiste Por Referencia, saveNombre Por Referencia, saveVida Por Referencia, saveAtaque Por Referencia, saveOro Por Referencia, saveNivel Por Referencia, saveIntentos Por Referencia, saveInventario Por Referencia, saveCantidadItems Por Referencia)
	Definir i Como Entero
	saveNombre        <- nombre
	saveVida          <- vida
	saveAtaque        <- ataque
	saveOro           <- oro
	saveNivel         <- nivel
	saveIntentos      <- intentos
	saveCantidadItems <- cant
	Para i <- 1 Hasta cant Con Paso 1 Hacer
		saveInventario[i] <- inv[i]
	FinPara
	saveExiste <- Verdadero
	
	Escribir ""
	Escribir " >> Partida guardada en partida.txt (en memoria)"
	Escribir "    Nombre: ", nombre
	Escribir "    Vida: ", vida, "  Ataque: ", ataque, "  Oro: ", oro
	Escribir "    Nivel: ", nivel, "  Intentos: ", intentos
	Escribir "    Items guardados: ", cant
FinSubProceso
SubProceso cargarPartida(saveNombre, saveVida, saveAtaque, saveOro, saveNivel, saveIntentos, saveInventario, saveCantidadItems, nombreJugador Por Referencia, vidaJugador Por Referencia, vidaMaxJugador Por Referencia, ataqueJugador Por Referencia, defensaJugador Por Referencia, oroJugador Por Referencia, nivelJugador Por Referencia, posXJugador Por Referencia, posYJugador Por Referencia, intentosJugador Por Referencia, mazmorrasPasadas Por Referencia, vivoJugador Por Referencia, inventario Por Referencia, cantidadItems Por Referencia)
	Definir i Como Entero
	nombreJugador     <- saveNombre
	vidaJugador       <- saveVida
	vidaMaxJugador    <- 100           
	ataqueJugador     <- saveAtaque
	defensaJugador    <- 1             
	oroJugador        <- saveOro
	nivelJugador      <- saveNivel
	intentosJugador   <- saveIntentos + 1  
	posXJugador       <- 2             .
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

SubProceso dano <- calcularDanio(ataqueBase)
	Definir variacion Como Entero
	variacion <- azar(5)  
	dano <- ataqueBase + variacion
	Si dano < 1 Entonces
		dano <- 1
	FinSi
FinSubProceso

SubProceso vivo <- estaVivo(vida)
	Si vida > 0 Entonces
		vivo <- Verdadero
	SiNo
		vivo <- Falso
	FinSi
FinSubProceso
}SubProceso indice <- buscarItem(inv, cant, item)
	Definir i Como Entero
	Definir encontrado Como Logico
	indice     <- 0
	encontrado <- Falso
	Para i <- 1 Hasta cant Con Paso 1 Hacer
		Si NO encontrado Entonces
			Si inv[i] = item Entonces
				indice     <- i
				encontrado <- Verdadero
			FinSi
		FinSi
	FinPara
FinSubProceso
SubProceso oro <- generarOroInicial
	oro <- 20 + azar(11)  
FinSubProceso


SubProceso vida <- generarVidaInicial
	vida <- 100
FinSubProceso
