#include <Servo.h>

#define IN1  8   //K1、K2 motor direction
#define IN2  9     //K1、K2 motor direction
#define IN3  10    //K3、K4 motor direction
#define IN4  12   //K3、K4 motor direction
#define ENA  5    // Needs to be a PWM pin to be able to control motor speed ENA
#define ENB  6    // Needs to be a PWM pin to be able to control motor speed ENB

#define SERVO     11  //servo connect to D11
#define Echo    A3 // Ultrasonic Echo pin connect to A2
#define Trig    A2  // Ultrasonic Trig pin connect to A3

Servo myservo;    // create servo object to control a servo
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

int pos = 0;
void setup() {
 
  /*servo*/
  myservo.attach(SERVO);
  myservo.write(90);
  /*init HC-SR04*/
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trig, LOW);
 
  /******L298N******/
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);
  Serial.begin(9600);
  Serial.println("welcome to use SpreadRo your Lawn friend...");
  Serial.println("send <servo/>: test servo");
  Serial.println("send <distance/>: test HC-SR04");
  Serial.println("send <go/>: test robot go ahead");
  Serial.println("send <back/>: test robot go back");
  Serial.println("send <stop/>: test robot stop");
  Serial.println("--------------------------------------------------->>");
}


void loop() {
    myservo.write(90);  //setservo position according to scaled value
    delay(100);
    Distance_test();
    middleDistance = Distance_test();

    if(middleDistance <= 20) {    
      go_stop();
      delay(100);                        
      myservo.write(10);          
      delay(500); 

      rightDistance = Distance_test();
     
      delay(500);
      myservo.write(180);              
      delay(500);
      leftDistance = Distance_test();
     
      delay(500);
      myservo.write(90);              
      delay(1000);
      go_back();
      
      if(rightDistance > leftDistance) {
        go_right();
        delay(360);
      }
      else if(rightDistance < leftDistance) {
        go_left();
        delay(360);
      }
      else if ((rightDistance <= 10) && (leftDistance <= 10)) {
        go_back();
        delay(180);
      }
      else {
        go_ahead();
      }
      
    }  
    else {
        go_ahead();
    }
    
}


int Distance_test() {
  digitalWrite(Trig, LOW);  
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);  
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance * 0.01657;   //distance in centimeters   
  return (int)Fdistance;
}  

/*robot go ahead*/
void go_ahead()
{
  //set motor spped
  analogWrite(ENA,255);
  analogWrite(ENB,255);
  //motor go ahead
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
/*robot go back*/
void go_back()
{
  //set motor spped
  analogWrite(ENA,255);
  analogWrite(ENB,255);
  //motor go back
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
}
void go_left() {
  // write up turn left function
  //set motor spped
  analogWrite(ENA,255);
  analogWrite(ENB,255);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(300);
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   delay(300);
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   delay(300);
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   delay(300);
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   delay(300);
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void go_right() {
  // write up turn right function
  //set motor spped
  analogWrite(ENA,255);
  analogWrite(ENB,255);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(300);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
   delay(300);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
   delay(300);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
   delay(300);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
   delay(300);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
/*robot stop*/
void go_stop()
{
  //change the speed to 0 to stop the motor
  analogWrite(ENA,0);
  analogWrite(ENB,0);
}