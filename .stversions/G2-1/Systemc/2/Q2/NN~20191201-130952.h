#include "systemc.h"

using namespace std;
SC_MODULE(NN)
{	
	public:
		sc_in<float> In1,In2;
		sc_out<float> O;
	NN (sc_module_name ,int w1 , int w2 , int b):sc_module(name),w1(w1),w2(w2),b(b){
		SC_METHOD(nn_calc);
		sensitive << In1 << In2;
	}

	private:
	void nn_calc();
	float sigmoid(float In1 , float In2);
	int w1 , w2 ,b;
		
};
