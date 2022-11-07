#include<stdlib.h>

#include "type.h"
#include "tensor.h"

double Max(Vector* wave){
	double value=(wave->array[0]); 
	uint32_t i;
	for(i=0;i<wave->shape;i++){
		value = (value < (wave->array[i])) ? (wave->array[i]) : value;
	}
	return value;
}


double Min(Vector* wave){
	double value=(wave->array[0]); 
	uint32_t i;
	for(i=0;i<wave->shape;i++){
		value = (value > (wave->array[i])) ? (wave->array[i]) : value;
	}
	return value;
}


Vector* MinMaxScaling(Vector* wave){
	Vector* output = (Vector*) calloc(1, sizeof(Vector));
	output->array = (double*) calloc(wave->shape, sizeof(double));
	output->shape = wave->shape;
	
	double min = Min(wave);
	double max = Max(wave);
	double diff = max - min;
	uint32_t i;
	for(i=0;i<wave->shape;i++){
		output->array[i] = (wave->array[i] - min) / diff;
	}
	return output;
}