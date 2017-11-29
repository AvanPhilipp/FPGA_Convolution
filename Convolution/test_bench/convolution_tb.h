#include <stdio.h>
#include <string>

#include "../design/template/constants.h"
#include "convolution_tb.h"

std::string convolution_test(){

	stream<DATA_TYPE[1]> input("conv_test_input");
#pragma HLS RESOURCE variable=input core=FIFO_SRL
#pragma HLS STREAM variable=input depth=1 dim=1

	stream<DATA_TYPE[32]> output("conv_test_output");
#pragma HLS RESOURCE variable=output core=FIFO_SRL
#pragma HLS STREAM variable=output depth=32 dim=1

	stream<WEIGHT> weight("conv_test_weight");
#pragma HLS RESOURCE variable=weight core=FIFO_SRL

	stream<WEIGHT> weight_forward("conv_test_forward");
#pragma HLS RESOURCE variable=weight_forward core=FIFO_SRL



	convolution_template<28,28,1,3,32>(input,output,weight,weight_forward,true);

	return "Convolution";
}
