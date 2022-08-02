#include "definitionsInternal.h"
struct MergedNeuronInitGroup0
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* V;
    scalar* RefracTime;
    float* inSynInSyn0;
    float* inSynInSyn1;
    unsigned int numNeurons;
    
}
;
struct MergedSynapseConnectivityInitGroup0
 {
    unsigned int* rowLength;
    uint32_t* ind;
    unsigned int rowStride;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    
}
;
struct MergedSynapseConnectivityInitGroup1
 {
    unsigned int* rowLength;
    uint32_t* ind;
    unsigned int rowStride;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    
}
;
static MergedNeuronInitGroup0 mergedNeuronInitGroup0[2];
void pushMergedNeuronInitGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* RefracTime, float* inSynInSyn0, float* inSynInSyn1, unsigned int numNeurons) {
    mergedNeuronInitGroup0[idx].spkCnt = spkCnt;
    mergedNeuronInitGroup0[idx].spk = spk;
    mergedNeuronInitGroup0[idx].V = V;
    mergedNeuronInitGroup0[idx].RefracTime = RefracTime;
    mergedNeuronInitGroup0[idx].inSynInSyn0 = inSynInSyn0;
    mergedNeuronInitGroup0[idx].inSynInSyn1 = inSynInSyn1;
    mergedNeuronInitGroup0[idx].numNeurons = numNeurons;
}
static MergedSynapseConnectivityInitGroup0 mergedSynapseConnectivityInitGroup0[2];
void pushMergedSynapseConnectivityInitGroup0ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons) {
    mergedSynapseConnectivityInitGroup0[idx].rowLength = rowLength;
    mergedSynapseConnectivityInitGroup0[idx].ind = ind;
    mergedSynapseConnectivityInitGroup0[idx].rowStride = rowStride;
    mergedSynapseConnectivityInitGroup0[idx].numSrcNeurons = numSrcNeurons;
    mergedSynapseConnectivityInitGroup0[idx].numTrgNeurons = numTrgNeurons;
}
static MergedSynapseConnectivityInitGroup1 mergedSynapseConnectivityInitGroup1[2];
void pushMergedSynapseConnectivityInitGroup1ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons) {
    mergedSynapseConnectivityInitGroup1[idx].rowLength = rowLength;
    mergedSynapseConnectivityInitGroup1[idx].ind = ind;
    mergedSynapseConnectivityInitGroup1[idx].rowStride = rowStride;
    mergedSynapseConnectivityInitGroup1[idx].numSrcNeurons = numSrcNeurons;
    mergedSynapseConnectivityInitGroup1[idx].numTrgNeurons = numTrgNeurons;
}
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
void initialize() {
    const auto initStart = std::chrono::high_resolution_clock::now();
    // ------------------------------------------------------------------------
    // Neuron groups
     {
        // merged neuron init group 0
        for(unsigned int g = 0; g < 2; g++) {
            const auto *group = &mergedNeuronInitGroup0[g]; 
            group->spkCnt[0] = 0;
            for (unsigned i = 0; i < (group->numNeurons); i++) {
                group->spk[i] = 0;
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    scalar initVal;
                    const scalar scale = (-5.00000000000000000e+01f) - (-6.00000000000000000e+01f);
                    initVal = (-6.00000000000000000e+01f) + (standardUniformDistribution(hostRNG) * scale);
                    group->V[i] = initVal;
                }
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    scalar initVal;
                    initVal = (0.00000000000000000e+00f);
                    group->RefracTime[i] = initVal;
                }
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    group->inSynInSyn0[i] = 0.000000000e+00f;
                }
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    group->inSynInSyn1[i] = 0.000000000e+00f;
                }
            }
            // current source variables
        }
    }
    // ------------------------------------------------------------------------
    // Synapse groups
    // ------------------------------------------------------------------------
    // Custom update groups
    // ------------------------------------------------------------------------
    // Custom WU update groups
    // ------------------------------------------------------------------------
    // Synapse sparse connectivity
     {
        // merged synapse connectivity init group 0
        for(unsigned int g = 0; g < 2; g++) {
            const auto *group = &mergedSynapseConnectivityInitGroup0[g]; 
            memset(group->rowLength, 0, group->numSrcNeurons * sizeof(unsigned int));
            for (unsigned int i = 0; i < group->numSrcNeurons; i++) {
                // Build sparse connectivity
                int prevJ = -1.00000000000000000e+00f;
                while(true) {
                    const scalar u = standardUniformDistribution(hostRNG);
                    prevJ += (1 + (int)(log(u) * (-9.49122158102990454e+00f)));
                    if(prevJ < group->numTrgNeurons) {
                       do {
                        const unsigned int idx = (i * group->rowStride) + group->rowLength[i];
                        group->ind[idx] = prevJ+0;
                        group->rowLength[i]++;
                    }
                    while(false);
                    }
                    else {
                       break;
                    }
                    
                }
            }
        }
    }
     {
        // merged synapse connectivity init group 1
        for(unsigned int g = 0; g < 2; g++) {
            const auto *group = &mergedSynapseConnectivityInitGroup1[g]; 
            memset(group->rowLength, 0, group->numSrcNeurons * sizeof(unsigned int));
            for (unsigned int i = 0; i < group->numSrcNeurons; i++) {
                // Build sparse connectivity
                int prevJ = -1.00000000000000000e+00f;
                while(true) {
                    int nextJ;
                    do {
                       const scalar u = standardUniformDistribution(hostRNG);
                       nextJ = prevJ + (1 + (int)(log(u) * (-9.49122158102990454e+00f)));
                    } while(nextJ == i);
                    prevJ = nextJ;
                    if(prevJ < group->numTrgNeurons) {
                       do {
                        const unsigned int idx = (i * group->rowStride) + group->rowLength[i];
                        group->ind[idx] = prevJ+0;
                        group->rowLength[i]++;
                    }
                    while(false);
                    }
                    else {
                       break;
                    }
                    
                }
            }
        }
    }
    initTime += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - initStart).count();
}

void initializeSparse() {
    const auto initSparseStart = std::chrono::high_resolution_clock::now();
    // ------------------------------------------------------------------------
    // Synapse groups with sparse connectivity
    // ------------------------------------------------------------------------
    // Custom sparse WU update groups
    initSparseTime += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - initSparseStart).count();
}
