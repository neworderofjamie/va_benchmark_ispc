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

struct MergedNeuronUpdateGroup0
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* V;
    scalar* RefracTime;
    float* inSynInSyn0;
    float* inSynInSyn1;
    uint32_t* recordSpk;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronSpikeQueueUpdateGroup0
 {
    unsigned int* spkCnt;
    
}
;
static uniform MergedNeuronUpdateGroup0 mergedNeuronUpdateGroup0[2];
export void pushMergedNeuronUpdateGroup0ToDevice(uniform unsigned int idx, unsigned int* uniform spkCnt, unsigned int* uniform spk, scalar* uniform V, scalar* uniform RefracTime, float* uniform inSynInSyn0, float* uniform inSynInSyn1, uint32_t* uniform recordSpk, uniform unsigned int numNeurons) {
    mergedNeuronUpdateGroup0[idx].spkCnt = spkCnt;
    mergedNeuronUpdateGroup0[idx].spk = spk;
    mergedNeuronUpdateGroup0[idx].V = V;
    mergedNeuronUpdateGroup0[idx].RefracTime = RefracTime;
    mergedNeuronUpdateGroup0[idx].inSynInSyn0 = inSynInSyn0;
    mergedNeuronUpdateGroup0[idx].inSynInSyn1 = inSynInSyn1;
    mergedNeuronUpdateGroup0[idx].recordSpk = recordSpk;
    mergedNeuronUpdateGroup0[idx].numNeurons = numNeurons;
}
static uniform MergedNeuronSpikeQueueUpdateGroup0 mergedNeuronSpikeQueueUpdateGroup0[2];
export void pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(uniform unsigned int idx, unsigned int* uniform spkCnt) {
    mergedNeuronSpikeQueueUpdateGroup0[idx].spkCnt = spkCnt;
}

// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
export void pushMergedNeuronUpdate0recordSpkToDevice(uniform unsigned int idx, uint32_t* uniform value) {
    mergedNeuronUpdateGroup0[idx].recordSpk = value;
}

export void neuronSpikeQueueUpdateKernel() {
	// merged0
    foreach (id = 0 ... 2) {
        MergedNeuronSpikeQueueUpdateGroup0 *group = &mergedNeuronSpikeQueueUpdateGroup0[id]; 
        group->spkCnt[0] = 0;
    }
}

export void updateNeuronsKernel(uniform float t, uniform unsigned int recordingTimestep)
 {
	// merged0
	// Loop through groups
	for(uniform unsigned int g = 0; g < 2; g++) {
		const MergedNeuronUpdateGroup0* uniform group = &mergedNeuronUpdateGroup0[g]; 
		foreach (lid = 0 ... group->numNeurons) {
			scalar lV = group->V[lid];
			scalar lRefracTime = group->RefracTime[lid];
			
			float Isyn = 0;
			 {
				// pull inSyn values in a coalesced access
				float linSyn = group->inSynInSyn0[lid];
				Isyn += (9.51625819640404824e-01f) * linSyn;
				linSyn *= (9.04837418035959518e-01f);
				group->inSynInSyn0[lid] = linSyn;
			}
			 {
				// pull inSyn values in a coalesced access
				float linSyn = group->inSynInSyn1[lid];
				Isyn += (9.06346234610090895e-01f) * linSyn;
				linSyn *= (8.18730753077981821e-01f);
				group->inSynInSyn1[lid] = linSyn;
			}
			// test whether spike condition was fulfilled previously
			// calculate membrane potential
			if (lRefracTime <= 0.0f) {
			  scalar alpha = ((Isyn + (0.00000000000000000e+00f)) * (2.00000000000000000e+01f)) + (-4.90000000000000000e+01f);
			  lV = alpha - ((9.51229424500714016e-01f) * (alpha - lV));
			}
			else {
			  lRefracTime -= DT;
			}
			
			// test for and register a true spike
			const bool spike = (lRefracTime <= 0.0f && lV >= (-5.00000000000000000e+01f));
			if (spike) {
				const unsigned int word = lid / 32;
				const unsigned int bit = lid % 32;
				uniform const unsigned int numRecordingWords = (group->numNeurons + 31) / 32;
				atomic_or_global(&group->recordSpk[(recordingTimestep * numRecordingWords * 1) + word], 1 << bit);

				// spike reset code
				lV = (-6.00000000000000000e+01f);
				lRefracTime = (5.00000000000000000e+00f);
			}
			
			
			const unsigned int spikeOffset = exclusive_scan_add(spike ? 1 : 0);
			if(spike) {
				group->spk[spikeOffset] = lid;
			}
			
			uniform const unsigned int spikeCount = reduce_add(spike ? 1 : 0);
			if(programIndex == 0) {
				group->spkCnt[0] = spikeCount;
			}
			
			group->V[lid] = lV;
			group->RefracTime[lid] = lRefracTime;
		}
    }
}