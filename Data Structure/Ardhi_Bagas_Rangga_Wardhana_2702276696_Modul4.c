#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define TABLE_SIZE 1007

typedef struct Medicine {
    char id[30];
    char name[51];
    char manufacturer[26];
    char registration_number[11];
    char batch_number[17];
    struct Medicine* next;
} Medicine;

Medicine* hashTable[TABLE_SIZE];
int last_id = 1; // Making last_id global

void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

int hashFunction(char* id) {
    int sum = 0;
    for (int i = 0; id[i] != '\0'; i++) {
        sum += id[i];
    }
    return sum % TABLE_SIZE;
}

bool endsWith(const char *str, const char *suffix) {
    if (!str || !suffix) {
        return false;
    }
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    if (suffix_len > str_len) {
        return false;
    }
    return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

bool isNumeric(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isUniqueMedicineName(const char *name) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Medicine* current = hashTable[i];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                return false;
            }
            current = current->next;
        }
    }
    return true;
}

void viewMedicines() {
    int empty = 1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            empty = 0;
            break;
        }
    }

    if (empty) {
        printf("\nThere are no medicines!\n\n");
        return;
    }

    printf("| %-20s | %-20s | %-25s | %-15s | %-16s |\n", "ID", "Name", "Manufacturer", "Registration Number", "Batch Number");
    printf("---------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        Medicine* current = hashTable[i];
        while (current != NULL) {
            printf("| %-20s | %-20s | %-25s | %-15s | %-16s |\n",
                   current->id, current->name, current->manufacturer, current->registration_number, current->batch_number);
            current = current->next;
        }
    }
}

void insertMedicine(int count) {
    char name[51], manufacturer[26], registration_number[11], batch_number[17];

    for (int i = 0; i < count; i++) {
        // Input and validate Medicine Name
        do {
            printf("Enter Medicine Name (5 to 50 characters, unique): ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0'; // Remove newline character
            if (strlen(name) < 5 || strlen(name) > 50) {
                printf("Medicine Name must be between 5 and 50 characters.\n");
            } else if (!isUniqueMedicineName(name)) {
                printf("Medicine Name must be unique.\n");
            } else {
                break;
            }
        } while (true);

        // Input and validate Manufacturer Name
        do {
            printf("Enter Manufacturer Name (must end with 'Ltd.', 3 to 25 characters): ");
            fgets(manufacturer, sizeof(manufacturer), stdin);
            manufacturer[strcspn(manufacturer, "\n")] = '\0'; // Remove newline character
            if (strlen(manufacturer) < 3 || strlen(manufacturer) > 25) {
                printf("Manufacturer Name must be between 3 and 25 characters.\n");
            } else if (!endsWith(manufacturer, "Ltd.")) {
                printf("Manufacturer Name must end with 'Ltd.'\n");
            } else {
                break;
            }
        } while (true);

        // Input and validate Registration Number
        do {
            printf("Enter Registration Number (10 digits): ");
            fgets(registration_number, sizeof(registration_number), stdin);
            registration_number[strcspn(registration_number, "\n")] = '\0'; // Remove newline character
            if (strlen(registration_number) != 10 || !isNumeric(registration_number)) {
                printf("Registration Number must be numeric and 10 digits long.\n");
            } else {
                break;
            }
        } while (true);

        // Input and validate Batch/Lot Number
        do {
            printf("Enter Batch/Lot Number (at least 16 digits): ");
            fgets(batch_number, sizeof(batch_number), stdin);
            batch_number[strcspn(batch_number, "\n")] = '\0'; // Remove newline character
            if (strlen(batch_number) < 16) {
                printf("Batch/Lot Number must be at least 16 digits.\n");
            } else if (!isNumeric(batch_number)) {
                printf("Batch/Lot Number must be numeric.\n");
            } else {
                break;
            }
        } while (true);

        // Create new medicine entry
        Medicine* newMedicine = (Medicine*)malloc(sizeof(Medicine));
        if (newMedicine == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        sprintf(newMedicine->id, "M%05d-%s-%c%c", last_id++, registration_number, manufacturer[0], name[0]);
        strcpy(newMedicine->name, name);
        strcpy(newMedicine->manufacturer, manufacturer);
        strcpy(newMedicine->registration_number, registration_number);
        strcpy(newMedicine->batch_number, batch_number);
        newMedicine->next = NULL;

        // Insert the new medicine into the hash table
        int index = hashFunction(newMedicine->id);
        newMedicine->next = hashTable[index];
        hashTable[index] = newMedicine;

        printf("Medicine inserted successfully with ID: %s\n", newMedicine->id);
    }
}

void removeMedicine(char* id) {
    int index = hashFunction(id);
    Medicine* current = hashTable[index];
    Medicine* prev = NULL;

    while (current != NULL && strcmp(current->id, id) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Medicine not found.\n");
        return;
    }

    if (prev == NULL) {
        hashTable[index] = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Medicine removed successfully.\n");
}

void mainMenu() {
    int choice;

    while (1) {
        printf("1. View Medicines\n");
        printf("2. Insert Medicines\n");
        printf("3. Remove Medicine\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character left by scanf

        switch (choice) {
            case 1:
                viewMedicines();
                break;
            case 2: {
                int count;
                printf("Enter the number of medicines you want to insert: ");
                scanf("%d", &count);
                getchar(); // Clear the newline character left by scanf
                insertMedicine(count);
                break;
            }
            case 3: {
                printf("Enter Medicine ID: ");
                char id[30];
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = '\0'; // Remove newline character
                removeMedicine(id);
                break;
            }
            case 4:
                // Free all allocated memory before exiting
                for (int i = 0; i < TABLE_SIZE; i++) {
                    Medicine* current = hashTable[i];
                    while (current != NULL) {
                        Medicine* toFree = current;
                        current = current->next;
                        free(toFree);
                    }
                }
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

int main() {
    initializeTable();
    mainMenu();
    return 0;
}