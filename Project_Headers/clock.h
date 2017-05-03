#ifndef CLOCK_H_
#define CLOCK_H_

#define IGNORE_HH 24
#define IGNORE_MM 60
#define IGNORE_SS 60

void tick(void);
void get_time_as_str(char []);
void cambiar_hora(char,char,char);

#endif /* CLOCK_H_ */
