#include "RCFilter.h"

RCFilter lpfAcc[3];
RCFilter lpfGyr[3];


void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {

	if (hspi->Instance == SPI1) {

		if (imu.readingAcc) {

			BMI088_ReadAccelerometerDMA_Complete(&imu);

			/* Filter accelerometer data */
			RCFilter_Update(&lpfAcc[0], imu.acc_mps2[0]);
			RCFilter_Update(&lpfAcc[1], imu.acc_mps2[1]);
			RCFilter_Update(&lpfAcc[2], imu.acc_mps2[2]);

		}

		if (imu.readingGyr) {

			BMI088_ReadGyroscopeDMA_Complete(&imu);

			/* Filter gyroscope data */
			RCFilter_Update(&lpfGyr[0], imu.gyr_rps[0]);
			RCFilter_Update(&lpfGyr[1], imu.gyr_rps[1]);
			RCFilter_Update(&lpfGyr[2], imu.gyr_rps[2]);

		}

        char longBuf[128];
        sprintf(longBuf, "%.4f, %.4f\r\n", imu.acc_mps2[0], lpfAcc.out[0]);
	}
}


void main (void) {
    for (uint8_t n = 0; n < 3; n++) {
	    RCFilter_Init(&lpfAcc[n], 5.0f, 0.01f);
	    RCFilter_Init(&lpfGyr[n], 25.0f, 0.01f);
    }

    while(1);
}