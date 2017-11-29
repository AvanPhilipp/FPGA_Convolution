#include <hls_stream.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>

using namespace hls;

typedef short DATA_TYPE;
typedef short WEIGHT_TYPE;

struct WEIGHT{
	WEIGHT_TYPE value;
	ap_uint<1> last;
};
