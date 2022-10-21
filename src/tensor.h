#ifndef __TENSOR_H__
#define __TENSOR_H__
#include "type.h"
Vector * Array1d(uint32_t size);
Vector* Zeros(uint32_t size);
Vector* Ones(uint32_t size, double value);
void ShowArray1d(Vector array);
void FreeVector(Vector* ptr);
void FreeIndex(Index* ptr);
#endif