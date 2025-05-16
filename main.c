#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Account structure
typedef struct {
    char name[50];
    int accountNumber;
    int pin;
    float balance;
} Account;

// Fuction prototype

// Utility functions
void cleanScreen();
void pause();

int main() {
    printf("Hello, World!\n");
    return 0;
}



// ***** Utility Functions *****
// Clean terminal
void cleanScreen() {
    printf("\033[H\033[J");
}

// Pause the program
void pause() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}