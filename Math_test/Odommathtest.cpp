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
float Scales[4] = {4.25, 1, 12, 360};

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


// void OdomMath2(){
 
//  D_val[0] = D_Encod[0] / Scales[];
//  D_val[1] = itickDiff[1] / chassisScales.straight;

//   double deltaTheta = (D_val[0] - deltaR) / chassisScales.wheelTrack.convert(meter);
//   double localOffX, localOffY;

//   if (deltaTheta != 0) {
//     localOffX = 2 * std::sin(deltaTheta / 2) * chassisScales.middleWheelDistance.convert(meter);
//     localOffY = 2 * std::sin(deltaTheta / 2) *
//                 (deltaR / deltaTheta + chassisScales.wheelTrack.convert(meter) / 2);
//   } else {
//     localOffX = 0;
//     localOffY = deltaR;
//   }

//   double avgA = state.theta.convert(radian) + (deltaTheta / 2);

//   double polarR = std::sqrt(localOffX * localOffX + localOffY * localOffY);
//   double polarA = std::atan2(localOffY, localOffX) - avgA;

//   double dX = std::sin(polarA) * polarR;
//   double dY = std::cos(polarA) * polarR;

//   if (isnan(dX)) {
//     dX = 0;
//   }

//   if (isnan(dY)) {
//     dY = 0;
//   }

//   if (isnan(deltaTheta)) {
//     deltaTheta = 0;
//   }

//   return OdomState{dX * meter, dY * meter, deltaTheta * radian};


// }
void OdomMath(){
    std::cout << "started Calculations \n";
    D_val[0] = (D_Encod[0]/TPR)*circum;
    D_val[1] = (D_Encod[1]/TPR)*circum;
    D_val[2] = (D_Encod[0] - D_Encod[1])/(Scales[2]);

    std::cout << "D_val:    " << D_val[0] << "  "<< D_val[1] << "  "<< D_val[2] << "\n";
    
//   double deltaTheta = (deltaL - deltaR) / chassisScales.wheelTrack.convert(meter);
//   double localOffX, localOffY;

//   if (deltaTheta != 0) {
//     localOffX = 2 * std::sin(deltaTheta / 2) * chassisScales.middleWheelDistance.convert(meter);
//     localOffY = 2 * std::sin(deltaTheta / 2) *
//                 (deltaR / deltaTheta + chassisScales.wheelTrack.convert(meter) / 2);
//   } else {
//     localOffX = 0;
//     localOffY = deltaR;
//   }

//   double avgA = state.theta.convert(radian) + (deltaTheta / 2);

//   double polarR = std::sqrt(localOffX * localOffX + localOffY * localOffY);
//   double polarA = std::atan2(localOffY, localOffX) - avgA;

//   double dX = std::sin(polarA) * polarR;
//   double dY = std::cos(polarA) * polarR;

//   if (isnan(dX)) {
//     dX = 0;
//   }

//   if (isnan(dY)) {
//     dY = 0;
//   }

//   if (isnan(deltaTheta)) {
//     deltaTheta = 0;
//   }

//   return OdomState{dX * meter, dY * meter, deltaTheta * radian};
// }

    double radius_r = 0, radius_c = 0, h = 0, h2 = 0;  // rad for big circle
    double beta = 0, alpha = 0, theta = 0;
    double Xx = 0, Yy = 0, Xy = 0, Yx = 0;
    


    if (D_val[2] != 0) {
        std::cout << "is turning \n";
        radius_r = D_val[1] / D_val[2];
        std::cout << "radius_r"<<radius_r << "\n";
        beta = D_val[2] / 2.0;
        std::cout << "beta" << beta << "\n";
        h2 = (D_val[0]+D_val[1])/2;
        h = (D_val[0]+D_val[1])/2;


    } else {
      h = D_val[0];
      h2 = 0;
      beta = 0;
    }

    
    alpha = Coord[2] + beta;
        std::cout << "alpha" << alpha << "\n";
        std::cout << "h" << h << "\n";
        std::cout << "h2" << h2 << "\n";



    Xx = h2 * cos(alpha);
    Xy = h2 * -sin(alpha);
    Yx = h * sin(alpha);
    Yy = h * cos(alpha);

    std::cout <<"PRECORD    " << Xx << "    " << Xy << "    " << Yx << "    "<<  Yy << "\n";


    
    Coord[0] += Xx + Yx;
    Coord[1] += Xy + Yy;
    Coord[2] += theta;
    std::cout << "Coord: " << Coord[0] << " "<< Coord[1] << " " << Coord[2] <<"\n";
    
    

    
return;
}


int main(){
   std::cout << "left?";
    std::cin >> Curr_Encod[0];
    std::cout << "right?";
    std::cin >> Curr_Encod[1];
    // Curr_Encod[0] = Left.get_value();
    // Curr_Encod[1] = Right.get_value();

    D_Encod[0] = Curr_Encod[0] - Prev_Encod[0];
    D_Encod[1] = Curr_Encod[1] - Prev_Encod[1];

    // std::cout << "ODOM ON" << Curr_Encod[0] << "    " << Prev_Encod[0] << "    " << D_Encod[0] << "\n";

    OdomMath();
    // pros::delay(20);
    Prev_Encod[0] = Curr_Encod[0];
    Prev_Encod[1] = Curr_Encod[1];
    return 1;
}