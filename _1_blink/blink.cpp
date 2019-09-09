#include <wiringPi.h>

void setup(){
	wiringPiSetup();
	pinMode(7,OUTPUT);
}

void loop(){
	while(1){
		digitalWrite(7,HIGH);
		delay(500);
		digitalWrite(7,LOW);
		delay(500);	
	}

}

int main(){
	setup();
	loop();	
}
