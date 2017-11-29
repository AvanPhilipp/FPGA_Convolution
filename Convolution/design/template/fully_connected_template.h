#include "constants.h"

template<int IN_WIDTH, int IN_HEIGHT, int IN_DEPTH, int OUT_DEPTH> inline
void convolution_template(
		stream<DATA_TYPE[IN_DEPTH]> &input,
		stream<DATA_TYPE[OUT_DEPTH]> &output,
		stream<WEIGHT[IN_DEPTH]> &weight,
		stream<WEIGHT[IN_DEPTH]> &weight_forward,
		bool weight_load)
{
	const int IN_SIZE = IN_WIDTH*IN_HEIGHT;

	WEIGHT_TYPE weight_memory[IN_SIZE][IN_DEPTH][OUT_DEPTH];
	WEIGHT_TYPE bias[OUT_DEPTH];


	DATA_TYPE input_register[IN_DEPTH];
	DATA_TYPE output_register[OUT_DEPTH];


	if(weight_load){
		FOR_FEATURES:for(int o=0;o<OUT_DEPTH;o++){
			FOR_SIZE:for(int s=0;s<IN_SIZE;s++){
				FOR_DEPTH:for(int d=0;d<IN_DEPTH;d++){
					weight_memory[s][d][o] = weight.read();
				}
			}
			bias[o] = weight.read();
		}
		bool exit=false;
		while(!exit){
			WEIGHT temp_weight = weight.read();
			if(temp_weight.last) exit=true;
			weight_forward.write(temp_weight);
		}
	}

	FOR_SIZE:for(int s=0;s<IN_SIZE;s++){
		input_register = input.read();
			FOR_FEATURES:for(int o=0;o<OUT_DEPTH;o++){
				FOR_DEPTH:for(int d=0;d<IN_DEPTH;d++){
				if(s==0 && d==0){
					output_register[o] =bias[o] + input_register * weight_memory[s][d][o];
				}
				else{
					output_register[o] += input_register * weight_memory[s][d][o];
				}
			}
		}
		output.write(output_register);
	}
}

