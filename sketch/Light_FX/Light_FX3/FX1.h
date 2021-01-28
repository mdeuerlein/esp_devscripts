void fx1_high ()  
{
    
    int gain = 4;
    int pos = random8(NUM_LEDS);
    if (pos > NUM_LEDS-gain) { pos = NUM_LEDS-gain;}
    
        leds[ 42 ] = CHSV( 220, 255, 205);
        FastLED.show(); 
    delay(1);
        leds[ 43 ] = CHSV( 220, 255, 205);
        FastLED.show(); 
    delay(1);
        leds[ 44 ] = CHSV( 220, 255, 205);
        FastLED.show(); 
    delay(1);
        leds[ 45 ] = CHSV( 220, 255, 205);
   
    
}
void fx1_mid ()  
{
    
    int gain = 2;
    int pos = random8(NUM_LEDS);
    if (pos > NUM_LEDS-gain) { pos = NUM_LEDS-gain;}
    leds[ 30 ] = CHSV( 190, 255, 205);
    FastLED.show(); 
    delay(1);
    leds[ 31 ] = CHSV( 190, 255, 205);
    FastLED.show(); 
    delay(1);
    
}
void fx1_low ()  
{
    
    
    int gain = 2;
    int pos = random8(NUM_LEDS);
    if (pos > NUM_LEDS-gain) { pos = NUM_LEDS-gain;}
        leds[ 20 ] = CHSV( 170, 250, 200);
        FastLED.show(); 
    delay(1);
        leds[ 21 ] = CHSV( 170, 250, 205);
FastLED.show(); 
    delay(1);
}
void fx1_lowest () 
{
    
    int gain = 3;
    int pos = random16(NUM_LEDS);
    if (pos > NUM_LEDS-gain) { pos = NUM_LEDS-gain;}
    
        leds[ 10 ] = CHSV( 160, 250, 200);
        FastLED.show(); 
    delay(1);
        leds[ 11 ] = CHSV( 160, 250, 200);
        FastLED.show(); 
    delay(1);
        leds[ 12 ] = CHSV( 160, 250, 200);
    FastLED.show(); 
    delay(1);

}

void fx1() 
{
  Serial.println(snd_average);
    fadeToBlackBy( leds, NUM_LEDS, 5);
         if (snd_average > snd_max*0.7) fx1_high();
    else if (snd_average > snd_max*0.55) fx1_mid();
    else if (snd_average > snd_max*0.4) fx1_low();
    else fx1_lowest();
    FastLED.show(); 
    delay(5);
    
}
