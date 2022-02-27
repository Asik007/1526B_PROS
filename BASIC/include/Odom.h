#pragma once
#include "api.h"

// extern pros::ADIPort Left_enc;
// extern pros::ADIPort Right_enc;





/*
Scales:
    Wheel Size
    Wheel Ratio
    Wheel to Wheel Dist
    TPR
*/

extern float Coords[3];

extern double pi;
extern float circum;
extern float TPR;
extern float degrad(float yup);
extern float raddeg(float yup);


void OdomMath();

extern float xDiff;
extern float yDiff;

extern float computedDist;
extern float computedAngle;

void computeDiffs(float X1, float Y1);
extern double computeDistance();
extern double computeAngle();

extern double computeDistanceToPoint(float X1, float Y1);

extern float computeAngleToPoint(float X1, float Y1);
void computeDistanceAndAngleToPoint(float X1, float Y1);
void ResetEnc();

extern float TargetDistLeftT;
extern float TargetDistRightT;


extern float TargetTicksLeftT;
extern float TargetTicksRightT;

extern float TargetTicksLeftS;
extern float TargetTicksRightS;



void angletoDist(float target);
void Disttotick();
void DisttotickStr();