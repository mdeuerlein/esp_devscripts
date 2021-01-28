void fx1_high ()  
{
    int gain = 3;
    int pos = random16(NUM_LEDS);
    if (pos > NUM_LEDS-gain) { pos = NUM_LEDS-gain;}
    for (int i = 0; i < gain; i++) {
        leds[ pos+i ] = CHSV( 210, 250, 245);
    }
   
    
}
void fx1_mid ()  
{
    int gain = 2;
    int pos = random16(NUM_LEDS);
    if (pos > NUM_LEDS-gain) { pos = NUM_LEDS-gain;}
    for (int i = 0; i < gain; i++) {
        leds[ pos+i ] = CHSV( 210, 250, 20);
    }
    
}
void fx1_low ()  
{
    
    int gain = 2;
    int pos = random16(NUM_LEDS);
    if (pos > NUM_LEDS-gain) { pos = NUM_LEDS-gain;}
    for (int i = 0; i < gain; i++) {
        leds[ pos+i ] = CHSV( 150+random16(10), 250, 100);
    }
}
void fx1_lowest () 
{
    int gain = 2;
    int pos = random16(NUM_LEDS);
    if (pos > NUM_LEDS-gain) { pos = NUM_LEDS-gain;}
    for (int i = 0; i < gain; i++) {
        leds[ pos+i ] = CHSV( 150+random16(10), 250, 20);
    }

}
void colors() {

} 
void fx1() 
{
    fadeToBlackBy( leds, NUM_LEDS, 5);
         if (snd_average > snd_max*0.8) fx1_high();
    else if (snd_average > snd_max*0.6) fx1_mid();
    else if (snd_average > snd_max*0.4) fx1_low();
    else if (snd_average > snd_max*0.2) fx1_lowest();
    FastLED.show(); 
}
