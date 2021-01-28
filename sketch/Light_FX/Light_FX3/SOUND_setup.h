#define ANALOG_THRESHOLD 600
int snd_average = 0;
int snd_current = 0;
int snd_max = 1;
int val_max = 1;
int val_avg = 1;
int val_last = 1;
int peak = 0;

void get_sound() {
  
  //Serial.print(1000);Serial.print(" ");
  
  int value = analogRead(A0);
  Serial.println(value);
  if(value>val_max) val_max = value;
  snd_current = map(value,0, val_max, 0,1023);
  
  //Serial.print(snd_current);Serial.print(" ");
  
  snd_average = (snd_average*9+snd_current)/10;
  if (snd_average > snd_max) snd_max = snd_average;
  //Serial.print(snd_average);Serial.print(" ");

}
