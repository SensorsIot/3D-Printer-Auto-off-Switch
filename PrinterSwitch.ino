// Printer Switch

/* This sketch is for Attiny45/85. It switches a relays on and swithces it off 
 * after the TIMEOUT period unless the End switch is open (which means, the printer prints)
 *  
 */


#define OPEN     HIGH
#define CLOSED   LOW


// Pin1 RESET  #define DEBUG1 PB5 // Pin1, nur mit Fuse change
// Pin2
#define DEBUG2 PB3
// Pin3
#define ENDSWITCH    PB4
// Pin4 GND
// Pin5
#define RELAIS PB0
// Pin6
#define DEBUG6 PB1
// Pin7
#define DEBUG7 PB2
// Pin8 VCC



const unsigned long TIMEOUT = 900000; // 15min *60sec*1000(millis);

byte status = 1;  // Printer idle
unsigned long startTime;



void setup() {

  pinMode(ENDSWITCH, INPUT_PULLUP);
  pinMode(RELAIS, OUTPUT);

  digitalWrite(RELAIS, HIGH); // Switch Printer on
  startTime=millis();
}


void loop () {

  switch (status) {

    case 1:
      // Printer idle
      digitalWrite(RELAIS, HIGH);
      if (digitalRead(ENDSWITCH) == OPEN)  status = 2;  // Printer busy
      else {
        if ((millis() - startTime) > TIMEOUT) status = 3;  // Printer off
      }
      break;

    case 2:
      // Printer busy
      digitalWrite(RELAIS, HIGH);
      if (digitalRead(ENDSWITCH) == CLOSED) {
        startTime = millis(); // next cycle starts
        status = 1;  // Printer idle
      }
      break;


    case 3:
      // Printer off
      digitalWrite(RELAIS, LOW);
      while (1 == 1);
      break;

    default:
      //        status = 1;
      break;
  }
  delay(50);
}
























































