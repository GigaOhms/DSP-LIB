#include <stdint.h>

#include "MovingRMS.h"

void MovingRMS_Init(MovingRMS *mrms, uint16_t L){
	mrms->L = L;
	mrms->invL = 1.0f / ((float)L);
	mrms->count = 0;
	// Clear buffer
	for (uint16_t n = 0; n < L; n++)
		mrms->in_sq_L[n] = 0.0f;
	// Clear output
	mrms->out_sq = 0.0f;
}

float MovingRMS_Update(MovingRMS *mrms, float in){
	float in_sq = in * in;
	mrms->in_sq_L[mrms->count] = in_sq;
	if (mrms->count == (mrms->L - 1))
		mrms->count = 0;
	else
		mrms->count++;
	mrms->out_sq = mrms->out_sq + mrms->invL * (in_sq - mrms->in_sq_L[mrms->count]);
	return mrms->out_sq;
}
