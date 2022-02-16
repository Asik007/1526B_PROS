#include <vex.h>
#include "Constants.h"
#include "Variables.h"
using namespace vex;


//multiuse functions

//These first 2 allow for me to freely go between radians and degrees

float degrad(int pog){return pog * (pi/180);}
float raddeg(int pog){return pog * (180/pi);}

//This was my clunky first implementation to calculate the angle to a point with global orientations (I.E. north is 0degrees)
void calc(float x, float y, float x1, float y1){
  float dist = sqrt(((x1-x)*(x1-x)) + ((y1-y)*(y1-y)));
  float rot = atan((y1-y)/(x1-x));
  if(x<=x1 && y<=y1){rot = 90-raddeg(atan((y1-y)/(x1-x)));}
    else if(x<=x1 && y>=y1){rot = 180-raddeg(atan((y1-y)/(x1-x)));}
      else if(x>=x1 && y>=y1){rot = 270-raddeg(atan((y1-y)/(x1-x)));}
        else if(x>=x1 && y>=y1){rot = 360-raddeg(atan((y1-y)/(x1-x)));}
  Rotrot = rot;
  Rotdist = dist;
}



//The task that would track the position of the bot
void track(void){
  Encod[0] = Left.rotation(rotationUnits::raw)/Left_tick; 
  Encod[1] = Right.rotation(rotationUnits::raw)/Right_tick; 
  Brain.Screen.print("POGCHAMP");
  Left.setPosition(0,rotationUnits::raw);
  Right.setPosition(0,rotationUnits::raw); 
}


//Getting how much the encoder values changed
void getDelta(void){
  std::fill_n(Delta, 4, 0);
  Delta[0] = (Encod[0] + Encod[1]/2);
  Delta[3] = (Encod[0] + Encod[1])/(2*cent_dist);
  Delta[1] = Delta[0] * cos(Delta[3]/2);
  Delta[2] = Delta[0] * sin(Delta[3]/2);
}

//This is the main math for the encoders
void odometry(void){
  track();
  getDelta();
  for (int i = 0; i < 4; i++) {
    Pos[i] = Prev_Pos[i] + Delta[i];
  }
  for (int i = 0; i < 4; i++) {
    Prev_Pos[i] = Pos[i];
  }
}


//Function to control the front lift
void frt_lift(int POO){
  if(POO == 1){
    Claw.rotateFor(fwd, 90, degrees);
    Lift.rotateFor(fwd, 180, degrees);
  }
  else if (POO == 2) {
  Lift.rotateFor(reverse, 170, degrees);
  Claw.rotateFor(reverse,90, degrees);
  }
}

//Function to control the Back lift

void bak_lift(int POO){
  if(POO == 1){
    Back_Lift.rotateFor(fwd, 90, degrees);
  }
  else if (POO == 2) {
    Back_Lift.rotateFor(fwd, 90, degrees);
  }
}
