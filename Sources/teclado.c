#include <mc9s08sh8.h>

const unsigned char ERROR=42;//significado de la vida, que la vida es un error
void columna_presionada(unsigned char *);
void fila_presionada(unsigned char *,unsigned char);
const char map[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};

//TODO(agustin) esto no corresponde
char ult='~';
void comprobar_tecla(void){
	//hay alguna tecla presionada?
	unsigned char filaPresionada;
	unsigned char columnaPresionada;
	columna_presionada(&columnaPresionada);
	if(columnaPresionada==ERROR)return;	
	fila_presionada(&filaPresionada,columnaPresionada);
	if(filaPresionada==ERROR)return;	
	ult=map[filaPresionada][columnaPresionada];
}
void ultimo_char(char * u){
	*u = ult;
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
		if(cp!=ERROR){
			*fp=filaAct;
			PTBD=0x00;
			return;
		}
		filaAct++;
	}
	*fp=ERROR;	
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
	*cp=ERROR;
}
