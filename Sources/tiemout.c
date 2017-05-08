#include "timeout.h"

const unsigned char flag='?';
unsigned char timeoutAct=flag;
unsigned char contador=0; // en 100 milisegundos

void contar(void){
	contador++;
}
void start_timeout(char sec){
	if(timeoutAct != flag)
		return;
	
	contador = 0;
	timeoutAct = sec;
}

char termino(void){
	if(contador >= timeoutAct){
		timeoutAct=flag;
		return 1;
	}
	return 0;
}
