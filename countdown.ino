#include <Servo.h> 
#define start 180

Servo digitone;
Servo digittwo;
Servo digithour;
int postionone = start;
int postiontwo = start;
int postionhour = start;
unsigned long pasttime = 0;
unsigned long currenttime = millis();
int finished = 0;



void setup() {
 
 // attaching servos 
digitone.attach(11);
digittwo.attach(10);
digithour.attach(9);

//sets up intial countdown
digitone.write(postionone);
digittwo.write(postiontwo);
digithour.write(postionhour);

}

// increases digit one and hour servo angle, 9 postions
int posincrone(int x) {
  int y;
  y = x - 20;
  return y;
}
// increases digit two servo angle, 5 postions
int posincrtwo(int x) {
  int y;
  y = x - 36;
  return y;
}

void loop() {
  currenttime = millis();
  
    // checks to see if 1 min has gone by.
  if (currenttime - pasttime > 60000 || finished != 1) {
    pasttime = currenttime;
    
    // if the digitone is not in the zeros postion it will move it one postion down
      if (postionone >= 0) {
      digitone.write(postionone);
      postionone = posincrone(postionone);
      
    // if it is in the zero postion, the next servo, digittwo, will move one postion, and reset digitone to 180 degrees
      }else {
        postionone = start;
        digittwo.write(postiontwo);
        postionone = posincrtwo(postiontwo);
            if (postiontwo >= 0) {
            digithour.write(postionhour);
            postionhour = posincrone(postionhour);
        } else { 
            postiontwo = start;
        }
    
    }
  }
  // checks to see if countdown has finished
   if (postionhour == 0 || postiontwo == 0 || postionone ==0) {
     finished = 1;
}
}

