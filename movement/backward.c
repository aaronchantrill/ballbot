#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <argp.h>
#include <stdbool.h>
#include <wiringPi.h>

const char *argp_program_version="backward 1.1";
const char *argp_program_bug_address="drask@dottywood.org";

static int pwm=1; // pwm pin BCM18

static char doc[]="Backward -- Move the robot backward";
static char args_doc[]="Args Doc";
static struct argp_option options[]={
    { "speed",       's',"SPEED",       0,"Speed"        },
    { "milliseconds",'m',"MICROSECONDS",0,"Microseconds" },
    { 0 }
};
struct arguments{
    int speed;
    int milliseconds;
};

static error_t parse_opt( int key, char *arg, struct argp_state *state ){
    struct arguments *arguments=state->input;
    switch(key){
        case 's':
            // arguments->speed=(int)strtol(arg,(char **)NULL,10);
            arguments->speed=atoi(arg);
            break;
        case 'm':
            // arguments->milliseconds=(int)strtol(arg,(char **)NULL,10);
            arguments->milliseconds=atoi(arg);
            break;
        default:
            // printf("key=%s\n",key);
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

// static struct argp argp={options,parse_opt,args_doc,doc};
static struct argp argp={options,parse_opt,0,doc};

int main(int argc,char **argv){
    printf("Backwards\n");
    struct arguments arguments;
    
    arguments.speed=1023;
    arguments.milliseconds=1000;

    argp_parse( &argp,argc,argv,0,0,&arguments );

    printf("SPEED=%d\nMILLISECONDS=%d\n",arguments.speed,arguments.milliseconds);

    wiringPiSetup();
    pinMode(pwm,PWM_OUTPUT);
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    pwmWrite(pwm,arguments.speed);

    if(arguments.milliseconds>0){
        delay(arguments.milliseconds);
        digitalWrite(pwm,0);
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
    }
    return 0;
}

