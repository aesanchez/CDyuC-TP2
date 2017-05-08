#include "timeout.h"

const unsigned char flag = '?';
unsigned char timeoutAct = flag;
unsigned char timeout_contador = 0; // en 100 milisegundos

void timeout_contar(void) {
	timeout_contador++;
}

// sec escalado en 0.1 segundos
// ejemplo: si sec=5 -> son 0.5 segundos
void timeout_empezar(char sec) {
	if (timeoutAct != flag){
		return;
	}
	timeout_contador = 0;
	timeoutAct = sec;
}
void timeout_reset(){
	timeout_contador=0;
}

char timeout_termino(void) {
	if (timeout_contador >= timeoutAct) {
		timeoutAct = flag;
		return 1;
	}
	return 0;
}
