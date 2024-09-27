#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

double freq[] = {98.0, 146.0, 196,0};
int str[] = {2,3,4};
int prevPress[] = {0,0,0};
int currPress[] = {0,0,0};
int buzz = 8;
int count_ = 0;

double calc_freq(double dist, int str_ind){
	return freq[str_ind]*pow(2,dist/600.);
}

void setup(){
	Serial.begin(9600);
	Wire.begin();
	sensor.init();
	sensor.setTimeout(1600);
	sensor.startContinuous();
	pinMode(str[0],INPUT);
	pinMode(str[1],INPUT);
	pinMode(str[2],INPUT);
	pinMode(buzz, OUTPUT);
}

void loop(){
	int distance = sensor.readRangeContinuousMillimeters();
  if(distance >= 0 && distance <= 600){
    for(int i=0;i<3;i++) currPress[i] = digitalRead(str[i]);
    count_ = 0;
    for(int i=0;i<3;i++){
      if(currPress[i]) count_++;
      if(prevPress[i]!=currPress[i] && currPress[i]){
        Serial.print("String number playing:");
        Serial.print(i,DEC);
        Serial.print("\t");
        Serial.print("Distance from Sensor:");
          
        Serial.print(distance,DEC);
        Serial.print("\n");
        tone(buzz, calc_freq(distance, i));
        break;
      } 
    }
  }
	if(!count_) tone(buzz,0);
	for(int i=0;i<3;i++) prevPress[i] = currPress[i];
}
// 	for(int i=0;i<3;i++){
//   		for(int j=0;j<26;j++){
//   			tone(buzz,(calc_freq(j*24,i)));
        // Serial.print("String number playing:");
        // Serial.print(i,DEC);
        // Serial.print("\t");
        // Serial.print("Distance from Sensor:");
        
        // Serial.print(j*24,DEC);
        // Serial.print("\n");
//         delay(250);
//   		}
// 	}
// }


