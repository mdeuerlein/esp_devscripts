#define ANALOG_THRESHOLD 800
int snd_avg_long = 0;
int snd_avg_short = 0;
int snd_current = 0;
int snd_max = 1;
int val_max = 1;
int peak = 0;

void get_sound() {
  
  //Serial.print(1000);Serial.print(" ");
  
  int value = analogRead(A0);
  if(value>val_max) val_max = value;
  snd_current = map(value,0, val_max, 0,1023);
  
  if(snd_current>snd_max) snd_max = snd_current;
  
  snd_avg_long = (snd_avg_long*10+snd_current)/11;
  snd_avg_short = (snd_avg_short+snd_current)/2;  
  


}

void check_peaks() {
  Serial.print(peak);Serial.println(" ");
  peak=0;
}
