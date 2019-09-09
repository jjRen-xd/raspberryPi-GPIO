#include <wiringPi.h>
#include<iostream>
#include<string>

using namespace std;

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

#define HIGH_TIME 32
int DHT11_Pin = 1;
int tmp_Int,tmp_Dec,rh_Int,rh_Dec;

string getTime(){
	time_t timep;
	time (&timep);
	char tmp[32];
	strftime(tmp,sizeof(tmp),"%Y-%m-%d_%H:%M:%S",localtime(&timep));
	return tmp;
}

uint8 readDht11Data(void){
	uint32 databuf = 0;
	uint8 crc = 0;
	//Host sends start singal
	pinMode(DHT11_Pin,OUTPUT);
	digitalWrite(DHT11_Pin,HIGH);
	delayMicroseconds(4);
	digitalWrite(DHT11_Pin,LOW);
	delay(25);
	digitalWrite(DHT11_Pin,HIGH);
	delayMicroseconds(60);
	//Detection of slave response signal	
	pinMode(DHT11_Pin,INPUT);	
	pullUpDnControl(DHT11_Pin,PUD_UP);	//Pull-up resistance
	
	if(digitalRead(DHT11_Pin) == 0){		//Sensor ans
		while(!digitalRead(DHT11_Pin));	//Wait to high level
		delayMicroseconds(80);

		for(uint8 i = 0;i<32;i++){			//DATA:4*8
			while(digitalRead(DHT11_Pin));	//Wait to low level
			while(!digitalRead(DHT11_Pin));//Wait to high_level
			delayMicroseconds(HIGH_TIME);
		
			databuf *=2;
			if(digitalRead(DHT11_Pin)){
				databuf++;
			}		
		}
		
		for(uint8 i= 0;i<8;i++){
			while(digitalRead(DHT11_Pin));	//Wait to low level
			while(!digitalRead(DHT11_Pin));//Wait to high_level
			delayMicroseconds(HIGH_TIME);
		
			crc*=2;
			if(digitalRead(DHT11_Pin)){
				crc++;
			}
		}
		
		rh_Int = (databuf>>24)&0xff;
		rh_Dec = (databuf>>16)&0xff;
		tmp_Int = (databuf>>8)&0xff;
		tmp_Dec = databuf&0xff;
		//cout<<"crc:"<<(crc&0xff)<<"  ";
		if((rh_Int + rh_Dec + tmp_Int + tmp_Dec) == (crc&0xff))
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

void setup(){
	wiringPiSetup();
	pinMode(DHT11_Pin,OUTPUT);
	digitalWrite(DHT11_Pin,HIGH);
}

void loop(){
	delay(2000);
	if(readDht11Data()){
		cout<<"Successful!"<<endl;
		cout<<'['<<getTime()<<"]  ";
		cout<<"RH:"<<rh_Int<<"."<<rh_Dec<<"  ";
		cout<<"TMP:"<<tmp_Int<<"."<<tmp_Dec<<endl;
	}
	else{
		cout<<"Error!"<<endl;
	}
}

int main(){
	setup();
	while(1)
		loop();	
}


