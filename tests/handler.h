#include "o2.h"

int handleSensor(int status, int cal, int flag){
    int res, cal_res, retval;    
    if(flag == FLAG_CAL && cal == CAL_IDLE){ // Calibrate
	retval=COND1;
    }
    else if(cal== CAL_DONE){ // Reset sensor
	retval=COND2;
    }
    else if(cal == CAL_IDLE && flag == FLAG_DONE){ // Reset flag
	retval=COND3;
    }
    else if(flag == FLAG_OFF){ // Manual Shutdown
	retval=COND4;
    }
    else if((status == IDLE || status == STANDBY) && flag == FLAG_NONE){ // Turn ON
	retval=COND5;
    }
    return retval;
}