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
// Account functions
Account withdraw(Account account);
Account deposit(Account account);
// user interface
Account loginMenu(int *success);
int showMenu(Account account, Account *result);
// Utility functions
void cleanScreen();
void pause();

int main() {
    Account currentAccount;
    int loggedIn = 0;
    int exitApp = 0;

    // Aplication loop
    while (!exitApp)
    {
        int found = 0;
        currentAccount = loginMenu(&found);

        // Validates if login fail or not 
        if (!found)
        {
            printf("Login failed.\n");
            pause();
            continue;
        }

        int status = 0;
        // Main menu loop
        while (status != 1) {
            Account updatedAccount;
            status = showMenu(currentAccount, &updatedAccount);
            currentAccount = updatedAccount;
        }
        
        // Exit flag
        if (status == 2)
        {
            exitApp = 1;
        }
    }
    
    printf("Thank you for using HNB!\n");
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

// ***** Account Functions *****
// Withdraw money from account
Account withdraw(Account account) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    // Check if sufficient balance is available
    if (amount > account.balance) {
        printf("Insufficient balance.\n");
    } else {
        account.balance -= amount;
        printf("Withdrawal successful.\n");
    }

    pause();
    return account;
}

// Deposit money into account
Account deposit(Account account) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    // Check if amount is valid
    if (amount <= 0) {
        printf("Invalid amount.\n");
    } else {
        account.balance += amount;
        printf("Deposit successful.\n");
    }

    pause();
    return account;
}

// ***** User Interface Functions *****
// Display login menu
Account loginMenu(int *success) {
    int accountNumber;
    int pin;

    cleanScreen();

    printf("=====================================\n");
    printf("        WELCOME TO SAO BANK          \n");
    printf("=====================================\n");
    printf("              LOGIN MENU             \n");
    printf("-------------------------------------\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    printf("Enter PIN: ");
    scanf("%d", &pin);

    // Load account from file
    return loadAccount(accountNumber, pin, success);
}

// Display main menu
int showMenu(Account account, Account *result) {
    int choice;
    cleanScreen();

    printf("=====================================\n");
    printf("         SAO - Hello, %s!\n", account.name);
    printf("=====================================\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Logout\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);
    getchar();
    
        switch (choice) {
        case 1:
            printf("Your current balance is: $%.2f\n", account.balance);
            pause();
            *result = account;
            return 0;
        case 2:
            *result = deposit(account);
            updateAccount(*result);
            return 0;
        case 3:
            *result = withdraw(account);
            updateAccount(*result);
            return 0;
        case 4:
            return 1; // Logout
        case 5:
            return 0; // To enable exit optin change 0 for 2.
        default:
            printf("Invalid option.\n");
            pause();
            *result = account;
            return 0;
    }

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