#include <stdlib.h>

int readReg(){
    int rnum, retval;
    time_t seed;
    srand((unsigned)time(&seed));
    rnum = rand() % 10;

    // 50% chance of error
    if(rnum > 5)
	retval=1;
    else
	retval=-1;
    return retval;
}

int writeReg(){
    int rnum, retval;
    time_t seed;
    srand((unsigned)time(&seed));
    rnum = rand() % 10;

    // 50% chance of error
    if(rnum > 5)
	retval=1;
    else
	retval=-1;
    return retval;
}
