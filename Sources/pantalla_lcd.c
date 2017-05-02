#include "lcd.h"

#define STR_LEN 17
unsigned char primerFila[STR_LEN];
unsigned char segundaFila[STR_LEN];

void flush_fila(char);

/*
void copy_string(char d[], char s[]) {
   int c = 0;
   while (s[c] != '\0') {
      d[c] = s[c];
      c++;
   }
   d[c] = '\0';
}
*/
void pantalla_update(void) {
	LCD_pos_xy(0,0);
	LCD_write_string(primerFila);
	LCD_pos_xy(0,1);
	LCD_write_string(segundaFila);
}

void pantalla_init(void) {
	LCD_init(DISPLAY_8X5|_2_LINES,DISPLAY_ON|CURSOR_OFF);
	flush_fila(0);
	flush_fila(1);
	pantalla_update();
}

void flush_fila(char f){
	LCD_pos_xy(0,f);
	LCD_write_string("                ");
}

void push_string(char str[],char fila){
	if(fila > 1){return;}
	flush_fila(fila);
	char length=sizeof(str);
	char offset=(STR_LEN-length)/2;
	char i;
	for(i=offset;i<(length+offset);i++){
		if(fila==0){
			primerFila[i]=str[i-offset];
		}else{
			segundaFila[i]=str[i-offset];
		}
	}
}
