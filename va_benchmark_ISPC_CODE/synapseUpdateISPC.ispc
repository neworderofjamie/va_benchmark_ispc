#define DT 1.00000000000000000e+00f
typedef float scalar;
#define SCALAR_MIN 1.175494351e-38f
#define SCALAR_MAX 3.402823466e+38f

#define TIME_MIN 1.175494351e-38f
#define TIME_MAX 3.402823466e+38f

typedef uint8 uint8_t;
typedef uint16 uint16_t;
typedef uint32 uint32_t;
typedef uint64 uint64_t;
typedef int8 int8_t;
typedef int16 int16_t;
typedef int32 int32_t;
typedef int64 int64_t;

struct MergedPresynapticUpdateGroup0
 {
    float* inSyn;
    unsigned int* srcSpkCnt;
    unsigned int* srcSpk;
    unsigned int* rowLength;
    uint32_t* ind;
    unsigned int rowStride;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    scalar g;
    
}
;
static uniform MergedPresynapticUpdateGroup0 mergedPresynapticUpdateGroup0[4];
export void pushMergedPresynapticUpdateGroup0ToDevice(uniform unsigned int idx, float* uniform inSyn, unsigned int* uniform srcSpkCnt, unsigned int* uniform srcSpk, unsigned int* uniform rowLength, uint32_t* uniform ind, uniform unsigned int rowStride, uniform unsigned int numSrcNeurons, uniform unsigned int numTrgNeurons, uniform scalar g) {
    mergedPresynapticUpdateGroup0[idx].inSyn = inSyn;
    mergedPresynapticUpdateGroup0[idx].srcSpkCnt = srcSpkCnt;
    mergedPresynapticUpdateGroup0[idx].srcSpk = srcSpk;
    mergedPresynapticUpdateGroup0[idx].rowLength = rowLength;
    mergedPresynapticUpdateGroup0[idx].ind = ind;
    mergedPresynapticUpdateGroup0[idx].rowStride = rowStride;
    mergedPresynapticUpdateGroup0[idx].numSrcNeurons = numSrcNeurons;
    mergedPresynapticUpdateGroup0[idx].numTrgNeurons = numTrgNeurons;
    mergedPresynapticUpdateGroup0[idx].g = g;
}
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
export void updatePresynapticKernel(uniform float t)
{
	// merged presynaptic update group 0
	for(uniform unsigned int g = 0; g < 4; g++) {
		const MergedPresynapticUpdateGroup0* uniform group = &mergedPresynapticUpdateGroup0[g]; 
		foreach (lid = 0 ... group->rowStride) {
			// loop through all incoming spikes
			for (uniform unsigned int j = 0; j < group->srcSpkCnt[0]; j++) {
				uniform const unsigned int idPre = group->srcSpk[j];
				if (lid < group->rowLength[idPre]) {
					const unsigned int synAddress = (idPre * group->rowStride) + lid;
					const unsigned int ipost = group->ind[synAddress];
					//atomic_add_global(&group->inSyn[ipost], (varying scalar)group->g);
					group->inSyn[ipost] += group->g;
				}
			}
		}
    }
}