#define motorLeftForward 3
#define motorRightForward 9
#define motorLeftBackward 6
#define motorRightBackward 5
#define pingPin 7

void setup() {
  // put your setup code here, to run once:
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);

  pinMode(A0, INPUT); //meest rechter buiten baan
  pinMode(A1, INPUT); //rechter binnen baan
  pinMode(A2, INPUT); //links binnen baan
  pinMode(A3, INPUT); //meest linker buiten baan
  Serial.begin(9600);
}

long currentDistance = 0;
int leftMotorCalibration = 255;
int rightMotorCalibration = 255;

void loop() {
  bool RightOut = digitalRead(A0);
  bool RightIn = digitalRead(A1);
  bool LeftIn = digitalRead(A2);
  bool LeftOut = digitalRead(A3);
  bool value[4] = {RightOut, RightIn, LeftIn, LeftOut};
  currentDistance = getDistance();
  if(currentDistance > 5){
    int rechtdoor = richting(value[0], value[1], value[2], value[3]);
  }else{
    driveContoller(-100, -100);
    delayMicroseconds(50);
  }
  Serial.println(rechtdoor);
}

int getDistance () {
  long duration;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);


  return duration / 74 / 2;
}

void driveController(float leftDrive, float rightDrive) {
  int powerLeftDrive = 0;
  int powerRightDrive = 0;
  if(leftDrive == 0) {
    analogWrite(motorLeftForward, 0);
    analogWrite(motorLeftBackward, 0);
  } else if(leftDrive > 0) {
    powerLeftDrive = leftMotorCalibration * (leftDrive / 100);
    Serial.println(powerLeftDrive);
    analogWrite(motorLeftForward, powerLeftDrive);
    analogWrite(motorLeftBackward, 0);
  } else {
    powerLeftDrive = leftMotorCalibration * (-1 * leftDrive / 100);
    analogWrite(motorLeftForward, 0);
    analogWrite(motorLeftBackward, powerLeftDrive);
  }

  if(rightDrive == 0) {
    analogWrite(motorRightForward, 0);
    analogWrite(motorRightBackward, 0);
  } else if(rightDrive > 0) {
    
    powerRightDrive = rightMotorCalibration * (rightDrive / 100);
    Serial.println(powerRightDrive);
    analogWrite(motorRightForward, powerRightDrive);
    analogWrite(motorRightBackward, 0);
  } else {
    powerRightDrive = rightMotorCalibration * (-1 * rightDrive / 100);
    analogWrite(motorRightForward, 0);
    analogWrite(motorRightBackward, powerRightDrive);
  }
}



int richting(bool RO, bool RI, bool LI, bool LO) {
  
  // rechtdoor
  if(RO == false && RI == true && LI == true && LO == false){
    driveController(100,100);
  }
  
  // rechts 90 graden
  if(RO == true && RI == true && LI == true && LO == false){
    driveController(100, -100);
  }

  // links 90 graden
  if(RO == false && RI == true && LI == true && LO == true){
    driveController(-100, 100);
  }

  // flouwe bocht naar rechts
  if(RO == true && RI == true && LI == false && LO == false){
    driveContoller(-50, 100);
  }

  // flouwe bocht naar links
  if(RO == false && RI == false && LI == true && LO == true){
    driveContoller(100, -50);
  }

  // kruispunt
  if(RO == true && RI == true && LI == true && LO == true){
    driveContoller(100, 100);
  }  
}

