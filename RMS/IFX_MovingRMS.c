#include "IFX_MovingRMS.h"

void IFX_MovingRMS_Init(IFX_MovingRMS *mrms, uint16_t L){
	mrms->L = L;
	mrms->invL = 1.0f / ((float)L);
	mrms->count = 0;

	for (uint16_t n = 0; n < L; n++)
		mrms->in_sq_L[n] = 0.0f;
	mrms->out_sq_L[n] = 0.0f;
}

float IFX_MovingRMS_Update(IFX_MovingRMS *mrms, float in){
	float in_sq = in * in;
	mrms->in_sq_L[mrms->count] = in_sq;
	if (mrms->count == (mrms->L - 1))
		mrms->count = 0;
	else
		mrms->count++;
	mrms->out_sq = mrms->out + mrms->invL * (in_sq - mrms->in_sq_L[mrms->count]);
	return mrms->out_sq;
}