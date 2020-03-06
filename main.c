//Tyler Powell 
//Lab 3 - Linux shell 
//3207


// #include "main.h"
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
// #include <fcnt1.h>  // file not found??

int main(int argc, char** argv);
void initShell();
void getInput(char **line);
// char* tokInput(char* line, char **cmd, 
//                 char **arg1, char **arg2); //returns argFlag
ssize_t getBatch(char *line, char *fileName, char **newArgv, char *argFlag);
char* tokInput(char *line, char **newArgv);
int builtInCmd(char **newArgv); //returns 1 if it is a built in, else 0

//built in commands
void cd();
void clr();
void dir();
void environ();
void echo(char **newArgv);
void help();
void builtpause();
void quit();

int main(int argc, char** argv){
    initShell();
    char **newArgv = malloc(8);
    char* line = NULL;
    char* argFlag;
    if(argc > 1){ //if the initial argument count to run the program is greater than one then take input from file
        printf("Main loop: batch file\n");
        // printf("%s\n", argv[1]);
        getBatch(line, argv[1], newArgv, argFlag);
    }
    while(1){ //forever loop
        if(argc == 1){
            // printf("Main loop: getting input from user\n");
            getInput(&line);
        }
        argFlag = tokInput(line, newArgv);
        printf("Main loop: command: %s\n", newArgv[0]);
        printf("Main loop: arg flag: %s\n", argFlag);
        if(builtInCmd(newArgv)){ 
            printf("Main loop: cool now what?\n");
        }else{
            //notBuiltinCmd() -- parameters?
        }
        //this will only work if there is a space after exit 
        if(strcmp(newArgv[0], "exit") == 0){ //or eof then exit!
            printf("Main loop: Exiting shell...\n"); 
            exit(0);
        }
    }
}

void initShell(){
    puts("\nWelcome to my linux shell!!");
}

ssize_t getBatch(char *line, char *fileName, char **newArgv, char *argFlag){
    size_t len = 0;
    ssize_t lineSize;
    FILE *file = fopen("test.txt", "r");
    if(!file){
        printf("file not found");
    }
    while(getline(&line, &len, file) != -1){
        printf("Line : %s\n", line);
        argFlag = tokInput(line, newArgv);
        printf("%s\n", argFlag);
        printf("%s \n", newArgv[0]);
        printf("%s \n", newArgv[1]);
        printf("%s \n", newArgv[2]);
        if(builtInCmd(newArgv)){
            printf("Main loop: cool now what?\n");
        }else{
            //notBuiltinCmd() -- parameters?
        }
        //this will only work if there is a space after exit 
        if(strcmp(newArgv[0], "exit") == 0){ //or eof then exit!
            printf("Main loop: Exiting shell...\n"); 
            exit(0);
        }
        if(line == '\0'){
            printf("Exiting shell");
            exit(0);
        }
    }
    return lineSize;
}

void getInput(char **line){
    size_t len = 0;
    ssize_t read;
    char buff[PATH_MAX] = "";
    char *cwd = getcwd(NULL, 0);
    printf("%s $ ", cwd);
    read = getline(line, &len, stdin);
    // printf("%s", *line);
}
 
int builtInCmd(char **newArgv){
    char* cmd = newArgv[0];
    if(strcmp(cmd, "cd") == 0){
            cd(newArgv[1]);
            return 1;
    }
    else if(strcmp(cmd, "clr")== 0){
            clr();
            return 1;
    }
    else if(strcmp(cmd, "dir")== 0){
            dir();
            return 1;
    }
    else if(strcmp(cmd, "environ")== 0){
            environ();
            return 1;
    }
    else if(strcmp(cmd, "echo")== 0){
            echo(newArgv);
            return 1;
    }
    else if(strcmp(cmd, "help")== 0){
            help();
            return 1;
    }
    else if(strcmp(cmd, "pause")== 0){
            builtpause();
            return 1;
    }
    else if(strcmp(cmd, "quit")== 0){
            quit();
            return 1;
    }
    else{
        return 0;
    }
}

char* tokInput(char* line, char** newArgv){
    char* token;
    token =  strtok(line," ");
    char** parsedLine; // used to store the tokens
    parsedLine = malloc(sizeof(line));
    int parsedLineInd = 0;
    char *argFlag = NULL;
    while(token != NULL){
        if(strcmp(token, "<") == 0){
            argFlag = "in_redirection";
            // printf("file redirection");
        }else if(strcmp(token, ">") == 0){
            argFlag = "out_redirection"; //trucate file
            // printf("out_redirection\n");
        }else if(strcmp(token, ">>") == 0){
            argFlag = "doub_out_redirection"; //append to file
            // printf("file redirection");
        }else if(strcmp(token, "|") == 0){
            argFlag = "pipe";
            // printf("piping");
        }else if(strcmp(token, "&") == 0){
            argFlag = "background";
            // printf("background execution");
        }
        newArgv[parsedLineInd] = token;
        // printf("%d", parsedLineInd);
        parsedLineInd++;
        token = strtok(NULL, " ");
    }
    // printf( "tokInput: cmd: %s\n", newArgv[0]);
    // printf( "tokInput: arg1: %s\n", newArgv[1]);
    // printf( "tokInput: arg2: %s\n", newArgv[2]);

    //can you have more than one argument? I think so with file redirection
    // printf( tokInput: cmd: %s\n", *cmd);
    return argFlag;
}

//works
void cd(char *arg1){
    //need to put spaces after this or it does not work 
    if(chdir(arg1) == 0){

    }else{
        printf("\nSomething went wrong with changing directories\n");
    }
    printf("Built in command: cd\n");
}

//works
void clr(){
    printf("\033[H\033[2J");
    // printf("Built in command: clr\n");
}

//works
void dir(){ //come back to this one slide 14-16
    char dirName[2] = "/"; //name of dir
    DIR *dir = opendir(dirName);
    struct dirent *s; //directory entry
    while((s = readdir(dir)) != NULL){
        printf("%s\t\n", s->d_name);
    }
    printf("Built in command: dir\n");
}

//works
void environ(){ 
    printf("\n---------ENVIRONMENT----------\n");
    printf("USER: %s\n", getenv("USER"));
    printf("PATH : %s\n", getenv("PATH"));
    printf("HOME : %s\n", getenv("HOME"));
    printf("ROOT : %s\n", getenv("ROOT"));
}

//kinda works?
void echo(char** newArgv){
    char **temp = newArgv;
    temp++;
    while(*temp != '\0'){
        printf("Argument: %s\n", *temp);
        temp++;
    }
}

//works but needs to be finished
void help(){
    printf("Built in command: help\n");
}

//works
void builtpause(){
    printf("Shell paused. Hit ENTER to resume.\n");
    getchar();
}

//works
void quit(){
    printf("Exiting shell...");
    exit(0);
    printf("Built in command: quit\n");
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