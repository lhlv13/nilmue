// dllmain.cpp : 定義 DLL 應用程式的進入點。
#include "pch.h"

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "type.h"
#include "nilmue.h"



///////////////////////
// 動態記憶體配置
///////////////////////
Vector* Array1d(uint32_t size) {
	// dynamic memory 1D-array
	Vector* arr = (Vector*)calloc(1, sizeof(Vector));
	arr->array = (double*)calloc(size, sizeof(double));
	arr->shape = size;
	return arr;
}

Vector* Zeros(uint32_t size) {
	return Array1d(size);
}

Vector* Ones(uint32_t size, double value) {
	Vector* arr = Array1d(size);
	uint32_t i;
	for (i = 0; i < size; i++) {
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
	uint32_t i;
	for (i = 0; i < array.shape; i++) {
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


double Max(Vector* wave) {
	double value = (wave->array[0]);
	uint32_t i;
	for (i = 0; i < wave->shape; i++) {
		value = (value < (wave->array[i])) ? (wave->array[i]) : value;
	}
	return value;
}


double Min(Vector* wave) {
	double value = (wave->array[0]);
	uint32_t i;
	for (i = 0; i < wave->shape; i++) {
		value = (value > (wave->array[i])) ? (wave->array[i]) : value;
	}
	return value;
}


Vector* MinMaxScaling(Vector* wave) {
	Vector* output = (Vector*)calloc(1, sizeof(Vector));
	output->array = (double*)calloc(wave->shape, sizeof(double));
	output->shape = wave->shape;

	double min = Min(wave);
	double max = Max(wave);
	double diff = max - min;
	uint32_t i;
	for (i = 0; i < wave->shape; i++) {
		output->array[i] = (wave->array[i] - min) / diff;
	}
	return output;
}

// Standard Sin Wave
Vector* Sin(double A, double frequency, double sampling_points_of_T, double seconds, double phi) {
	/*
		Input:
		---------
		A: 振幅
		frequency: 頻率
		sampling_points_of_T: 每周期取樣幾個點
		seconds: 波型持續幾秒
		phi: 相位

		Return:
		----------
		Vector*
	*/
	Vector* output = (Vector*)calloc(1, sizeof(Vector));
	double Ts, n;
	double* sin_wave = NULL;
	Ts = 1.0 / (frequency * sampling_points_of_T);
	n = seconds / Ts;  // 總採樣數
	sin_wave = (double*)calloc((uint32_t)floor(n), sizeof(double));
	uint32_t i;
	for (i = 0; i < n; i++) {
		sin_wave[i] = A * sin(2 * PI * frequency * (double)i * Ts + phi * PI / 180.0);
	}
	output->array = sin_wave;
	output->shape = n;

	return output;
}

Vector* Cos(double A, double frequency, double sampling_points_of_T, double seconds, double phi) {
	/*
		Input:
		---------
		A: 振幅
		frequency: 頻率
		sampling_points_of_T: 每周期取樣幾個點
		seconds: 波型持續幾秒
		phi: 相位

		Return:
		----------
		Vector*
	*/
	Vector* output = (Vector*)calloc(1, sizeof(Vector));
	double Ts, n;
	double* sin_wave = NULL;
	Ts = 1.0 / (frequency * sampling_points_of_T);
	n = seconds / Ts;  // 總採樣數
	sin_wave = (double*)calloc((uint32_t)floor(n), sizeof(double));
	uint32_t i;
	for (i = 0; i < n; i++) {
		sin_wave[i] = A * cos(2 * PI * frequency * (double)i * Ts + phi * PI / 180.0);
	}
	output->array = sin_wave;
	output->shape = n;

	return output;
}

// Convolution
Vector* Conv1d(Vector* arr, Vector* kernel, uint32_t step) {
	Vector* conv = conv = (Vector*)calloc(1, sizeof(Vector));;

	conv->shape = (uint32_t)(((double)arr->shape - (double)kernel->shape) / (double)step + 1.0);
	conv->array = (double*)calloc(conv->shape, sizeof(double));
	uint32_t i, j, index;
	for (i = 0, index = 0; i < (arr->shape - kernel->shape + 1); i += step, index++) {
		for (j = 0; j < kernel->shape; j++) {
			conv->array[index] += arr->array[i + j] * kernel->array[j];
		}
		conv->array[index] /= (double)kernel->shape;
	}
	return conv;
}

//  Zero-Crossing
Index* ZeroCrossing(Vector* wave, uint32_t sampling_points_of_T) {
	// return:  sampling points list of zero-crossing
	//// 增加除錯功能  assert sampling_points_of_T > 0,""
	// 初始
	Index* zeros = (Index*)calloc(1, sizeof(Index));
	zeros->shape = 0;
	uint32_t step = (uint32_t)(7 * sampling_points_of_T / 8);
	uint32_t final_index;
	// 補頭
	if (wave->array[0] < 1 && wave->array[0] >= 0.0) {
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
	if (wave->array[wave->shape - 1]<0 && (wave->shape - final_index)>step) {
		zeros->array = (uint32_t*)realloc(zeros->array, sizeof(uint32_t) * (++(zeros->shape)));
		zeros->array[zeros->shape - 1] = wave->shape - 1;
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
	for (i = 0; i < zeros->shape - 1; i++) {

		temp = 0.0;
		start = zeros->array[i];
		end = (uint32_t)zeros->array[i + 1];

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


// 峰值包絡線
Vector** PeakEnvelope(Vector* wave, Index* zeros) {
	Vector* up = (Vector*)calloc(1, sizeof(Vector));
	up->shape = 0;
	Vector* down = (Vector*)calloc(1, sizeof(Vector));
	down->shape = 0;

	double maxv, minv;
	maxv = wave->array[0];
	minv = wave->array[0];
	uint32_t start, end;
	uint32_t i, j;
	for (i = 0; i < (zeros->shape) - 1; i++) {
		start = zeros->array[i];
		end = zeros->array[i + 1];
		// 找 最大、最小值
		for (j = start; j < end; j++) {
			minv = (minv > (wave->array)[j]) ? (wave->array)[j] : minv;
			maxv = (maxv < (wave->array)[j]) ? (wave->array)[j] : maxv;
		}

		// 賦值
		up->array = (double*)realloc(up->array, sizeof(double) * (++(up->shape)));
		down->array = (double*)realloc(down->array, sizeof(double) * (++(down->shape)));
		up->array[(up->shape) - 1] = maxv;
		down->array[(down->shape) - 1] = minv;
	}


	// Return
	Vector** output = (Vector**)calloc(2, sizeof(Vector*));
	output[0] = up;
	output[1] = down;

	return output;
}


// V-I 軌跡
Matrix* VItrajectory(Vector* V, Vector* I, uint32_t grid) {
	if ((V->shape) != (I->shape)) {
		exit(1);
	}

	double grid_v;
	uint32_t row, col;
	////記憶體配置
	uint32_t i;
	double** vi = (double**)calloc(grid, sizeof(double*));
	for (i = 0; i < grid; i++) {
		vi[i] = (double*)calloc(grid, sizeof(double));
	}

	//歸一化
	Vector* mmv = MinMaxScaling(V);
	Vector* mmi = MinMaxScaling(I);

	////賦值
	grid_v = 1.0 / (double)(grid - 1);
	for (i = 0; i < (V->shape); i++) {
		row = mmi->array[i] / grid_v; // double > uint32 !!?
		col = mmv->array[i] / grid_v; // double > uint32 !!?

		vi[row][col] = 255;
	}


	FreeVector(mmv); //記憶體釋放
	FreeVector(mmi); //記憶體釋放



	// Return
	Matrix* output = (Matrix*)calloc(1, sizeof(Matrix));
	output->array = vi;
	output->w = grid;
	output->h = grid;
	return output;
}



// --------------------------------------------------------------
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

