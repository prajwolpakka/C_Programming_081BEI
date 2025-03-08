# Bank Management System 🏦

A simple Bank Management System in C that allows users to create accounts, log in, deposit, withdraw money, and view their transaction history.

### Features 🚀
- ✅ **User Registration** – Create a new bank account
- ✅ **User Login** – Secure authentication with account number and password
- ✅ **Deposit Money** – Add funds to your account
- ✅ **Withdraw Money** – Withdraw funds with balance checks
- ✅ **Transaction History** – View past transactions
- ✅ **Account Balance Updates** – Automatically updates after each transaction

### How It Works 🔄

When you **run the program**, it first displays a welcome screen with two options:  
**Create Account** or **Login**.

- If you **select "Create Account"**, the system will ask for a username and password, assign a unique **account number**, and save the details for future access.
- If you **select "Login"**, you must enter your **account number, username, and password**. If the credentials match, you will be logged in successfully.

Once logged in, you can perform the following actions:

- ✅ **Deposit Money** – Add funds to your account.
- ✅ **Withdraw Money** – Withdraw funds if you have enough balance.
- ✅ **View Account Statement** – Check your transaction history, including deposits and withdrawals.
- ✅ **Exit** – Log out and close the program.

The system securely **updates balances** and **logs transactions** to ensure accuracy and reliability. 🚀

### Files Used 📂
- `userdetail.txt` – Stores user account details
- `transaction_log.txt` – Stores transaction history

### Requirements 🛠
- C Compiler (e.g., GCC)
- Standard C libraries (`stdio.h`, `stdlib.h`, `time.h`, `unistd.h`)

