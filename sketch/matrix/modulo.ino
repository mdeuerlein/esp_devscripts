var pos = 0;
var band = 1;
var vals = '';

var peak = 7;

    if( peak % 2 == 0) {
      pos = (peak * 32) + (32 - 1) - band*5;
    } else {
      pos = (peak * 32) + band*5;
    }

    for (var i = 0; i < 5; i++) 
    {
      var led = 0;
      if( peak % 2 == 0) {
         led  = pos -i;
      } else {
        led = pos +i;
      }
      vals +=  led + ' | '; 
    }
alert(vals);
