


#include "main.h"
#include "PeopleCounter.h"



/*VL53L1_DEV dev;
uint8_t	Dev=0x52;
int status = 0;
volatile int IntCount;

int8_t error;
uint8_t byteData, sensorState=0;
uint16_t wordData;
uint16_t Distance;
uint8_t RangeStatus;
uint8_t dataReady;
int center[2] = {167,231}; // these are the spad center of the 2 8*16 zones
int Zone = 0;
int PplCounter = 0;
int lastPplCounter = 0;

uint8_t buf[128];*/



int ProcessPeopleCountingData(int16_t Distance, uint8_t zone) {
    static int PathTrack[] = {0,0,0,0};
    static int PathTrackFillingSize = 1; // init this to 1 as we start from state where nobody is any of the zones
    static int LeftPreviousStatus = NOBODY;
    static int RightPreviousStatus = NOBODY;
    static int PeopleCount = 0;

    int CurrentZoneStatus = NOBODY;
    int AllZonesCurrentStatus = 0;
    int AnEventHasOccured = 0;

	if (Distance < DIST_THRESHOLD_MAX) {
		// Someone is in !
		CurrentZoneStatus = SOMEONE;
	}

	// left zone
	if (zone == LEFT) {

		if (CurrentZoneStatus != LeftPreviousStatus) {
			// event in left zone has occured
			AnEventHasOccured = 1;

			if (CurrentZoneStatus == SOMEONE) {
				AllZonesCurrentStatus += 1;
			}
			// need to check right zone as well ...
			if (RightPreviousStatus == SOMEONE) {
				// event in left zone has occured
				AllZonesCurrentStatus += 2;
			}
			// remember for next time
			LeftPreviousStatus = CurrentZoneStatus;
		}
	}
	// right zone
	else {

		if (CurrentZoneStatus != RightPreviousStatus) {

			// event in left zone has occured
			AnEventHasOccured = 1;
			if (CurrentZoneStatus == SOMEONE) {
				AllZonesCurrentStatus += 2;
			}
			// need to left right zone as well ...
			if (LeftPreviousStatus == SOMEONE) {
				// event in left zone has occured
				AllZonesCurrentStatus += 1;
			}
			// remember for next time
			RightPreviousStatus = CurrentZoneStatus;
		}
	}

	// if an event has occured
	if (AnEventHasOccured) {
		if (PathTrackFillingSize < 4) {
			PathTrackFillingSize ++;
		}

		// if nobody anywhere lets check if an exit or entry has happened
		if ((LeftPreviousStatus == NOBODY) && (RightPreviousStatus == NOBODY)) {

			// check exit or entry only if PathTrackFillingSize is 4 (for example 0 1 3 2) and last event is 0 (nobobdy anywhere)
			if (PathTrackFillingSize == 4) {
				// check exit or entry. no need to check PathTrack[0] == 0 , it is always the case

				if ((PathTrack[1] == 1)  && (PathTrack[2] == 3) && (PathTrack[3] == 2)) {
					// This an entry
					PeopleCount ++;

				} else if ((PathTrack[1] == 2)  && (PathTrack[2] == 3) && (PathTrack[3] == 1)) {
					// This an exit
					PeopleCount --;
				}
			}

			PathTrackFillingSize = 1;
		}
		else {
			// update PathTrack
			// example of PathTrack update
			// 0
			// 0 1
			// 0 1 3
			// 0 1 3 1
			// 0 1 3 3
			// 0 1 3 2 ==> if next is 0 : check if exit
			PathTrack[PathTrackFillingSize-1] = AllZonesCurrentStatus;
		}
	}

	// output debug data to main host machine
	return(PeopleCount);

}

/*void VL53L1X_Init(void) {
	  HAL_GPIO_WritePin(GPIOB, XSDN_Pin, 1);
	  HAL_Delay(500);
	  // Those basic I2C read functions can be used to check your own I2C functions
	  status = VL53L1_RdByte(dev, 0x010F, &byteData);
	  sprintf(buf,"VL53L1X Model_ID: %X\n", byteData);
	  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
	  status = VL53L1_RdByte(dev, 0x0110, &byteData);
	  sprintf(buf,"VL53L1X Module_Type: %X\n", byteData);
	  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
	  status = VL53L1_RdWord(dev, 0x010F, &wordData);
	  sprintf(buf,"VL53L1X: %X\n", wordData);
	  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
	  while (sensorState == 0) {
	      status = VL53L1X_BootState(dev, &sensorState);
	      HAL_Delay(2);
	  }

	  fprintf(buf,"Chip booted OK\n");
	  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);

	  // Initialize and configure the device according to people counting need
	  status = VL53L1X_SensorInit(dev);
	  status += VL53L1X_SetDistanceMode(dev, 2); // 1=short, 2=long
	  status += VL53L1X_SetTimingBudgetInMs(dev, 20); // in ms possible values [20, 50, 100, 200, 500]
	  status += VL53L1X_SetInterMeasurementInMs(dev, 20);
	  status += VL53L1X_SetROI(dev, 8, 16); // minimum ROI 4,4
	  if (status != 0) {
		  fprintf(buf,"Error in Initialization or configuration of the device\n");
		  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
	      //return (-1);
	  }

	  fprintf(buf,"Start counting people  ...\n");
	  HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
	  status = VL53L1X_StartRanging(dev);   // This function has to be called to enable the ranging

	  HAL_Delay(500);
}*/

/*void VL53L1X_Count(struct VL53L1_Data_t *datos) {
    while (dataReady == 0) {
			status = VL53L1X_CheckForDataReady(dev, &dataReady);
			HAL_Delay(2);
    }

		dataReady = 0;
		status += VL53L1X_GetRangeStatus(dev, &RangeStatus);
		status += VL53L1X_GetDistance(dev, &Distance);
		status += VL53L1X_ClearInterrupt(dev); // clear interrupt has to be called to enable next interrupt
		if (status != 0) {
			fprintf(buf,"Error in operating the device\n");
			HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
			//return (-1);
		}

		// wait a couple of milliseconds to ensure the setting of the new ROI center for the next ranging is effective
		// otherwise there is a risk that this setting is applied to current ranging (even if timing has expired, the intermeasurement
		// may expire immediately after.
		HAL_Delay(10);
		status = VL53L1X_SetROICenter(dev, center[Zone]);
		if (status != 0) {
			fprintf(buf,"Error in chaning the center of the ROI\n");
			HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
			//return (-1);
		}

		// inject the new ranged distance in the people counting algorithm
		PplCounter = ProcessPeopleCountingData(Distance, Zone);

		Zone++;
		Zone = Zone%2;

		/*sprintf(buf,"Zone: %d, RangeStatus: %d, Distance: %d, Counter: %d\n", Zone, RangeStatus, Distance, PplCounter);
		HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);*/

		/*if(lastPplCounter != PplCounter) {
			sprintf(buf,"Zone: %d, RangeStatus: %d, Distance: %d, Counter: %d\n", Zone, RangeStatus, Distance, PplCounter);
			HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
			lastPplCounter = PplCounter;
		}*/

		/*datos->Zone = Zone;
		datos->RangeStatus = RangeStatus;
		datos->Distance = Distance;
		datos->PplCounter = PplCounter;
}*/
