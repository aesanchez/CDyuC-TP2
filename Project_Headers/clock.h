#ifndef CLOCK_H_
#define CLOCK_H_

void tick(void);
void get_time_as_str(char []);
void cambiar_hora(unsigned char,unsigned char,unsigned char);

#define IGNORE_HH 24
#define IGNORE_MM 60
#define IGNORE_SS 60

#endif 
