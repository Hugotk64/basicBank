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
// File I/O functions
Account loadAccount(int accountNumber, int pin, int *found);
int updateAccount(Account account);
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

// Update account in file
int updateAccount(Account account) {
    // Open the file in read mode
    FILE *file = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    Account tempAccount;
    int found = 0;

    // Check if the files opened successfully
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    // Read each line from the file and write to temp file
    while (fscanf(file, "%49[^,],%d,%d,%f\n", tempAccount.name, &tempAccount.accountNumber, &tempAccount.pin, &tempAccount.balance) == 4) {
        // If account number matches, update the account
        if (tempAccount.accountNumber == account.accountNumber) {
            fprintf(tempFile, "%s,%d,%d,%.2f\n", account.name, account.accountNumber, account.pin, account.balance);
            found = 1;
        } else {
            fprintf(tempFile, "%s,%d,%d,%.2f\n", tempAccount.name, tempAccount.accountNumber, tempAccount.pin, tempAccount.balance);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace original file with updated file
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    return found;
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