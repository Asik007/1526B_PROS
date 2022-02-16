#include "main.h"
// #include ""



//Initializing the left and right encoders
pros::ADIEncoder Left (1, 2, true);
pros::ADIEncoder Right (3, 4);


// the value of encoders at the given time
float Curr_Encod[2];


//the Delta (change in value) of the encoders
float D_Encod[2];

//the Delta value from the encoders converted into inches
float D_val[3];

//the previous value of the encoders
float Prev_Encod[2] = {0,0};

/*
Scales:
    Wheel Size
    Wheel Ratio
    Wheel to Wheel Dist / 2
    TPR (Ticks per Revolution of the Encoders)
*/
float Scales[4] = {4.25, 1, 6, 360};

//The Coordinates of the Bot
float Coord[3] = {0,0,0};



double pi = 2*acos(0.0);


float circum = Scales[0] * pi;


float TPR = Scales[3] * Scales[1];

//Function to convert Degrees to Radians
float degrad(float yup){
    return (yup * (pi/180));
}

//Function to convert Radians to Degrees
float raddeg(float yup){
    return (yup / (pi/180));
}


#include <cmath>

//This marks the beginning of variables used for calculating how far the robot has to go and where

//The difference for X & Y between the Bot and a certain point
float xDiff;
float yDiff;

//The computed distance and angle that the bot has to turn to and run for
float computedDist;
float computedAngle;

//The target Distance the encoders have to rotate till
float TargetDistLeft;
float TargetDistRight;

//The target tick value that the encoders must reach
float TargetTicksLeft;
float TargetTicksRight;


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

void angletoDist(float target){
    TargetDistLeft = degrad(target) * Scales[2];
    TargetDistRight = degrad(target) * Scales[2];

    return;
}

void Disttotick(){
    TargetTicksLeft = (TargetDistLeft / circum) * TPR;
    TargetTicksRight = (TargetDistRight / circum) * TPR;
    return;
}


void OdomMath(){
    std::cout << "started Calculations \n";
    
    //This is the main math of Odom

    // Note: 
    // index[0] = an X val
    // index[1] = a Y val
    // index[2] = a theta value 
    
    D_val[0] = (D_Encod[0]/TPR)*circum;
    D_val[1] = (D_Encod[1]/TPR)*circum;
    D_val[2] = (D_Encod[0] - D_Encod[1])/(Scales[2]);
    float D_s = (D_val[0]+D_val[1])/2;

    std::cout << "D_val:    " << D_val[0] << "  "<< D_val[1] << "  "<< D_val[2] << "\n";

    
    
    Coord[0] += D_s * (cos(Coord[2] + ((D_val[1] - D_val[0])/(4 * Scales[2]))));
    Coord[1] += D_s * (sin(Coord[2] + ((D_val[1] - D_val[0])/(4 * Scales[2]))));
    Coord[2] += raddeg((D_val[1] - D_val[0])/(2 * Scales[2]));
    std::cout << "Coord: " << Coord[0] << " "<< Coord[1] << " " << Coord[2] <<"\n";
    
    

    
return;
}


//This is just from my original test environment to calculate odometry data

// void tracking_task(){
//    std::cout << "left?";
//     std::cin >> Curr_Encod[0];
//     std::cout << "right?";
//     std::cin >> Curr_Encod[1];
//     // Curr_Encod[0] = Left.get_value();
//     // Curr_Encod[1] = Right.get_value();

//     D_Encod[0] = Curr_Encod[0] - Prev_Encod[0];
//     D_Encod[1] = Curr_Encod[1] - Prev_Encod[1];

//     // std::cout << "ODOM ON" << Curr_Encod[0] << "    " << Prev_Encod[0] << "    " << D_Encod[0] << "\n";

//     OdomMath();
//     // pros::delay(20);
//     Prev_Encod[0] = Curr_Encod[0];
//     Prev_Encod[1] = Curr_Encod[1];
//     return;
// }



//This is the task that is run for the odometry to work and it is ran every 20 ms
void tracking_task(){
    Left.reset();
    Right.reset();
    while(true){

    Curr_Encod[0] = Left.get_value();
    Curr_Encod[1] = Right.get_value();

    
    std::cout << "Curr_Encod: \n";
    std::cout << "Left: " << Curr_Encod[0] << " Right:  " << Curr_Encod[1] << "\n";
    // std::cout << "Left: " << Curr_Encod[0] << " Right:  " << Curr_Encod[1] << "\n";



    D_Encod[0] = Prev_Encod[0] - Curr_Encod[0];
    D_Encod[1] = Prev_Encod[1] - Curr_Encod[1];
    std::cout << "Prev_Encod: \n";
    std::cout << "LeftPE: " << Prev_Encod[0] << " RightPE:  " << Prev_Encod[1] << "\n";
    std::cout << "D_Encod: \n";
    std::cout << "LeftDE: " << D_Encod[0] << " RightDE:  " << D_Encod[1] << "\n";
    OdomMath();
    pros::delay(20);
    Prev_Encod[0] = Curr_Encod[0];
    Prev_Encod[1] = Curr_Encod[1];
    }
}