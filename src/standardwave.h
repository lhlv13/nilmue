#ifndef __STANDARDWAVE_H__
#define __STANDARDWAVE_H__

#include "type.h"
Vector * Sin(double A, double frequency, double sampling_points_of_T, double seconds, double phi);
Vector * Cos(double A, double frequency, double sampling_points_of_T, double seconds, double phi);

#endif