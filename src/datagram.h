#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct cmd{
    int cmd_num, rw, reg, data;
};

int parseCommand(struct cmd *_cmd, char cmd[14]) {
    char c_num[2], c_rw[2], c_reg[6], c_data[4];
    
    int num, rw, reg, data, offset = 0;

    strncpy(c_num, cmd, 2);
    num=(int)strtol(c_num, NULL, 16);
    offset+=2;
    
    if(num == 10) { // Bridge mode
	strncpy(c_rw, cmd+offset, 1);
	rw = (int)strtol(c_rw, NULL, 16);
	offset+=1;
	
	strncpy(c_reg, cmd+offset, 4);
	reg = (int)strtol(c_reg, NULL, 16);
	offset+=4;
	
	if(rw == 1) { // if write, get data
	    strcpy(c_data, cmd+offset);
	    data = (int)strtol(c_data, NULL, 16);
	    offset+=1;
	}
	else {
	    data = 0;	    
	}	
    }
    else {
	rw = 0;
	reg = 0;
	data = 0;
    }

    _cmd->cmd_num = num;
    _cmd->rw = rw;
    _cmd->reg = reg;
    _cmd->data = data;
    
    return 1;
}

int getCommand(char *cmd_out, int cmd_num, int rw_in, int reg_in, int data_in) {
    char num[2], rw[2], reg[4], data[4], cmd[14];
    int offset = 1;
    
    offset = sprintf(cmd, "%02x", cmd_num);
    printf("offset: %d\n", offset);
    offset+=sprintf(cmd+offset, "%x", rw_in);
    printf("offset: %d\n", offset);
    offset+=sprintf(cmd+offset, "%x", reg_in);
    printf("offset: %d\n", offset);
    
    if(rw_in == 1)
	offset+=sprintf(cmd+offset, "%04x", data_in);
    
    strcpy(cmd_out, cmd);
}
