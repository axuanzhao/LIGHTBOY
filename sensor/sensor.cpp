#include <stdio.h>
#include <wiringPi.h>

int main(void)
{
	wiringPiSetup();
	int detect = 2;
	int LED = 3;
	
	pinMode(detect,INPUT);
	pinMode(LED,OUTPUT);
	
//	int i = digitalRead(detect);
	while(1)
	{
		
		if(digitalRead(detect) == 1){
			printf("Someone is here.\n");
			digitalWrite(LED, HIGH);
		}
		
		else if(digitalRead(detect) == 0){
			printf("No one is here.\n");
			digitalWrite(LED,LOW);
		}
		
		else{
			printf("Fault.\n");
		}
		delay(1000);
	}
	return 0;
}
