#include <SoftwareSerial.h>
#include <string.h>

#define BAUD 9600
#define MOTOR_BAUD 115200
SoftwareSerial motors(4, 5);


void setup(){
    Serial.begin(BAUD);
    motors.begin(MOTOR_BAUD);
}

int cur_iter = 0;
void loop(){
    uint8_t cmd[9];
	char ret;
    cmd[0] = 0x01;
    cmd[1] = 0x01;
    cmd[2] = 0x00;
    cmd[3] = 0x00;
    cmd[4] = 0x00;
    cmd[5] = 0x00;
    cmd[6] = 0x00;
    cmd[7] = 0xc8;
    cmd[8] = 0xca;
    // uint8_t ck;
    // ck = cmd[0];
    // for(int i=1; i<8; i++)
    // 	ck+=cmd[i];
    
    for(int i=0; i<9; i++)
	motors.write(cmd[i]);
    while(!motors.available());
    while(motors.available()){
	ret = motors.read();
	Serial.println(ret);
    }
    delay(5000);
}
