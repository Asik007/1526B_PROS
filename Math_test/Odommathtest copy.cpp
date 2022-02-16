#include <stdio.h>
#include <iostream>
#include <math.h>
// #include ""


float Curr_Encod[2];
float D_Encod[2];
float D_val[4];

float Prev_Encod[2] = {0,0};


/*
Scales:
    Wheel Size
    Wheel Ratio
    Wheel to Wheel Dist
    TPR
*/
float Scales[4] = {4.25, 1, 6, 360};

float Coord[3] = {0,0,0};

double pi = 2*acos(0.0);
float circum = Scales[0] * pi;
float TPR = Scales[3] * Scales[1];
    //figure out how okapi does their scale stuff

// }
float degrad(float yup){
    return (yup * (pi/180));
}

float raddeg(float yup){
    return (yup / (pi/180));
}


void OdomMath(){
    std::cout << "started Calculations \n";
    D_val[0] = (D_Encod[0]/TPR)*circum;
    D_val[1] = (D_Encod[1]/TPR)*circum;
    D_val[2] = (D_Encod[0] - D_Encod[1])/(Scales[2]);
    float D_s = (D_val[0]+D_val[1])/2;

    std::cout << "D_val:    " << D_val[0] << "  "<< D_val[1] << "  "<< D_val[2] << "\n";

    
    
    Coord[0] += D_s * (cos(Coord[2] + ((D_val[1] - D_val[0])/(4 * Scales[2]))));
    Coord[1] += D_s * (sin(Coord[2] + ((D_val[1] - D_val[0])/(4 * Scales[2]))));
    Coord[2] += raddeg(D_val[1] - D_val[0])/(2 * Scales[2]);
    std::cout << "Coord: " << Coord[0] << " "<< Coord[1] << " " << Coord[2] <<"\n";
    
    

    
return;
}

#include <cmath>

float xDiff;
float yDiff;

float computedDist;
float computedAngle;

void computeDiffs(float X1, float Y1) {
  xDiff = (X1 - Coord[0]);
  yDiff = (Y1 - Coord[1]);
  return;
}

double computeDistance() {
  return std::sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

double computeAngle() {
  return std::atan2(yDiff, xDiff) - degrad(Coord[2]);
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

    TargetDistLeftT =degrad(target) * Scales[2];
    TargetDistRightT = -1 *degrad(target) * Scales[2];

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
int main(){

    std::cout << "origin X? \n";
    std::cin >> Coord[0];
    std::cout << "origin Y? \n";
    std::cin >> Coord[1];
    std::cout << "origin Theta? \n";
    std::cin >> Coord[2];
    while(true){
    std::cout << "Dest X? \n";
    std::cin >> pog;
    std::cout << "Dest Y? \n";
    std::cin >> pogy;
    computeDistanceAndAngleToPoint(pog, pogy);
    std::cout << "Distance and Angle: " << computedDist << ",    " << computedAngle << "\n";
    angletoDist(computedAngle);

    std::cout << "Computed distances for Turn: " << TargetDistLeftT << "  " << TargetDistRightT<< "\n";
    Disttotick();

    std::cout << "Computed ticks for Turn: " << TargetTicksLeftT << "  " << TargetTicksRightT<< "\n";
    DisttotickStr();
    std::cout << "Computed ticks for Str: " << TargetTicksLeftS << "  " << TargetTicksRightS<< "\n"; 

    }

// while(true){

//     // Curr_Encod[0] = Left.get_value();
//     // Curr_Encod[1] = Right.get_value();
// std::cout << "Left encoder?"
// std::cin >> Curr_Encod[0];
// std::cin >> Curr_Encod[1];

    
//     std::cout << "Curr_Encod: \n";
//     std::cout << "Left: " << Curr_Encod[0] << " Right:  " << Curr_Encod[1] << "\n";
//     std::cout << "Left: " << Curr_Encod[0] << " Right:  " << Curr_Encod[1] << "\n";



//     D_Encod[0] = Prev_Encod[0] - Curr_Encod[0];
//     D_Encod[1] = Prev_Encod[1] - Curr_Encod[1];
//     std::cout << "Prev_Encod: \n";
//     std::cout << "Left: " << Prev_Encod[0] << " Right:  " << Prev_Encod[1] << "\n";
//     std::cout << "D_Encod: \n";
//     std::cout << "Left: " << D_Encod[0] << " Right:  " << D_Encod[1] << "\n";
//     OdomMath();
//     // pros::delay(20);
//     Prev_Encod[0] = Curr_Encod[0];
//     Prev_Encod[1] = Curr_Encod[1];
//     }    return 1;
}



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

void drive(int left, int right){
  targetLeft = targetLeft + left;
  targetRight = targetRight + right;
  velCap = 0; //reset velocity cap for slew rate
}