#include "datagram.h"

void setup(){
    Serial.begin(9600);
}

void loop(){
    char *readval;
    struct cmd _cmd;
    readval = malloc(14);
    if(Serial.available()){
	Serial.readBytes(readval, 12);
	Serial.println(readval);
	parseCommand(&_cmd, readval);
	Serial.println(_cmd.cmd_num);
	Serial.println(_cmd.rw);
	Serial.println(_cmd.reg);
	Serial.println(_cmd.data);
	Serial.flush();
    }
    free(readval);
}
