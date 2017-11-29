#include "constants.h"

template<int IN_WIDTH, int IN_HEIGHT, int IN_DEPTH, int POOL_SIZE> inline
void pooling_template(
		stream<DATA_TYPE[IN_DEPTH]> &input,
		stream<DATA_TYPE[IN_DEPTH]> &output)
{
	DATA_TYPE image_register[IN_DEPTH];
	DATA_TYPE max[IN_DEPTH];

	FOR_IMAGE_HEIGHT:for(int h=0;h<IN_HEIGHT;h++){
		FOR_IMAGE_WIDTH:for(int w=0;w<IN_WIDTH;w++){
			image_register = input.read();
			FOR_IMAGE_DEPTH:for(int d=0;d<IN_DEPTH;d++){
				FOR_POOL_HEIGHT:for(int ph=0;ph<POOL_SIZE;ph++){
					FOR_POOL_WIDTH:for(int pw=0;pw<POOL_SIZE;pw++){
						if(ph==0 && pw==0){
							max[d]=image_register[d];
						}
						else {
							if(max[d]<image_register[d]){
								max[d]=image_register[d];
							}
						}
						if(pw==POOL_SIZE-1 && ph==POOL_SIZE-1){
							output.write(max);
						}
					}
				}
			}
		}
	}
}
