/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "httpServerRemoteFunc.h"

char *getTime(char *arg);
char *setPwm(char *arg);
char *getGPIO(char *arg);

const struct func{
    char *cmd;                   // type this letter
    char *(*fnctPt)(char *a);
};  

typedef const struct func funcType;
typedef funcType *funcTypePtr;

funcType funcTable[] = {
    {"getTime", getTime},  
    {"setPwm", setPwm},
    {"getGPIO1", getGPIO}
};

const int table_length = sizeof(funcTable)/sizeof(*funcTable);
 
char *getGPIO(char *arg) {
    
}

char *getTime(char *arg) {
    time_t timer;
    static char buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("get time function is called");
   
    return buffer;
}
  
char *setPwm(char *arg) {
   static char buffer[256];
   
   //   if(setPWMDutyCycle(atoi(arg),1))
        sprintf(buffer,"OK - Set PWM to %s",arg);
	printf("OK - Set PWM to %s",arg);
	//   else
	// sprintf(buffer,"FAIL - Set PWM to %s",arg);
   return buffer;
}

char *commandInterpreter(char *cmd, char *arg) {
    static char response[256];
    funcTypePtr ptr;
    for(int row=0; row < table_length; row++){
        ptr = &funcTable[row];
        if(strcmp(cmd, ptr->cmd)==0){
            sprintf(response,"%s",ptr->fnctPt(arg)); 
            return response;
        }
    }
    return response;
}
