#include <Wire.h>
#include <VL53L0X.h>
#include <Tone.h>

VL53L0X sensor
Tone tone1;

double freq[] = {98.0, 146.0, 196,0};
int str[] = {2,3,4};
int prevPress{0,0,0};
int currPress{0,0,0};
int buzz = 8;

void setup(){
	Serial.begin(9600);
	Wire.begin();
	tone1.begin(buzz);
	sensor.init();
	sensor.setTimeout()
	sensor.startContinuous()
	pinMode(str1,INPUT);
	pinMode(str2,INPUT);
	pinMode(str3,INPUT);
	pinMode(buzz, OUTPUT);
}

void loop(){
	int distance = sensor.readRangeContinuousMillimeters();
	for(int i=0;i<3;i++) currPress[i] = digitalRead(str[i]);
	for(int i=0;i<3;i++){
		if(prevPress[i]==currPress[i] && currPress[i]){
			tone1.stop();
			tone1.play((int) calc_freq(distance, i));
			break;
		} 
	}
	for(int i=0;i<3;i++) prevPress[i] = currPress[i];
}

double calc_freq(double dist, int str_ind){
	return freq[str_ind]*pow(2,dist/60.);
}
