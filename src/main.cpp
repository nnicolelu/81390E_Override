#include <iostream>
#include <cmath>
#include "vex.h"

// tyler stop using one laptop >:(
// or you get sent to the gulag

bool isClosed = true;
bool isThingyActive = true;
double left_speed = 0; 
//go to gulags
double right_speed = 0;
int UserControlMode = 0;
int AutonomousMode =7;
int AutonMin = 0;
int AutonMax = 8;
bool isred = true;
bool isSortingColors = true;
void Drive_Autonomous(int, int, int);
void Drive_Autonomous_Volt(int, int, int);
void DriveBrake();
void DriveToRing();
void GyroTurnABS(float, int, int, float);
#pragma once
using namespace vex;
competition Competition;
brain Brain;
controller Controller;
motor Intake = motor(PORT12, ratio6_1, true);
motor LeftArm     = motor(PORT20, ratio18_1, false);
motor RightArm    = motor(PORT20, ratio18_1, true);
// motor LeftFront   = motor(PORT2, ratio6_1, true);
// motor LeftMiddle  = motor(PORT3, ratio6_1, false);
// motor LeftBack    = motor(PORT1, ratio6_1, true);
// motor RightFront  = motor(PORT5, ratio6_1, false);
// motor RightMiddle = motor(PORT6, ratio6_1, true);
// motor RightBack   = motor(PORT4, ratio6_1, false); bajBRWuab meow

motor LeftFront = motor(PORT1, ratio6_1, false); //11
motor LeftMiddle = motor(PORT7, ratio6_1, true); //12
motor LeftBack = motor(PORT15, ratio6_1, true); //13
motor Outake = motor(PORT18,ratio6_1,false);
motor RightFront = motor(PORT10, ratio6_1, true); //1
motor RightMiddle = motor(PORT6, ratio6_1, false); //4
motor RightBack = motor(PORT20, ratio6_1, false); //14
rotation odom = rotation(PORT11); 
pneumatics clamp(Brain.ThreeWirePort.F);
pneumatics doinkerR(Brain.ThreeWirePort.H);
pneumatics lift (Brain.ThreeWirePort.B);
pneumatics antler (Brain.ThreeWirePort.E);
inertial Gyro = inertial(PORT3);
optical OpticalSensor = optical(PORT20);
vex::aivision AIVision1(PORT5, aivision::ALL_AIOBJS);
gps GPS = gps(PORT20);

double goal = 0;


float OneStick = 0;
float TwoStick = 0;
float ThreeStick = 0;
float FourStick = 0;


void drawGUI()
{
  // Draws 2 buttons to be used for selecting auto
  Brain.Screen.clearScreen();
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(1, 40, "Select Auton then Press Go");
  Brain.Screen.printAt(320, 50, "0. Blue pos");
  Brain.Screen.printAt(320, 70, "1. Red pos");
  Brain.Screen.printAt(320, 90, "2. Red Rush");
  Brain.Screen.printAt(320, 110, "3. Red Awp");
  Brain.Screen.printAt(320, 130, "4. Red 5-Ring E");
  Brain.Screen.printAt(320, 150, "5. Blue Rush");
  Brain.Screen.printAt(320, 170, "6. Blue Awp");
  Brain.Screen.printAt(320, 190, "7. Blue 5-Ring E");
  Brain.Screen.printAt(320, 210, "8. Drive 30 Inches");
  Brain.Screen.printAt(1, 40, "Select Auton then Press Go");
  Brain.Screen.printAt(1, 200, "Auton Selected =  %d   ", AutonomousMode);
  Brain.Screen.setFillColor(vex::red);
  Brain.Screen.drawRectangle(20, 50, 100, 100);
  Brain.Screen.drawCircle(300, 75, 25);
  Brain.Screen.printAt(25, 75, "Select");
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(170, 50, 100, 100);
  Brain.Screen.printAt(175, 75, "GO");
  Brain.Screen.setFillColor(black);
}
void selectAuton()
{
  bool selectingAuton = true;

  int x = Brain.Screen.xPosition(); // get the x position of last touch of the screen
  int y = Brain.Screen.yPosition(); // get the y position of last touch of the screen

  // check to see if buttons were pressed
  if (x >= 20 && x <= 120 && y >= 50 && y <= 150)
  { // select button pressed
    AutonomousMode++;
    if (AutonomousMode > AutonMax)
    {
      AutonomousMode = AutonMin; // rollover
    }
    Brain.Screen.printAt(1, 200, "Auton Selected =  %d   ", AutonomousMode);
  }

  if (x >= 170 && x <= 270 && y >= 50 && y <= 150)
  {
    selectingAuton = false; // GO button pressed
    Brain.Screen.printAt(1, 200, "Auton  =  %d   GO           ", AutonomousMode);
  }

  if (!selectingAuton)
  {
    Brain.Screen.setFillColor(green);
    Brain.Screen.drawCircle(300, 75, 25);
  }
  else
  {
    Brain.Screen.setFillColor(vex::red);
    Brain.Screen.drawCircle(300, 75, 25);
  }

  wait(10, msec); // slow it down
  Brain.Screen.setFillColor(black);
}
void Drive_Autonomous(int LeftSpeed, int RightSpeed, int WaitTime)
{
  LeftFront.spin(fwd, LeftSpeed, pct);
  LeftMiddle.spin(fwd, LeftSpeed, pct);
  LeftBack.spin(fwd, LeftSpeed, pct);
  RightFront.spin(fwd, RightSpeed, pct);
  RightMiddle.spin(fwd, RightSpeed, pct);
  RightBack.spin(fwd, RightSpeed, pct);
  wait(WaitTime, msec);
}
void drive(int lspeed, int rspeed, int wt)
{
  lspeed *= 0.12;
  rspeed *= 0.12;

  LeftFront.spin(fwd, lspeed, volt);
  LeftMiddle.spin(fwd, lspeed, volt);
  LeftBack.spin(fwd, lspeed, volt);
  RightFront.spin(fwd, rspeed,volt);
  RightMiddle.spin(fwd, rspeed,volt);
  RightBack.spin(fwd, rspeed, volt);
  wait(wt, msec);
}
void DriveBrake()
{
  LeftFront.stop(brake);
  LeftMiddle.stop(brake);
  LeftBack.stop(brake);
  RightFront.stop(brake);
  RightMiddle.stop(brake);
  RightBack.stop(brake);
}
void Drivecoast()
{
  LeftFront.stop(coast);
  LeftMiddle.stop(coast);
  LeftBack.stop(coast);
  RightFront.stop(coast);
  RightMiddle.stop(coast);
  RightBack.stop(coast); // 
}
float pi = 3.14;
float dia = 3.25;
float diaO = 2;
float gearRatio = 0.75;
float width = 14;
void Drive_Autonomous_Volt(int LeftSpeed, int RightSpeed, int WaitTime)
{
  LeftFront.spin(fwd, LeftSpeed / 100 * 120, volt);
  LeftMiddle.spin(fwd, LeftSpeed / 100 * 120, volt);
  LeftBack.spin(fwd, LeftSpeed / 100 * 120, volt);
  RightFront.spin(fwd, RightSpeed / 100 * 120, volt);
  RightMiddle.spin(fwd, RightSpeed / 100 * 120, volt);
  RightBack.spin(fwd, RightSpeed / 100 * 120, volt);
  wait(WaitTime, msec);
}
double targetL = 2;

enum state {    
    idle,
    loading,
    middle,
};
state currentState = idle;

void toggleState() {
    switch(currentState){
        case idle:
            currentState = loading;
            LeftArm.setVelocity(100,pct);
            RightArm.setVelocity(100,pct);
            Intake.setVelocity(100,pct);
            
            targetL = 1;


            break;

        case loading:
            currentState = middle;
            LeftArm.setVelocity(100,pct);
            RightArm.setVelocity(100,pct);
            Intake.setVelocity(100,pct);
            targetL = 435;
            break; // old 24
        case middle:
            currentState = idle;
            LeftArm.setVelocity(100,pct);
            RightArm.setVelocity(100,pct);
            Intake.setVelocity(100,pct);
            targetL = 655;

            break;



    }
}
void liftControl() {
    double kp = 0.05;
    double kd = 0.05;
    double lasterror = 0;
    double x = (LeftArm.position(deg) + RightArm.position(deg));
    double error = targetL - x;
    double speed = error * kp+kd*(error-lasterror);

    LeftArm.spin(fwd, speed, volt);
    RightArm.spin(fwd, speed, volt);
    lasterror = error;
}
void doubleToggle(){
  toggleState();
  toggleState();
}
void Setup_UserControl()
{
  //set all the drive motors brake modes to coast.
  LeftFront.setBrake(coast);
  LeftMiddle.setBrake(coast);
  LeftBack.setBrake(coast);
  RightFront.setBrake(coast);
  RightMiddle.setBrake(coast);
  RightBack.setBrake(coast);

  // Set all of the drive motors to 100 percent velocity.
  LeftFront.setVelocity(100, pct);
  LeftMiddle.setVelocity(100, pct);
  LeftBack.setVelocity(100, pct);
  RightFront.setVelocity(100, pct);
  RightMiddle.setVelocity(100, pct);
  RightBack.setVelocity(100, pct);
  Controller.ButtonL1.pressed(toggleState);
  Controller.ButtonL2.pressed(doubleToggle);

}
void load(){
  clamp.set(!clamp.value());
}
void doinkerRtoggle()
{
  if (isClosed)
  {
    Controller.rumble(".");
    doinkerR.open();
    isClosed = !isClosed;
  }
  else
  {
    Controller.rumble(".");
    doinkerR.close();
 isClosed = !isClosed;
  }
}


void driver_doinker()
{
  Controller.ButtonA.pressed(doinkerRtoggle);
}

enum Color
{
  blue,
  red
};
bool colorDetected(Color color)
{
  int hue = OpticalSensor.hue();
  switch (color)
  {
  case Color::red:
    if (hue >= 4 && hue <= 27)
    {
      return true;
    }
    break;
  case Color::blue:
    if (hue >= 185 && hue <= 225)
    {
      return true;
    }
    break;
  }
  return false;
} 
//
int intakeState = 0;
bool sortColor = false;
int ladybrownposition = 0;


// void liftmacro(){
//   lift.setVelocity(100,pct);


//   if(ladybrownposition == 0){
//     lift.spinTo(540.5, degrees, true);
//     ladybrownposition = 1;
//   }
//   else{
//     lift.spinTo(640, degrees, true);
//     ladybrownposition = 2;
//   }
// }

    

// void liftrest(){
//   lift.spinTo(0, degrees, true);
//   ladybrownposition = 0;
// }
float Outake_state = 0;
void intakeControl()
{
  float count = 0;
  Outake.setVelocity(100,pct);
  while (true)
  {
    if (intakeState == 1) {
          OpticalSensor.setLightPower(100, percent);
    }
    else {
          OpticalSensor.setLightPower(0, percent);
    }

    if (isSortingColors)
    {
      if (isred)
      {
        if (colorDetected(Color::blue) && OpticalSensor.isNearObject())
        {
          sortColor = true;
        }
      }
      else if (colorDetected(Color::red) && OpticalSensor.isNearObject())
      {
        sortColor = true;
      }
    }
    



    if (intakeState == 1){
      Intake.spin(fwd);
      Outake.spin(fwd);
        // if(Intake.efficiency(pct)<=12){
        //   count++;
        // }
      wait(10, msec);
    }
    else if(intakeState == -1){
    Intake.spin(reverse);
    Outake.spin(reverse);

    wait(10, msec);
    }
    else {
      Intake.stop();
      Outake.stop();
    }

  }
}
void Spin_Intake(bool direction) {
  //78846781b
  // If the direction is true...
  if (direction) {

    // Spin the intake forward.
    intakeState = -1;

    // If the direction is false...
  }
  else if (direction == false)
  {

    // Spin the intake backward.
    intakeState = 1;
  }
}
void Spin_Outake(bool direction) {
  //78846781b
  // If the direction is true...
  if (direction) {

    // Spin the intake forward.
    Outake_state = -1;

    // If the direction is false...
  }
  else if (direction == false)
  {

    // Spin the intake backward.
    Outake_state = 1;
  }
}    
void Stop_Intake()
{
  intakeState = 0;
}
void Stop_Outake()
{
  Outake_state = 0;
}
void Intake_UserControl()
{  
 
  // If the button R2 is being pressed...
  if (Controller.ButtonR2.pressing())
  {

    // Spin the intake forward.
    Spin_Intake(false);

    // AutoUnjam_Intake();

    // If the button R1 is being pressed...
  }
  else if (Controller.ButtonR1.pressing())
  {

    // Spin the intake backward.
    Spin_Intake(true);
    // ColorSorting();
    // vex::thread colorSortingThread(ColorSorting);
    // AutoUnjam_Intake();
    // If neither button R2 nor R1 is being pressed...
  }
  else
  {

    // Stop the intake motor from spinning.
    Stop_Intake();
  } 

  // If the button R2 is being pressed...
  if (Controller.ButtonL2.pressing())
  {

    // Spin the intake forward.
    Spin_Outake(false);

    // AutoUnjam_Intake();

    // If the button R1 is being pressed...
  }
  else if (Controller.ButtonL1.pressing())
  {

    // Spin the intake backward.
    Spin_Outake(true);
    // ColorSorting();
    // vex::thread colorSortingThread(ColorSorting);
    // AutoUnjam_Intake();
    // If neither button R2 nor R1 is being pressed...
  }
  else
  {

    // Stop the intake motor from spinning.
    Stop_Outake();
  }
  
}

void Drive_UserControl()
{


  // Set the stick variables to the axis's of the controller sticks.
  OneStick = Controller.Axis1.position();
  TwoStick = Controller.Axis2.position();
  ThreeStick = Controller.Axis3.position();
  FourStick = Controller.Axis4.position();

  // Calculate left_speed and right_speed.
  left_speed = (ThreeStick + (OneStick * fabs(OneStick)) / 100) * 12 / 100;
  right_speed = (ThreeStick - (OneStick * fabs(OneStick)) / 100) * 12 / 100;

  // Spin the motors at left_speed in volts.
  LeftFront.spin(fwd, left_speed, volt);
  LeftMiddle.spin(fwd, left_speed, volt);
  LeftBack.spin(fwd, left_speed, volt);

  // Spin the motors at right_speed in volts.
  RightFront.spin(fwd, right_speed, volt);
  RightMiddle.spin(fwd, right_speed, volt);
  RightBack.spin(fwd, right_speed , volt);

}
void LIFTWork(){
  lift.set(!lift.value());
}
void AntlerDEscore(){
  antler.set(!antler.value());
}

void GyroTurnABS(float target, int timelimit = 2500, int settleTime = 144, float kp = 0.9)
{
  float kd = 8.32; float ki = 0.0515; // OLD WAS 4
  double heading = Gyro.rotation(); // Initialize a variable for heading
  float accuracy = 2.0; // How accurate to make the turn in degrees
  float error = target - Gyro.rotation(); // Initialize error
  float preError = 0.0; // Previous error value
  float integral = 0.0; // Accumulated error over time
  float speed;
  float lastSpeed = 0.0; // Stores the last output speed
  vex::timer timer;
  vex::timer settleTimer;
  while (1)
  {
    // Calculate speed based on error, derivative, and integral
    error = target - heading;
    if (error > 180) {
      error -= 360;
    }
    else if (error < -180) {
      error += 360;
    }
    
    integral += error * ki; // Accumulate error over time
      if (integral >=40){
        integral = 40;
      }
      else if (integral <=-40){
        integral = -40;
      }
      
    speed = kp * error + kd * (error - preError) + ki * integral;
    preError = error;

    Drive_Autonomous(speed, -speed, 10);

    // Update last speed
    lastSpeed = speed;

    if (timer.time(vex::timeUnits::msec) >= timelimit)
    {
      break;
    }
    if (fabs(error) < accuracy)
    {
      if (settleTimer.time() > settleTime) {
        break;
      }
    }
    else {
      settleTimer.reset();
    }
  }
  DriveBrake(); // Stop the drive
}
float target2 = 0;
void inchDriveC(float target, float timeLimit, float mspeed, float chainspeed = 40,double target2 = Gyro.rotation(), double target3 = Gyro.rotation(), int c = 0)
{
  float heading = 0;
  float angle_error = 0;
  float angle_last_error = 0;
  float angleP = 2;
  float turn_speed = 0;
  float angleD = 0.2;
  float aacuracy = 0.5; 
  RightFront.setPosition(0, rev);
  RightBack.setPosition (0,rev);
  float x = 0;
  float error2 = target;
  float error = target;
  float kp = 7;
  float speed = kp * error;
  float accuracy = 0.05; // was 0.05
  float kd = 0.4;
  double last_error = 0;
  double dt = 0.01;
  double last_speed = 0;
  vex::timer timer; // Create a timer object
  timer.clear();
  while (fabs(error) >= accuracy)
  {
    heading = Gyro.rotation();
    if (target2 > 180)
    {
      target - 360;
    }
    else if (target2 < -180)
    {
      target + 360;
    }

    x = ((RightFront.position(rev)+RightBack.position(rev))/2) * pi * dia * gearRatio;
    //  std::cout << x << "\n"; // stope the drive
    error = target - x;
    angle_error = target2 - heading;
    speed = kp * error + kd * (error - last_error) / dt;
    turn_speed = angleP * angle_error + angleD * (angle_error - angle_last_error) / dt;
    if (speed >= 100)
    {
      speed = 100;
    }
    else if (speed <= -100)
    {
      speed = -100;
    }
    if(mspeed >=0&&mspeed <= chainspeed){
    if (fabs(speed) < chainspeed )
    {
      if (speed > 0)
      {
        speed = chainspeed;
      }
      else
      {
        speed = (-1*chainspeed);
      }
    }
    }

    drive(mspeed*(speed+turn_speed), mspeed*(speed-turn_speed), 10);
    last_error = error;
    angle_last_error = angle_error;
    if(fabs(angle_error)<= aacuracy){
      target2 = target3;
    }
    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
    std::cout << x << std::endl;
  }
}
void inchDriveC3(float target, float timeLimit, float mspeed,bool chained = false, double target2 = Gyro.rotation())
{
  float heading = 0;
  float angle_error = 0;
  float angle_last_error = 0;
  float angleP = 2;
  float turn_speed = 0;
  float angleD = 0.2;
  float aacuracy = 0.5; 
  RightFront.setPosition(0, rev);
  RightBack.setPosition (0,rev);
  float x = 0;
  float error2 = target;
  float error = target;
  float kp = 7;
  float speed = kp * error;
  float accuracy = 0.05; // was 0.05
  float kd = 0.4;
  double last_error = 0;
  double dt = 0.01;
  double last_speed = 0;
  double Ftarget = 0;
  vex::timer timer; // Create a timer object
  timer.clear();
  if(chained = false){
  while (fabs(error) >= accuracy)
  {
    heading = Gyro.rotation();
    if (target2 > 180)
    {
      target - 360;
    }
    else if (target2 < -180)
    {
      target + 360;
    }

    x = ((RightFront.position(rev)+RightBack.position(rev))/2) * pi * dia * gearRatio;
    //  std::cout << x << "\n"; // stope the drive
    error = target - x;
    angle_error = target2 - heading;
    speed = kp * error + kd * (error - last_error) / dt;
    turn_speed = angleP * angle_error + angleD * (angle_error - angle_last_error) / dt;
    if (speed >= 100)
    {
      speed = 100;
    }
    else if (speed <= -100)
    {
      speed = -100;
    }


    drive(mspeed*(speed+turn_speed), mspeed*(speed-turn_speed), 10);
    last_error = error;
    angle_last_error = angle_error;
    if(fabs(angle_error)<= aacuracy){
      target2 = target3;
    }
    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
    std::cout << x << std::endl;
  }
  DriveBrake();
}else{
    while (fabs(error) >= accuracy){

      heading = Gyro.rotation();
      if (target2 > 180)
      {
        target - 360;
      }
      else if (target2 < -180)
      {
        target + 360;
      }
      if (target >0){
        Ftarget = target + 2;
      }
      else if (target <0){
        Ftarget = target -2;
      }
      x = ((RightFront.position(rev)+RightBack.position(rev))/2) * pi * dia * gearRatio;
      //  std::cout << x << "\n"; // stope the drive
      error = Ftarget - x;
      angle_error = target2 - heading;
      speed = kp * error + kd * (error - last_error) / dt;
      turn_speed = angleP * angle_error + angleD * (angle_error - angle_last_error) / dt;
      if (speed >= 100)
      {
        speed = 100;
      }
      else if (speed <= -100)
      {
        speed = -100;
      }


      drive(mspeed*(speed+turn_speed), mspeed*(speed-turn_speed), 10);
      last_error = error;
      angle_last_error = angle_error;
      if(fabs(angle_error)<= aacuracy){
        target2 = target3;
      }
      if (timer.time(vex::timeUnits::msec) >= timeLimit)
      {
        break;
      }
      std::cout << x << std::endl;
  }
}
}

void inchDriveC2(float target, float timeLimit,double mspeed = 100, double target2 = Gyro.rotation(), double distbetweentarget=0, double target3 = Gyro.rotation(),double distbetweentarget2=0,double target4 = Gyro.rotation(), int c = 0)
{
  float heading = 0;
  float angle_error = target2;
  float angle_last_error = 0;
  float angleP = 2;
  float turn_speed = 0;
  float angleD = 0.2;
  float aacuracy = 0.7; 
  RightFront.setPosition(0, rev);
  float x = 0;
  float error2 = target;
  float error = target;
  float kp = 7;
  float speed = kp * error;
  float accuracy = 0.05; // was 0.05
  float kd = 0.4;
  double last_error = 0;
  double dt = 0.01;
  double last_speed = 0;
  vex::timer timer; // Create a timer object
  timer.clear();
  bool s = false;
  int count;

  while (fabs(error) >= accuracy)
  {
    heading = Gyro.rotation();
    if (target2 > 180)
    {
      target2 - 360;
    }
    else if (target2 < -180)
    {
      target2 + 360;
    }
    x = RightFront.position(rev) * pi * dia * gearRatio;
    error = target - x;
    if(fabs(error<=distbetweentarget)&&s==false){
      target2 = target3;

      s=true;
    }
    if(fabs(angle_error)<=aacuracy&&s==true&&fabs(error)<=distbetweentarget2){
      target2 = target4;
      s=true;
    }


    angle_error = target2 - heading;
    speed = kp * error + kd * (error - last_error) / dt;
    turn_speed = angleP * angle_error + angleD * (angle_error - angle_last_error) / dt;
    if(fabs(mspeed) <= fabs(speed)){
      if(speed >= 0){
        speed = mspeed;
      }
      else if(speed <=0){
        speed = -mspeed;
      }
      else{
        speed = speed;
      }
    }
    if (speed >= 100)
    {
      speed = 100;
    }
    else if (speed <= -100)
    {
      speed = -100;
    }


    drive((speed+turn_speed),(speed-turn_speed), 10);
    last_error = error;
    angle_last_error = angle_error;
    std::cout << count <<", " << error <<", " << speed + turn_speed<<", " << speed - turn_speed <<", " << heading << std::endl;


    count++;
    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }
}
// Adjustable "Gain" - change this to make the robot turn faster or slower

void Align(){
    AIVision1.takeSnapshot(aivision::ALL_TAGS);
    double Tkp = 6; 
    double Tki = 0; 
    double Tkd = 0; 
    double kp =1;
    double ki =0;
    double kd =0;
    double last_error = 0;
    double Tlast_error = 0;
    double accuracy = 0.05;
    double realWidth = 5.5;
    double focalLength = 271.6;
    double pixelWidth = AIVision1.objects[0].centerX;
    double distance = (realWidth * focalLength) / pixelWidth;
    double error = 0-distance;
    Brain.Screen.print(AIVision1.objectCount);
  if (AIVision1.objectCount > 0) {

    pixelWidth = AIVision1.objects[0].centerX;
    aivision::object targetTag = AIVision1.objects[0];
    while(fabs(error)>=accuracy){

    distance = (realWidth * focalLength) / pixelWidth;
    error = 0-distance;
    double heading = Gyro.rotation();
    
    float Terror = targetTag.angle - heading;
    float speed = error*kp + kd * (error - last_error);
    float turnVelocity = Terror * Tkp ;
    drive(turnVelocity,-turnVelocity,1);

    // if (AIVision1.objects[0].width > 100) {
    //     DriveBrake();
    //     break; 
    // }
    std::cout  << targetTag.angle <<std::endl;
    std::cout  << turnVelocity<<std::endl;



  last_error = error;
  Tlast_error = Terror;
  }

}
}
LeftFront
void inchDriveO(float target, float timeLimit, float mspeed, float chainspeed = 40,double target2 = Gyro.rotation(), double target3 = Gyro.rotation(), int c = 0)
{
  float heading = 0;
  float angle_error = 0;
  float angle_last_error = 0;
  float angleP = 2;
  float turn_speed = 0;
  float angleD = 0.4;
  float aacuracy = 0.5; 
  double startposition = odom.position(rev);
  float x = 0;
  float error2 = target;
  float error = target;
  float kp = 7;
  float speed = kp * error;
  float accuracy = 0.05; // was 0.05
  float kd = 1.2;
  double last_error = 0;
  double dt = 0.01;
  double last_speed = 0;
  vex::timer timer; // Create a timer object
  timer.clear();

  while (fabs(error) >= accuracy)
  {
    heading = Gyro.rotation();
    if (target2 > 180)
    {
      target - 360;
    }
    else if (target2 < -180)
    {
      target + 360;
    }
    x = (odom.position(rev)- startposition) * diaO*pi;
    //  std::cout << x << "\n"; // stope the drive
    error = target - x;
    angle_error = target2 - heading;
    speed = kp * error + kd * (error - last_error) / dt;
    turn_speed = angleP * angle_error + angleD * (angle_error - angle_last_error) / dt;
    if (speed >= 100)
    {
      speed = 100;
    }
    else if (speed <= -100)
    {
      speed = -100;
    }
    if(mspeed >=0&&mspeed <= chainspeed){
    if (fabs(speed) < chainspeed )
    {
      if (speed > 0)
      {
        speed = chainspeed;
      }
      else
      {
        speed = (-1*chainspeed);
      }
    }
    }

    drive(mspeed*(speed+turn_speed), mspeed*(speed-turn_speed), 10);
    last_error = error;
    angle_last_error = angle_error;
    if(fabs(angle_error)<= aacuracy){
      target2 = target3;
    }
    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
    std::cout << x << std::endl;
  }
}
void arcturn(float target, float arcdegree, float timeLimit, int b = 1.5, int c = 0)
{
  float heading = 0;
  float angle_error = 0;
  float angle_last_error = 0;
  float angleP = 1.2;
  float turn_speed = 0;
  float angle_accuracy = 0.3;
  LeftMiddle.setPosition(0, rev);
  float x = 0;
  float error = target;
  float kp = 6;
  float speed = kp * error;
  float accuracy = 0.1; // was 0.05
  float kd = 0.5;
  double last_error = 0;
  double dt = 0.01;
  vex::timer timer; // Create a timer object
  timer.clear();
  while (fabs(error) > accuracy or fabs(angle_error) > angle_accuracy)
  {
    heading = Gyro.rotation();
    x = LeftMiddle.position(rev) * pi * dia * gearRatio;
    if (angle_error > 180)
    {
      error = error - 360;
    }
    else if (angle_error < -180)
    {
      error = error + 360;
    }
    error = target - x;
    angle_error = arcdegree - heading;
    speed = kp * error + kd * (error - last_error) / dt + b * error / fabs(error);
    turn_speed = angleP * angle_error + c * angle_error / fabs(angle_error);
    if (speed >= 100)
    {
      speed = 100;
    }
    else if (speed <= -100)
    {
      speed = -100;
    }

    drive(speed + turn_speed, speed - turn_speed, 10);
    last_error = error;
    angle_last_error = angle_error;
    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }
  DriveBrake();
}

void gyroTurnF(float target, double mspeed =1, double accuracy = 0.3, float b = 2.4)
{
  float heading = 0.0; // initialize a variable for heading
  double error = target - heading;
  double ki = 0.5;
  double intergal = 0;

  double kp = 5; // 7.85;//was 6
  double speed = 0;
  double kd = 40; // 0.65;//was 0.3
  double last_error = 0;
  double dt = 0.01; // reset Gyro to zero degrees
  int count = 0;
  vex::timer timer; // Create a timer object

  timer.clear(); // Clear any previous timer value
  int timeLimit = 1200;
  while (fabs(error) >= accuracy or count <= 5)
  {
    heading = Gyro.rotation(); // measure the heading of the robot
    std::cout << heading << "\n";
    error = target - heading;

    if (error > 180)
    {
      error = error - 360;
    }
    else if (error < -180)
    {
      error = error + 360;
    }

    if (fabs(error) < 15 && fabs(error) > 0.5)
    {
      intergal += error;
    }
    else
    {
      intergal = 0;
    }

    if (intergal >= 50)
    {
      intergal = 50;
    }
    else if (intergal <= -50)
    {
      intergal = -50;
    }


    speed = kp * error + kd * (error - last_error)  + ki * intergal;

    drive(speed*mspeed, -speed*mspeed,10); // turn right at speed
    last_error = error;
    if (fabs(error) <= accuracy + 0.3)
    {
      count++;
    }
    else
      count = 0;

    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }

  DriveBrake();
  std::cout << "newline" << "\n"; // stope the drive
}
void gyropivotR(float target, bool direction, double accuracy = 0.5,  int timeLimit = 1200, float b = 2.4)
{
  float heading = Gyro.rotation(); // initialize a variable for heading
  double error = target - heading;
  double ki = 0.95;
  double intergal = 0;

  double kp = 7; // 7.85;//was 6
  double speed = 0;
  double kd = 0.45; // 0.65;//was 0.3
  double last_error = 0;
  double dt = 0.01; // reset Gyro to zero degrees
  int count = 0;
  vex::timer timer; // Create a timer object

  timer.clear(); // Clear any previous timer value
  while (fabs(error) >= accuracy )
  {
    heading = Gyro.rotation(); // measure the heading of the robot
    std::cout << heading << "\n";
    error = target - heading;

    if (error > 180)
    {
      error = error - 360;
    }
    else if (error < -180)
    {
      error = error + 360;
    }

    if (fabs(error) < 10 && fabs(error) > 1)
    {
      intergal += error;
    }
    else
    {
      intergal = 0;
    }

    if (intergal >= 50)
    {
      intergal = 50;
    }
    else if (intergal <= -50)
    {
      intergal = -50;
    }

    // calculate error
    speed = kp * error + kd * (error - last_error) / dt + ki * intergal;
    if (direction == true){
      if (speed>=0){
        speed *=-1;
      }
    }
    else if (direction == false){
      if (speed<=0){
        speed *=-1;
      }
    }
    drive(0, -speed*0.5, dt * 1000); // turn right at speed
    last_error = error;
    if (fabs(error) <= accuracy + 0.3)
    {
      count++;
    }
    else
      count = 0;

    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }

  DriveBrake();
  std::cout << "newline" << "\n"; // stope the drive
}

void gyropivotL(float target, bool direction, double accuracy = 0.5,  int timeLimit = 1200, float b = 2.4)
{
  float heading = Gyro.rotation(); // initialize a variable for heading
  double error = target - heading;
  double ki = 0.95;
  double intergal = 0;

  double kp = 7; // 7.85;//was 6
  double speed = 0;
  double kd = 0.72; // 0.65;//was 0.3
  double last_error = 0;
  double dt = 0.01; // reset Gyro to zero degrees
  int count = 0;
  vex::timer timer; // Create a timer object

  timer.clear(); // Clear any previous timer value

  while (fabs(error) >= accuracy )
  {
    heading = Gyro.rotation(); // measure the heading of the robot
    std::cout << heading << "\n";
    error = target - heading;

    if (error > 180)
    {
      error = error - 360;
    }
    else if (error < -180)
    {
      error = error + 360;
    }

    if (fabs(error) < 10 && fabs(error) > 1)
    {
      intergal += error;
    }
    else
    {
      intergal = 0;
    }

    if (intergal >= 50)
    {
      intergal = 50;
    }
    else if (intergal <= -50)
    {
      intergal = -50;
    }

    // calculate error
    speed = kp * error + kd * (error - last_error) / dt + ki * intergal;
    if (direction == true){
      if (speed<=0){
        speed *=-1;
      }
    }
    else if (direction == false){
      if (speed>=0){
        speed *=-1;
      }
    }
    drive(speed*0.5, 0, dt * 1000); // turn right at speed
    last_error = error;
    if (fabs(error) <= accuracy + 0.3)
    {
      count++;
    }
    else
      count = 0;

    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }

  DriveBrake();
  std::cout << "newline" << "\n"; // stope the drive
}
void gyropivotRC(float target, bool direction, double accuracy = 0.5,  int timeLimit = 1200, float b = 2.4)
{
  float heading = 0.0; // initialize a variable for heading
  double error = target;
  double ki = 0.95;
  double intergal = 0;

  double kp = 7; // 7.85;//was 6
  double speed = 0;
  double kd = 0.72; // 0.65;//was 0.3
  double last_error = 0;
  double dt = 0.01; // reset Gyro to zero degrees
  int count = 0;
  vex::timer timer; // Create a timer object

  timer.clear(); // Clear any previous timer value
  while (fabs(error) >= accuracy )
  {
    heading = Gyro.rotation(); // measure the heading of the robot
    std::cout << heading << "\n";
    error = target - heading;

    if (error > 180)
    {
      error = error - 360;
    }
    else if (error < -180)
    {
      error = error + 360;
    }

    if (fabs(error) < 10 && fabs(error) > 1)
    {
      intergal += error;
    }
    else
    {
      intergal = 0;
    }

    if (intergal >= 50)
    {
      intergal = 50;
    }
    else if (intergal <= -50)
    {
      intergal = -50;
    }

    // calculate error
    speed = kp * error + kd * (error - last_error) / dt + ki * intergal;
    if (direction == true){
      if (speed>=0){
        speed *=-1;
      }
    }
    else if (direction == false){
      if (speed<=0){
        speed *=-1;
      }
    }
    drive(0, -speed*0.5, dt * 1000); // turn right at speed
    last_error = error;
    if (fabs(error) <= accuracy + 0.3)
    {
      count++;
    }
    else
      count = 0;

    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }

  Drivecoast();
  std::cout << "newline" << "\n"; // stope the drive
}
void gyropivotLC(float target, bool direction, double accuracy = 0.5,  int timeLimit = 1200, float b = 2.4)
{
  float heading = Gyro.rotation(); // initialize a variable for heading
  double error = target - heading;
  double ki = 0.95;
  double intergal = 0;

  double kp = 7; // 7.85;//was 6
  double speed = 0;
  double kd = 0.45; // 0.65;//was 0.3
  double last_error = 0;
  double dt = 0.01; // reset Gyro to zero degrees
  int count = 0;
  vex::timer timer; // Create a timer object

  timer.clear(); // Clear any previous timer value
  while (fabs(error) >= accuracy )
  {
    heading = Gyro.rotation(); // measure the heading of the robot
    std::cout << heading << "\n";
    error = target - heading;

    if (error > 180)
    {
      error = error - 360;
    }
    else if (error < -180)
    {
      error = error + 360;
    }

    if (fabs(error) < 10 && fabs(error) > 1)
    {
      intergal += error;
    }
    else
    {
      intergal = 0;
    }

    if (intergal >= 50)
    {
      intergal = 50;
    }
    else if (intergal <= -50)
    {
      intergal = -50;
    }

    // calculate error
    speed = kp * error + kd * (error - last_error) / dt + ki * intergal;
    if (direction == true){
      if (speed<=0){
        speed *=-1;
      }
    }
    else if (direction == false){
      if (speed>=0){
        speed *=-1;
      }
    }
    drive(speed*0.4, 0, dt * 1000); // turn right at speed
    last_error = error;
    if (fabs(error) <= accuracy + 0.3)
    {
      count++;
    }
    else
      count = 0;

    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }

  Drivecoast();
  std::cout << "newline" << "\n"; // stope the drive
}
void arcturnLH(int r, float arcdeg, int timeLimit, float max_drift = 0.15)
{
float startHeading = Gyro.rotation();
float targetHeading = arcdeg;

float turnAmount = targetHeading - startHeading;
while (turnAmount < 0) turnAmount += 360;
while (turnAmount >= 360) turnAmount -= 360;

float heading = Gyro.rotation();
float angle_last_error = 0;

float angleP = 1.2;
float angleD = 0.05;

float turn_speed = 0;
float angle_accuracy = 0.3;
float robotwidth = 15;

LeftMiddle.setPosition(0, rev);
RightMiddle.setPosition(0, rev);

float Lx = 0;
float Rx = 0;
float settletime = 150;

double Ltarget = 2 * pi * r * fabs(turnAmount / 360.0);
double Rtarget = 2 * pi * (r + robotwidth) * fabs(turnAmount / 360.0);

float Lerror = Ltarget;
float Rerror = Rtarget;
float Lkp = 7;
float count = 0;
float Rkp = 7;
float accuracy = 0.1;
float Lkd = 0.35;
float Rkd = 0.35;
double Llast_error = 0;
double Rlast_error = 0;
double dt = 0.01;
double Lki = 0.5;
double Lintergal = 0;
double Rki = 0.5;
double Rintergal = 0;

float angle_target = startHeading;
float Lspeed = Lkp * Lerror + Lkd * (Lerror - Llast_error) / dt + Lintergal * Lki;
float Rspeed = Rkp * Rerror + Rkd * (Rerror - Rlast_error) / dt + Rintergal * Rki;
float angle_error = angle_target - heading;

vex::timer timer;
vex::timer errortimer;
timer.clear();

while (true)
{
heading = Gyro.rotation();

Lx = LeftMiddle.position(rev) * pi * dia * gearRatio;
Rx = RightMiddle.position(rev) * pi * dia * gearRatio;

angle_target = startHeading + (Lx * 360) / (2 * pi * r);

angle_error = angle_target - heading;

if (angle_error > 180)
{
angle_error = angle_error - 360;
}
else if (angle_error < -180)
{
angle_error = angle_error + 360;
}

Lerror = Ltarget - Lx;
Rerror = Rtarget - Rx;

if (fabs(Lerror) < 10 && fabs(Lerror) > 1)
{
Lintergal += Lerror;
}
else
{
Lintergal = 0;
}if (Lintergal >= 40)
{
Lintergal = 40;
}
else if (Lintergal <= -40)
{
Lintergal = -40;
}

if (fabs(Rerror) < 10 && fabs(Rerror) > 1)
{
Rintergal += Rerror;
}
else
{
Rintergal = 0;
}

if (Rintergal >= 40)
{
Rintergal = 40;
}
else if (Rintergal <= -40)
{
Rintergal = -40;
}

Lspeed = Lkp * Lerror + Lkd * (Lerror - Llast_error) / dt + Lintergal * Lki;
Rspeed = Rkp * Rerror + Rkd * (Rerror - Rlast_error) / dt + Rintergal * Rki;

Brain.Screen.printAt(1, 20, "Lspeed = %.2f Rspeed = %.2f ", Lspeed, Rspeed);

turn_speed = angleP * angle_error + angleD * (angle_error - angle_last_error) / dt;

float maxTurn = fabs(Lspeed) * max_drift;

if (turn_speed > maxTurn)
{
turn_speed = maxTurn;
}
else if (turn_speed < -maxTurn)
{
turn_speed = -maxTurn;
}

if (Lspeed >= 100)
{
Lspeed = 100;
}
else if (Lspeed <= -100)
{
Lspeed = -100;
}

if (Rspeed >= 100)
{
Rspeed = 100;
}
else if (Rspeed <= -100)
{
Rspeed = -100;
}

if (fabs(angle_error) > angle_accuracy)
{
errortimer.clear();
}

if (fabs(Lerror) <= accuracy + 0.3 && fabs(Rerror) <= accuracy + 0.3)
{
count++;
}
else
{
count = 0;
}

drive(Lspeed - turn_speed, Rspeed + turn_speed, 10);

Llast_error = Lerror;
Rlast_error = Rerror;
angle_last_error = angle_error;

if (count >= 20 || timer.time(vex::timeUnits::msec) >= timeLimit)
{
break;
}

vex::wait(10, vex::timeUnits::msec);
}

DriveBrake();
}
void arcturnL(int r, float arcdeg, int timeLimit, float max_drift = 0.15)
{
  float heading = Gyro.rotation();
  float Initheading = Gyro.rotation();

  float angle_last_error = 0;
  float angleP = 0;
  float angleD = 0;
  float turn_speed = 0;
  float angle_accuracy = 0.3;
  float robotwidth = 15;
  LeftMiddle.setPosition(0, rev);
  RightMiddle.setPosition(0, rev);
  float Lx = 0;
  float Rx = 0;
  float settletime = 150;
  double Ltarget = 2 * pi * (r)*fabs(arcdeg / 360.0);
  double Rtarget = 2 * pi * (r + robotwidth) * fabs(arcdeg / 360.0);
  float Lerror = Ltarget;
  float Rerror = Rtarget;
  float Lkp = 7;
  float count = 0;
  float Rkp = 7;
  float accuracy = 0.1; // was 0.05
  float Lkd = 0.35;
  float Rkd = 0.35;
  double Llast_error = 0;
  double Rlast_error = 0;
  double dt = 0.01;
  double Lki = 0.5;
  double Lintergal = 0;
  double Rki = 0.5;
  double Rintergal = 0;
  float angle_target = (Rx * 360) / (2 * pi * r);
  float Lspeed = Lkp * Lerror + Lkd * (Lerror - Llast_error) / dt + Lintergal * Lki;
  float Rspeed = Rkp * Rerror + Rkd * (Rerror - Rlast_error) / dt + Rintergal * Rki;
  float angle_error = angle_target;
  vex::timer timer;
  vex::timer errortimer; // Create a timer object
  timer.clear();
  while (count >= 2)
  {

    heading = Gyro.rotation();
    Lx = LeftMiddle.position(rev) * pi * dia * gearRatio;
    Rx = RightMiddle.position(rev) * pi * dia * gearRatio;
    angle_target = (Lx * 360) / (2 * pi * r);

    Lerror = Ltarget - Lx;
    Rerror = Rtarget - Rx;
    angle_error = angle_target - heading;

    if (angle_error > 180)
    {
      angle_error = angle_error - 360;
    }
    else if (angle_error < -180)
    {
      angle_error = angle_error + 360;
    }
    if (fabs(Lerror) < 10 && fabs(Lerror) > 1)
    {
      Lintergal += Lerror;
    }
    else
    {
      Lintergal = 0;
    }
    if (Lintergal >= 40)
    {
      Lintergal = 40;
    }
    else if (Lintergal <= -40)
    {
      Lintergal = -40;
    }
    if (fabs(Rerror) < 10 && fabs(Rerror) > 1)
    {
      Rintergal += Rerror;
    }
    else
    {
      Rintergal = 0;
    }
    if (Rintergal >= 40)
    {
      Rintergal = 40;
    }

    else if (Rintergal <= -40)
    {
      Rintergal = -40;
    }
    Lspeed = Lkp * Lerror + Lkd * (Lerror - Llast_error) / dt + Lintergal * Lki;
    Rspeed = Rkp * Rerror + Rkd * (Rerror - Rlast_error) / dt + Rintergal * Rki;
    Brain.Screen.printAt(1, 20, "Lspeed = %.2f     Rspeed = %.2f  ", Lspeed, Rspeed);
    turn_speed = angleP * angle_error + angleD * (angle_error - angle_last_error) / dt;
    // turn_speed = std::min(std::fabs(turn_speed), std::fabs(Lspeed) * max_drift);

    if (Lspeed >= 100)
    {
      Lspeed = 100;
    }
    else if (Lspeed <= -100)
    {
      Lspeed = -100;
    }
    if (Rspeed >= 100)
    {
      Rspeed = 100;
    }
    else if (Rspeed <= -100)
    {
      Rspeed = -100;
    }

    if (fabs(angle_error) > angle_accuracy)
    {
      errortimer.clear();
    }
    if (fabs(Lerror) <= accuracy + 0.3 || fabs(Rerror) <= accuracy + 0.3)
    {
      count++;
    }
    else
      count = 0;

    drive(Lspeed - turn_speed, Rspeed + turn_speed, 10);
    Llast_error = Lerror;
    Rlast_error = Rerror;
    angle_last_error = angle_error;
    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }
  DriveBrake();
}
void arcturnR(float r, float arcdeg, int timeLimit, float max_drift = 0.1)
{
  float heading = Gyro.rotation();

  float angle_last_error = 0;
  float angleP = 0;
  float angleD = 0;
  float turn_speed = 0;
  float angle_accuracy = 0.3;
  float robotwidth = 10.5;
  LeftMiddle.setPosition(0, rev);
  RightMiddle.setPosition(0, rev);
  float Lx = 0;
  float Rx = 0;
  float settletime = 150;
  double Ltarget = 2 * pi * (r) * fabs(arcdeg / 360.0);
  double Rtarget = 2 * pi * (r+robotwidth)*fabs(arcdeg / 360.0);
  float Lerror = Ltarget;
  float Rerror = Rtarget;
  float Lkp = 7;
  float count = 0;
  float Rkp = 7;
  float accuracy = 0.1; // was 0.05
  float Lkd = 0.35;
  float Rkd = 0.35;
  double Llast_error = 0;
  double Rlast_error = 0;
  double dt = 0.01;
  double Lki = 0;
  double Lintergal = 0;
  double Rki = 0;
  double Rintergal = 0;
  float angle_target = (Lx * 360) / (2 * pi * r);
  float Lspeed = Lkp * Lerror + Lkd * (Lerror - Llast_error) / dt + Lintergal * Lki;
  float Rspeed = Rkp * Rerror + Rkd * (Rerror - Rlast_error) / dt + Rintergal * Rki;
  float angle_error = angle_target;
  vex::timer timer;
  vex::timer errortimer; // Create a timer object
  timer.clear();
  while (fabs(Lerror) >= accuracy || fabs(Rerror) >= accuracy || count <= 5)
  {

    heading = Gyro.rotation();
    Lx = LeftMiddle.position(rev) * pi * dia * gearRatio;
    Rx = RightMiddle.position(rev) * pi * dia * gearRatio;
    angle_target = (Lx * 360) / (2 * pi * r);

    Lerror = Ltarget - Lx;
    Rerror = Rtarget - Rx;
    angle_error = angle_target - heading;

  
    if (angle_error > 180)
    {
      angle_error = angle_error - 360;
    }
    else if (angle_error < -180)
    {
      angle_error = angle_error + 360;
    }


    if (fabs(Lerror) < 10 && fabs(Lerror) > 1)
    {
      Lintergal += Lerror;
    }
    else
    {
      Lintergal = 0;
    }
    
    
    if (Lintergal >= 40)
    {
      Lintergal = 40;
    }
    else if (Lintergal <= -40)
    {
      Lintergal = -40;
    }



    if (fabs(Rerror) < 10 && fabs(Rerror) > 1)
    {
      Rintergal += Rerror;
    }
    else
    {
      Rintergal = 0;
    }
    
    
    if (Rintergal >= 40)
    {
      Rintergal = 40;
    }
    else if (Rintergal <= -40)
    {
      Rintergal = -40;
    }


    Lspeed = Lkp * Lerror + Lkd * (Lerror - Llast_error) / dt + Lintergal * Lki;
    Rspeed = Rkp * Rerror + Rkd * (Rerror - Rlast_error) / dt + Rintergal * Rki;
    Brain.Screen.printAt(1, 20, "Lspeed = %.2f     Rspeed = %.2f  ", Lspeed, Rspeed);
    turn_speed = angleP * angle_error + angleD * (angle_error, angle_last_error) / dt;
    turn_speed = std::min(std::fabs(turn_speed), std::fabs(Lspeed) * max_drift);
    Lspeed = Lspeed*0.3;
    Rspeed = Rspeed*0.3;

    if (fabs(angle_error) > angle_accuracy)
    {
      errortimer.clear();
    }
    if (fabs(Lerror) <= accuracy + 0.3 || fabs(Rerror) <= accuracy + 0.3)
    {
      count++;
    }
    else
      count = 0;

    drive(Lspeed - turn_speed, Rspeed + turn_speed, 10);
    Llast_error = Lerror;
    Rlast_error = Rerror;
    angle_last_error = angle_error;
    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }
  DriveBrake();
}
void arcturnLC(float r, float arcdeg, int timeLimit, float max_drift = 0.15)
{
  float heading = Gyro.rotation();

  float angle_last_error = 0;
  const float angleP {12};
  const float angleD {0.8};
  float turn_speed = 0;
  float angle_accuracy = 0.3;
  float robotwidth = 12;
  LeftMiddle.setPosition(0, rev);
  RightMiddle.setPosition(0, rev);
  float Lx = 0;
  float Rx = 0;
  float settletime = 150;
  double Ltarget = 2 * pi * (r)*fabs(arcdeg / 360.0);
  double Rtarget = 2 * pi * (r+ robotwidth) * fabs(arcdeg / 360.0);
  float Lerror = Ltarget;
  float Rerror = Rtarget;
  float Lkp = 6;
  float count = 0;
  float Rkp = 6;
  float accuracy = 0.1; // was 0.05
  float Lkd = 0.5;
  float Rkd = 0.5;
  double Llast_error = 0;
  double Rlast_error = 0;
  double dt = 0.01;
  double Lki = 0.5;
  double Lintergal = 0;
  double Rki = 0.5;
  double Rintergal = 0;
  float angle_target = (Rx * 360) / (2 * pi * r);
  float Lspeed = Lkp * Lerror + Lkd * (Lerror - Llast_error) / dt + Lintergal * Lki;
  float Rspeed = Rkp * Rerror + Rkd * (Rerror - Rlast_error) / dt + Rintergal * Rki;
  float angle_error = angle_target;
  vex::timer timer;
  vex::timer errortimer; // Create a timer object
  timer.clear();
  while (fabs(Lerror) >= accuracy || fabs(Rerror) >= accuracy)
  {

    heading = Gyro.rotation();
    Lx = LeftMiddle.position(rev) * pi * dia * gearRatio;
    Rx = RightMiddle.position(rev) * pi * dia * gearRatio;
    angle_target = (Lx * 360) / (2 * pi * r);

    Lerror = Ltarget - Lx;
    Rerror = Rtarget - Rx;
    angle_error = angle_target - heading;

    if (angle_error > 180)
    {
      angle_error = angle_error - 360;
    }
    else if (angle_error < -180)
    {
      angle_error = angle_error + 360;
    }


    if (fabs(Lerror) < 10 && fabs(Lerror) > 1)
    {
      Lintergal += Lerror;
    }
    else
    {
      Lintergal = 0;
    }


    if (Lintergal >= 40)
    {
      Lintergal = 40;
    }
    else if (Lintergal <= -40)
    {
      Lintergal = -40;
    }

  
    if (fabs(Rerror) < 10 && fabs(Rerror) > 1)
    {
      Rintergal += Rerror;
    }
    else
    {
      Rintergal = 0;
    }


    if (Rintergal >= 40)
    {
      Rintergal = 40;
    }

    else if (Rintergal <= -40)
    {
      Rintergal = -40;
    }


    Lspeed = Lkp * Lerror + Lkd * (Lerror - Llast_error) / dt + Lintergal * Lki;
    Rspeed = Rkp * Rerror + Rkd * (Rerror - Rlast_error) / dt + Rintergal * Rki;
    Brain.Screen.printAt(1, 20, "Lspeed = %.2f     Rspeed = %.2f  ", Lspeed, Rspeed);
    turn_speed = angleP * angle_error + angleD * (angle_error, angle_last_error) / dt;
    turn_speed = std::min(std::fabs(turn_speed), std::fabs(Lspeed) * max_drift);



    std::cout <<"Heading: "<< heading << '\n';
    std::cout <<"angle Error "<<angle_error<<'\n';
    std::cout <<"LSpeed: " << Lspeed << '\n';
    std::cout <<"RSpeed: " << Rspeed << '\n';
    std::cout <<"Lerror: " << Lerror << '\n';
    std::cout <<"Rerror: " << Rerror << '\n';
    std::cout <<"turn_speed: "<< turn_speed << '\n';
    std::cout << "\n";

    if (Lspeed >= 100)
    {
      Lspeed = 100;
    }
    else if (Lspeed <= -100)
    {
      Lspeed = -100;
    }


    if (Rspeed >= 100)
    {
      Rspeed = 100;
    }
    else if (Rspeed <= -100)
    {
      Rspeed = -100;
    }


    Lspeed = Rspeed*(Ltarget/Rtarget);


    if (fabs(angle_error) > angle_accuracy)
    {
      errortimer.clear();
    }


    if (fabs(Lerror) <= accuracy + 0.3 || fabs(Rerror) <= accuracy + 0.3)
    {
      count++;
    }
    else
      count = 0;


    if (fabs(Lspeed) < 70 && Lerror > 3)
    {
      if (Lspeed > 0)
      {
        Lspeed = 70;
      }
      else
      {
        Lspeed = -70;
      }
    }


    if (fabs(Rspeed) < 70 && Rerror > 3)
    {
      if (Rspeed > 0)
      {
        Rspeed = 70;
      }
      else
      {
        Rspeed = -70;
      }
    }


    drive(Lspeed-turn_speed, Rspeed+turn_speed, 10);


    Llast_error = Lerror;
    Rlast_error = Rerror;
    angle_last_error = angle_error;
    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }
  Drivecoast();
}


void arcturnRC(float r, float arcdeg, int timeLimit, float max_drift = 0.1)
{
  float heading = Gyro.rotation();

  float angle_last_error = 0;
  float angleP = 6.5;
  float angleD = 0.1;
  float turn_speed = 0;
  float angle_accuracy = 0.3;
  float robotwidth = 15;
  LeftMiddle.setPosition(0, rev);
  RightMiddle.setPosition(0, rev);
  float Lx = 0;
  float Rx = 0;
  float settletime = 150;
  double Ltarget = 2 * pi * (r ) * fabs(arcdeg / 360.0);
  double Rtarget = 2 * pi * (r- robotwidth)*fabs(arcdeg / 360.0);
  float Lerror = Ltarget;
  float Rerror = Rtarget;
  float Lkp = 6;
  float count = 0;
  float Rkp = 6;
  float accuracy = 0.1; // was 0.05
  float Lkd = 0.5;
  float Rkd = 0.5;
  double Llast_error = 0;
  double Rlast_error = 0;
  double dt = 0.01;
  double Lki = 0.5;
  double Lintergal = 0;
  double Rki = 0.5;
  double Rintergal = 0;
  float angle_target = (Rx * 360) / (2 * pi * r);
  float Lspeed = Lkp * Lerror + Lkd * (Lerror - Llast_error) / dt + Lintergal * Lki;
  float Rspeed = Rkp * Rerror + Rkd * (Rerror - Rlast_error) / dt + Rintergal * Rki;
  float angle_error = angle_target;
  vex::timer timer;
  vex::timer errortimer; // Create a timer object
  timer.clear();
  while (fabs(Lerror) >= accuracy || fabs(Rerror) >= accuracy)
  {

    heading = Gyro.rotation();
    Lx = LeftMiddle.position(rev) * pi * dia * gearRatio;
    Rx = RightMiddle.position(rev) * pi * dia * gearRatio;
    angle_target = (Lx * 360) / (2 * pi * r);

    Lerror = Ltarget - Lx;
    Rerror = Rtarget - Rx;
    angle_error = angle_target - heading;

    if (angle_error > 180)
    {
      angle_error = angle_error - 360;
    }
    else if (angle_error < -180)
    {
      angle_error = angle_error + 360;
    }
    if (fabs(Lerror) < 10 && fabs(Lerror) > 1)
    {
      Lintergal += Lerror;
    }
    else
    {
      Lintergal = 0;
    } 
    if (Lintergal >= 40)
     {
      Lintergal = 40;
    } 
    else if (Lintergal <= -40)
    {
      Lintergal = -40;
    } 
    if (fabs(Rerror) < 10 && fabs(Rerror) > 1)
    {
      Rintergal += Rerror;
    }
    else    
    { 
      Rintergal = 0; 
    }
    if (Rintergal >= 40)
    {
      Rintergal = 40;
    }

    else if (Rintergal <= -40)
    {
      Rintergal = -40;
    }
    Lspeed = Lkp * Lerror + Lkd * (Lerror - Llast_error) / dt + Lintergal * Lki;
    Rspeed = Rkp * Rerror + Rkd * (Rerror - Rlast_error) / dt + Rintergal * Rki;
    Brain.Screen.printAt(1, 20, "Lspeed = %.2f     Rspeed = %.2f  ", Lspeed, Rspeed);
    turn_speed = angleP * angle_error + angleD * (angle_error, angle_last_error) / dt;
    turn_speed = std::min(std::fabs(turn_speed), std::fabs(Lspeed) * max_drift);

    if (Lspeed >= 100)
    {
      Lspeed = 100;
    }
    else if (Lspeed <= -100)
    {
      Lspeed = -100;
    }
    if (Rspeed >= 100)
    {
      Rspeed = 100;
    }
    else if (Rspeed <= -100)
    {
      Rspeed = -100;
    }
    Rspeed = Rtarget/Ltarget;


    if (fabs(angle_error) > angle_accuracy)
    {
      errortimer.clear();
    }
    if (fabs(Lerror) <= accuracy + 0.3 || fabs(Rerror) <= accuracy + 0.3)
    {
      count++;
    }
    else
      count = 0;
    if (fabs(Lspeed) < 70 && Lerror > 3)
    {
      if (Lspeed > 0)
      {
        Lspeed = 70;
      }
      else
      {
        Lspeed = -70;
      }
    }
    if (fabs(Rspeed) < 70 && Rerror > 3)
    {
      if (Rspeed > 0)
      {
        Rspeed = 70;
      }
      else
      {
        Rspeed = -70;
      }
    }
       
    drive(Lspeed, Rspeed, 10);
    Llast_error = Lerror;
    Rlast_error = Rerror;
    angle_last_error = angle_error;
    if (timer.time(vex::timeUnits::msec) >= timeLimit)
    {
      break;
    }
  }
} 


void MegaTag(){

}
void autonomous(void)
{
  float START_ANGLE;
  float HEADING;
  vex::thread(intakeControl);

  switch (AutonomousMode)
  { 
    case 0:
    Gyro.setRotation(0,deg);
    Intake.setVelocity(100,pct);
    Outake.setVelocity(100,pct);
    intakeState = 1;
    antler.open();
    inchDriveC2(49,2900,45,0,18,-90,19,-90);
    inchDriveC(20,1250,0.6,40);

    
    gyroTurnF(-90);
    inchDriveC(-36.5,1600,0.6,40);
    intakeState =1;
    DriveBrake();
    intakeState = 1;
    Outake_state = 1;
    wait(2000,msec);
    Outake_state = 0;
    antler.close();
    gyroTurnF(170);
    inchDriveC(18,1200,0.6,30);
    antler.open();
    gyroTurnF(-45);
    inchDriveC(-18,1100,0.6,30);
    clamp.open();
    wait(2000,msec);
    inchDriveO(37,1200,1,60);
    gyroTurnF(-90);
    inchDriveC(-17,1500,0.8,50);
    DriveBrake();










    



    
    //launch loader
    


    







    DriveBrake();
    // gyropivotRC(45,true);
    // DriveBrake();

    break;
    case 1:
    Intake.setVelocity(100,pct);
    Outake.setVelocity(100,pct);
    intakeState = 1;
    inchDriveC2(37,2100,45,0,14,45,30,45);
    DriveBrake();
    antler.open();
    lift.open();
    wait(200,msec);
    gyroTurnF(-80);
    inchDriveO(-28,700,1,60);
    gyropivotL(180,false,0.3,1000);
    // wait(200,msec);
    // inchDriveC(-15,900,1,40);
    // gyroTurnF(180);
    intakeState = 1;
    Outake_state = 1;
    wait(2000,msec);
    Outake_state = 0;
    gyroTurnF(180);

    inchDriveC(30,1200,0.6,50);
    DriveBrake();
    wait(1200,msec);
    inchDriveC(-10,1400,1,60);
    antler.close();
    gyroTurnF (-45);
    inchDriveC(14,800,1,60);
    gyropivotLC(0,true);
    inchDriveC(20,1000,1,60);
    gyroTurnF(-45);



    DriveBrake();
    break;
    case 2:
    Intake.setVelocity(100,pct);
    clamp.open();
    lift.open();
    intakeState = 1;
    inchDriveC2(48,2900,45,0,17,90,19,90);
    gyroTurnF(90);
    inchDriveC(-30,1200,0.6,40);
    Outake_state = 1;

    wait(900,msec);
    inchDriveC(5.3,800,1,0.6);
    gyropivotLC(-133.5,true,0.3,800);
    inchDriveC(33.2,2000,0.6,40);
    Outake_state = 0;
    inchDriveC(-8,1200,0.6,40);
    gyropivotL(180,false,0.5,600);
    clamp.close();
    inchDriveC(49,1850,0.7,50);
    clamp.open();
    gyroTurnF(135);
    intakeState = 0;
    inchDriveC(-19,1500,0.8,40);
    intakeState = 1;
    clamp.close();
    lift.close();
    DriveBrake();





    break;
    case 3:
    Intake.setVelocity(100,pct);
    antler.open();
    antler.open();
    intakeState = 1;
    inchDriveC2(49,2900,45,0,19,90,20,90);
    gyroTurnF(90,1,0.7);
    inchDriveC(-5,100,1,60);
    inchDriveC(7,250,1,60);
    DriveBrake();
    wait(1400,msec);
    inchDriveC(-14,1200,0.8,40);
  
    antler.close();
    gyroTurnF(-45);
    inchDriveO(28,900,0.8,40);
    gyroTurnF(-89);
    inchDriveO(65,3500,0.8,40,-90);
    gyroTurnF(180);
    inchDriveO(14,1000,0.4,40);
    gyroTurnF(-90);
    inchDriveC(-20,900,0.7,40);
    DriveBrake();
    Outake_state = 1;
    wait(3000,msec);
    Outake_state = 0;
    antler.open();
    gyroTurnF(-90,1,0.7);

    inchDriveC(47,1000,0.4,30);
    wait(1500,msec);
    gyroTurnF(-90);
    inchDriveC(-35,1500,0.6,40);
    DriveBrake();
    Outake_state = 1;
    wait(3000,msec);
    Outake_state = 0;
    inchDriveO(10,1500,0.8,40);
    gyroTurnF(180);

    inchDriveO(95,4000,0.8,70);
    gyroTurnF(-90);
    inchDriveC(32,1800,0.5,30);
    inchDriveC(8,250,1,60);
    inchDriveC(-5,100,1,60);
    inchDriveC(8,250,1,60);
    wait(700,msec);
    gyroTurnF(-90);
    inchDriveC(-10,2100,0.7,40);
    antler.close();
    gyroTurnF(135);
    inchDriveC(23,1000,0.6,40);
    gyroTurnF(91);

    inchDriveC(82,3500,0.8,30);
    gyroTurnF(0);
    inchDriveC(10 ,2000,0.7,40);
    gyroTurnF(90);
    inchDriveC(-28,1200,1,40);
    DriveBrake();
    Outake_state = 1;
    wait(2100,msec);
    gyroTurnF(90);
    Outake_state = 0;
    antler.open();
    inchDriveC(38,1000,0.5,40);
    wait(1500,msec);
    gyroTurnF(90);
    inchDriveC(-35,1500,0.6,40);
    Outake_state = 1;
    wait(2000,msec);
    Outake_state = 0;
    inchDriveO(13,1200,1,60);

    gyroTurnF(45);
    antler.close();
    inchDriveC(26,1000,1,60);
    gyroTurnF(10);
    inchDriveC(45,2200,0.7,65);
    DriveBrake();






    break;
    case 4:
    Intake.setVelocity(100,pct);
    intakeState = 1;
    inchDriveC2(45,2900,40,0,24,-45,16,-135);
    inchDriveC(-14,1500,0.8,50);
    DriveBrake();
    clamp.open();
    intakeState =0;
    intakeState = 1;
    Outake_state = -1;
    wait(1100,msec);
    Outake_state = 0;
    antler.open();
    clamp.close();

    inchDriveC2(80,2700,60,-135,37,-180,15,-180);
    wait(1400,msec);
    inchDriveC(-10,1100,0.8,40);
    antler.close();
    gyroTurnF(135);
    inchDriveC(-20,1200,0.8,40);
    gyroTurnF(180);
    inchDriveO(-74,2800,1,60);
    gyroTurnF(-20);
    inchDriveC(-25,1200,0.8,40);
    gyroTurnF(0);
    Outake_state = 1;
    wait(2500,msec);
    Outake_state = 0;
    inchDriveC(38,1200,0.8,40);
    wait(1200,msec);
    inchDriveC(-38,1400,1,60);
    Outake_state = 1;
    wait(2500,msec);
    Outake_state = 0;    

    

    break;
    case 5:
    Intake.setVelocity(100,pct);
    intakeState = 1;
    inchDriveC2(85,3500,75,0,20,-90,10,0);
    gyroTurnF(-100);
    inchDriveC(-45,1200,0.8,40);
    Outake_state =1;
    wait(1400,msec);
    Outake_state = 0;
    antler.open();
    inchDriveC(40,1500,0.6,40);
    wait(1500,msec);
    inchDriveC(-10,1000,1,60);
    break;
    case 6:
    break;
    case 7:

    inchDriveC(5,1500,1,0);
    DriveBrake();

    break;
    case 8:
//skills auton
    inchDriveO(24,1000,1,0);
    DriveBrake();
  }
}
void pre_auton(void)
{
  Gyro.setRotation(0,deg);
  drawGUI();
  Brain.Screen.pressed(selectAuton);
  vex::thread intakeThread(intakeControl);


    {
while (true) {
  liftControl();
 Brain.Screen.printAt(1, 20, "Gyro Rotation: %f", Gyro.rotation());
wait(10, msec);
} };
}
void usercontrol(void)
{

  Brain.Screen.clearScreen();
  Controller.Screen.clearScreen();
  Brain.Screen.setFillColor(yellow);
  wait(50, msec);
  Controller.Screen.setCursor(5, 0);
  Controller.Screen.print("MGO:OPEN");
  Controller.Screen.setCursor(1, 0);
  Controller.Screen.print("CLR:ON");


// Default Control Scheme
    // Call the function "Setup_UserControl".
    Setup_UserControl();

    driver_doinker();    //  vex::thread colorSortingThread(ColorSorting);
    Intake.setVelocity(100,pct);
    Outake.setVelocity(100,pct);
    //trollol lol 
    AIVision1.tagDetection(true);
    Controller.ButtonDown.pressed(LIFTWork);
    Controller.ButtonY.pressed(AntlerDEscore);  
    Controller.ButtonB.pressed(Align);  
    


    while (true)
    {
      // if(Controller.ButtonL1.pressing() == true){
      //   LeftArm.spin(fwd,100,pct);
      //   RightArm.spin(fwd,100,pct);
      // }
      // if(Controller.ButtonL2.pressing() == true){
      //   LeftArm.spin(reverse,100,pct);
      //   RightArm.spin(reverse,100,pct);
      // }

      liftControl();
      Drive_UserControl();
      Intake_UserControl();
      // std::cout << Gyro.heading() << std::endl;
  }
}

int main()
{
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
}