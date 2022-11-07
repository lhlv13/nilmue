#ifndef __FEATURES_H__
#define __FEATURES_H__

#include "type.h"
Index* ZeroCrossing(Vector * wave, uint32_t sampling_points_of_T);
Vector* RMS(Vector* wave, Index* zeros);
Vector** PeakEnvelope(Vector* wave, Index* zeros);
Matrix* VItrajectory(Vector* V, Vector* I, uint32_t grid);
#endif