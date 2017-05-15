#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "pantalla.h"
#include "mef.h"
#include "teclado.h"

#ifdef __cplusplus
extern "C"
#endif

void MCU_init(void); /* Device initialization function declaration */

void main(void) {
	MCU_init();
	teclado_init();
	MEF_init();
	pantalla_init();
	for (;;) {
		pantalla_update();
	}
}
