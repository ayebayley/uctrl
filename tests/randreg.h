
/* 
Possible return values as int i:
- int i >= 0: success, value is read and returned
- int i < 0:  failure, error code value is returned

*/
int readReg(i);

/* 
Possible return values as int i:
- int i == 0: success, value is written
- int i < 0:  failure, error code value is returned

*/
int writeReg(i, value);

