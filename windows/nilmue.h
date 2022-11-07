#ifndef __NILM_H__
#define __NILM_H__


#ifdef __cplusplus
extern "C"
{
#endif
#include "type.h"
	__declspec(dllexport) Vector* Array1d(uint32_t size);
	__declspec(dllexport) Vector* Zeros(uint32_t size);
	__declspec(dllexport) Vector* Ones(uint32_t size, double value);
	__declspec(dllexport) void ShowArray1d(Vector array);
	__declspec(dllexport) void FreeVector(Vector* ptr);
	__declspec(dllexport) void FreeIndex(Index* ptr);
	__declspec(dllexport) double Max(Vector* wave);
	__declspec(dllexport) double Min(Vector* wave);
	__declspec(dllexport) Vector* MinMaxScaling(Vector* wave);
	__declspec(dllexport) Vector* Conv1d(Vector* arr, Vector* kernel, uint32_t step);
	__declspec(dllexport) Index* ZeroCrossing(Vector* wave, uint32_t sampling_points_of_T);
	__declspec(dllexport) Vector* RMS(Vector* wave, Index* zeros);
	__declspec(dllexport) Vector** PeakEnvelope(Vector* wave, Index* zeros);
	__declspec(dllexport) Matrix* VItrajectory(Vector* V, Vector* I, uint32_t grid);
	__declspec(dllexport) Vector* Sin(double A, double frequency, double sampling_points_of_T, double seconds, double phi);
	__declspec(dllexport) Vector* Cos(double A, double frequency, double sampling_points_of_T, double seconds, double phi);

#ifdef __cplusplus
}
#endif

#endif