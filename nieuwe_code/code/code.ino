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
int leftMotorCalibration = 250;
int rightMotorCalibration = 255;

void loop() {
  //value is een array waar de uiteindelijke beslissing in komt te staan
  bool value[5];

  //Array waar de waardes van de sensoren in komen
  bool RightOutArray[5];
  bool RightInArray[5];
  bool LeftInArray[5];
  bool LeftOutArray[5];

  //waarde van de afstand meter
  int lenght[5];

  //vul de array's
  for(int i = 0; i < 5; i++){
    RightOutArray[i] = digitalRead(A0);
    RightInArray[i] = digitalRead(A1);
    LeftInArray[i] = digitalRead(A2);
    LeftOutArray[i] = digitalRead(A3);
    
  }
  for(int i = 0; i < 5; i++) {
    lenght[i] = getDistance();
    Serial.println(lenght[i]);
    delay(10);
  }

  //waardes waar de totaal aantal waardes in staan
  float RightOutTotal;
  float RightInTotal;
  float LeftInTotal;
  float LeftOutTotal;
  float lenghtTotal;

  //maak het totaal
  for(int i = 0; i < 5; i++){
    RightOutTotal += RightOutArray[i];
    RightInTotal += RightInArray[i];
    LeftInTotal += LeftInArray[i];
    LeftOutTotal += LeftOutArray[i];
    lenghtTotal += lenght[i];
    
  }

  RightOutTotal = RightOutTotal / 5;
  RightInTotal = RightInTotal / 5;
  LeftInTotal = LeftInTotal / 5;
  LeftOutTotal = LeftOutTotal / 5;
  lenghtTotal = lenghtTotal / 5;
  //bereken de waardes die kunenn worden gebruikt in de if-statements
  if(RightOutTotal > 0.8){
    value[0] = true;
  }else{
    value[0] = false;
  }

  if(RightInTotal > 0.8){
    value[1] = true;
  }else{
    value[1] = false;
  }

  if(LeftInTotal > 0.8){
    value[2] = true;
  }else{
    value[2] = false;
  }

  if(LeftOutTotal > 0.8){
    value[3] = true;
  }else{
    value[3] = false;
  }
  
//  if(lenghtTotal > 5){
    int rechtdoor = richting(value[0], value[1], value[2], value[3]);

//  }else{
//    driveController(0, 0);
//    delayMicroseconds(50);
//  }
//  
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

void driveController(float rightDrive, float leftDrive) {
  int powerLeftDrive = 0;
  int powerRightDrive = 0;
  if(leftDrive == 0) {
    analogWrite(motorLeftForward, 0);
    analogWrite(motorLeftBackward, 0);
  } else if(leftDrive > 0) {
    powerLeftDrive = leftMotorCalibration * (leftDrive / 100);
//    Serial.println(powerLeftDrive)/;
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
//    Serial.println(powerRightDrive);/
    analogWrite(motorRightForward, powerRightDrive);
    analogWrite(motorRightBackward, 0);
  } else {
    powerRightDrive = rightMotorCalibration * (-1 * rightDrive / 100);
    analogWrite(motorRightForward, 0);
    analogWrite(motorRightBackward, powerRightDrive);
  }
}



int richting(bool RO, bool RI, bool LI, bool LO) {

  Serial.print("RO: ");
  Serial.println(RO);
  Serial.print("RI: ");
  Serial.println(RI);
  Serial.print("LI: ");
  Serial.println(LI);
  Serial.print("LO: ");
  Serial.println(LO);
//  int driveDirection = 0;
//  driveDirection = driveDirection + 10 * RO;
//  driveDirection = driveDirection - 1 * RI;
//  driveDirection = driveDirection + 1 * LI;
//  driveDirection = driveDirection - 10 * LO;
//
//  if(driveDirection == 0) {
//    driveController(100,100);
//    Serial.println("rechtdoor");
//  } else if(driveDirection == 1) {  // Flauwe bocht naar rechts 
//    driveController(100, 0);
//    Serial.println("naar links");
//  } else if(driveDirection == -1) { // Flauwe bocht naar links
//    driveController(0, 100);
//    Serial.println("naar rechts");
//  } else if(driveDirection < -1) {   // Links 90 graden
//    driveController(-100, 100);
//    Serial.println("scherpe naar  Rechts");
//  } else if(driveDirection > 1) { // Rechts 90 graden
//    driveController(100, -100);
//    Serial.println("scherpe bocht naar links");
//  }
//  Serial.println(driveDirection);
  // rechtdoor
  if(RO == false && RI == true && LI == true && LO == false){
    driveController(100,100);
    Serial.println("rechtdoor");
  }

  if(RO == true) {
    driveController(90, 0);
  }

  if(LO == true) {
    driveController(0, 90);
  }
  
  // rechts 90 graden
  if(RO == true && RI == true && LI == true && LO == false){
    driveController(90, -90);
    Serial.println("rechts 90 graden");
  }

  // links 90 graden
  if(RO == false && RI == true && LI == true && LO == true){
    driveController(-90, 90);
    Serial.println("links 90 graden");
  }

  // flouwe bocht naar rechts
  if(RI == true && LI == false){
    driveController(90, -50);
    Serial.println("flouwe bocht naar rechts");
  }

  // flouwe bocht naar links
  if(RI == false && LI == true){
    driveController(-50, 90);
    Serial.println("flouwe bocht naar links");
  }

  // kruispunt
  if(RO == true && RI == true && LI == true && LO == true){
    driveController(90, 90);
    Serial.println("kuispunt rechtdoor");
  }

  if(RO == false && RI == false && LI == false && LO == false) {
    driveController(90, 90);
  }
}

