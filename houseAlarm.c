#include <stdio.h>
#include "ifttt.h"
#include <wiringPi.h>
#include <time.h>

#define GREEN_LED 1
#define RED_LED   0
#define BUTTON	  2
#define SENSOR	  4
#define SPEAKER   3

void alarm_OFF();
void alarm_ARMING();
void alarm_ARMED();
void alarm_TRIGGERED();
void alarm_SOUNDING();

void alarm_OFF(){
time_t delay = time(NULL);
double wait = delay+2;
printf("Alarm Off\n");
digitalWrite(SPEAKER, LOW);
digitalWrite(GREEN_LED,HIGH);
digitalWrite(RED_LED,LOW);
while(delay<wait){
delay = time(NULL);
}
while(1){
if(digitalRead(BUTTON) == LOW){
	printf("got a 0\n");
	break;
	}
}
alarm_ARMING();
}

void alarm_ARMING(){
time_t current = time(NULL);
double end = current+10;
printf("Alarm Arming\n");
while(current<end){
	if((current%2) == 0){
	digitalWrite(GREEN_LED,LOW);
	}
	else{
	digitalWrite(GREEN_LED,HIGH);
	}
current = time(NULL);
}
 alarm_ARMED();
}

void alarm_ARMED(){
int x;
printf("Alarm Armed\n");
 digitalWrite(GREEN_LED,LOW);
 digitalWrite(RED_LED,HIGH);
 while(1){
	if(digitalRead(BUTTON) == 0){
	x=0;
	break;}
	else if(digitalRead(SENSOR) == 1){
	x=1;
	break;
	}
  }
 if(x == 0){ alarm_OFF();}
 else if(x == 1){alarm_TRIGGERED();}
}

void alarm_TRIGGERED(){
int t;
time_t start = time(NULL);
double end = start+10;
printf("Alarm Triggered\n");
 while(start<end){
	if(digitalRead(BUTTON) == 0){t=1;
	printf("Got a zero\n");
	break;}
	if((start%2) == 0){
	digitalWrite(GREEN_LED, HIGH);
	digitalWrite(RED_LED, HIGH);
	}
	else if((start%2) ==1){
	digitalWrite(GREEN_LED, LOW);
	digitalWrite(RED_LED, LOW);
	}
	else{t=0;}
	start = time(NULL);
  }
 if(t == 0){alarm_SOUNDING();}
 else if(t == 1){alarm_OFF();}
}

void alarm_SOUNDING(){
time_t start = time(NULL);
double interval = start+2;
int next;
printf("Alarm Sounding\n");
ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/qUjk5_1YTEvBRpXGUmjd4", "Karan Patel", "Alarm Triggered", "214191506");
printf("Email Sent\n");
while(1){
	while(start<interval){
	 if(digitalRead(BUTTON)==0){break;}
	
	digitalWrite(SPEAKER,HIGH);
	digitalWrite(GREEN_LED,HIGH);
	digitalWrite(RED_LED,HIGH);
	start = time(NULL);
	}
	next= start+2;
	while(interval<next){
	 if(digitalRead(BUTTON)==0){break;}
	
	digitalWrite(SPEAKER,LOW);
        digitalWrite(GREEN_LED,LOW);
        digitalWrite(RED_LED,LOW);
        interval = time(NULL);
	}
	start = time(NULL);
	interval = start+2;
	if(digitalRead(BUTTON)==0){
	printf("button pressed\n");
	break;}
  }
		
alarm_OFF();
}

int main(int argc, char *argv[])
{
 
  wiringPiSetup () ;
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(SPEAKER, OUTPUT);
  pinMode(BUTTON, INPUT);
  pullUpDnControl(BUTTON, PUD_UP);
  pinMode(SENSOR, INPUT);
  pullUpDnControl(SENSOR, PUD_UP);
  alarm_OFF();
  /*NOTREACHED*/
  return 0 ;
}
