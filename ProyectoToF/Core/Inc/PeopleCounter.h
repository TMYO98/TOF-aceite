#ifndef INC_PEOPLECOUNTER_H_
#define INC_PEOPLECOUNTER_H_



#include "VL53L1X_API.h"
#include "VL53l1X_calibration.h"



#define isInterrupt 1 /* If isInterrupt = 1 then device working in interrupt mode, else device working in polling mode */

// People Counting defines
#define NOBODY 0
#define SOMEONE 1
#define LEFT 0
#define RIGHT 1
#define DIST_THRESHOLD_MAX  /*1780*/ 350



/*struct VL53L1_Data_t{

	int Zone;
	uint8_t RangeStatus;
	uint16_t Distance;
	int PplCounter;

};*/
//typedef VL53L1_Data_t *VL53L1_Data;



int ProcessPeopleCountingData(int16_t Distance, uint8_t zone);
//void VL53L1X_Init(void);
//void VL53L1X_Count(struct VL53L1_Data_t *datos);



#endif /* INC_PEOPLECOUNTER_H_ */
