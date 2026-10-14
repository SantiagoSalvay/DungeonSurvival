#include "Gestion.h"
#include "ErroresMios.h"

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
