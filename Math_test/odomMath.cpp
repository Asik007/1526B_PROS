/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// #include "okapi/api/odometry/odomMath.hpp"
// #include "okapi/api/util/mathUtil.hpp"
#include <cmath>

float xDiff;
float yDiff

void computeDistanceToPoint(float X1, float X2, float State_X, float State_y) {
  auto [xDiff, yDiff] = computeDiffs(ipoint, istate);
  return computeDistance(xDiff, yDiff) * meter;
}

QAngle OdomMath::computeAngleToPoint(const Point &ipoint, const OdomState &istate) {
  const auto [xDiff, yDiff] = computeDiffs(ipoint, istate);
  return computeAngle(xDiff, yDiff, istate.theta.convert(radian)) * radian;
}

std::pair<QLength, QAngle> OdomMath::computeDistanceAndAngleToPoint(float X1, float Y1, float State_X, float State_Y) {
  computeDiffs();
  return std::make_pair(computeDistance(X1, Y1),
                        computeAngle());
}

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

// QAngle OdomMath::constrainAngle360(const QAngle &theta) {
//   return theta - 360_deg * std::floor(theta.convert(degree) / 360.0);
// }

// QAngle OdomMath::constrainAngle180(const QAngle &theta) {
//   return theta - 360_deg * std::floor((theta.convert(degree) + 180.0) / 360.0);
// }
// } // namespace okapi
