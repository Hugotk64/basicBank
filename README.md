# basicBank

Simple console-based banking application in C. It allows users to log in, check balances, deposit and withdraw money. All data is stored in a text file for persistence.

# 📋 Features

- Account login with account number and pin

- View account balance

- Deposit money

- Withdraw money

- Account data stored and updated in `accounts.txt`

- Clean, user-friendly terminal interface

# 🗂️ Project Structure

basiBank/

|--accounts.txt

|--main.c

|--README.md

# 📄 accounts.txt Format

Each account is stored as a single line in the following format:
name,accountNumber,pin,balance

Example:
Hugo,172839,1234,123.45

# 🛠️ How to Build and Run

Use `gcc` to compile the program:
gcc main.c -o bank

To run use bash:
./bank

# ✅ How to Use

Once you compile the program and run it you have to:

-Open accounts.txt to see accounts information

-Log in using any of the account number and pin of any listed account

-check the balance of this account

-Deposit money into the account

-Withdrawn mony from the account

-Check the balance again to see updated amount

-Log out to try other accounts

-Exit the program

💡 Tip: You can add or edit accounts manually in `accounts.txt`.

# ⚠️ Disclaimer

The EXIT option in this program is intentionally disable as a reference to the anime Sword Art Online (SAO) where players are trapped in a VR game and unable to exit.

Of course, unlike the anime, you're not actually stuck here, you can exit the program anytime by pressing Ctrl+C or closing the terminal. There is also a comment in the code indicating how to change it.

# 👨‍💻 Author
Hugo Antonio Castillo Vargas
Student of Computer Engineering
UNED - Universidad Estatal a Distancia