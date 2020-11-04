#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

const char *argp_program_version="right 1.0";
const char *argp_program_bug_address="drask@dottywood.org";

static char doc[]="Right -- Turn the robot right";

static int pwm=1; // BCM18

static struct argp_option options[]={
    {"speed",'s',"SPEED",0,"Speed"},
    {"milliseconds",'m',"MILLISECONDS",0,"Milliseconds"},
    {0}
};

struct arguments{
    int speed;
    int milliseconds;
};

static error_t parse_opt(int key,char *arg,struct argp_state *state){
    struct arguments *arguments=state->input;
    switch (key){
        case 's':
            arguments->speed=atoi(arg);
            break;
        case 'm':
            arguments->milliseconds=atoi(arg);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp ={ options, parse_opt, 0, doc };

int main(int argc,char **argv){
    printf("Right\n");
    struct arguments arguments;
    
    arguments.speed=1023;
    arguments.milliseconds=1000;
    
    argp_parse( &argp,argc,argv,0,0,&arguments );
    printf("SPEED=%d\nMILLISECONDS=%d\n",arguments.speed,arguments.milliseconds);
    
	wiringPiSetup();
    pinMode(pwm,PWM_OUTPUT);
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(4,OUTPUT);
	pinMode(5,OUTPUT);
	digitalWrite(2,LOW);
	digitalWrite(3,HIGH);
	digitalWrite(4,HIGH);
	digitalWrite(5,LOW);
    pwmWrite( pwm,arguments.speed );
    
    delay( arguments.milliseconds );

	digitalWrite(2,LOW);
	digitalWrite(3,LOW);
	digitalWrite(4,LOW);
	digitalWrite(5,LOW);
    pwmWrite(pwm,0);
    
	return 0;
}

