# Dungeon Survival — Especificaciones Técnicas y Guía de Instalación

Documentación oficial del proyecto **Dungeon Survival**, un juego 2D de mazmorras con combate por turnos desarrollado en **C++** con **SFML 3.1.0** sobre **Visual Studio 2022**.

Esta guía detalla **todos** los pasos para que cualquier persona pueda clonar el repositorio, instalar las dependencias y ejecutar el juego sin errores.

---

## 1. Requisitos del sistema

### 1.1. Hardware mínimo

| Componente | Mínimo recomendado |
|------------|--------------------|
| Sistema operativo | Windows 10 (64 bits) o Windows 11 |
| Procesador | Intel/AMD x64 de doble núcleo, 2.0 GHz o superior |
| Memoria RAM | 4 GB |
| GPU | Compatible con OpenGL 3.0+ (cualquier integrada moderna) |
| Almacenamiento | ~3 GB libres (1.5 GB del SDK SFML + Visual Studio + el proyecto) |
| Resolución | 1280 × 720 mínima (el juego usa ventana 1280 × 720) |

### 1.2. Software base

- **Windows 10 / 11 (64 bits)** — es obligatoriamente la arquitectura **x64**, la configuración de 32 bits del proyecto no enlaza SFML.
- **Git** (opcional, para clonar el repositorio) — [https://git-scm.com/downloads](https://git-scm.com/downloads)
- **Visual Studio 2022 Community** (ver paso 2)
- **SFML 3.1.0** (ver paso 3)

> ⚠️ **Importante:** el proyecto está configurado para SFML **3.x** (no 2.x). Las APIs cambiaron entre ambas versiones, por lo que usar SFML 2.5 / 2.6 produce errores de compilación.

---

## 2. Instalación de Visual Studio 2022 Community

### 2.1. Descarga

1. Entrar a [https://visualstudio.microsoft.com/es/vs/community/](https://visualstudio.microsoft.com/es/vs/community/).
2. Descargar el instalador (`VisualStudioSetup.exe`).
3. Ejecutarlo como administrador.

### 2.2. Componentes a marcar (Workloads)

Al abrir el instalador hay que tildar **obligatoriamente** la siguiente carga de trabajo:

- ✅ **Desarrollo para el escritorio con C++** (`Desktop development with C++`)

Dentro del panel derecho ("Detalles de instalación"), verificar que estén marcados los componentes individuales:

- ✅ MSVC v143 — VS 2022 C++ x64/x86 build tools (latest)
- ✅ Windows 11 SDK (cualquier versión 10.0.x reciente)
- ✅ Herramientas de generación de perfiles de C++
- ✅ C++ CMake tools for Windows (opcional, recomendado)
- ✅ Compatibilidad con C++ AddressSanitizer (opcional)
- ✅ IntelliCode

> El `.vcxproj` indica `PlatformToolset = v145`, que se resuelve automáticamente con el toolset **MSVC v143** moderno de VS 2022.

### 2.3. Verificación

Tras instalar, abrir **"Visual Studio Installer"** → "Modificar" → comprobar que la workload de C++ está instalada y actualizada a la última versión disponible.

---

## 3. Instalación y configuración de SFML 3.1.0

El proyecto está configurado para encontrar SFML en una **ruta fija**: `C:\SFML-3.1.0`. Si se instala en otro lugar hay que cambiar la ruta en las propiedades del proyecto (ver paso 4.4).

### 3.1. Descarga

1. Entrar a la página oficial: [https://www.sfml-dev.org/download/sfml/3.1.0/](https://www.sfml-dev.org/download/sfml/3.1.0/)
2. Descargar la versión: **Visual C++ 17 (2022) — 64-bit**.
3. El archivo será un `.zip` llamado aproximadamente `SFML-3.1.0-windows-vc17-64-bit.zip`.

### 3.2. Extracción

1. Descomprimir el `.zip` en `C:\`.
2. Renombrar (si hace falta) la carpeta resultante a exactamente: **`C:\SFML-3.1.0`**.
3. La estructura final debe ser:

```
C:\SFML-3.1.0\
├── bin\        ← contiene los .dll (sfml-graphics-3.dll, etc.)
├── include\    ← contiene los headers (SFML/Graphics.hpp, etc.)
├── lib\        ← contiene los .lib (sfml-graphics-d.lib, etc.)
└── ...
```

### 3.3. Por qué esa ruta

El archivo `DungeonSurvival.vcxproj` tiene escrito:

```xml
<AdditionalIncludeDirectories>C:\SFML-3.1.0\include</AdditionalIncludeDirectories>
<AdditionalLibraryDirectories>C:\SFML-3.1.0\lib</AdditionalLibraryDirectories>
```

Así que la ruta debe ser **idéntica** (mismas mayúsculas, mismo guion, mismo punto). Si se coloca en otro lugar, hay que ajustar el proyecto (ver paso 4.4).

---

## 4. Configuración del proyecto

### 4.1. Clonar / descargar el repositorio

```powershell
git clone <URL_del_repositorio> DungeonSurvival
cd DungeonSurvival
```

O bien descargar el `.zip` y descomprimirlo.

### 4.2. Abrir la solución

Hacer doble clic en `DungeonSurvival.slnx` (o abrir desde Visual Studio: `File → Open → Project/Solution`).

### 4.3. Seleccionar la configuración correcta

En la barra superior de Visual Studio, elegir:

- Configuración: **`Debug`** (recomendada para desarrollo) o **`Release`** (para distribuir)
- Plataforma: **`x64`** (¡obligatorio!)

> ❌ La plataforma **`Win32`** no está configurada con SFML en el `.vcxproj`. Compilar con Win32 produce errores de enlace (`unresolved external symbol sf::...`).

### 4.4. (Solo si SFML está en otra ruta) Modificar las rutas

Si por algún motivo el SDK SFML no quedó en `C:\SFML-3.1.0`:

1. Click derecho sobre el proyecto `DungeonSurvival` → **Propiedades**.
2. Asegurar que arriba esté seleccionado `Configuration: All Configurations`, `Platform: x64`.
3. Cambiar:
   - **C/C++ → General → Additional Include Directories** → reemplazar `C:\SFML-3.1.0\include` por la ruta correcta.
   - **Linker → General → Additional Library Directories** → reemplazar `C:\SFML-3.1.0\lib`.
4. **Linker → Input → Additional Dependencies** debe contener:

   ```
   sfml-graphics-d.lib;
   sfml-audio-d.lib;
   sfml-window-d.lib;
   sfml-system-d.lib;
   %(AdditionalDependencies)
   ```

   En **Release** se usan las mismas (sin `-d`):

   ```
   sfml-graphics.lib;
   sfml-audio.lib;
   sfml-window.lib;
   sfml-system.lib;
   %(AdditionalDependencies)
   ```

### 4.5. Propiedades clave del proyecto

| Propiedad | Valor |
|-----------|-------|
| **Platform Toolset** | `v145` (VS 2022) |
| **Windows SDK Version** | `10.0` (cualquier 10.x instalada) |
| **C++ Language Standard** | `ISO C++17` (`/std:c++17`) — config x64 |
| **Character Set** | `Use Unicode Character Set` |
| **SubSystem** | `Console (/SUBSYSTEM:CONSOLE)` |
| **Configuration Type** | `Application (.exe)` |
| **Runtime Library** | MD (Multi-threaded DLL) / MDd en Debug — coincide con SFML dinámico |

---

## 5. DLLs de SFML (runtime)

Cuando se ejecuta el `.exe` Windows necesita encontrar las DLLs de SFML. El repo **ya las incluye** en la raíz del proyecto:

| Build | DLLs necesarias |
|-------|-----------------|
| **Debug** | `sfml-graphics-d-3.dll`, `sfml-window-d-3.dll`, `sfml-system-d-3.dll`, `sfml-audio-d-3.dll` |
| **Release** | `sfml-graphics-3.dll`, `sfml-window-3.dll`, `sfml-system-3.dll`, `sfml-audio-3.dll` |

### 5.1. Ubicación de las DLLs

Deben estar **al lado del ejecutable** generado (en `x64\Debug\` o `x64\Release\`) **o** en el directorio de trabajo desde el que se ejecuta. Las dos opciones válidas son:

- **Opción A (recomendada para Debug en VS):** dejar las DLLs en la raíz del proyecto y asegurarse de que Visual Studio ejecute con `Working Directory = $(ProjectDir)` (lo normal por defecto).
- **Opción B (para distribuir el `.exe`):** copiar las 4 DLLs (más los assets) al lado del `.exe` final.

Si Windows muestra el error **"The code execution cannot proceed because sfml-graphics-d-3.dll was not found"**, la causa es que la DLL no está accesible — copiala al directorio del `.exe`.

---

## 6. Assets necesarios

El juego carga estos archivos por **ruta relativa** desde el directorio de trabajo. Todos están en el repositorio y deben permanecer junto al `.vcxproj`/`.exe`:

### 6.1. Imágenes (PNG / JPG)

| Archivo | Descripción |
|---------|-------------|
| `fondo.png` | Fondo de menú principal |
| `fondo_pelea.png` | Fondo de las batallas |
| `prota_01.png` | Sprite del jugador |
| `Enemigo.png` | Sprite del enemigo común |
| `boss-01.png` | Sprite del jefe final (Guardian) |
| `cofre.png` | Sprite de los cofres |
| `mercader.png` | Sprite del NPC mercader |
| `salida.png` | Sprite de la puerta / salida de nivel |
| `customladrillo.png` | Textura de pared |
| `suelo.jpg` | Textura de suelo |

### 6.2. Fuentes (TTF)

| Archivo | Uso |
|---------|-----|
| `medieval.ttf` | Fuente decorativa principal (títulos, menús) |
| `arial.ttf`, `arialbd.ttf`, `ariali.ttf`, `arialbi.ttf` | Fuente regular del HUD y diálogos |
| `ARIALN.TTF`, `ARIALNB.TTF`, `ARIALNI.TTF`, `ARIALNBI.TTF` | Variantes "Narrow" usadas en cinemáticas |
| `ariblk.ttf` | Black (negrita gruesa) para énfasis |

### 6.3. Datos persistentes

- `partidas.txt` — archivo donde el juego escribe los slots de guardado. Se genera/actualiza solo cuando el jugador guarda. Si no existe, el juego lo crea.

> 📌 Si se mueve el ejecutable a otra carpeta hay que **copiar todos los assets** al mismo directorio. De lo contrario el juego abre con texturas en negro o se cierra al no encontrar las fuentes.

---

## 7. Estructura del proyecto

```
DungeonSurvival/
├── Main.cpp                    ← Entry point: llama a iniciarjuego()
├── Motor.cpp                   ← Bucle principal, estados, render y eventos (≈3700 líneas)
├── Menu.h                      ← Declaración de iniciarjuego()
├── funciones.cpp / funciones.h ← Lógica: movimiento, interacción, save/load, inventario
├── mapaf.cpp / mapa.h          ← Carga y dibujado del mapa (matrices)
├── entidades.cpp               ← Inicialización de personajes/enemigos
├── structs.h                   ← personaje, enemigo, mercader, cofre, registro_partida
├── partidas.txt                ← Guardado persistente
├── DungeonSurvival.slnx        ← Solución de Visual Studio
├── DungeonSurvival.vcxproj     ← Proyecto C++
├── *.png / *.jpg               ← Sprites y fondos
├── *.ttf                       ← Fuentes
└── sfml-*-3.dll                ← Runtimes de SFML 3.1.0
```

---

## 8. Compilación y ejecución

### 8.1. Desde Visual Studio

1. Verificar configuración: `Debug | x64` (o `Release | x64`).
2. Menú **Build → Build Solution** (`Ctrl + Shift + B`).
3. La salida del compilador debe terminar en:
   ```
   ========== Build: 1 succeeded, 0 failed ==========
   ```
4. Ejecutar con `F5` (con debugger) o `Ctrl + F5` (sin debugger).

### 8.2. Desde la línea de comandos (opcional)

Abrir **"x64 Native Tools Command Prompt for VS 2022"** y ejecutar:

```bat
cd C:\ruta\al\proyecto\DungeonSurvival
msbuild DungeonSurvival.vcxproj /p:Configuration=Release /p:Platform=x64
```

El binario queda en `x64\Release\DungeonSurvival.exe`.

---

## 9. Controles del juego

| Tecla | Acción |
|-------|--------|
| `W` `A` `S` `D` | Mover al personaje |
| `E` | Interactuar (puerta, cofre, mercader, enemigo) |
| `5` | Abrir / cerrar inventario |
| `6` | **Ordenar inventario alfabéticamente** |
| `8` | Guardar partida |
| `9` | Volver al menú principal |
| `Esc` | Pausa (en juego) / Volver (en menús) |
| `Enter` | Equipar / usar item / confirmar |
| `Flechas` o `W` `S` | Navegar listas (inventario / tienda) |

---

## 10. Resolución de problemas frecuentes

### ❌ "Cannot open include file: 'SFML/Graphics.hpp'"
**Causa:** la ruta de includes está mal o SFML no está en `C:\SFML-3.1.0`.
**Solución:** revisar paso 3.2 y 4.4.

### ❌ "unresolved external symbol __imp_sf::..."
**Causa:** o estás compilando en `Win32` (no soportado) o falta enlazar las `.lib` de SFML.
**Solución:** cambiar plataforma a `x64` y revisar paso 4.4 (Additional Dependencies).

### ❌ "The code execution cannot proceed because sfml-graphics-d-3.dll was not found"
**Causa:** las DLLs no están junto al `.exe`.
**Solución:** copiar las 4 DLLs de SFML al lado del ejecutable (paso 5).

### ❌ El juego abre con cuadros negros o sin texto
**Causa:** no encuentra los `.png` / `.ttf` porque el "working directory" no es el del proyecto.
**Solución:** click derecho sobre el proyecto → Propiedades → Debugging → `Working Directory = $(ProjectDir)`. Alternativa: copiar los assets al lado del `.exe`.

### ❌ Error LNK1104 — "cannot open file 'sfml-graphics.lib'"
**Causa:** estás en Release pero solo tenés las `.lib` Debug (o viceversa).
**Solución:** SFML 3.1.0 (zip oficial) trae las dos variantes en `C:\SFML-3.1.0\lib`. Verificar que existan los archivos `sfml-*.lib` y `sfml-*-d.lib`.

### ❌ "MSB8020 — Cannot find Platform Toolset = 'v145'"
**Causa:** falta la workload de C++ de VS 2022 o una versión muy vieja.
**Solución:** abrir Visual Studio Installer → Modificar → instalar "Desktop development with C++" actualizado (paso 2.2).

---

## 11. Checklist final antes de ejecutar

- [ ] Visual Studio 2022 Community con workload **Desktop development with C++** instalada.
- [ ] SFML 3.1.0 extraído en **`C:\SFML-3.1.0`** (versión VC17 / 64-bit).
- [ ] Configuración activa en VS: **`Debug | x64`** o **`Release | x64`** (nunca Win32).
- [ ] Todos los assets (`.png`, `.jpg`, `.ttf`) presentes en la carpeta del proyecto.
- [ ] DLLs `sfml-*-3.dll` accesibles desde el directorio de ejecución.
- [ ] `partidas.txt` con permisos de escritura (o que el directorio los tenga para crearlo).

Si los seis ítems están cumplidos, **`Ctrl + F5`** debe abrir la ventana del juego sin errores. 🎮

---

## 12. Información del proyecto

| Campo | Valor |
|-------|-------|
| Lenguaje | C++17 (config x64) / C++20 (config Win32 no usada) |
| Compilador | MSVC v143 / Toolset v145 (Visual Studio 2022) |
| Librería gráfica | SFML 3.1.0 |
| Plataforma objetivo | Windows 10 / 11 — x64 |
| Tipo de aplicación | Console + ventana SFML |
| Persistencia | Archivo de texto `partidas.txt` |
| Arquitectura | Monolítica con máquina de estados (`estado_pantalla`) |
