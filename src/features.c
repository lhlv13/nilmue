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
	uint32_t i;
	for (i = 1; i < wave->shape; i++) {
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
Vector* RMS(Vector* wave, Index* zeros) {
	Vector* rms = (Vector*)calloc(1, sizeof(Vector));
	rms->shape = 0;
	double temp = 0;
	uint32_t start, end;
	uint32_t i;
	for (i = 0; i < zeros->shape-1; i++) {

		temp = 0.0;
		start = zeros->array[i];
		end = (uint32_t)zeros->array[i+1];

		// Calculate RMS
		uint32_t j;
		for (j = start; j < end; j++) {
			temp += (wave->array[j] * wave->array[j]);
		}
		temp = sqrt(temp / (double)(end - start));

		// Record
		rms->array = (double*)realloc(rms->array, sizeof(double) * (++(rms->shape)));
		rms->array[rms->shape - 1] = temp;

	}

	return rms;
}


Vector** PeakEnvelope(Vector* wave, Index* zeros){
	Vector* up = (Vector*) calloc(1, sizeof(Vector));
	up->shape = 0;
	Vector* down = (Vector*) calloc(1, sizeof(Vector));
	down->shape = 0;
	
	double maxv, minv;
	maxv = wave->array[0];
	minv = wave->array[0];
	uint32_t start, end;
	uint32_t i, j;
	for(i=0;i<(zeros->shape)-1;i++){
		start = zeros->array[i];
		end = zeros->array[i+1];
		// 找 最大、最小值
		for(j=start;j<end;j++){
			minv = (minv > (wave->array)[j])? (wave->array)[j] : minv;
			maxv = (maxv < (wave->array)[j]) ? (wave->array)[j] : maxv;
		}

		// 賦值
		up->array = (double*) realloc(up->array, sizeof(double)*(++(up->shape)));
		down->array = (double*) realloc(down->array, sizeof(double)*(++(down->shape)));
		up->array[(up->shape)-1] = maxv;
		down->array[(down->shape)-1] = minv;
	}
	
	
	// Return
	Vector** output = (Vector**) calloc(2, sizeof(Vector*));
	output[0] = up;
	output[1] = down;
	
	return output;
}


