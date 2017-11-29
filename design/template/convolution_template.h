#include "constants.h"

template<int IN_WIDTH, int IN_HEIGHT, int IN_DEPTH, int KERNEL_SIZE, int OUT_DEPTH> inline
void convolution_template(
		stream<DATA_TYPE[IN_DEPTH]> &input,
		stream<DATA_TYPE[OUT_DEPTH]> &output,
		stream<WEIGHT> &weight,
		stream<WEIGHT> &weight_forward,
		bool weight_load)
{
	WEIGHT_TYPE kernel[KERNEL_SIZE][KERNEL_SIZE][IN_DEPTH][OUT_DEPTH];
	WEIGHT_TYPE bias[OUT_DEPTH];

	DATA_TYPE input_register[IN_DEPTH];
	DATA_TYPE output_register[OUT_DEPTH];

	if(weight_load){
		FOR_KERNEL_OUT:for(int o=0;o<OUT_DEPTH;o++){
			FOR_KERNEL_HEIGHT:for(int kh=0;kh<KERNEL_SIZE;kh++){
				FOR_KERNEL_WIDTH:for(int kw=0;kw<KERNEL_SIZE;kw++){
					FOR_KERNEL_DEPTH:for(int d=0;d<IN_DEPTH;d++){
						kernel[kh][kw][d][o] = weight.read();
					}
				}
			}
			bias[o]=weight.read();
		}
		bool exit=false;
		while(!exit){
			WEIGHT temp_weight = weight.read();
			if(temp_weight.last) exit=true;
			weight_forward.write(temp_weight);
		}
	}


	FOR_IMAGE_HEIGHT:for(int h=0;h<IN_HEIGHT;h++){
		FOR_IMAGE_WIDTH:for(int w=0;w<IN_WIDTH;w++){
			input_register = input.read();
			FOR_IMAGE_DEPTH:for(int d=0;d<IN_DEPTH;d++){
				FOR_IMAGE_FEATURE:for(int o=0;o<OUT_DEPTH;o++){
					FOR_KERNEL_HEIGHT:for(int kh=0;kh<KERNEL_SIZE;kh++){
						FOR_KERNEL_WIDTH:for(int kw=0;kw<KERNEL_SIZE;kw++){
							if(kw==0 && kh==0 && d==0){
								output_register[o]=bias[o]+input_register[d]*kernel[kh][kw][d][o];
							}
							else{
								output_register[o]+=input_register[d]*kernel[kh][kw][d][o];
							}
						}
					}
				}
			}
			output.write(output_register);
		}
	}
}
