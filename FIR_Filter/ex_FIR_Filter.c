#include "FIRFilter.h"

FIRFilter barFilterMovingAverage;

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {

    if (hspi->Instance == SPI3) {
		if (bar.reading) {
			SPL06_ReadDMA_Complete(&bar);
			/* Filter barometer readings using 10-point moving average filter */
			FIRFilter_Update(&barFilterMovingAverage, bar.pressure_Pa);
		}
	}

}


void main (void) {
    FIRFilter_Init(&barFilterMovingAverage);

    while (1)
    {
        /* code */
    }
}