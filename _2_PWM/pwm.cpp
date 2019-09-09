#include <wiringPi.h>

int pwmPin = 1;
void servoTurn(int servoPin,float angle){
	angle = (angle/180)*200+50;
	pwmWrite(servoPin,angle);
}

void setup(){
	wiringPiSetup();
	pinMode(pwmPin,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetRange(2000);
	pwmSetClock(192);
}

void loop(){
	for(int i=0;i<=180;i++){
		servoTurn(pwmPin,i);
		delay(10);	
	}
	for(int i=180;i>=0;i--){
		servoTurn(pwmPin,i);
		delay(5);	
	}
	/*servoTurn(pwmPin,0);
	delay(200);
	servoTurn(pwmPin,180);
	delay(200);*/

}

int main(){
	setup();
	while(1)
		loop();	
}

