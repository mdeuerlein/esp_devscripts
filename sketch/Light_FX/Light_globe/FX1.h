void fx1_high ()  
{
    leds[0] = CHSV( 160 , 255, bright); 
    leds[1] = CHSV( 160 , 255, 255);
   
    
}
void fx1_mid ()  
{
     leds[ 1 ] = CHSV( 10, 255, bright);
     leds[ 0 ] = CHSV( 160, 255, bright);
    
}
void fx1_low ()  
{
     leds[ 1 ] = CHSV( 10, 255, bright);
     leds[ 0 ] = CHSV( 10, 255, bright);
     
   

    
}
void colors() {

} 
void fx1() {
  fadeToBlackBy( leds, NUM_LEDS, 5);
  
    if (snd_current > snd_max*0.8) { 
      leds[ 0 ] += CRGB::Red;
      leds[ 1 ] += CRGB::Red;
    } else if (snd_current > snd_max*0.6) { 
      leds[ 0 ] += CRGB::Blue;
      leds[ 1 ] += CRGB::Blue;
    } else if (snd_current > snd_max*0.5) { 
      leds[ 0 ] += CRGB::Green;
      leds[ 1 ] += CRGB::Green;
    } 
  FastLED.show(); 
}
