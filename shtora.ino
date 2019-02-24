#include <Stepper_28BYJ.h>
const int stepsPerRevolution = 4078;
Stepper_28BYJ myStepper_28BYJ(stepsPerRevolution, 8, 9, 10, 11);

boolean butt_flag = 0;
boolean butt;
#define kolvopovorotov 5000
#define h1 05
#define h2 20
#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS1307);
boolean h3;


void setup() {
  time.begin();
  time.settime(0, 51, 3, 20, 03, 19, 2);



  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);


}

void loop() {
  butt = digitalRead(4);

  h3 = time.gettime("H");
  



  while (h3<h2 && h3>=h1) {
    if (butt == 1 && butt_flag == 1 ) {
      butt_flag = 0;
      myStepper_28BYJ.step(5000);
      Serial.println(1);
    }


    if ( butt == 0 && butt_flag == 0 ) {
      butt_flag = 1;
      myStepper_28BYJ.step(-5000);
      Serial.println(2);
    }
  }
  while (h3>=h2 && h3<h1) {
    if (butt == 1 && butt_flag == 1) {
      butt_flag = 0;
      myStepper_28BYJ.step(-5000);
      Serial.println(3);
    }


    if ( butt == 0 && butt_flag == 0 ) {
      butt_flag = 1;
      myStepper_28BYJ.step(5000);
      Serial.println(4);
    }
  }

  if (h3 == h1) {
    myStepper_28BYJ.step(5000);
    Serial.println(5);
  }


  if (h3 == h2) {
    myStepper_28BYJ.step(-5000);
    Serial.println(6);
  }

}
