#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "type.h"
#include "tensor.h"

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