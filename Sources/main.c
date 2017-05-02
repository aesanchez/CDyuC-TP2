#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#include "pantalla_lcd.h"

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void);

void main(void) {	
	MCU_init();
	pantalla_init();
	//inicializo el puerto B para el teclado
	PTBDD=0x0F;
	PTBPE=0xF0;	
	
	for(;;) {
		pantalla_update();
	}
}

