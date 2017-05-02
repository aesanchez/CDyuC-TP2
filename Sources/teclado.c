#include <mc9s08sh8.h>

const unsigned char NO_PRESIONADO=42;//significado de la vida, que la vida no se presiona
const unsigned char TECLA_VACIA='<';
void columna_presionada(unsigned char *);
void fila_presionada(unsigned char *,unsigned char);
const char map[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};

char teclUlt=TECLA_VACIA;
void comprobar_tecla(void){
	unsigned char filaPresionada;
	unsigned char columnaPresionada;
	columna_presionada(&columnaPresionada);
	if(columnaPresionada==NO_PRESIONADO) {
		if(teclaUlt == TECLA_VACIA)return;
		push_tecla(teclaUlt);
		teclaUlt = TECLA_VACIA;
		return;
	}	
	fila_presionada(&filaPresionada,columnaPresionada);
	if(filaPresionada==NO_PRESIONADO){
		return;
	}	
	teclaUlt=map[filaPresionada][columnaPresionada];
}

void fila_presionada(unsigned char * fp,unsigned char cp){
	unsigned char filaAct=0;
	while(filaAct<4){
		PTBD=0x0F;
		switch(filaAct){
		case 0:
			PTBD_PTBD0=0;
			break;
		case 1:
			PTBD_PTBD1=0;
			break;
		case 2:
			PTBD_PTBD2=0;
			break;
		case 3:
			PTBD_PTBD3=0;
			break;
		}
		columna_presionada(&cp);
		if(cp!=NO_PRESIONADO){
			*fp=filaAct;
			PTBD=0x00;
			return;
		}
		filaAct++;
	}
	*fp=NO_PRESIONADO;	
}

void columna_presionada(unsigned char * cp){
	if(PTBD_PTBD7==0){
		*cp=3;
		return;
	}
	if(PTBD_PTBD6==0){
		*cp=2;
		return;
	}
	if(PTBD_PTBD5==0){
		*cp=1;
		return;
	}
	if(PTBD_PTBD4==0){
		*cp=0;
		return;
	}
	*cp=NO_PRESIONADO;
}
