//Tyler Powell 
//Lab 3 - Linux shell 
//3207


#include "main.h"
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
// #include <fcnt1.h>   file not found??

int main(int argc, char** argv);
void initShell();
char* getInput();
char* parseInput(char* line);

int main(int argc, char** argv){
    initShell();
    char* line = NULL;
    line = getInput();
    // printf("%s",line);
    // line = getInput();
    char* parsedInput = parseInput(line);
}

void initShell(){
    puts("\nWelcome to my linux shell!!");
}

char* getInput(){
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    printf("directory place holder: ");
    (read = getline(&line, &len, stdin));
    return line;
}

char* parseInput(char* line){
    char* token = strtok(line, " ");
    char** parsedLine; // used to store the tokens
    parsedLine = malloc(sizeof(line));
    int parsedLineInd = 0;
    while(token != NULL){
        // if(strcmp(token, ">") == 0){
        //     printf("file redirection");
        // }else if(strcmp(token, ">>") == 0){
        //     printf("file redirection");
        // }else if(strcmp(token, "|") == 0){
        //     printf("piping");
        // }else if(strcmp(token, "&") == 0){
        //     printf("background execution");
        // }
        // else if(strcmp(token, "cd") == 0){
        //     printf("ahh that's how that works");
        // }
        parsedLine[parsedLineInd] = token;
        printf("%s\n", parsedLine[parsedLineInd]);
        parsedLineInd++;
        token = strtok(NULL, " ");
    }
    return token;
}

// while(*tempLine != '\0'){
    //     char* parsedCmd = NULL;
    //     parsedCmd = malloc(sizeof(tempLine));
    //     int parsedCmdInd = 0;
    //     while(*tempLine != ' ' && *tempLine != '\0'){
    //         // printf("templine: %s\n",tempLine);
    //         parsedCmd[parsedCmdInd] = *tempLine;
    //         // printf("parsedcmd %s\n", parsedCmd);
    //         parsedCmdInd++;
    //         tempLine++;
    //     }
    //     // printf("%s\n", parsedCmd);
    //     parsedLine[parsedLineInd] = parsedCmd;
    //     // printf("parsedLine : %s\n", parsedLine[parsedLineInd]);
    //     parsedLineInd++;
    //     tempLine++;
    // }
    // printf("%s %s %s", tempLine[0], tempLine[1], tempLine[2]);