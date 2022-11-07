#ifndef __TYPE_H__
#define __TYPE_H__
#define PI 3.1415926
typedef unsigned int uint32_t;

typedef struct{
	uint32_t* array;
	uint32_t shape;
}Index;

typedef struct {
	double* array;
	uint32_t shape;
}Vector;

typedef struct {
	double** array;
	uint32_t w;
	uint32_t h;
}Matrix;

#endif

