IFX_Moving mrms
volatile uint_t mrmsWindowLength = 2048;
volatile float	mrmsSqEstimate   = 0.0fl;

void main(){
	IFX_MovingRMS_Init(&mrms, mrmsWindowLength);
	mrmsSqEstimate = IFX_MovingRMS_Update(&mrms, leftIn)
}