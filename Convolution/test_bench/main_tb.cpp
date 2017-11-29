#include <stdio.h>
#include "convolution_tb.h"
#include "pooling_tb.h"
#include "fully_connected_tb.h"

int main(){
//	printf("%s test done.\n",convolution_test().c_str()); // nem jó még
	printf("%s test done.\n",pooling_test().c_str()); // Nem csinál semmit
	printf("%s test done.\n",fully_connected_test().c_str()); // Nem csinál semmit
	return 0;
}
