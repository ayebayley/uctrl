#include "datagram.h"

void setup(){
    Serial.begin(9600);
}

void loop(){
    char cmd_buf[14];
    unsigned char c;
    int i;
    struct cmd _cmd;
    if(Serial.available()>0){
	// Serial.readBytes(cmd_buf, 11);
	// parseCommand(&_cmd, cmd_buf);
	for(i=0; i<11 && Serial.available()>0; i++)
	    c = Serial.read();
	Serial.println(c);
	Serial.flush();
	// Serial.println(_cmd.cmd_num);
    }
}
