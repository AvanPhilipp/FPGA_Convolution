#include <stdio.h>
#include <fstream>
#include <stdexcept>

#include "../design/template/constants.h"

#define IMAGE_PATH "/home/kotfu/BSCThesis/data/t10k-images.idx3-ubyte"
#define LABEL_PATH "/home/kotfu/BSCThesis/data/t10k-labels.idx1-ubyte"
#define WEIGHT_PATH "/home/kotfu/BSCThesis/Weights/test_weights.wgt"

#define TEST_COUNT 10


int reverseBits(int n) {
//        n = (n >> 1) & 0x55555555 | (n << 1) & 0xaaaaaaaa;
//        n = (n >> 2) & 0x33333333 | (n << 2) & 0xcccccccc;
//        n = (n >> 4) & 0x0f0f0f0f | (n << 4) & 0xf0f0f0f0;
        n = (n >> 8) & 0x00ff00ff | (n << 8) & 0xff00ff00;
        n = (n >> 16) & 0x0000ffff | (n << 16) & 0xffff0000;
        return n;
}

void read_image(hls::stream< DATA_TYPE[1] > &input, int number_of_images=TEST_COUNT){
	printf("Reading image from %s\n", IMAGE_PATH);
	std::ifstream in_image(IMAGE_PATH);
	if(!in_image.is_open()) throw std::runtime_error("Image file failed to open");

	int magic;
	in_image.read((char*)&magic,sizeof(magic));
	magic = reverseBits(magic);
	if(magic != 2051) throw std::runtime_error("Invalid MNIST image file!");

	int image_counter;
	in_image.read((char*)&image_counter,sizeof(image_counter));
	image_counter = reverseBits(image_counter);

	int height;
	in_image.read((char*)&height,sizeof(height));
	height = reverseBits(height);

	int width;
	in_image.read((char*)&width,sizeof(width));
	width = reverseBits(width);

	unsigned char temp_value;
	DATA_TYPE value[1];
	for(int image_counter=0; image_counter<width;image_counter++){
		for(int w=0; w<width;w++){
			for(int h=0; h<height;h++){
				in_image >> temp_value;
				value[0]=temp_value;
				input.write(value);
			}
		}
	}
}

void read_weight(hls::stream<WEIGHT> &weight, int number_of_weights){
////	for(std::string line; std::getline(in_weights, line);){
//
//		float temp_weight;
//
//		std::sscanf( line.c_str(), "%f", &temp_weight );
//
//		My_Temlpate_Struct load;
//		load.weight = temp_weight*(1 << 15);
//		load.last = 0;
//
////		printf("Weight: %f, struct_weight: %d\n",temp_weight,load.weight);
//
//		templ.write(load);
//
////		printf("type: %s, value: %f\n", typeid(weight).name(),weight);
//
//	}
//
//	My_Temlpate_Struct load;
//	load.weight = 0;
//	load.last = 1;
//	templ.write(load);
////	printf("%d Weight loaded\n", i);


}

void convolution_test(){
	hls::stream< DATA_TYPE[1] > input("conv_test_input");
	hls::stream< DATA_TYPE[32] > output("conv_test_output");
	hls::stream<WEIGHT> &weight("conv_test_weight");
	hls::stream<WEIGHT> &weight_forward("conv_test_weight_forward");

	read_image(input,1);
	read_weight(weight, 28*28*1*32);

	convolution_template<28,28,1,3,32>(input,output,weight,weight_forward,true);

	for(int c=0;c<28*28;c++){
		output.read();
	}
	printf("Convolution test success.\n");
}


int main(){
	convolution_test();



	printf("%s test done.\n",pooling_test().c_str()); // Nem csinál semmit
	printf("%s test done.\n",fully_connected_test().c_str()); // Nem csinál semmit
	return 0;
}
