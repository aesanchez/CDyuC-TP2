#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "lcd.h"
#include "clock.h"
#include "teclado.h"
#include "evento.h"


#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */
extern unsigned char stringOut[16];
void main(void) {	
	char strAux[9];
	char ult='~';
	MCU_init();    
	LCD_init(DISPLAY_8X5|_2_LINES,DISPLAY_ON|CURSOR_OFF);	
	//inicializo el puerto B para el teclado
	PTBDD=0x0F;
	PTBPE=0xF0;	
	
	//limpio posible basura
	LCD_pos_xy(0,0);
	LCD_write_string("                ");
	LCD_pos_xy(0,1);
	LCD_write_string("                ");
	for(;;) {
		LCD_pos_xy(4,0);
		get_time_as_str(strAux);
		LCD_write_string(strAux);
		
		LCD_pos_xy(0,1);
		LCD_write_string(stringOut);
	}
}

