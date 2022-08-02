//
// neuronUpdateISPC.h
// (Header automatically generated by the ispc compiler.)
// DO NOT EDIT THIS FILE.
//

#pragma once
#include <stdint.h>



#ifdef __cplusplus
namespace ispc { /* namespace */
#endif // __cplusplus

#ifndef __ISPC_ALIGN__
#if defined(__clang__) || !defined(_MSC_VER)
// Clang, GCC, ICC
#define __ISPC_ALIGN__(s) __attribute__((aligned(s)))
#define __ISPC_ALIGNED_STRUCT__(s) struct __ISPC_ALIGN__(s)
#else
// Visual Studio
#define __ISPC_ALIGN__(s) __declspec(align(s))
#define __ISPC_ALIGNED_STRUCT__(s) __ISPC_ALIGN__(s) struct
#endif
#endif


///////////////////////////////////////////////////////////////////////////
// Functions exported from ispc code
///////////////////////////////////////////////////////////////////////////
#if defined(__cplusplus) && (! defined(__ISPC_NO_EXTERN_C) || !__ISPC_NO_EXTERN_C )
extern "C" {
#endif // __cplusplus
    extern void neuronSpikeQueueUpdateKernel();
    extern void pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(uint32_t idx, uint32_t * spkCnt);
    extern void pushMergedNeuronUpdate0recordSpkToDevice(uint32_t idx, uint32_t * value);
    extern void pushMergedNeuronUpdateGroup0ToDevice(uint32_t idx, uint32_t * spkCnt, uint32_t * spk, float * V, float * RefracTime, float * inSynInSyn0, float * inSynInSyn1, uint32_t * recordSpk, uint32_t numNeurons);
    extern void updateNeuronsKernel(float t, uint32_t recordingTimestep);
#if defined(__cplusplus) && (! defined(__ISPC_NO_EXTERN_C) || !__ISPC_NO_EXTERN_C )
} /* end extern C */
#endif // __cplusplus


#ifdef __cplusplus
} /* namespace */
#endif // __cplusplus
