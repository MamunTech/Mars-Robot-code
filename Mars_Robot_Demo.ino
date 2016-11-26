//#include "TimerOne.h" //for creating 
int mp1=26,mm1=27,mp2=22,mm2=23,mp3=28,mm3=29,mp4=24,mm4=25,mp5=32,mm5=33,mp6=30,mm6=31;//motor
int ut=9,ue=10;//Ultrasonic sensor ut=tigger and ue=echo
int sm=8;//Servo motor
int sw1=21; // 2 external interrupt pin mean 21 pin in arduino mega                                 //,sw2=27; //Switch
int sp1=1,sp0=0; //speed of the wheel
 long duration, distance;
 //char a=" ";

 int motor=6;
 
 #include <Servo.h>

Servo myservo;
Servo mamun;

int pos = 0;
int pos1=0; 

void setup() {
  
 myservo.attach(8);
 mamun.attach(7);

   
pinMode(mp1,OUTPUT);
pinMode(mm1,OUTPUT);
pinMode(mp2,OUTPUT);
pinMode(mm2,OUTPUT);
pinMode(mp3,OUTPUT);
pinMode(mm3,OUTPUT);
pinMode(mp4,OUTPUT);
pinMode(mm4,OUTPUT);
pinMode(mp5,OUTPUT);
pinMode(mm5,OUTPUT);
pinMode(mp6,OUTPUT);
pinMode(mm6,OUTPUT);

pinMode(motor,OUTPUT);

myservo.write(pos);         //positioning the zero position fo survo position
mamun.write(pos1);          //positioning the zero position fo survo position

pinMode(sw1,INPUT);

  pinMode(ut, OUTPUT);// ultrasonic sensor triger
  pinMode(ue, INPUT); // ultrasonic senosr echo
Serial.begin(9600);
//attachInterrupt(sw1,bluetooth,FALLING);

//Timer1.initialize(1000000); // monitor the distance in every 1 second
//Timer1.attachInterrupt(ultrasonic);

}
void forward()                                                       // car move forward
{
  digitalWrite(mp1,sp1);
  digitalWrite(mp2,sp1);
  digitalWrite(mp3,sp1);
  digitalWrite(mp4,sp1);
  digitalWrite(mp5,sp1);
  digitalWrite(mp6,sp1);
  
  digitalWrite(mm1,sp0);
  digitalWrite(mm2,sp0);
  digitalWrite(mm3,sp0);
  digitalWrite(mm4,sp0);
  digitalWrite(mm5,sp0);
  digitalWrite(mm6,sp0);
  }
  void backward()                                                      //car move backward
  {
  digitalWrite(mp1,sp0);
  digitalWrite(mp2,sp0);
  digitalWrite(mp3,sp0);
  digitalWrite(mp4,sp0);
  digitalWrite(mp5,sp0);
  digitalWrite(mp6,sp0);
  
  digitalWrite(mm1,sp1);
  digitalWrite(mm2,sp1);
  digitalWrite(mm3,sp1);
  digitalWrite(mm4,sp1);
  digitalWrite(mm5,sp1);
  digitalWrite(mm6,sp1);
    }
void leftside()                                                         //car move left side
{
    digitalWrite(mp1,sp0);
    digitalWrite(mm1,sp1);
    digitalWrite(mp3,sp0);
    digitalWrite(mm3,sp1);
    digitalWrite(mp5,sp0);
    digitalWrite(mm5,sp1);

    
     digitalWrite(mp2,sp0);
     digitalWrite(mm2,sp0);
     digitalWrite(mp4,sp0);
     digitalWrite(mm4,sp0);
     digitalWrite(mp6,sp0);
     digitalWrite(mm6,sp0);

  }
  void rightside()                                                      //car move right side
  {
    digitalWrite(mp1,sp1);
    digitalWrite(mm1,sp0);
    digitalWrite(mp3,sp1);
    digitalWrite(mm3,sp0);
    digitalWrite(mp5,sp1);
    digitalWrite(mm5,sp0);

    
     digitalWrite(mp2,sp0);
     digitalWrite(mm2,sp0);
     digitalWrite(mp4,sp0);
     digitalWrite(mm4,sp0);
     digitalWrite(mp6,sp0);
     digitalWrite(mm6,sp0);
    
    }
void Stop()                                                        // car stop it's movement 
    {
   digitalWrite(mp1,sp0);
  digitalWrite(mp2,sp0);
  digitalWrite(mp3,sp0);
  digitalWrite(mp4,sp0);
  digitalWrite(mp5,sp0);
  digitalWrite(mp6,sp0);
   digitalWrite(mm1,sp0);
  digitalWrite(mm2,sp0);
  digitalWrite(mm3,sp0);
  digitalWrite(mm4,sp0);
  digitalWrite(mm5,sp0);
  digitalWrite(mm6,sp0);
      }
      
void ServoMotorOn()                                              // Survo motor start moving
{
  while(pos1<=90){
  for ( pos1 = 0; pos1 <= 90; pos1 += 1)                    // goes from 0 degrees to 180 degrees
  { 
    mamun.write(pos1);                                           // tell servo to go to position in variable 'pos1'
    delay(15);                               
  }
}
}

void ServoMotorOff()                                          //servo motor move to the initial position 
 {while(pos1>=0){
   for ( pos1 = 90; pos1 >= 0; pos1 -= 1)                  // goes from 180 degrees to 0 degrees
   { 
    mamun.write(pos1);                                           // tell servo to go to position in variable 'pos1'
    delay(15);                                
  } 
 }
}
    
void MotorOn()                                                  // motor start running
{
      analogWrite(motor,200);
      delay(200);
}
void MotorOff()                                                    // motor stop running
{
    analogWrite(motor,0);
      delay(20);
}

 long ultrasonic(){
  digitalWrite(ut, LOW);                                        // Added this line  
  digitalWrite(ut, HIGH);
  delayMicroseconds(10);                                          // Added this line
  digitalWrite(ut, LOW);
  duration = pulseIn(ue, HIGH);
  distance = (duration/2) / 29.1;

// Serial.println(distance);//in cm(centemeter)
    
  return distance;
  }
  
void loop() {
Stop();

while(digitalRead(21)==HIGH)                                            //manual control
{
  //Serial.println("High"); 
    // Serial.println(a);
  while(Serial.available()){
//  a=Serial.read();
 Serial.println("High"); 
    // Serial.println(a);
     
switch(Serial.read()){
case 'U':
forward();                                                      // function for going upward 
break;
case 'D':
backward();                                                    //function for going downward 
break;
case 'L':
leftside();                                                   //function for going left 
break;
case 'R':
rightside();                                                //function for going right
break;
case 'S':
Stop();                                                    //function for stop the car
break;
case 'A':
ServoMotorOn();                                            // function for survo motor move
break;
case 'B': 
ServoMotorOff();                                           //function for survo motor moves to the initial positon 
break;
case 'C':
MotorOn();                                                 // function for motor start running
break;
case 'E':
MotorOff();                                                //function for motor stop running
break;
}
}
}
// a=" ";

 
while(digitalRead(21)==LOW)  //auto control
{
  Serial.println("LOW");
long x=ultrasonic();
  Serial.println(x);

if(x>30){
  Serial.println("Grater 30");
   forward();
  }
  
 if(x<30) {
  Serial.println("Less 30");
  Stop();
   for (pos = 0; pos <= 180; pos += 1) { 
    myservo.write(pos);
   
    leftside();
    // in steps of 1 degree
   }
    
      
    for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);             
    delay(15); }   
   
}
}}
