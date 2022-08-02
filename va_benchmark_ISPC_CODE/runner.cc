#include "definitionsInternal.h"

std::uniform_real_distribution<float> standardUniformDistribution(0.000000000e+00f, 1.000000000e+00f);
std::normal_distribution<float> standardNormalDistribution(0.000000000e+00f, 1.000000000e+00f);
std::exponential_distribution<float> standardExponentialDistribution(1.000000000e+00f);


extern "C" {
// ------------------------------------------------------------------------
// global variables
// ------------------------------------------------------------------------
unsigned long long iT;
float t;
unsigned long long numRecordingTimesteps = 0;
std::mt19937 hostRNG;

// ------------------------------------------------------------------------
// timers
// ------------------------------------------------------------------------
double initTime = 0.0;
double initSparseTime = 0.0;
double neuronUpdateTime = 0.0;
double presynapticUpdateTime = 0.0;
double postsynapticUpdateTime = 0.0;
double synapseDynamicsTime = 0.0;

// ------------------------------------------------------------------------
// merged group arrays
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// local neuron groups
// ------------------------------------------------------------------------
unsigned int* glbSpkCntE;
unsigned int* glbSpkE;
uint32_t* recordSpkE;
scalar* VE;
scalar* RefracTimeE;
unsigned int* glbSpkCntI;
unsigned int* glbSpkI;
uint32_t* recordSpkI;
scalar* VI;
scalar* RefracTimeI;

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// pre and postsynaptic variables
// ------------------------------------------------------------------------
float* inSynIE;
float* inSynEE;
float* inSynII;
float* inSynEI;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------
const unsigned int maxRowLengthEE = 415;
unsigned int* rowLengthEE;
uint32_t* indEE;
const unsigned int maxRowLengthEI = 129;
unsigned int* rowLengthEI;
uint32_t* indEI;
const unsigned int maxRowLengthIE = 411;
unsigned int* rowLengthIE;
uint32_t* indIE;
const unsigned int maxRowLengthII = 127;
unsigned int* rowLengthII;
uint32_t* indII;

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------

}  // extern "C"
// ------------------------------------------------------------------------
// extra global params
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// copying things to device
// ------------------------------------------------------------------------
void pushEStateToDevice(bool uninitialisedOnly) {
}

void pushIStateToDevice(bool uninitialisedOnly) {
}

void pushEEStateToDevice(bool uninitialisedOnly) {
}

void pushEIStateToDevice(bool uninitialisedOnly) {
}

void pushIEStateToDevice(bool uninitialisedOnly) {
}

void pushIIStateToDevice(bool uninitialisedOnly) {
}


// ------------------------------------------------------------------------
// copying things from device
// ------------------------------------------------------------------------
void pullEStateFromDevice() {
}

void pullIStateFromDevice() {
}

void pullEEStateFromDevice() {
}

void pullEIStateFromDevice() {
}

void pullIEStateFromDevice() {
}

void pullIIStateFromDevice() {
}


// ------------------------------------------------------------------------
// helper getter functions
// ------------------------------------------------------------------------

void copyStateToDevice(bool uninitialisedOnly) {
    pushEStateToDevice(uninitialisedOnly);
    pushIStateToDevice(uninitialisedOnly);
    pushEEStateToDevice(uninitialisedOnly);
    pushEIStateToDevice(uninitialisedOnly);
    pushIEStateToDevice(uninitialisedOnly);
    pushIIStateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
}

void copyStateFromDevice() {
    pullEStateFromDevice();
    pullIStateFromDevice();
    pullEEStateFromDevice();
    pullEIStateFromDevice();
    pullIEStateFromDevice();
    pullIIStateFromDevice();
}

void copyCurrentSpikesFromDevice() {
}

void copyCurrentSpikeEventsFromDevice() {
}

void allocateRecordingBuffers(unsigned int timesteps) {
    numRecordingTimesteps = timesteps;
     {
        const unsigned int numWords = 100 * timesteps;
         {
            recordSpkE = new uint32_t[numWords];
            pushMergedNeuronUpdate0recordSpkToDevice(0, recordSpkE);
        }
    }
     {
        const unsigned int numWords = 25 * timesteps;
         {
            recordSpkI = new uint32_t[numWords];
            pushMergedNeuronUpdate0recordSpkToDevice(1, recordSpkI);
        }
    }
}

void pullRecordingBuffersFromDevice() {
    if(numRecordingTimesteps == 0) {
        throw std::runtime_error("Recording buffer not allocated - cannot pull from device");
    }
     {
        const unsigned int numWords = 100 * numRecordingTimesteps;
         {
        }
    }
     {
        const unsigned int numWords = 25 * numRecordingTimesteps;
         {
        }
    }
}

void allocateMem() {
    // ------------------------------------------------------------------------
    // global variables
    // ------------------------------------------------------------------------
     {
        uint32_t seedData[std::mt19937::state_size];
        std::random_device seedSource;
        for(int i = 0; i < std::mt19937::state_size; i++) {
            seedData[i] = seedSource();
        }
        std::seed_seq seeds(std::begin(seedData), std::end(seedData));
        hostRNG.seed(seeds);
    }
    
    // ------------------------------------------------------------------------
    // timers
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // local neuron groups
    // ------------------------------------------------------------------------
    glbSpkCntE = new unsigned int[1];
    glbSpkE = new unsigned int[3200];
    VE = new scalar[3200];
    RefracTimeE = new scalar[3200];
    glbSpkCntI = new unsigned int[1];
    glbSpkI = new unsigned int[800];
    VI = new scalar[800];
    RefracTimeI = new scalar[800];
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    inSynIE = new float[3200];
    inSynEE = new float[3200];
    inSynII = new float[800];
    inSynEI = new float[800];
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    rowLengthEE = new unsigned int[3200];
    indEE = new uint32_t[1328000];
    rowLengthEI = new unsigned int[3200];
    indEI = new uint32_t[412800];
    rowLengthIE = new unsigned int[800];
    indIE = new uint32_t[328800];
    rowLengthII = new unsigned int[800];
    indII = new uint32_t[101600];
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    
    pushMergedNeuronInitGroup0ToDevice(0, glbSpkCntE, glbSpkE, VE, RefracTimeE, inSynIE, inSynEE, 3200);
    pushMergedNeuronInitGroup0ToDevice(1, glbSpkCntI, glbSpkI, VI, RefracTimeI, inSynII, inSynEI, 800);
    pushMergedSynapseConnectivityInitGroup0ToDevice(0, rowLengthEI, indEI, 129, 3200, 800);
    pushMergedSynapseConnectivityInitGroup0ToDevice(1, rowLengthIE, indIE, 411, 800, 3200);
    pushMergedSynapseConnectivityInitGroup1ToDevice(0, rowLengthEE, indEE, 415, 3200, 3200);
    pushMergedSynapseConnectivityInitGroup1ToDevice(1, rowLengthII, indII, 127, 800, 800);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntE, glbSpkE, VE, RefracTimeE, inSynIE, inSynEE, recordSpkE, 3200);
    pushMergedNeuronUpdateGroup0ToDevice(1, glbSpkCntI, glbSpkI, VI, RefracTimeI, inSynII, inSynEI, recordSpkI, 800);
    pushMergedPresynapticUpdateGroup0ToDevice(0, inSynEE, glbSpkCntE, glbSpkE, rowLengthEE, indEE, 415, 3200, 3200, 7.99999999999999930e-04f);
    pushMergedPresynapticUpdateGroup0ToDevice(1, inSynEI, glbSpkCntE, glbSpkE, rowLengthEI, indEI, 129, 3200, 800, 7.99999999999999930e-04f);
    pushMergedPresynapticUpdateGroup0ToDevice(2, inSynIE, glbSpkCntI, glbSpkI, rowLengthIE, indIE, 411, 800, 3200, -1.01999999999999990e-02f);
    pushMergedPresynapticUpdateGroup0ToDevice(3, inSynII, glbSpkCntI, glbSpkI, rowLengthII, indII, 127, 800, 800, -1.01999999999999990e-02f);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntE);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(1, glbSpkCntI);
}

void freeMem() {
    // ------------------------------------------------------------------------
    // global variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // timers
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // local neuron groups
    // ------------------------------------------------------------------------
    delete[] glbSpkCntE;
    delete[] glbSpkE;
    delete[] recordSpkE;
    delete[] VE;
    delete[] RefracTimeE;
    delete[] glbSpkCntI;
    delete[] glbSpkI;
    delete[] recordSpkI;
    delete[] VI;
    delete[] RefracTimeI;
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    delete[] inSynIE;
    delete[] inSynEE;
    delete[] inSynII;
    delete[] inSynEI;
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    delete[] rowLengthEE;
    delete[] indEE;
    delete[] rowLengthEI;
    delete[] indEI;
    delete[] rowLengthIE;
    delete[] indIE;
    delete[] rowLengthII;
    delete[] indII;
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    
}

size_t getFreeDeviceMemBytes() {
    return 0;
}

void stepTime() {
    updateSynapses(t);
    updateNeurons(t, (unsigned int)(iT % numRecordingTimesteps)); 
    iT++;
    t = iT*DT;
}

