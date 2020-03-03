//
//  main.c
//  
//
//  Created by Tyler Powell on 2/21/20.
//

#include "main.h"
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcnt1.h>

int main();

void userInput(); // takes no arguments but it uses global variable
//void parseInput(); //returns parsed array of symbols?

int processString();
int containsPipe(); //contains pipe

int containsFRD(); //contains file redirect
void readFile();
void writeToFile(); //append or create? //should this be a whole ass method?

int containsRib();

void runNormal();
void runPipe();
void runInBack();

void handleCmds(); //command handler

int containsEnd();

//command functions:
cd();
clr();
dir();
environ();
echo();
help();
pause();
quit();


int main(){
    
    //create one contains function and just pass the chars that we are looking for?
    while(0){
        char** parsedUI; //user input
        bool write;
        if(containsFRD(parsedUI)){
            wrightto?
                1. write = true; //1 is yes do this later
                2. continue
            readto?
                1. readFile(parsedUI)
                2. break;
            both?
                1. readFile(parsedUI) and write = true
                2. sweet break;
            
            //add logic to make sure that the ??
        }
        ui = userInput(); //makes prompt and returns the buffer
        
        if(containsRiB()){ //does ui contain & Run in back
            runInBack(write, ui);
        }
        
        if(containsPipe){
            runPipe(write);
        }
        
        else{
            runNormal(write);
        }
        if(containsExit(parsedUI)){
            print("goodbye");
            exit(0);
        }
    }
    
}

char** userInput(){
    //getline from stdin
    //puts input into a string
    parseInput(input);
}
char** parseInput(){
    //tokenizes data
    //parse Input and puts each token into an array of str
}

int containsFRD(char** parsedUI){
    //returns 1 if a >, >>, <, << is found
    //else returns 0
}

void readFile(char** parsedUI, line){
    //get the file to read from
    //parse the line
}

int containsRiB(char** parsedUI){
    //returns 1 if a & is found
    //else returns 0
}

int containsPipe(char** parsedUI){
    //returns 1 if a pipe is found
    //else returns 0
}
void runInBack(char** parsedUI){
    //calls fork and runs the program in the back using execvp calls the prompt and puts the process in background
}

void runPipe(char** parsedUI){ //should this be passed the command?
    //checks to make sure the processes are one of the 4 valid functions
    //calls fork on the first process and then uses dup2 to redirect the output to process2
}
void runNormal(char** parsedUI){
    //get command from parsed UI
    //fork it and run the program using execvp and then use wait for the program to finish
}

void handleCmds(parsed){
    for(string in parsed){
        switch:
            case "cd":
                chdir();
            case "clr":
                clear();
            case "dir":
                dir();
            case "environ":
                environ();
            case "echo":
                echo();
            case "help":
                help();
            case "pause":
                pause();
            case "quit":
                print("see ya later");
                exit(0);
    }
}


