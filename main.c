#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "src/type.h"
#include "src/tensor.h"
#include "src/tool.h"
#include "src/conv.h"
#include "src/features.h"
#include "src/standardwave.h"


int main(int* argc, char** argv){
    Vector* sin = Sin(5, 60, 32, 1, 0);
	Vector* cos = Cos(5, 60, 32, 1, 0);
	//Vector* cos = Cos(10, 3, 3, 1, 0);
	//Vector* conv = Conv1d(sin, cos, 1);
	//double value = Min(sin);
    // ShowArray1d(*conv);
	//printf("%f",value);
	
	//Vector* minmax = MinMaxScaling(sin);
	//ShowArray1d(*minmax);
	
	Matrix* vi = VItrajectory(sin, cos, 10);
	uint32_t r, c;
	for(r=0;r<vi->h;r++){
		for(c=0;c<vi->w;c++){
			printf("%f, ", vi->array[r][c]);
		}
		printf("\n");
	}
	
	
    return 0;
}
