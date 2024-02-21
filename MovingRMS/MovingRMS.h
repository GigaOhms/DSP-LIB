#ifndef MOVINGRMS_H
#define MOVINGRMS_H

#define MOVING_RMS_MAX_BUF 200

typedef struct {
	uint16_t L;		// Windows length
	float invL;		// 1 divided by window length
	uint16_t count;		// circular buffer
	float in_sq_L[MOVING_RMS_MAX_BUF];
	float out_sq;		// RMS estimate Squared
} MovingRMS;


void MovingRMS_Init(MovingRMS *mrms, uint16_t L);
float MovingRMS_Update(MovingRMS *mrms, float in);

#endif