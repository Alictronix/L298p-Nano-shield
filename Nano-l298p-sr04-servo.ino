#include <Servo.h>
 
// setup servo
#define SERVORIGHT   50
#define SERVOCENTRE  100
#define SERVOLEFT    150
#define SERVOPIN     2

#define TRIGPIN      6
#define ECHOPIN      7
#define BUZZ         4
Servo servo;
int E1 = 3;
int M1 = 12;
int E2 = 11;
int M2 = 13;

int value=255;
char command;

void Stop()
{
    analogWrite (E1, 0); 
    analogWrite (E2, 0); 
    delay (30);
}
 
void forward()
{
    digitalWrite (M1, HIGH);
    digitalWrite (M2, HIGH);
    analogWrite (E1, value); 
    analogWrite (E2, value);
    delay (30);
}
 
void backward()
{
    digitalWrite (M1, LOW);
    digitalWrite (M2, LOW);
    analogWrite (E1, value); 
    analogWrite (E2, value); 
    delay (30);
}
 
void left()
{
    digitalWrite (M1, LOW);
    digitalWrite (M2, HIGH);
    analogWrite (E1, value); 
    analogWrite (E2, value); 
    delay (30);
}
 
void right()
{
    digitalWrite (M1, HIGH);
    digitalWrite (M2, LOW);
    analogWrite (E1, value); 
    analogWrite (E2, value); 
    delay (30);
}

int stopCount = 0;

int ping()
{
    // pause for 50ms between scans
    delay(50);
 
    // send ping
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
 
    // read echo
    long duration = pulseIn(ECHOPIN, HIGH);
 
    // convert distance to cm
    unsigned int centimetres = int(duration / 2 / 29.1);
 
    return centimetres;
}
 
char scan()
{
    // ping times in microseconds
    unsigned int left_scan, centre_scan, right_scan;
    char choice;
 
    // scan left
    servo.write(SERVOLEFT);
    delay(300);
    left_scan = ping();
 
    // scan right
    servo.write(SERVORIGHT);
    delay(600);
    right_scan = ping();
 
    // scan straight ahead
    servo.write(SERVOCENTRE);
    delay(300);
    centre_scan = ping();
 
    if (left_scan>right_scan && left_scan>centre_scan)
    {
        choice = 'l';
    }
    else if (right_scan>left_scan && right_scan>centre_scan)
    {
        choice = 'r';
    }
    else {
      choice = 'c';
    }
 
    return choice;
}
 
void setup (){
tone(BUZZ, 500, 500);
tone(BUZZ, 1000, 500);
pinMode (M1, OUTPUT);
pinMode (M2, OUTPUT);

Serial.begin(9600); //Set the baud rate to your Bluetooth module. 
servo.attach(SERVOPIN);
// set the trig pin to output (send sound waves)
pinMode(TRIGPIN, OUTPUT);
 
// set the echo pin to input (receive sound waves)
pinMode(ECHOPIN, INPUT);
}
void loop (){
// get distance from obstacle straight ahead
unsigned int distance = ping();
if (distance < 30 && distance > 0)
    {
        if (distance < 10)
        {
            // turn around
            backward();
            delay(300);
            left();
            delay(700);
        }
        else
        {
            // stop both motors
            Stop();
            
            // scan for obstacles
            char turn_direction = scan();
 
            // turn left/right or ignore and go straight
            if (turn_direction == 'l')
            {
                left();
                delay(500);
            }
            else if (turn_direction == 'r')
            {
                right();
                delay(500);
            }
            else if (turn_direction == 'c')
            {
              stopCount++;
              if(stopCount > 3){
                stopCount = 0;
                Serial.println("Turn back...");
                right();
                delay(700);
              }
              
            }
        }
    }
    else
    {
        // no obstacle, keep going forward
       forward();
    }
}
