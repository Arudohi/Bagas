// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct Date {
//     int day;
//     int month;
//     int year;
// } Date;

// typedef struct Transaction {
//     int id;
//     char type[10]; // "income" or "expense"
//     double amount;
//     Date date;
//     char description[50];
//     struct Transaction *left;
//     struct Transaction *right;
// } Transaction;

// Transaction* createTransaction(int id, char *type, double amount, Date date, char *description) {
//     Transaction *newTransaction = (Transaction *)malloc(sizeof(Transaction));
//     newTransaction->id = id;
//     strcpy(newTransaction->type, type);
//     newTransaction->amount = amount;
//     newTransaction->date = date;
//     strcpy(newTransaction->description, description);
//     newTransaction->left = newTransaction->right = NULL;
//     return newTransaction;
// }

// int compareDates(Date date1, Date date2) {
//     if (date1.year != date2.year) return date1.year - date2.year;
//     if (date1.month != date2.month) return date1.month - date2.month;
//     return date1.day - date2.day;
// }

// Date createDate(int day, int month, int year) {
//     Date date;
//     date.day = day;
//     date.month = month;
//     date.year = year;
//     return date;
// }

// Transaction* insertTransaction(Transaction *root, Transaction *newTransaction) {
//     if (root == NULL) return newTransaction;

//     if (compareDates(newTransaction->date, root->date) < 0) {
//         root->left = insertTransaction(root->left, newTransaction);
//     } else {
//         root->right = insertTransaction(root->right, newTransaction);
//     }
//     return root;
// }

// void displayTransactions(Transaction *root, char *type) {
//     if (root == NULL) return;

//     displayTransactions(root->left, type);

//     if (strcmp(root->type, type) == 0) {
//         printf("ID: %d\n", root->id);
//         printf("Amount: %.2f\n", root->amount);
//         printf("Date: %02d/%02d/%04d\n", root->date.day, root->date.month, root->date.year);
//         printf("Description: %s\n\n", root->description);
//     }

//     displayTransactions(root->right, type);
// }

// double calculateTotal(Transaction *root, char *type) {
//     if (root == NULL) return 0;

//     double total = 0;
//     if (strcmp(root->type, type) == 0) {
//         total = root->amount;
//     }

//     return total + calculateTotal(root->left, type) + calculateTotal(root->right, type);
// }

// Transaction* findTransaction(Transaction *root, int id) {
//     if (root == NULL || root->id == id) return root;

//     if (id < root->id) {
//         return findTransaction(root->left, id);
//     } else {
//         return findTransaction(root->right, id);
//     }
// }

// void editTransaction(Transaction *root, int id, double newAmount, Date newDate, char *newDescription) {
//     Transaction *transaction = findTransaction(root, id);
//     if (transaction != NULL) {
//         transaction->amount = newAmount;
//         transaction->date = newDate;
//         strcpy(transaction->description, newDescription);
//     } else {
//         printf("Transaction not found!\n");
//     }
// }

// void printMenu(double income, double expense, double total) {
//     printf("\n==============================\n");
//     printf("Total\n");
//     printf("Current Total: %.2f\n", total);
//     printf("------------------------------\n");
//     printf("Income   |   Expense\n");
//     printf("%.2f    |    %.2f\n", income, expense);
//     printf("------------------------------\n");
//     printf("1. Add Transaction\n");
//     printf("2. Display Income\n");
//     printf("3. Display Expenses\n");
//     printf("4. Display Total Money\n");
//     printf("5. Edit Transaction\n");
//     printf("6. Exit\n");
//     printf("==============================\n");
//     printf("Enter your choice: ");
// }

// int main() {
//     Transaction *root = NULL;

//     int choice = 0;

//     double income = 0.0, expense = 0.0, total = 0.0;

//     while (1) {
//         income = calculateTotal(root, "income");
//         expense = calculateTotal(root, "expense");
//         total = income - expense;
        
//         printMenu(income, expense, total);
//         scanf("%d", &choice);

//         switch (choice) {
//             case 1:
//                 // Add Transaction
//                 {
//                     int id;
//                     char type[10], description[50];
//                     double amount;
//                     Date date;

//                     printf("Enter ID: ");
//                     scanf("%d", &id);
//                     printf("Enter type (income/expense): ");
//                     scanf("%s", type);
//                     printf("Enter amount: ");
//                     scanf("%lf", &amount);
//                     printf("Enter date (dd mm yyyy): ");
//                     scanf("%d %d %d", &date.day, &date.month, &date.year);
//                     printf("Enter description: ");
//                     getchar(); // Consume newline character left by previous scanf
//                     fgets(description, sizeof(description), stdin);
//                     description[strcspn(description, "\n")] = '\0'; // Remove newline character from description

//                     root = insertTransaction(root, createTransaction(id, type, amount, date, description));
//                 }
//                 break;
//             case 2:
//                 // Display Income
//                 printf("\nIncome Transactions:\n");
//                 displayTransactions(root, "income");
//                 printf("Press Enter to continue...");
//                 getchar(); // Wait for Enter key
//                 getchar(); // Wait for Enter key
//                 break;
//             case 3:
//                 // Display Expenses
//                 printf("\nExpense Transactions:\n");
//                 displayTransactions(root, "expense");
//                 printf("Press Enter to continue...");
//                 getchar(); // Wait for Enter key
//                 getchar(); // Wait for Enter key
//                 break;
//             case 4:
//                 // Display Total Money
//                 printf("\nTotal Income: %.2f\n", income);
//                 printf("Total Expenses: %.2f\n", expense);
//                 printf("Net Money: %.2f\n", total);
//                 printf("Press Enter to continue...");
//                 getchar(); // Wait for Enter key
//                 getchar(); // Wait for Enter key
//                 break;
//             case 5:
//                 // Edit Transaction
//                 {
//                     int id;
//                     double amount;
//                     Date date;
//                     char description[50];

//                     printf("Enter ID of transaction to edit: ");
//                     scanf("%d", &id);
//                     printf("Enter new amount: ");
//                     scanf("%lf", &amount);
//                     printf("Enter new date (dd mm yyyy): ");
//                     scanf("%d %d %d", &date.day, &date.month, &date.year);
//                     printf("Enter new description: ");
//                     getchar(); // Consume newline character left by previous scanf
//                     fgets(description, sizeof(description), stdin);
//                     description[strcspn(description, "\n")] = '\0'; // Remove newline character from description

//                     editTransaction(root, id, amount, date, description);
//                 }
//                 break;
//             case 6:
//                 // Exit
//                 printf("Exiting program...\n");
//                 exit(0);
//             default:
//                 printf("Invalid choice. Please try again.\n");
//         }
//     }

//     return 0;
// }

// #include <stdio.h>

// // Function prototypes
// void addIncome();
// void addExpense();
// void editIncome();
// void editExpense();
// void viewTransactionHistory();
// void generateReport();

// // Global variables to store financial data
// float totalMoney = 0.0;
// float totalIncome = 0.0;
// float totalExpense = 0.0;

// int main() {
//     int choice;
    
//     do {
//         printf("===== Personal Finance Management System =====\n\n");
//         printf("Total Money: $%.2f\n", totalMoney);
//         printf("Total Income: $%.2f\n", totalIncome);
//         printf("Total Expense: $%.2f\n\n", totalExpense);
        
//         printf("===== Menu Options =====\n\n");
//         printf("1. Add Income\n");
//         printf("2. Add Expense\n");
//         printf("3. Edit Income\n");
//         printf("4. Edit Expense\n");
//         printf("5. View Transaction History\n");
//         printf("6. Generate Report\n");
//         printf("7. Exit\n\n");
        
//         printf("Choose an option: ");
//         scanf("%d", &choice);
        
//         switch(choice) {
//             case 1:
//                 addIncome();
//                 break;
//             case 2:
//                 addExpense();
//                 break;
//             case 3:
//                 editIncome();
//                 break;
//             case 4:
//                 editExpense();
//                 break;
//             case 5:
//                 viewTransactionHistory();
//                 break;
//             case 6:
//                 generateReport();
//                 break;
//             case 7:
//                 printf("Exiting the program...\n");
//                 break;
//             default:
//                 printf("Invalid choice! Please try again.\n");
//         }
//     } while(choice != 7);
    
//     return 0;
// }

// void addIncome() {
//     float amount;
//     printf("Enter the income amount: $");
//     scanf("%f", &amount);
//     totalMoney += amount;
//     totalIncome += amount;
//     printf("Income added successfully!\n\n");
// }

// void addExpense() {
//     float amount;
//     printf("Enter the expense amount: $");
//     scanf("%f", &amount);
//     totalMoney -= amount;
//     totalExpense += amount;
//     printf("Expense added successfully!\n\n");
// }

// void editIncome() {
//     // To be implemented
//     printf("Edit Income function is not implemented yet.\n\n");
// }

// void editExpense() {
//     // To be implemented
//     printf("Edit Expense function is not implemented yet.\n\n");
// }

// void viewTransactionHistory() {
//     // To be implemented
//     printf("View Transaction History function is not implemented yet.\n\n");
// }

// void generateReport() {
//     // To be implemented
//     printf("Generate Report function is not implemented yet.\n\n");
// }

#include <stdio.h>
#include <string.h>

// Define constants
#define MAX_TRANSACTIONS 100

// Define structures
typedef struct {
    float amount;
    char description[50];
} Transaction;

// Function prototypes
void addIncome();
void addExpense();
void editTransaction(char *type);
void viewTransactionHistory();
void generateReport();

// Global variables to store financial data
float totalMoney = 0.0;
float totalIncome = 0.0;
float totalExpense = 0.0;
Transaction incomes[MAX_TRANSACTIONS];
Transaction expenses[MAX_TRANSACTIONS];
int incomeCount = 0;
int expenseCount = 0;

int main() {
    int choice;

    do {
         printf("===== Personal Finance Management System =====\n\n");
        printf("+---------------------------------+\n");
        printf("|              Total              |\n");
        printf("| %20.2f            |\n", totalMoney);
        printf("|---------------------------------|\n");
        printf("|     Income     |     Expense    |\n");
        printf("| %12.2f   | %12.2f   |\n", totalIncome, totalExpense);
        printf("+---------------------------------+\n\n");

        printf("===== Menu Options =====\n\n");
        printf("1. Add Income\n");
        printf("2. Add Expense\n");

        printf("3. Edit Income\n");
        printf("4. Edit Expense\n");
        printf("5. View Transaction History\n");
        printf("6. Generate Report\n");
        printf("7. Exit\n\n");

        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addIncome();
                break;
            case 2:
                addExpense();
                break;
            case 3:
                editTransaction("income");
                break;
            case 4:
                editTransaction("expense");
                break;
            case 5:
                viewTransactionHistory();
                break;
            case 6:
                generateReport();
                break;
            case 7:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

void addIncome() {
    if (incomeCount >= MAX_TRANSACTIONS) {
        printf("Maximum income transactions reached!\n\n");
        return;
    }

    Transaction income;
    printf("Enter the income amount: $");
    scanf("%f", &income.amount);
    getchar(); // Consume newline character
    printf("Enter a description: ");
    fgets(income.description, sizeof(income.description), stdin);
    income.description[strcspn(income.description, "\n")] = '\0'; // Remove newline character

    incomes[incomeCount++] = income;
    totalMoney += income.amount;
    totalIncome += income.amount;

    printf("Income added successfully!\n\n");
}

void addExpense() {
    if (expenseCount >= MAX_TRANSACTIONS) {
        printf("Maximum expense transactions reached!\n\n");
        return;
    }

    Transaction expense;
    printf("Enter the expense amount: $");
    scanf("%f", &expense.amount);
    getchar(); // Consume newline character
    printf("Enter a description: ");
    fgets(expense.description, sizeof(expense.description), stdin);
    expense.description[strcspn(expense.description, "\n")] = '\0'; // Remove newline character

    expenses[expenseCount++] = expense;
    totalMoney -= expense.amount;
    totalExpense += expense.amount;

    printf("Expense added successfully!\n\n");
}

void editTransaction(char *type) {
    int index;
    float newAmount;
    char newDescription[50];

    if (strcmp(type, "income") == 0) {
        printf("Enter the index of the income to edit (0-%d): ", incomeCount - 1);
        scanf("%d", &index);
        if (index < 0 || index >= incomeCount) {
            printf("Invalid index!\n\n");
            return;
        }
        printf("Enter the new income amount: $");
        scanf("%f", &newAmount);
        getchar(); // Consume newline character
        printf("Enter the new description: ");
        fgets(newDescription, sizeof(newDescription), stdin);
        newDescription[strcspn(newDescription, "\n")] = '\0'; // Remove newline character

        totalMoney += newAmount - incomes[index].amount;
        totalIncome += newAmount - incomes[index].amount;

        incomes[index].amount = newAmount;
        strcpy(incomes[index].description, newDescription);
    } else {
        printf("Enter the index of the expense to edit (0-%d): ", expenseCount - 1);
        scanf("%d", &index);
        if (index < 0 || index >= expenseCount) {
            printf("Invalid index!\n\n");
            return;
        }
        printf("Enter the new expense amount: $");
        scanf("%f", &newAmount);
        getchar(); // Consume newline character
        printf("Enter the new description: ");
        fgets(newDescription, sizeof(newDescription), stdin);
        newDescription[strcspn(newDescription, "\n")] = '\0'; // Remove newline character

        totalMoney -= newAmount - expenses[index].amount;
        totalExpense += newAmount - expenses[index].amount;

        expenses[index].amount = newAmount;
        strcpy(expenses[index].description, newDescription);
    }

    printf("Transaction edited successfully!\n\n");
}

void viewTransactionHistory() {
    printf("\n===== Transaction History =====\n\n");

    printf("Incomes:\n");
    for (int i = 0; i < incomeCount; i++) {
        printf("%d. Amount: $%.2f, Description: %s\n", i, incomes[i].amount, incomes[i].description);
    }

    printf("\nExpenses:\n");
    for (int i = 0; i < expenseCount; i++) {
        printf("%d. Amount: $%.2f, Description: %s\n", i, expenses[i].amount, expenses[i].description);
    }

    printf("\nPress Enter to continue...");
    getchar(); // Wait for Enter key
    getchar(); // Wait for Enter key
    printf("\n");
}

void generateReport() {
    printf("\n===== Financial Report =====\n\n");
    printf("Total Money: $%.2f\n", totalMoney);
    printf("Total Income: $%.2f\n", totalIncome);
    printf("Total Expense: $%.2f\n\n", totalExpense);

    printf("Income Transactions:\n");
    for (int i = 0; i < incomeCount; i++) {
        printf("%d. Amount: $%.2f, Description: %s\n", i, incomes[i].amount, incomes[i].description);
    }

    printf("\nExpense Transactions:\n");
    for (int i = 0; i < expenseCount; i++) {
        printf("%d. Amount: $%.2f, Description: %s\n", i, expenses[i].amount, expenses[i].description);
    }

    printf("\nReport generated successfully!\n\n");
}