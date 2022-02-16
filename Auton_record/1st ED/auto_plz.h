#pragma once

int Curr_Encod[2];
int D_Encod[2];
int Prev_Encod[2] = {0,0};


/*
Scales:
    Wheel Size
    Wheel Ratio
    Wheel to Wheel Dist
    TPR
*/
float Scales[4] = {4.25, 1, 12, 360};

float Coord[3] = {0,0,0};


pros::ADIEncoder Left (1, 2, true);
pros::ADIEncoder Right (3, 4);



double pi = acos(0.0);
float circum = Scales[1] * 2 * pi;
float TPR = Scales[3] * Scales[1];

void tracking_task();
void raddeg();
void degrad();