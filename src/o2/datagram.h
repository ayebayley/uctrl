#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct cmd{
    unsigned int command, rw, reg, data;
    char checksum;
};

int parseCommand(struct cmd *_cmd, char cmd[13]);
char getChecksum(char cmd[13]);
