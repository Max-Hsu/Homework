#include "NN.h"

float NN::sigmoid(float In1 , float In2){
	float x = In1*w1+In2*w2+b;
	return 0.5+0.25*x-x*x*x/48+x*x*x*x*x/480;
}
void NN::nn_calc()
{
	O = sigmoid(In1 , In2);
}
