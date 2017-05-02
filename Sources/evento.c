unsigned char tecla;
unsigned char vacio=1;

void push_tecla(unsigned char t){
	tecla = t;
	vacio=0;
}

unsigned char pop_tecla(void){
	vacio=1;
	return tecla;
}

unsigned char tecla_vacia(void){
	return vacio;
}
