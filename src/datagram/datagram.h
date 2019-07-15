#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct cmd{
    unsigned int cmd_num, rw, reg, data;
    char checksum;
};

int parseCommand(struct cmd *_cmd, char cmd[14]) {
    char *c_num, *c_rw, *c_reg, *c_data, *endptr, *checksum;
    /* char checksum; */
    c_num = malloc(2);
    c_rw = malloc(1);
    c_reg = malloc(4);
    c_data = malloc(4);
    checksum = malloc(1);
    
    int num, rw, reg, data, offset = 0;

    strncpy(c_num, cmd, 2);
    num=(int)strtol(c_num, NULL, 16);
    offset+=2;
    
    strncpy(c_rw, cmd+offset, 1);
    rw = (int)strtol(c_rw, NULL, 16);
    offset+=1;
	
    strncpy(c_reg, cmd+offset, 4);
    reg = strtol(c_reg, &endptr, 16);
    offset+=4;
	
    strncpy(c_data, cmd+offset, 4);
    data = (int)strtol(c_data, &endptr, 16);
    offset+=4;

    strcpy(checksum, cmd+offset);
    
    _cmd->cmd_num = num;
    _cmd->rw = rw;
    _cmd->reg = reg;
    _cmd->data = data;    
    _cmd->checksum = *checksum;
    
    free(c_num);
    free(c_rw);
    free(c_reg);
    free(c_data);
    free(checksum);
    return 1;
}

