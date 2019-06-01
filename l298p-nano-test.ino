int E1 = 3;
int M1 = 12;
int E2 = 11;
int M2 = 13;
int value;
void setup ()
{
pinMode (M1, OUTPUT);
pinMode (M2, OUTPUT);
}
void loop (){
for (value = 0; value <= 255; value += 5)
{
digitalWrite (M1, HIGH);
digitalWrite (M2, HIGH);
analogWrite (E1, value); // PWM speed control
analogWrite (E2, value); // PWM speed control
delay (30);
}
delay (1000);
for (value = 0; value <= 255; value += 5)
{
digitalWrite (M1, LOW);
digitalWrite (M2, LOW);
analogWrite (E1, value); // PWM speed control
analogWrite (E2, value); // PWM speed control
delay (30);
}
delay (1000);
}
