// MeCon Code Sample with Adjustable Speed Control
// Adjust the constant "servoSpeed" below to change arm movement speed 
// Use With MeCon Windows Software for Robotic Arm Motion Control
// Go to WWW.MICROBOTLABS.COM for more info
    


#include <Servo.h>

//MeArm HAS 4 SERVOS
Servo xServo;  // create servo object, arm base servo - rotate arm motion
Servo yServo;  // create servo object, left side servo - forward backwards motion
Servo zServo;  // create servo object, right side servo - forward backwards motion
Servo clawServo;  // create servo object, end of arm srevo - open,close the claw hand

//servo positions values, expects 1-180 deg.
int xPos = 90;
int yPos = 90;
int zPos = 90;
int clawPos = 90;

// variables
char endOfPacketChar;

// constants
const char servoEOPC = 'x';// end of serial data packet character
const int servoSpeed = 10;// Adjustable delay in milliseconds between servo position updates

//*************** INIT AT STARTUP *******************************************************************

void setup() {        // the setup function runs once when you press reset or power the board

  // assign servo to pin numbers
  xServo.attach(11);  // attaches the servo on pin 11 to the servo object
  yServo.attach(10);  // attaches the servo on pin 10 to the servo object
  zServo.attach(9);  // attaches the servo on pin 9 to the servo object
  int pos;
  pos=zServo.read();
  zServo.write(pos);
  clawServo.attach(6);  // attaches the servo on pin 6 to the servo object

  // initialize serial port and set baud rate
  Serial.begin(9600);

    
  Serial.print("*** MeCon Speed Control Demo ***");   // Arduino Boot Message

  

}

// ******************************************************************************************************
// ********************************** MAIN PROGRAM LOOP START *******************************************
// ******************************************************************************************************

void loop() {

  //Get servo position values from serial port
  //serial in packet patern = xVal,yVal,zVal,clawVal + end of packet char 'x'
  if (Serial.available() ) {
    xPos = Serial.parseInt();
    yPos = Serial.parseInt();
    zPos = Serial.parseInt();
    clawPos = Serial.parseInt();
    endOfPacketChar = Serial.read();
  }
  
//call function to set servo positions based on recived serial data 
setServoPos(xServo,(180 - xPos),servoSpeed,servoEOPC);// (180 - xPOS) Example of how to Reverse rotation of servo motor
setServoPos(yServo,180-yPos,servoSpeed,servoEOPC);
setServoPos(zServo,180-zPos,servoSpeed,servoEOPC);
setServoPos(clawServo,180-clawPos,servoSpeed,servoEOPC);

 
}


//********************************************************************************************************
//******************************* CUSTOM FUNCTIONS *******************************************************

//move servo motors to new positions 
void setServoPos(Servo servoX,int targetPosition, int speedX, char servoEOPCX){
    if (servoEOPCX != servoEOPC){
       return;
    }
    if (servoX.read()==targetPosition){
       return;
    }
    if (servoX.read() < targetPosition){
      servoX.write(servoX.read()+1);
      delay(speedX);
      return;
    }

    if (servoX.read() > targetPosition){
      servoX.write(servoX.read()-1);
      delay(speedX);
      return;
    }
}
