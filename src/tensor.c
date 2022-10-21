#include<stdio.h>
#include<stdlib.h>
#include "type.h"
///////////////////////
// 動態記憶體配置
///////////////////////
Vector* Array1d(uint32_t size) {
	// dynamic memory 1D-array
	Vector* arr = (Vector*) calloc(1, sizeof(Vector));
	arr->array = (double*)calloc(size, sizeof(double));
	arr->shape = size;
	return arr;
}

Vector* Zeros(uint32_t size){
	return Array1d(size);
}

Vector* Ones(uint32_t size, double value){
	Vector* arr = Array1d(size);
	for(uint32_t i=0;i<size;i++){
		arr->array[i] = value;
	}
	return arr;
}

///////////////////////
//顯示 Array 內容
///////////////////////
void ShowArray1d(Vector array) {
	// printf 1D-array
	printf("[");
	for (uint32_t i = 0; i < array.shape; i++) {
		printf("%f ", array.array[i]);
		if (i != (array.shape - 1)) {
			printf(",");
		}

	}
	printf("]");
}

///////////////////////
// 釋放記憶體
///////////////////////
void FreeVector(Vector* ptr) {
	free(ptr->array);
	free(ptr);
}

void FreeIndex(Index* ptr) {
	free(ptr->array);
	free(ptr);
}