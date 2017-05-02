#include "clock.h"

unsigned char HH=23;
unsigned char MM=59;
unsigned char SS=55;
const unsigned char escaler=10;
unsigned char calls=0;
//cada un segundo
void tick(void){
	if(calls++==escaler){
		SS++;
		if(SS==60){
			SS=0;
			MM++;
			if(MM==60){
				MM=0;
				HH++;
				if(HH==24){
					HH=0;
				}
			}
		}
		calls=0;
	}
}

void get_time_as_str(char str[]){
	str[0]=HH/10+'0';
	str[1]=HH%10+'0';
	str[2]=':';
	str[3]=MM/10+'0';
	str[4]=MM%10+'0';
	str[5]=':';
	str[6]=SS/10+'0';
	str[7]=SS%10+'0';
	str[8]='\0';
}




