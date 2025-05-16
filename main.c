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

// ***** File I/O Functions *****
// Load accounts from file
Account loadAccount(int accountNumber, int pin, int *found) {
    // Open the file in read mode
    FILE *file = fopen("accounts.txt", "r");
    Account account;
    *found = 0;

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return account;
    }

    // Read each line from the file and check for matching account number and pin
    while (fscanf(file, "%49[^,],%d,%d,%f\n", account.name, &account.accountNumber, &account.pin, &account.balance) == 4) {
        // Check if the account number and pin match
        if (account.accountNumber == accountNumber && account.pin == pin) {
            *found = 1;
            break;
        }
    }

    fclose(file);
    return account;
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