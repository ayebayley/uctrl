#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct cmd{
    unsigned int cmd_num, rw, reg, data;
};

int parseCommand(struct cmd *_cmd, char cmd[14]) {
    char *c_num, *c_rw, *c_reg, *c_data, *endptr;
    c_num = malloc(2);
    c_rw = malloc(2);
    c_reg = malloc(5);
    c_data = malloc(4);
    
    int num, rw, reg, data, offset = 0;

    strncpy(c_num, cmd, 2);
    num=(int)strtol(c_num, NULL, 16);
    offset+=2;
    strncpy(c_rw, cmd+offset, 2);
    rw = (int)strtol(c_rw, NULL, 16);
    offset+=2;
	
    strncpy(c_reg, cmd+offset, 4);
    reg = strtol(c_reg, &endptr, 16);
    offset+=4;
	
    strcpy(c_data, cmd+offset);
    data = (int)strtol(c_data, NULL, 16);
    offset+=2;

    _cmd->cmd_num = num;
    _cmd->rw = rw;
    _cmd->reg = reg;
    _cmd->data = data;
    free(c_num);
    free(c_rw);
    free(c_reg);
    free(c_data);
    return 1;
}

int getCommand(char *cmd_out, int cmd_num, int rw_in, int reg_in, int data_in) {
    char num[2], rw[2], reg[4], data[4], cmd[14];
    int offset = 1;
    
    offset = sprintf(cmd, "%02x", cmd_num);
    offset+=sprintf(cmd+offset, "%x", rw_in);
    offset+=sprintf(cmd+offset, "%x", reg_in);
    
    if(rw_in == 1)
	offset+=sprintf(cmd+offset, "%04x", data_in);
    
    strcpy(cmd_out, cmd);
}
