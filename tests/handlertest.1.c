#include <check.h>
#include <stdio.h>
#include "o2.h"
#include "handler.h"

/* int handleSensor(int status, int cal, int flag, int wr_success, int rr_success) */

// Regular operation: unwanted turn off
START_TEST(ht_regular){
    ck_assert_int_eq(handleSensor(IDLE, CAL_IDLE, FLAG_NONE), COND5); // Pull up to ON
    ck_assert_int_eq(handleSensor(STARTUP, CAL_IDLE, FLAG_NONE), COND0);
    ck_assert_int_eq(handleSensor(ON, CAL_IDLE, FLAG_NONE), COND0);
    ck_assert_int_eq(handleSensor(SHUTDOWN, CAL_IDLE, FLAG_NONE), COND0);
    ck_assert_int_eq(handleSensor(STANDBY, CAL_IDLE, FLAG_NONE), COND5);	
}
END_TEST

// Calibration wanted: calibrate when possible
START_TEST(ht_cal){
    ck_assert_int_eq(handleSensor(IDLE, CAL_IDLE, FLAG_CAL), COND5); // Pull up to ON
    ck_assert_int_eq(handleSensor(STARTUP, CAL_IDLE, FLAG_CAL), COND0); // Do nothing
    ck_assert_int_eq(handleSensor(ON, CAL_IDLE, FLAG_CAL), COND1);
    ck_assert_int_eq(handleSensor(SHUTDOWN, CAL_IDLE, FLAG_CAL), COND0); // Do nothing
    ck_assert_int_eq(handleSensor(STANDBY, CAL_IDLE, FLAG_CAL), COND5);	 // Pull up to ON
}
END_TEST

START_TEST(ht_off){
    ck_assert_int_eq(handleSensor(IDLE, CAL_IDLE, FLAG_OFF), COND0); // Do nothing
    ck_assert_int_eq(handleSensor(STARTUP, CAL_IDLE, FLAG_OFF), COND0); // Do nothing
    ck_assert_int_eq(handleSensor(ON, CAL_IDLE, FLAG_OFF), COND4);
    ck_assert_int_eq(handleSensor(SHUTDOWN, CAL_IDLE, FLAG_OFF), COND0); // Do nothing
    ck_assert_int_eq(handleSensor(STANDBY, CAL_IDLE, FLAG_OFF), COND4);	
}
END_TEST

// cal 
START_TEST(ht_cal_prog){
    ck_assert_int_eq(handleSensor(IDLE, CAL_PROG, FLAG_NONE), COND0); 
    ck_assert_int_eq(handleSensor(STARTUP, CAL_PROG, FLAG_NONE), COND0);
    ck_assert_int_eq(handleSensor(ON, CAL_PROG, FLAG_NONE), COND4);
    ck_assert_int_eq(handleSensor(SHUTDOWN, CAL_PROG, FLAG_NONE), COND0);
    ck_assert_int_eq(handleSensor(STANDBY, CAL_PROG, FLAG_NONE), COND4);	
}
END_TEST

Suite *handler_suite(){
    Suite *s;
    TCase *tc_core;

    s = suite_create("Sensor handler");
    tc_core =  tcase_create("Core");

    tcase_add_test(tc_core, ht_regular);
    tcase_add_test(tc_core, ht_cal);
    tcase_add_test(tc_core, ht_off);
    
    suite_add_tcase(s, tc_core);

    return s;
}

int main(){
    int fails;
    Suite *s;
    SRunner *sr;

    s = handler_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    fails=srunner_ntests_failed(sr);
    srunner_free(sr);
    return 0;
}
