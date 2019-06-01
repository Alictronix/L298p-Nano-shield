int E1 = 3;
int M1 = 12;
int E2 = 11;
int M2 = 13;

int value=255;
char command;
#define BUZZ         4

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
    delay (30);;
}
void setup ()
{
pinMode (M1, OUTPUT);
pinMode (M2, OUTPUT);
tone(BUZZ, 500, 500);
tone(BUZZ, 1000, 500);

Serial.begin(9600); //Set the baud rate to your Bluetooth module. 

}
void loop (){
if(Serial.available() > 0){
 command = Serial.read();
 Stop(); //initialize with motors stoped
 //Change pin mode only if new command is different from previous.
 Serial.println(command); 
switch(command){ 
case 'F':
 forward();
break;
case 'B':
 backward();
break; 
case 'L': 
 left(); 
break; 
case 'R':
 right();
break; }
}
}
