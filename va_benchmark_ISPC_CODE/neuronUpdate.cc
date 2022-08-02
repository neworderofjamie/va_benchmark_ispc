#include "definitionsInternal.h"
#include "supportCode.h"

extern "C" {
    void neuronSpikeQueueUpdateKernel();
    void updateNeuronsKernel(float t, uint32_t recordingTimestep);
}

void updateNeurons(float t, unsigned int recordingTimestep) {
     {
        neuronSpikeQueueUpdateKernel();
    }
     {
        updateNeuronsKernel(t, recordingTimestep);
    }
}
