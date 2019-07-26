#include <check.h>
#include "o2.h"
#include "handler.h"

/* int handleSensor(int status, int cal, int flag, int wr_success, int rr_success) */

START_TEST(test_handler){
    int i;
    
    ck_assert_int_eq(handleSensor(IDLE, CAL_IDLE, FLAG_NONE), COND5);
    ck_assert_int_eq(handleSensor(STARTUP, CAL_IDLE, FLAG_NONE), COND);
    ck_assert_int_eq(handleSensor(ON, CAL_IDLE, FLAG_NONE), 0);
    ck_assert_int_eq(handleSensor(SHUTDOWN, CAL_IDLE, FLAG_NONE), 0);
    ck_assert_int_eq(handleSensor(STANDBY, CAL_IDLE, FLAG_NONE), 0);
	
}
END_TEST

int main(){
    return 0;
}
