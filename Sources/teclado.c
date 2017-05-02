const unsigned char ERROR=42;//significado de la vida, que la vida es un error

void comprobar_tecla(void){
	//hay alguna tecla presionada?
	unsigned char columnaPresionada;
	columna_presionada(&columnaPresionada);
	if(columnaPresionada==ERROR) return;
	unsigned char filaPresionada;
	fila_presionada(&filaPresionada,columnaPresionada);
	if(filaPresionada==ERROR)return;
	
}

void fila_presionada(unsigned char * fp,unsigned char cp){
	unsigned char filaAct=0;
	while(filaAct<4){
		PTBD0=1;PTBD1=1;PTBD2=1;PTBD3=1;
		switch(filaAct){
		case 0:
			PTBD0=0;
			break;
		case 1:
			PTBD1=0;
			break;
		case 2:
			PTBD2=0;
			break;
		case 3:
			PTBD3=0;
			break;
		}
		columna_presionada(&cp);
		if(cp!=ERROR){//encontre la fila
			*fp=filaAct;
			return;
		}
		filaAct++;
	}
	*fp=ERROR;	
}

void columna_presionada(unsigned char * cp){
	if(PTBD7==0){
		*cp=3;
		return;
	}
	if(PTBD6==0){
		*cp=2;
		return;
	}
	if(PTBD5==0){
		*cp=1;
		return;
	}
	if(PTBD4==0){
		*cp=0;
		return;
	}
	*cp=ERROR;
}
