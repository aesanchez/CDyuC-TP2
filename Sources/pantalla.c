#include "pantalla.h"
#include "lcd.h"
#include <string.h>

char pantalla[2][STR_LEN + 1] = { { "                " },
		{ "                " } };


void setear_string(char str[], char fila) {
	char length = strlen(str);
	char offset = (STR_LEN - length) / 2;
	char i;
	//centra el string y completa la linea con espacios
	for (i = 0; i < STR_LEN; i++) {
		if((i<offset)||((length+offset)<=i))
		pantalla[fila][i]=' ';
		else
		pantalla[fila][i]=str[i-offset];
	}
}
void pantalla_init(void) {
	LCD_init(DISPLAY_8X5 | _2_LINES, DISPLAY_ON | CURSOR_OFF);
}
void pantalla_update(void) {
	LCD_pos_xy(0, 0);
	LCD_write_string(pantalla[0]);
	LCD_pos_xy(0, 1);
	LCD_write_string(pantalla[1]);
}
