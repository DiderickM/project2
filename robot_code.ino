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
  // put your main code here, to run repeatedly:
  currentDistance = getDistance();
//  Serial.println(currentDistance);
  bool RBuiten = digitalRead(A0);
  bool RBinnen = digitalRead(A1);
  bool LBinnen = digitalRead(A2);
  bool LBuiten = digitalRead(A3);
  driveController(100, 100);
//  richting(RBuiten, RBinnen, LBinnen, LBuiten);


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

int richting(bool RBuiten, bool RBinnen, bool LBinnen, bool LBuiten) {
  //TODO:
  // - Stop als alle sensoren actief zijn
  // - Ga links als dat mag
  // - Ga daarna rechts
  
  /* KRUISPUNT */
  if(RBuiten == 1 && RBinnen == 1 && LBinnen == 1 && LBuiten == 1){
    analogWrite(motorLeftForward, 0);
    analogWrite(motorRightForward, 0);
    analogWrite(motorLeftBackward, 0);
    analogWrite(motorRightBackward, 0); 
  }

  //kijk of de buiten sensoren niet actief zijn
  bool buiten;
  if(RBuiten == 0 && LBuiten == 0){
    buiten = true;
  }else{
    buiten = false;
  }
  
  //kijk of de binnen sensorern actief zijn
  bool binnen;
  if(RBinnen == 1 && LBinnen == 1){
    binnen = true;
  }else{
    binnen = false;
  }

  if(RBinnen == 1 && LBinnen == 0) {
    analogWrite(motorLeftForward, 150);
    analogWrite(motorRightForward, 0);
    analogWrite(motorLeftBackward, 0);
    analogWrite(motorRightBackward, 0);  
  }

  if(RBinnen == 0 && LBinnen == 1) {
    analogWrite(motorLeftForward, 0);
    analogWrite(motorRightForward, 0);
    analogWrite(motorLeftBackward, 0);
    analogWrite(motorRightBackward, 255);  
  }

  //als de robor rechtdoor moet
  if(buiten == true && binnen == true){
    analogWrite(motorLeftForward, 150);
    analogWrite(motorRightForward, 0);
    analogWrite(motorLeftBackward, 0);
    analogWrite(motorRightBackward, 255);  
  }

  /*LINKS AF */
  if(LBuiten = 0){
    return false;
  }

  /*RECHTS AF */
  if(RBuiten = 0){
    return false;
  }
}

