//Servo
#include <Servo.h>
Servo myservo_x;
Servo myservo_y;

int myservo_x_pin = 2;
int myservo_y_pin = 3;

//Joystick
int joy_x = A0;
int joy_y = A1;

// posisi 
int posisi_x;
int posisi_y;

void setup()
{
Serial.begin(9600);
myservo_x.attach(myservo_x_pin);
myservo_y.attach(myservo_y_pin);
}

void loop(){
int joy_y_read = analogRead(joy_y);
int joy_x_read = analogRead(joy_x);


// code posisi x
if (joy_x_read > 612){
    posisi_x = (posisi_x + 1)  ;
}
else if (joy_x_read < 400){
    posisi_x = (posisi_x - 1) ;
  }
else {
    posisi_x = posisi_x;
  }
if (posisi_x >= 180 ){
   posisi_x = 180;
} else if (posisi_x <= 0) {
  posisi_x = 0;
  }

// code posisi y
if (joy_y_read > 612){
    posisi_y = (posisi_y + 1)  ;
}
else if (joy_y_read < 400){
    posisi_y = (posisi_y - 1);
  }

if (posisi_y >= 180 ){
   posisi_y = 180;
} else if (posisi_y <= 0) {
  posisi_y = 0;
  }

  
myservo_y.write(posisi_y);
myservo_x.write(posisi_x);

Serial.print(posisi_x);
Serial.print("---");
Serial.println(posisi_y);
delay(20);
}
