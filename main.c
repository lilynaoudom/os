/*
    Author: Lily Naoudom
    Program: Parent-Child Cooperation, ITCS 3146
    Date: Apr 21 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void showMenu();
void result(int);

int main() {
    
    //print ids of parents
    printf("Parent process ID: %d, Parent's parent ID: %d\n", (int)getpid(), (int)getppid());
    int userChoice;
    
    do {
        
        showMenu();                     //display menu options
        scanf("%d", &userChoice);       //accept user choice
        result(userChoice);             //function call to create processes and execute tasks or terminate program
        
        printf("\nCurrent process PID %d\n", (int)getpid());
        
    } while (userChoice !=4);
    
    printf("Program terminated.");      //terminate program
    
}//end main

void showMenu() {
    
    printf("Choose the function to be performed by the child: \n");
    printf("\t(1) Display current date and time\n");
    printf("\t(2) Display the calendar of the current month\n");
    printf("\t(3) List the files in the current directory\n");
    printf("\t(4) Exit from the program\n");
    printf("\nEnter your choice: ");
    
}

void result(int userChoice) {
    
    if (userChoice == 4)    //user chooses to exit the program, so do not call fork() to create
        return;             //unnecessary processes
    
    pid_t pid = fork();     //create new process for each user choice chosen
    
    //child
    if (pid==0) {
        printf("Child process ID %d; Parent ID %d\n",(int)getpid(), (int)getppid());
        
        //switch function to handle task chosen
        //for each, child invokes a call to system to execute the requested command
        switch (userChoice){
            case 1:
                system("date");
                break;
            case 2:
                system("cal");
                break;
            case 3:
                system("ls -l");
                break;
        }//end switch
        
        exit(0);
    } else {        //parent waits until child process terminates the previous command
        wait(0);    //before displaying menu again
        return;
    }


}