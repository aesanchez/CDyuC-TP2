#include "clock.h"
#include "eventotecla.h"
#include "pantalla.h"
#include "timeout.h"

typedef enum {
	CERRADO, ABIERTO, DENEGADO, CAMBIAR_HH, CAMBIAR_MM, CAMBIAR_SS, CAMBIAR_C
} state;
state estadoActual;

char is_num(char);
char construir_num(char, char);
char obtener_numero(char);
void fCERRADO(void);
void fABIERTO(void);
void fDENEGADO(void);
void fCAMBIAR_HH(void);
void fCAMBIAR_MM(void);
void fCAMBIAR_SS(void);
void fCAMBIAR_C(void);
void (*MEF[])(void) = { fCERRADO, fABIERTO, fDENEGADO, fCAMBIAR_HH,
		fCAMBIAR_MM, fCAMBIAR_SS, fCAMBIAR_C };
char key;
char claveActual[5] = "1234";
char claveN[];
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
	default:
		//leer(claveN);
		//if(claveActual==claveN)
		//	estadoActual = ABIERTO;
		//else
		//	estadoActual = DENEGADO;
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
	i++;
	return 0;
}

void fABIERTO(void) {
	setear_string("ABIERTO", 1);
}
void fDENEGADO(void) {
	setear_string("DENEGADO", 1);
}

unsigned char flagBlink = 1;
void control_flagBlink() {
	timeout_empezar(5);
	if (timeout_termino() == 1) {
		flagBlink = flagBlink == 0 ? 1 : 0;
	}
}

void blinkear(char offset) {
	get_time_as_str(hhmmss);
	if ((flagBlink == 1) && (i < 2)) {
		hhmmss[i + offset] = ' ';
	}
	if (i == 1) {
		hhmmss[offset] = pro;
	}
	if (i == 2) {
		hhmmss[offset] = pro;
		hhmmss[1+offset] = sdo;
	}
	setear_string(hhmmss, 0);
}

void fCAMBIAR_HH(void) {
	setear_string("CAMBIANDO HORA", 1);
	control_flagBlink();
	blinkear(0);
	if (i < 2) {
		// return si es el primer numero y el numero no es valido
		if ((i == 0) && (obtener_numero(2) == 0)) {
			pro = key;
			return;
		}
		if ((pro == '2') && (obtener_numero(3) == 0))
			sdo = key;
		else if ((pro != '2') && obtener_numero(9) == 0)
			sdo = key;
	} else if (key != 'A') {
		if (tecla_vacia() == 0)
			key = pop_tecla();
	}

	if ((i == 2) && (key == 'A')) {
		cambiar_hora(construir_num(pro, sdo), IGNORE_MM, IGNORE_SS);
		estadoActual = CERRADO;
		key = CASO_NULO;
		i = 0;
	}
}

void fCAMBIAR_MM(void) {
	setear_string("CAMBIANDO MIN", 1);
	control_flagBlink();
	blinkear(3);
	if (i < 2) {
		if ((i == 0) && (obtener_numero(5) == 0)) {
			pro = key;
			return;
		}
		if (obtener_numero(9) == 0)
			sdo = key;
	} else if (key != 'B') {
		if (tecla_vacia() == 0)
			key = pop_tecla();
	}
	if ((i == 2) && (key == 'B')) {
		cambiar_hora(IGNORE_HH, construir_num(pro, sdo), IGNORE_SS);
		estadoActual = CERRADO;
		key = CASO_NULO;
		i = 0;
	}
}

void fCAMBIAR_SS(void) {
	setear_string("CAMBIANDO SEG", 1);
	control_flagBlink();
	blinkear(6);
	if (i < 2) {
		if ((i == 0) && (obtener_numero(5) == 0)) {
			pro = key;
			return;
		}
		if (obtener_numero(9) == 0)
			sdo = key;
	} else if (key != 'C') {
		if (tecla_vacia() == 0)
			key = pop_tecla();
	}
	if ((i == 2) && (key == 'C')) {
		cambiar_hora(IGNORE_HH, IGNORE_MM, construir_num(pro, sdo));
		estadoActual = CERRADO;
		key = CASO_NULO;
		i = 0;
	}
}

void fCAMBIAR_C(void) {

}
//void leer(char *clave){
//	int i = 0;
//	if (i < 5) {
//			if ((i == 0)) {
//				clave[i] = pop_tecla();
//			}
//			if (i == 1)
//				clave[i] = pop_tecla();
//			if ((i == 2)) {
//				clave[i] = pop_tecla();
//						}
//			if (i == 3)
//				clave[i] = pop_tecla();
//			if (i == 4)
//				clave[i] = pop_tecla(); 
//	}	
//}
