/*
 * lcd.h
 *
 *  Created on: 30/07/2013
 *      Author: pc2
 */

#ifndef LCD_H_
#define LCD_H_


// The following defines set the default pins for the LCD display
#ifndef LCD_ENABLE			 // if lcd_enable is not defined

#define LCD_ENABLE      PTCD_PTCD3	 // LCD enable pin on PTC3
#define LCD_ENABLE_DIR  PTCDD_PTCDD3	 // LCD enable pin direction

#define LCD_RS		    PTCD_PTCD2	 // LCD r/s pin on PTB2
#define LCD_RS_DIR	    PTCDD_PTCDD2	 // LCD r/s pin direction

#define LCD_D4          PTAD_PTAD0    // LCD data D4 pin
#define LCD_D4_DIR      PTADD_PTADD0  // LCD data D4 pin direction

#define LCD_D5          PTAD_PTAD1    // LCD data D5 pin
#define LCD_D5_DIR      PTADD_PTADD1  // LCD data D5 pin direction

#define LCD_D6          PTAD_PTAD2    // LCD data D6 pin
#define LCD_D6_DIR      PTADD_PTADD2  // LCD data D6 pin direction

#define LCD_D7          PTAD_PTAD3    // LCD data D7 pin
#define LCD_D7_DIR      PTADD_PTADD3  // LCD data D7 pin direction 

#endif

#define LCD_SEC_LINE    0x40    // Address of the second line of the LCD

// LCD configuration constants
#define CURSOR_ON       2
#define CURSOR_OFF      0
#define CURSOR_BLINK    1
#define CURSOR_NOBLINK  0
#define DISPLAY_ON      4
#define DISPLAY_OFF     0
#define DISPLAY_8X5     0
#define DISPLAY_10X5    4
#define _2_LINES        8
#define _1_LINE         0


//**************************************************************************
//* Prototypes
//**************************************************************************
void LCD_delay_ms (unsigned char time);
void LCD_send_nibble(char data);
void LCD_send_byte(char address, char data);
void LCD_init(char mode1, char mode2);
void LCD_pos_xy(char x, char y);
void LCD_write_char(char c);
void LCD_write_string (char *c);
void LCD_display_on(void);
void LCD_display_off(void);
void LCD_cursor_on(void);
void LCD_cursor_off(void);
void LCD_cursor_blink_on(void);
void LCD_cursor_blink_off(void);

#define BUS_CLOCK 8000

#endif /* LCD_H_ */
