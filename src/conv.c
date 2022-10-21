#include<stdlib.h>

#include "type.h"
#include "tensor.h"

// Convolution
Vector* Conv1d(Vector* arr, Vector* kernel, uint32_t step) {
	Vector* conv = conv = (Vector*)calloc(1, sizeof(Vector));;
	
	conv->shape = (uint32_t)(((double)arr->shape - (double)kernel->shape) / (double)step + 1.0);
	conv->array = (double*)calloc(conv->shape, sizeof(double));
	
	for (uint32_t i = 0, index=0; i < (arr->shape - kernel->shape + 1); i += step, index++) {
		for (uint32_t j = 0; j < kernel->shape; j++) {
			conv->array[index] += arr->array[i + j] * kernel->array[j];
		}
		conv->array[index] /= (double)kernel->shape;
	}
	return conv;
}