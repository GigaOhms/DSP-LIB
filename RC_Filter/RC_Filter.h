#ifndef __RC_FILTER__
#define __RC_FILTER__

typedef struct {
	float coeff[2];
	float out[2];
} RCFilter;

void RCFilter_Init(RCFilter *filt, float cutoffFreqHz, float sampleTimeS);
float RCFilter_Update(RCFilter *filt, float inp);

#endif