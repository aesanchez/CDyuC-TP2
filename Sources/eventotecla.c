#include "eventotecla.h"
char tecla=CASO_NULO;
char vacio = 1;//vacio=1 --> TRUE

void push_tecla(char t) {
	tecla = t;
	vacio = 0;
}
char pop_tecla() {
	vacio = 1;
	return tecla;
}
char tecla_vacia() {
	return vacio;
}
