#include <wiringPi.h>
int main(void)
{
	wiringPiSetup();
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(4,OUTPUT);
	pinMode(5,OUTPUT);
	digitalWrite(2,LOW);
	digitalWrite(3,LOW);
	digitalWrite(4,LOW);
	digitalWrite(5,HIGH);
	return 0;
}

