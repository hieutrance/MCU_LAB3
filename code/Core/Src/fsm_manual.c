#include "fsm_manual.h"
#include "fsm_automatic.h"

int index = 0;
int temp_time = 1;
void fsm_manual(){
	switch(status){
/////////////////////////////////////////////////////////////
	case MODIFY_RED:
		temp_timeRed = timeRed;
		time13 = temp_time;
		time24 = 2;
		if(isTimerFlagSet(1)==1){
			HAL_GPIO_TogglePin(RED_13_GPIO_Port , RED_13_Pin);
			HAL_GPIO_TogglePin(RED_24_GPIO_Port , RED_24_Pin);

			setTimer(1 , 500);
		}

		if(isTimerFlagSet(2)){
			setTimer(2 , 250);
			updateBufer();
			update7SegLed(index);

			index++;
			if(index >= 4){
				index = 0;
			}
		}

		if(isButtonPressed(MODIFY_BUTTON)){   // nhan tha --> +1
			temp_time++;
		}
		if(isButtonLongPressed(MODIFY_BUTTON)){ // nhan de --> +5
			temp_time += 5;
		}

		if(isButtonPressed(SET_BUTTON)){
			turnoff_red();
			status = MODIFY_YELLOW;
			setTimer(1 , 500);

			timeRed = temp_time;
			temp_time = 1;
		}
		if(isButtonPressed(MODE_BUTTON)){
			turnoff_red();
			status = MODIFY_YELLOW;
			setTimer(1 , 500);
			temp_time = 1;
		}
		break;
/////////////////////////////////////////////////////////////
	case MODIFY_YELLOW:
		temp_timeYellow = timeYellow;
		time13 = temp_time;
		time24 = 3;

		if(isTimerFlagSet(1)==1){
			HAL_GPIO_TogglePin(YELLOW_13_GPIO_Port , YELLOW_13_Pin);
			HAL_GPIO_TogglePin(YELLOW_24_GPIO_Port , YELLOW_24_Pin);

			setTimer(1 , 500);
		}

		if(isTimerFlagSet(2)){
			setTimer(2 , 250);
			updateBufer();
			update7SegLed(index);
			index++;
			if(index >= 4){
				index = 0;
			}
		}
		if(isButtonPressed(MODIFY_BUTTON)){   // nhan tha --> +1
			temp_time++;
		}
		if(isButtonLongPressed(MODIFY_BUTTON)){ // nhan de --> +5
			temp_time += 5;
		}

		if(isButtonPressed(SET_BUTTON)){
			turnoff_yellow();
			status = MODIFY_GREEN;
			setTimer(1 , 500);

			timeYellow = temp_time;
			temp_time = 1;
			time13 = 1;
		}

		if(isButtonPressed(MODE_BUTTON)==1){
			turnoff_yellow();
			status = MODIFY_GREEN;
			setTimer(1 , 500);
		}


		break;
/////////////////////////////////////////////////////////////
	case MODIFY_GREEN:
// neu den vang < den do -> den xanh = den do - den vang
// neu den vang > den do -> tra ve thoi gian mac dinh cho ca 3 den

		if(timeRed > timeYellow){
			time13 = timeRed - timeYellow;
			time24 = 4;
			timeGreen = time13;
			updateBufer();
		}
		else{
			timeRed = temp_timeRed;
			timeYellow = temp_timeYellow;

			time13 = 0;
			time24 = 4;
			updateBufer();
		}

		if(isTimerFlagSet(1)==1){
			HAL_GPIO_TogglePin(GREEN_13_GPIO_Port , GREEN_13_Pin);
			HAL_GPIO_TogglePin(GREEN_24_GPIO_Port , GREEN_24_Pin);

			setTimer(1 , 500);
		}

		if(isTimerFlagSet(2)){
			setTimer(2 , 250);
			updateBufer();
			update7SegLed(index);
			index++;
			if(index >= 4){
				index = 0;
			}
		}
		if(isButtonPressed(SET_BUTTON)){
			turnoff_green();
			status = INIT;
			temp_time = 1;
			time13 = timeRed;
			time24 = timeGreen;
		}
		if(isButtonPressed(MODE_BUTTON)==1){
			turnoff_green();
			temp_time = 1;
			status = INIT;
		}
		break;
	default:
		break;
	}
}


