#include<stdlib.h>
#include<math.h>
#include "type.h"
#include "tensor.h"

//  Zero-Crossing
Index* ZeroCrossing(Vector* wave, uint32_t sampling_points_of_T){
	// return:  sampling points list of zero-crossing
	//// 增加除錯功能  assert sampling_points_of_T > 0,""
	// 初始
	Index* zeros = (Index*) calloc(1, sizeof(Index));
	zeros->shape = 0;
	uint32_t step = (uint32_t)(7 * sampling_points_of_T / 8);
	uint32_t final_index;
	// 補頭
	if (wave->array[0] < 1 && wave->array[0]>=0.0) {
		zeros->array = (uint32_t*)realloc(zeros->array, sizeof(uint32_t) * (++(zeros->shape)));
		zeros->array[zeros->shape - 1] = 0;
	}
	// zeroCrossing
	for (uint32_t i = 1; i < wave->shape; i++) {
		if (wave->array[i - 1] < 0 && wave->array[i] > 0) {
			// 
			zeros->array = (uint32_t*)realloc(zeros->array, sizeof(uint32_t) * (++(zeros->shape)));
			zeros->array[zeros->shape - 1] = i;
			final_index = i;

			i += step;
		}
	}
	// 補尾
	if (wave->array[wave->shape-1]<0 && (wave->shape-final_index)>step) {
		zeros->array = (uint32_t*)realloc(zeros->array, sizeof(uint32_t) * (++(zeros->shape)));
		zeros->array[zeros->shape - 1] = wave->shape-1;
	}

	return zeros;
}


//RMS
Vector* RMS(Vector* wave, Vector* base_wave, uint32_t sampling_points_of_T) {
	Index* zeros = ZeroCrossing(base_wave, sampling_points_of_T);
	Vector* rms = (Vector*)calloc(1, sizeof(Vector));
	rms->shape = 0;
	double temp = 0;
	uint32_t start, end;
	for (uint32_t i = 0; i < zeros->shape-1; i++) {

		temp = 0.0;
		start = zeros->array[i];
		end = (uint32_t)zeros->array[i+1];

		// Calculate RMS
		for (uint32_t j = start; j < end; j++) {
			temp += (wave->array[j] * wave->array[j]);
		}
		temp = sqrt(temp / (double)(end - start));

		// Record
		rms->array = (double*)realloc(rms->array, sizeof(double) * (++(rms->shape)));
		rms->array[rms->shape - 1] = temp;

	}

	FreeIndex(zeros); //釋放記憶體

	return rms;
}


void minMaxScaling(Vector* wave){
	
}