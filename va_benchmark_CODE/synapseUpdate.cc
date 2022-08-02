#include "definitionsInternal.h"
#include "supportCode.h"

extern "C" {
    void updatePresynapticKernel(float t);
}

void updateSynapses(float t) {
     {
        updatePresynapticKernel(t);
    }
}
