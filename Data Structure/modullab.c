#include <stdio.h>
#include <string.h>

struct Medicine {
    char code[7];
    char name[20];
    char disease[20];
    int stock;
    int price;
};

void displayMedicines(struct Medicine medicines[], int numMedicines) {
    // printf("                                +------------------------+\n");
    // printf("                                |     SUNIB Hospital     |\n");
    // printf("                                +------------------------+\n");
    // printf("+-----------------------------------------------------------------------------------------------+\n");
    // printf("| No. | Medicine Code   | Medicine Name         | Disease               | Stock | Price         |\n");
    // printf("|-----------------------------------------------------------------------------------------------|\n");
    // for (int i = 0; i < numMedicines; i++) {
    //     printf("| %-3d | %-14s | %-21s | %-21s | %-5d | Rp. %d.%03d,-    |\n", i + 1, medicines[i].code, medicines[i].name, medicines[i].disease, medicines[i].stock, medicines[i].price / 1000, medicines[i].price % 1000);
    // }
    // printf("+-----------------------------------------------------------------------------------------------+\n\n");
}

void addStock(struct Medicine medicines[], int numMedicines) {
    displayMedicines(medicines, numMedicines);
    char code[7];
    int quantity;
    printf("\nEnter Medicine Code : ");
    scanf("%s", code);

    struct Medicine *medicine = NULL;
    for (int i = 0; i < numMedicines; i++) {
        if (strcmp(medicines[i].code, code) == 0) {
            medicine = &medicines[i];
            break;
        }
    }

    if (medicine != NULL) {
        printf("\nEnter Medicine Quantity (1-100): ");
        scanf("%d", &quantity);
        if (quantity >= 1 && quantity <= 100) {
            medicine->stock += quantity;
            // printf("\nStock added successfully!\n");
            // getchar(); // Clear input buffer
            printf("\nPress Enter to continue...\n");
            getchar(); // Wait for Enter key press
        } else {
            printf("Invalid quantity! Quantity must be between 1 and 100.\n");
        }
    } else {
        printf("Medicine Code Doesn't Exist!\n");
    }
}

void sell(struct Medicine medicines[], int numMedicines) {
    displayMedicines(medicines, numMedicines);
    char code[7];
    int quantity;
    printf("\nEnter Medicine Code : ");
    scanf("%s", code);

    struct Medicine *medicine = NULL;
    for (int i = 0; i < numMedicines; i++) {
        if (strcmp(medicines[i].code, code) == 0) {
            medicine = &medicines[i];
            break;
        }
    }

    if (medicine != NULL) {
        printf("\nEnter Medicine Quantity [1-%d]: ", medicine->stock);
        scanf("%d", &quantity);
        if (quantity >= 1 && quantity <= medicine->stock) {
            int total_price = medicine->price * quantity;
            // printf("Total Price = Rp %d,- x %d = Rp %d,-\n", medicine->price, quantity, total_price);
            printf("\n+----Total Price----+\n");
            printf("Rp. %.03d,-\n", medicine->price);
            printf("Quantity: %d\n", quantity);
            printf("--------------------x\n");
            printf("Total: Rp. %.03d,-\n", total_price);
            printf("+-------------------+\n\n\n");
            medicine->stock -= quantity;
            printf("--Thank You--\n");
            getchar(); // Clear input buffer
            printf("\nPress Enter to continue...");
            getchar(); // Wait for Enter key press
        } else {
            printf("Invalid quantity! Quantity must be between 1 and %d.\n", medicine->stock);
        }
    } else {
        printf("Medicine Code Doesn't Exist!\n");
    }
}

int main() {
    struct Medicine medicines[] = {
        {"DIZ001", "Paramex", "Dizziness", 120, 14000},
        {"FLU001", "Panadol", "Flu & Fever", 57, 8000},
        {"DIA001", "Diatabs", "Diarrhea", 10, 6500},
        {"DIA002", "Diapet", "Diarrhea", 18, 6000}
    };
    int numMedicines = sizeof(medicines) / sizeof(medicines[0]);

    int choice;
    while (1) {
        printf("                                +------------------------+\n");
        printf("                                |     SUNIB Hospital     |\n");
        printf("                                +------------------------+\n");
        printf("+-----------------------------------------------------------------------------------------------+\n");
        printf("| No. | Medicine Code   | Medicine Name         | Disease               | Stock | Price         |\n");
        printf("|-----------------------------------------------------------------------------------------------|\n");
        for (int i = 0; i < numMedicines; i++) {
            printf("| %-3d | %-14s | %-21s | %-21s | %-5d | Rp. %d.%03d,-    |\n", i + 1, medicines[i].code, medicines[i].name, medicines[i].disease, medicines[i].stock, medicines[i].price / 1000, medicines[i].price % 1000);
        }
        printf("+-----------------------------------------------------------------------------------------------+\n\n");

        printf("Menu :\n");
        printf("[1.] Add Stock\n");
        printf("[2.] Sell\n");
        printf("[3.] Exit\n");
        printf("\nInput choice [1-3]: ");
        
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStock(medicines, numMedicines);
                break;
            case 2:
                sell(medicines, numMedicines);
                break;
            case 3:
                printf("Exiting program...");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
