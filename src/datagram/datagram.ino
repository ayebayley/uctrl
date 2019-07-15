/*

In bridge mode (command 10 for now), if register is to be read, the rw byte should be 0 and the data bytes should be a bitflag of sensor IDs to be read. If register is to be written, rw should be >0 and equal to the sensor ID to be written, while data should be the bytes to be written

- TODO currently this script expects a trailing newline at the end of the output (this is appended by echo by default), which is why 13 bytes are read from serial when the actual commands are only 12 bytes. in the future, when pyserial is used instead of readbytes, this might change.. changes should be made to the code accordingly

 */

#include "datagram.h"

void setup(){
    Serial.begin(9600);
}

char getChecksum(char cmd[13]){
    unsigned char checksum;
    
    checksum = cmd[0];
    for(int i=1; i<11; i++)
	checksum+=cmd[i];
    checksum%=16;
    sprintf(&checksum, "%x", checksum);
    return checksum;
}

void loop(){
    char *readval, checksum, garbage;
    int i=0;
    struct cmd _cmd;
    readval = malloc(14);
    if(Serial.available()){
	Serial.readBytes(readval, 13);
	Serial.println(readval);
	checksum = getChecksum(readval);
	parseCommand(&_cmd, readval);
	Serial.println(_cmd.cmd_num);
	Serial.println(_cmd.rw);
	Serial.println(_cmd.reg);
	Serial.println(_cmd.data);
	Serial.println(_cmd.checksum);
	Serial.println(checksum);
	if(checksum==_cmd.checksum)
	    Serial.println("Match");
	else
	    Serial.println("No match");
	Serial.println(" ");
	// while(Serial.available() && i++<30)
	//     garbage = Serial.read();
	Serial.flush();
    }
    free(readval);
}
