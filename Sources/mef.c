#include "clock.h"
#include "eventotecla.h"
#include "pantalla.h"
#include "timeout.h"
#include <string.h>

typedef enum {
	CERRADO,
	ABIERTO,
	DENEGADO,
	CAMBIAR_HH,
	CAMBIAR_MM,
	CAMBIAR_SS,
	CAMBIAR_C,
	INGRESAR_CLAVE,
	CLAVE_NUEVA,
	FIN_NUEVA_CLAVE
} state;
state estadoActual;

char leer_clave(void);
char valido(char, char);
char construir_num(char, char);
char obtener_numero(char);
char igualdad_strings(char[], char[]);

void fCERRADO(void);
void fABIERTO(void);
void fDENEGADO(void);
void fCAMBIAR_HH(void);
void fCAMBIAR_MM(void);
void fCAMBIAR_SS(void);
void fCAMBIAR_C(void);
void fINGRESAR_CLAVE(void);
void fCLAVE_NUEVA(void);
void fFIN_NUEVA_CLAVE(void);

void (*MEF[])(void) = { fCERRADO, fABIERTO, fDENEGADO, fCAMBIAR_HH,
		fCAMBIAR_MM, fCAMBIAR_SS, fCAMBIAR_C, fINGRESAR_CLAVE, fCLAVE_NUEVA, fFIN_NUEVA_CLAVE};

char key;
char claveActual[16] = { '1', '2', '3', '4' };
char claveLeida[16];
char hhmmss[9];

void MEF_init(void) {
	key = CASO_NULO;
	estadoActual = CERRADO;
}

void MEF_update(void) {
	(*MEF[estadoActual])();
}

void fCERRADO(void) {
	get_time_as_str(hhmmss);
	setear_string(hhmmss, 0);
	setear_string("CERRADO", 1);
	if (tecla_vacia() == 0) {
		key = pop_tecla();
	}
	switch (key) {
	case 'A':
		estadoActual = CAMBIAR_HH;
		break;
	case 'B':
		estadoActual = CAMBIAR_MM;
		break;
	case 'C':
		estadoActual = CAMBIAR_SS;
		break;
	case 'D':
		estadoActual = CAMBIAR_C;
		break;
	case '*':
		break;
	case '#':
		break;
	case CASO_NULO:
		break;
		// entra a default cuando key es un numero
	default:
		estadoActual = INGRESAR_CLAVE;
		break;
	}
}

char valido(char n, char max) {
	return ((n - '0' <= max) && (n - '0' >= 0)) ? 1 : 0;
}

char construir_num(char pro, char sdo) {
	return (((pro - '0') * 10) + (sdo - '0'));
}

char i, pro, sdo;

// return:
// 		1: no hay tecla o no es valido
//		0: todo piola
char obtener_numero(char max) {
	if (tecla_vacia() == 1)
		return 1;
	key = pop_tecla();
	if (valido(key, max) == 0)
		return 1;
	i = ++i % 2;
	return 0;
}

void fABIERTO(void) {
	get_time_as_str(hhmmss);
	setear_string(hhmmss, 0);
	setear_string("ABIERTO", 1);
	timeout_empezar(50);
	if (timeout_termino() == 1) {
		key = CASO_NULO;
		// borrar basura
		pop_tecla();
		estadoActual = CERRADO;
	}
}

void fFIN_NUEVA_CLAVE(void) {
	get_time_as_str(hhmmss);
	setear_string(hhmmss, 0);
	setear_string("FIN NUEVA CLAVE", 1);
	timeout_empezar(50);
	if (timeout_termino() == 1) {
		key = CASO_NULO;
		// borrar basura
		pop_tecla();
		estadoActual = CERRADO;
	}
}

void fDENEGADO(void) {
	get_time_as_str(hhmmss);
	setear_string(hhmmss, 0);
	setear_string("DENEGADO", 1);
	timeout_empezar(20);
	if (timeout_termino() == 1) {
		key = CASO_NULO;
		// borrar basura
		pop_tecla();
		estadoActual = CERRADO;
	}
}

unsigned char flagBlink = 1;
void control_flagBlink() {
	timeout_empezar(5);
	if (timeout_termino() == 1) {
		flagBlink = flagBlink == 0 ? 1 : 0;
	}
}

char flagDosTeclas = 0;
void blinkear(char offset) {
	get_time_as_str(hhmmss);

	if (i == 1) {
		hhmmss[offset] = pro;
	}
	if (flagDosTeclas == 1) {
		hhmmss[offset] = pro;
		hhmmss[1 + offset] = sdo;
	}
	if (flagBlink == 1) {
		hhmmss[i + offset] = ' ';
	}
	setear_string(hhmmss, 0);
}

void fCAMBIAR_HH(void) {
	setear_string("CAMBIANDO HORA", 1);
	control_flagBlink();
	blinkear(0);
	// return si es el primer numero y el numero no es valido
	if ((i == 0) && (obtener_numero(2) == 0)) {
		pro = key;
		return;
	}
	if ((pro == '2') && (obtener_numero(3) == 0)) {
		sdo = key;
		flagDosTeclas = 1;
	} else if ((pro != '2') && obtener_numero(9) == 0) {
		sdo = key;
		flagDosTeclas = 1;
	}

	if ((key == 'A') && (flagDosTeclas == 1)) {
		flagDosTeclas = 0;
		cambiar_hora(construir_num(pro, sdo), IGNORE_MM, IGNORE_SS);
		key = CASO_NULO;
		i = 0;
		timeout_cerrar();
		estadoActual = CERRADO;
	}
}

void fCAMBIAR_MM(void) {
	setear_string("CAMBIANDO MIN", 1);
	control_flagBlink();
	blinkear(3);
	if ((i == 0) && (obtener_numero(5) == 0)) {
		pro = key;
		return;
	}
	if (obtener_numero(9) == 0) {
		sdo = key;
		flagDosTeclas = 1;
	}
	if ((flagDosTeclas == 1) && (key == 'B')) {
		flagDosTeclas = 0;
		cambiar_hora(IGNORE_HH, construir_num(pro, sdo), IGNORE_SS);
		timeout_cerrar();
		key = CASO_NULO;
		i = 0;
		estadoActual = CERRADO;
	}
}

void fCAMBIAR_SS(void) {
	setear_string("CAMBIANDO SEG", 1);
	control_flagBlink();
	blinkear(6);
	if ((i == 0) && (obtener_numero(5) == 0)) {
		pro = key;
		return;
	}
	if (obtener_numero(9) == 0) {
		sdo = key;
		flagDosTeclas = 1;
	}
	if ((flagDosTeclas == 1) && (key == 'C')) {
		flagDosTeclas = 0;
		cambiar_hora(IGNORE_HH, IGNORE_MM, construir_num(pro, sdo));
		timeout_cerrar();
		key = CASO_NULO;
		i = 0;
		estadoActual = CERRADO;
	}
}

char car = 0;
char asteriscos[17] = "                ";
void fCAMBIAR_C(void) {
	char j;
	setear_string("CLAVE ACTUAL:", 0);
	timeout_empezar(30);
	if (timeout_termino() == 1) {
		estadoActual = DENEGADO;
		for (j = 0; j < 16; j++) {
			asteriscos[j]=' ';
		}
		claveLeida[car] = '\0';
		car = 0;
		return;
	}
	for (j = 0; j < car; j++) {
		asteriscos[j]='*';
	}
	setear_string(asteriscos, 1);
	char aux = leer_clave();
	if (aux > 0) {
		for (j = 0; j < 16; j++) {
			asteriscos[j]=' ';
		}
		car = 0;
		timeout_cerrar();
		if (aux == 1) {
			if (igualdad_strings(claveLeida, claveActual) == 1) {
				estadoActual = CLAVE_NUEVA;
			} else {
				estadoActual = DENEGADO;
			}
		}		
		key = CASO_NULO;
	}
}

void fCLAVE_NUEVA(void) {
	char j;
	setear_string("CLAVE NUEVA:", 0);
	timeout_empezar(30);
	for (j = 0; j < car; j++) {
		asteriscos[j]='*';
	}
	setear_string(asteriscos, 1);
	if (timeout_termino() == 1) {
		key = CASO_NULO;
		estadoActual = CERRADO;
		car = 0;
		return;
	}
	char aux = leer_clave();
	if (aux > 0) {
		if(aux == 1){
			strcpy(claveActual, claveLeida);
		}		
		key = CASO_NULO;
		car = 0;
		timeout_cerrar();
		for (j = 0; j < 16; j++) {
			asteriscos[j]=' ';
		}
		estadoActual = CERRADO;
		return;
	}
}

char igualdad_strings(char clavel[], char clavea[]) {
	char k;
	if (strlen(clavel) != strlen(clavea))
		return 0;
	for (k = 0; k < strlen(clavea); k++) {
		if(clavel[k]!=clavea[k])
		return 0;
	}
	return 1;
}

void fINGRESAR_CLAVE(void) {
	char j;
	timeout_empezar(30);
	if (timeout_termino() == 1) {
		estadoActual = DENEGADO;
		for (j = 0; j < 16; j++) {
			asteriscos[j]=' ';
		}
		car = 0;
		return;
	}
	get_time_as_str(hhmmss);
	setear_string(hhmmss, 0);
	for (j = 0; j < car; j++) {
		asteriscos[j]='*';
	}
	setear_string(asteriscos, 1);

	if (car == 0)
		claveLeida[car++] = key;	
	char aux = leer_clave();		
	if (aux > 0) {
		for (j = 0; j < 16; j++) {
			asteriscos[j]=' ';
		}
		car = 0;
		timeout_cerrar();
		if(aux == 1){
			if (igualdad_strings(claveLeida, claveActual) == 1) {
				estadoActual = ABIERTO;
			} else {
				estadoActual = DENEGADO;
			}
		}		
		key = CASO_NULO;
	}
}
// return: 0 si todavia no termino
//         1 si termino correctamente la lectura de la clave
//         2 si se cancelo la carga de la clave
char leer_clave(void) {
	if (car == 16) {
		return 1;
	}
	if (tecla_vacia() == 0) {
		key = pop_tecla();
		// pregunta si es numero y es menor que 9
		timeout_reset();
		if (key == 'D') {
			claveLeida[car] = '\0';
			return 1;
		}
		if (key == '#') {
			return 2;
		}
		if (valido(key, 9) == 1) {
			claveLeida[car++] = key;
		}
	}
	return 0;
}

