#define motorLeftForward 3
#define motorRightForward 9
#define motorLeftBackward 6
#define motorRightBackward 5
#define pingPin 7

int RBuiten;
int RBinnen;
int LBinnen;
int LBuiten;

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
  // put your main code here, to run repeatedly:
  currentDistance = getDistance();
//  Serial.println(currentDistance);
  bool RBuiten = digitalRead(A0);
  bool RBinnen = digitalRead(A1);
  bool LBinnen = digitalRead(A2);
  bool LBuiten = digitalRead(A3);
  Serial.print(RBuiten);
  Serial.print(RBinnen);
  Serial.print(LBinnen);
  Serial.print(LBuiten);

//  richting(RBuiten, RBinnen, LBinnen, LBuiten);

driveDirection(RBuiten, RBinnen, LBinnen, LBuiten);
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
    
    analogWrite(motorRightForward, powerRightDrive);
    analogWrite(motorRightBackward, 0);
  } else {
    powerRightDrive = rightMotorCalibration * (-1 * rightDrive / 100);
    analogWrite(motorRightForward, 0);
    analogWrite(motorRightBackward, powerRightDrive);
  }
}

bool driveDirection(int RBuiten,int RBinnen,int LBinnen,int LBuiten){ 
  if(forward(RBuiten, RBinnen, LBinnen, LBuiten)){
    //ga wel rechtdoor
    driveController(100, 100);
    Serial.println("FORWARD");
  }else{
    //ga niet rechtdoor
    if(right(RBuiten, RBinnen, LBinnen, LBuiten)){
      driveController(100,50);
      Serial.println("RIGHT");
    }else{
      if(left(RBuiten, RBinnen, LBinnen, LBuiten)){
        driveController(50,100);
        Serial.println("LEFT");
      }
    }
  }
  Serial.println("OK");
  return true;
}

bool forward(bool RBuiten,bool RBinnen,bool LBinnen,bool LBuiten){
  if(RBuiten == false & LBuiten == false && RBinnen == true && LBinnen == true){
    return true;
  }else{
    return false;
  }
}

bool right(bool RBuiten,bool RBinnen,bool LBinnen,bool LBuiten){
  if(RBinnen == false && LBinnen == true){
    return true;
  }else{
    return false;
  }
  if(RBuiten == true & LBuiten == true && RBinnen == false && LBinnen == false){
    return true;
  }else{
    return false;
  }
}

bool left(bool RBuiten,bool RBinnen,bool LBinnen,bool LBuiten){
  if(RBinnen == true && LBinnen == false){
    return true;
  }else{
    return false;
  }
  if(RBuiten == false & LBuiten == false && RBinnen == true && LBinnen == true){
    return true;
  }else{
    return false;
  }
}


