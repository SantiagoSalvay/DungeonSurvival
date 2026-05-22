#include <string>

struct Personaje {
	std::string name;
	int oro;
	int vida;
	int cantidad_pociones_m;
	int cantidad_pociones_g;
	std::string arma_equipada;
	std::string armadura_equipada;
	int ataque;
	int defensa;
	int nivel_actual;
	int posicion_x;
	int posicion_y;
};

struct Enemigo {
	std::string nombre;
	int vida;
	int ataque;
	int defensa;
};

struct Mercader {
	std::string nombre;
	std::string catalogo[5];
	int precios[5];
};

struct Cofre {
	int loot[3];
	bool abierto;
};