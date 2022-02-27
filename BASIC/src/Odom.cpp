#include <stdio.h>
#include <iostream>
#include <math.h>
#include "main.h"


#define StartX 0
#define StartY 0
#define StartT 0

// pros::ADIPor Left_enc(7, E_ADI_LEGACY_ENCODER);
// pros::ADIPort Right_enc(1, E_ADI_LEGACY_ENCODER);

pros::ADIEncoder Left_enc (7,8);
pros::ADIEncoder Right_enc (1,2);


float Curr_Encod_L;
float Curr_Encod_R;

float D_Encod_L;
float D_Encod_R;

float D_val[3];

float Prev_Encod_L = 0;
float Prev_Encod_R = 0;



/*
Scales:
    Wheel Size
    Wheel Ratio
    Wheel to Wheel Dist
    TPR
*/
  float WheelSize = 4.25;
  float Ratio = 1;
  float W2W_dist = 6; //realy the radius
  float TPR_raw = 360;

  float Coords[3] = {0,0,0};

  double pi = 2*acos(0.0);
  float circum = WheelSize * pi;
  float TPR = TPR_raw * Ratio;
float D_s;
float D_W;


float degrad(float yup){return (yup * (pi/180));}

float raddeg(float yup){return (yup / (pi/180));}

void ResetEnc(){
    Right_enc.reset();
    Left_enc.reset();
    pros::delay(200);
    return;
}


void OdomMath(){
    Coords[3] = StartX,StartY,StartT;




    while(true){
    // std::cout << "started Calculations \n";

    Curr_Encod_L = Left_enc.get_value();


    Curr_Encod_R = Right_enc.get_value();

    // std::cout << "Curr_Encod:   "<< Curr_Encod_L << " "<<Curr_Encod_R << "\n";



    D_Encod_L = Prev_Encod_L - Curr_Encod_L;
    D_Encod_R = Prev_Encod_R - Curr_Encod_R;

    std::cout << "D_Encod:   "<< D_Encod_L << " "<<D_Encod_R << "\n";


    D_val[0] = (D_Encod_L/TPR)*circum;
    D_val[1] = (D_Encod_R/TPR)*circum;
    // D_val[2] = (D_Encod_R - D_Encod_L)/(2*W2W_dist);
    D_s = (D_val[0]+D_val[1])/2;
    D_W = (D_val[1] - D_val[0])/(2*W2W_dist);

    // std::cout << "D_val:    " << D_val[0] << "  "<< D_val[1] << "  "<< D_val[2] << "\n";

    // Coords[0] += D_s * (cos(Coords[2] + ((D_val[1] - D_val[0])/(4 * W2W_dist))));
    // Coords[1] += D_s * (sin(Coords[2] + ((D_val[1] - D_val[0])/(4 * W2W_dist))));
// D_val and D_val[1] = distance that the left and right wheel have moved along
//  the ground

Coords[2] += D_W;

Coords[0] += D_s*cos(Coords[2]); 
Coords[1] += D_s*sin(Coords[2]); 





    
    // Coords[0] += D_s * (cos(Coords[2] + ((D_val[1] - D_val[0])/(4 * W2W_dist))));
    // Coords[1] += D_s * (sin(Coords[2] + ((D_val[1] - D_val[0])/(4 * W2W_dist))));
    // Coords[2] += (D_val[1] - D_val[0])/(2 * W2W_dist);
    std::cout << "Coords: " << Coords[0] << " "<< Coords[1] << " " << Coords[2] <<"\n";

    Prev_Encod_L = Curr_Encod_L;
    Prev_Encod_R = Curr_Encod_R;  

    pros::delay(50);  
    }

return;}

#include <cmath>

float xDiff;
float yDiff;

float computedDist;
float computedAngle;

void computeDiffs(float X1, float Y1) {
  xDiff = (X1 - Coords[0]);
  yDiff = (Y1 - Coords[1]);
  return;
}

double computeDistance() {
  return std::sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

double computeAngle() {
  return std::atan2(yDiff, xDiff) - degrad(Coords[2]);
}


double computeDistanceToPoint(float X1, float Y1) {
  computeDiffs(X1, Y1);
  return computeDistance();
}

float computeAngleToPoint(float X1, float Y1) {
    computeDiffs(X1, Y1);
  return computeAngle();
}

void computeDistanceAndAngleToPoint(float X1, float Y1) {
  computeDiffs(X1, Y1);
  computedDist = computeDistance();
  computedAngle = raddeg(computeAngle());
  return;
}

float TargetDistLeftT;
float TargetDistRightT;


float TargetTicksLeftT;
float TargetTicksRightT;

float TargetTicksLeftS;
float TargetTicksRightS;



void angletoDist(float target){

    TargetDistLeftT =degrad(target) * W2W_dist;
    TargetDistRightT = -1 *degrad(target) * W2W_dist;

    return;
}

void Disttotick(){
    TargetTicksLeftT = (TargetDistLeftT / circum) * TPR;
    TargetTicksRightT = (TargetDistRightT / circum) * TPR;
    return;
}

void DisttotickStr(){
  TargetTicksLeftS = (computedDist / circum) * TPR;
  TargetTicksRightS = (computedDist / circum) * TPR;
  return;
}

float pog;
float pogy;
// int main(){

//     std::cout << "origin X? \n";
//     std::cin >> Coords[0];
//     std::cout << "origin Y? \n";
//     std::cin >> Coords[1];
//     std::cout << "origin Theta? \n";
//     std::cin >> Coords[2];
//     while(true){
//     std::cout << "Dest X? \n";
//     std::cin >> pog;
//     std::cout << "Dest Y? \n";
//     std::cin >> pogy;
//     computeDistanceAndAngleToPoint(pog, pogy);
//     std::cout << "Distance and Angle: " << computedDist << ",    " << computedAngle << "\n";
//     angletoDist(computedAngle);

//     std::cout << "Computed distances for Turn: " << TargetDistLeftT << "  " << TargetDistRightT<< "\n";
//     Disttotick();

//     std::cout << "Computed ticks for Turn: " << TargetTicksLeftT << "  " << TargetTicksRightT<< "\n";
//     DisttotickStr();
//     std::cout << "Computed ticks for Str: " << TargetTicksLeftS << "  " << TargetTicksRightS<< "\n"; 

//     }

// while(true){

//     // Curr_Encod[0] = Left_enc.get_value();
//     // Curr_Encod[1] = Right_enc.get_value();
// std::cout << "Left_enc encoder?"
// std::cin >> Curr_Encod[0];
// std::cin >> Curr_Encod[1];

    
//     std::cout << "Curr_Encod: \n";
//     std::cout << "Left_enc: " << Curr_Encod[0] << " Right_enc:  " << Curr_Encod[1] << "\n";
//     std::cout << "Left_enc: " << Curr_Encod[0] << " Right_enc:  " << Curr_Encod[1] << "\n";



//     D_Encod[0] = Prev_Encod[0] - Curr_Encod[0];
//     D_Encod[1] = Prev_Encod[1] - Curr_Encod[1];
//     std::cout << "Prev_Encod: \n";
//     std::cout << "Left_enc: " << Prev_Encod[0] << " Right_enc:  " << Prev_Encod[1] << "\n";
//     std::cout << "D_Encod: \n";
//     std::cout << "Left_enc: " << D_Encod[0] << " Right_enc:  " << D_Encod[1] << "\n";
//     OdomMath();
//     // pros::delay(20);
//     Prev_Encod[0] = Curr_Encod[0];
//     Prev_Encod[1] = Curr_Encod[1];
//     }    return 1;
// }



int velCap; //velCap limits the change in velocity and must be global
int targetLeft;
int targetRight;
/*
void drivePIDFn(void*){
  leftFrontDrive.tare_position(); //reset base encoders
  rightFrontDrive.tare_position();
  int errorLeft;
  int errorRight;
  float kp = 0.075;
  float kpTurn = 0.2;
  int acc = 5;
  int voltageLeft = 0;
  int voltageRight = 0;
  int signLeft;
  int signRight;
  delay(20);
  while(isAuton){
    errorLeft = targetLeft - leftFrontDrive.get_position(); //error is target minus actual value
    errorRight = targetRight - rightFrontDrive.get_position();

    signLeft = errorLeft / abs(errorLeft); // + or - 1
    signRight = errorRight / abs(errorRight);

    if(signLeft == signRight){
      voltageLeft = errorLeft * kp; //intended voltage is error times constant
      voltageRight = errorRight * kp;
    }
    else{
      voltageLeft = errorLeft * kpTurn; //same logic with different turn value
      voltageRight = errorRight * kpTurn;
    }

    velCap = velCap + acc;  //slew rate
    if(velCap > 115){
      velCap = 115; //velCap cannot exceed 115
    }

    if(abs(voltageLeft) > velCap){ //limit the voltage
      voltageLeft = velCap * signLeft;
    }

    if(abs(voltageRight) > velCap){ //ditto
      voltageRight = velCap * signRight;
    }

    leftBackDrive.move(voltageLeft); //set the motors to the intended speed
    leftFrontDrive.move(voltageLeft);
    rightBackDrive.move(voltageRight);
    rightFrontDrive.move(voltageRight);

    delay(20);
  }
}
*/

// void drive(int left, int right){
//   targetLeft = targetLeft + left;
//   targetRight = targetRight + right;
//   velCap = 0; //reset velocity cap for slew rate
// }