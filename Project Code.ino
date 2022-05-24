#include <AFMotor.h>
#define Max_Speed 255
#define Min_Speed 159
#define Lleft A5
#define Rright A4

//initial motors pin
AF_DCMotor motor1(3);
AF_DCMotor motor2(4);
AF_DCMotor motor3(1);
AF_DCMotor motor4(2);



char command;

void setup()
{
  pinMode(Lleft, INPUT);
  pinMode(Rright, INPUT);
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.

}


void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.
    Serial.println(command);
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'W':
        Square();
        break;
      case 'U':
        Circle();
        break;
      case 'V':
        Star ();
        break;
      case 'X':
        LineFollower();
        break;
    }
  }

}

void forward()
{
  motor1.setSpeed(Max_Speed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Max_Speed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Max_Speed);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(Max_Speed);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(Max_Speed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Max_Speed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(Max_Speed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Max_Speed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void left()
{
  motor1.setSpeed(Max_Speed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Max_Speed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(Max_Speed); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(Max_Speed); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void right()
{
  motor1.setSpeed(Max_Speed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Max_Speed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Max_Speed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Max_Speed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void Stop()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0); //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}


void Square()
{


  for (int i = 0 ; i < 4 ; i++)
  {
    forward();
    Serial.println ("up");
    delay (2000);

    right();
    Serial.println ("Right");
    delay(656);
    if (Serial.available() > 0) {
    int Lcommand = Serial.read();
    if (Lcommand != 0) {
      Stop();
      break;
    }
  }
  }
  Stop();
}

void Circle()
{


  for (int i = 0 ; i < 75 ; i++)
  {
    forward();
    Serial.println ("up");
    delay (75);
    right();
    Serial.println ("Right");
    delay(75);
    if (Serial.available() > 0) {
    int Lcommand = Serial.read();
    if (Lcommand == 'u') {
      Stop();
      break;
    }
  }
  }
  Stop();
}


void Star()
{
  for (int i = 0 ; i < 5 ; i++)
  {

   forward();
    delay (1000);
    right();
    delay(970);
    forward();
    delay (1000);
    left();
    delay(600);
  }
  Stop();

}

void LineFollower()
{
  while (1) {
    if (Serial.available() > 0) {
      int Lcommand = Serial.read();
      if (Lcommand == 'x') {
        Stop();
        break;
      }
    }


    int rLeft = analogRead(Lleft);
    int rRight = analogRead(Rright);
    Serial.print("Right");
    Serial.println(rRight);

    Serial.print("left");
    Serial.println(rLeft);


    if (analogRead(Lleft) < 700 && analogRead(Rright) < 700) {

      //forward();
      motor1.setSpeed(Min_Speed); //Define maximum velocity
      motor1.run(FORWARD); //rotate the motor clockwise
      motor2.setSpeed(Min_Speed); //Define maximum velocity
      motor2.run(FORWARD); //rotate the motor clockwise
      motor3.setSpeed(Max_Speed);//Define maximum velocity
      motor3.run(FORWARD); //rotate the motor clockwise
      motor4.setSpeed(Max_Speed);//Define maximum velocity
      motor4.run(FORWARD); //rotate the motor clockwise

      Serial.print("Right");
      Serial.println(rRight);

      Serial.print("left");
      Serial.println(rLeft);

    }
    //line detected by left sensor
    else if (analogRead(Lleft) > 700 && analogRead(Rright) < 700) {

      //left();
      motor1.setSpeed(Min_Speed); //Define maximum velocity
      motor1.run(BACKWARD); //rotate the motor anti-clockwise
      motor2.setSpeed(Min_Speed); //Define maximum velocity
      motor2.run(BACKWARD); //rotate the motor anti-clockwise
      motor3.setSpeed(Min_Speed); //Define maximum velocity
      motor3.run(FORWARD);  //rotate the motor clockwise
      motor4.setSpeed(Min_Speed); //Define maximum velocity
      motor4.run(FORWARD);  //rotate the motor clockwise
      Serial.print("Right");
      Serial.println(Rright);

      Serial.print("left");
      Serial.println(Lleft);
    }
    //line detected by right sensor
    else if (analogRead(Lleft) < 700 && analogRead(Rright) > 700) {

      //right();
      motor1.setSpeed(Min_Speed); //Define maximum velocity
      motor1.run(FORWARD); //rotate the motor clockwise
      motor2.setSpeed(Min_Speed); //Define maximum velocity
      motor2.run(FORWARD); //rotate the motor clockwise
      motor3.setSpeed(Min_Speed); //Define maximum velocity
      motor3.run(BACKWARD); //rotate the motor anti-clockwise
      motor4.setSpeed(Min_Speed); //Define maximum velocity
      motor4.run(BACKWARD); //rotate the motor anti-clockwise
      Serial.print("Right");
      Serial.println(Rright);

      Serial.print("left");
      Serial.println(Lleft);
    }
    //line detected by none
    else if (analogRead(Lleft) > 700 && analogRead(Rright) > 700) {
      Serial.print("Right");
      Serial.println(Rright);

      Serial.print("left");
      Serial.println(Lleft);
      Stop();
    }
  delay(15); //  كل ما يزيد العربية تبقي اسرع سرعة العربية في اللتراكنج
    Stop();
     
  }

}
