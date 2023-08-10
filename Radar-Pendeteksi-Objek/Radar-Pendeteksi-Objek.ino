//Servo
#include<Servo.h>
const int motorSignalPin = 9;

//Library Sensor Ultrasonik
#include <NewPing.h>
int TrigPin = 11;
int EchoPin = 12;
NewPing sonar(TrigPin,EchoPin);

// starting loaction
const int startAngle = 90;

// rotation limits
//const int minimumAngle = 6;
//const int maximumAngle = 175;
const int minimumAngle = 0;
const int maximumAngle = 180;

// speed
const int degreesPerCycle = 1;

// Library class instance
Servo motor;

void setup(void) 
{
    motor.attach(motorSignalPin);
    Serial.begin(9600);
}

void loop(void)
{
    static int currentAngle = startAngle;
    static int motorRotateAmount = degreesPerCycle;

    // move motor
    motor.write(currentAngle);
    delay(10);
    // calculate the distance from the sensor, and write the valu with locqtion to serial
    SerialOutput(currentAngle, CalculateDistance());

    // update motor location
    currentAngle += motorRotateAmount;

    // if the motor has reached the limits, change direction
    if(currentAngle <= minimumAngle || currentAngle >= maximumAngle) 
    {
        motorRotateAmount = -motorRotateAmount;
    }
}

int CalculateDistance(void)
{
    float jarak = sonar.ping_cm(); //satuan nya dalam cm
    return int(jarak);
}

void SerialOutput(const int angle, const int jarak)
{
    // convert the angle and distance to a string and serial print
    Serial.println(String(angle) + "," + String(jarak));
}
