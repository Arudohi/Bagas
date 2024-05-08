#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 1007
#define MAX_MEDICINES 16000
#define MAX_NAME_LENGTH 51
#define MAX_MANUFACTURER_LENGTH 26
#define MIN_BATCH_LENGTH 16

// Structure to hold medicine data
typedef struct {
    char id[21]; // 20 characters for ID (MXXXXX-XXXXXXXXXX-X)
    char name[MAX_NAME_LENGTH];
    char manufacturer[MAX_MANUFACTURER_LENGTH];
    char registrationNumber[11];
    char batchNumber[MAX_NAME_LENGTH];
} Medicine;

// Hash table node structure
typedef struct Node {
    Medicine *data;
    struct Node *next;
} Node;

Node *hashTable[HASH_SIZE]; // Global hash table

// Function prototypes
void toUpperCase(char *str);
int hashFunction(const char *key);
void initializeHashTable();
void viewMedicine();
void insertMedicine();
void removeMedicine();
void freeHashTable();
int isUniqueID(const char *id);
int isNumeric(const char *str);
int isValidManufacturer(const char *str);
int isValidBatch(const char *str);
void stripNewline(char *str); // Function declaration

int main() {
    int choice;
    initializeHashTable();

    do {
        printf("\nSunib Hospital\n");
        printf("===============\n");
        printf("1. View Medicine\n");
        printf("2. Insert Medicine\n");
        printf("3. Remove Medicine\n");
        printf("4. Exit\n");
        printf(">>> ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
                viewMedicine();
                break;
            case 2:
                insertMedicine();
                break;
            case 3:
                removeMedicine();
                break;
            case 4:
                printf("Exiting program...\n");
                freeHashTable();
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
    } while (1);

    return 0;
}

// Hash function to calculate index
int hashFunction(const char *key) {
    int sum = 0;
    while (*key) {
        sum += *key++;
    }
    return sum % HASH_SIZE;
}

// Initialize hash table
void initializeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// View all medicines
void viewMedicine() {
    int empty = 1;
    
    // Check if hash table is empty
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashTable[i] != NULL) {
            empty = 0;
            break;
        }
    }
    
    // If hash table is empty, display message and wait for any key press
    if (empty) {
        printf("There are no medicines!\n");
        printf("Press any key to continue...\n");
        getchar(); // Wait for any key press
        return; // Exit function
    }
    
    // Print table header
    printf("--------------------------------------------------------------------------------------------\n");
    printf("| %-20s | %-50s | %-30s | %-15s | %-20s |\n", "Medicine ID", "Medicine Name", "Manufacturer", "Reg. Number", "Batch Number");
    printf("--------------------------------------------------------------------------------------------\n");

    // Print table rows
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *current = hashTable[i];
        while (current != NULL) {
            printf("| %-20s | %-50s | %-30s | %-15s | %-20s |\n",
                   current->data->id, current->data->name, current->data->manufacturer,
                   current->data->registrationNumber, current->data->batchNumber);
            current = current->next;
        }
    }
    printf("--------------------------------------------------------------------------------------------\n");
}

// Insert a new medicine
void insertMedicine() {
    printf("\nInsert Medicine:\n");

    Medicine *newMedicine = (Medicine *)malloc(sizeof(Medicine));
    if (newMedicine == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Medicine Name (between 5 and 50 characters): ");
    fgets(newMedicine->name, sizeof(newMedicine->name), stdin);
    stripNewline(newMedicine->name);
    if (strlen(newMedicine->name) < 5 || strlen(newMedicine->name) > 50) {
        printf("Medicine Name must be between 5 and 50 characters.\n");
        free(newMedicine);
        return;
    }

    printf("Enter Manufacturer Name (must end with 'Ltd.' and between 3 and 25 characters): ");
    fgets(newMedicine->manufacturer, sizeof(newMedicine->manufacturer), stdin);
    stripNewline(newMedicine->manufacturer);
    if (!isValidManufacturer(newMedicine->manufacturer)) {
        printf("Invalid Manufacturer Name!\n");
        printf("Press any key to continue...");
        getchar(); // Wait for any key press
        free(newMedicine);
        return;
    }

    printf("Enter Registration Number (10 digits): ");
    fgets(newMedicine->registrationNumber, sizeof(newMedicine->registrationNumber), stdin);
    stripNewline(newMedicine->registrationNumber);
    if (!isNumeric(newMedicine->registrationNumber) || strlen(newMedicine->registrationNumber) != 10) {
        printf("Invalid Registration Number!\n");
        printf("Press any key to continue...");
        getchar(); // Wait for any key press
        free(newMedicine);
        return;
    }

    printf("Enter Batch/Lot Number (>=16): ");
    fgets(newMedicine->batchNumber, sizeof(newMedicine->batchNumber), stdin);
    stripNewline(newMedicine->batchNumber);

    if (strlen(newMedicine->batchNumber) < 16) {
        printf("Batch/Lot Number must be at least 16 characters.\n");
        printf("Press any key to continue...");
        getchar(); // Wait for any key press
        free(newMedicine);
        return;
    }

    int idCount = 0;
    char manufacturerInitial = toupper(newMedicine->manufacturer[0]);
    char medicineInitial = toupper(newMedicine->name[0]);
    char id[21];
    do {
        sprintf(id, "M%05d-%s-%c%c", idCount++, newMedicine->registrationNumber, manufacturerInitial, medicineInitial);
    } while (!isUniqueID(id));
    strcpy(newMedicine->id, id);

    int index = hashFunction(newMedicine->id);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = newMedicine;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    printf("Medicine added successfully!\n");
}

// Remove a medicine
void removeMedicine() {
    char id[21];
    printf("Input Medicine ID to delete: ");
    fgets(id, sizeof(id), stdin);
    stripNewline(id);

    int index = hashFunction(id);
    Node *current = hashTable[index];
    Node *prev = NULL;

    while (current != NULL && strcmp(current->data->id, id) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Medicine not found!\n");
        printf("Press any key to continue...");
        getchar(); // Wait for any key press
        return;
    }

    printf("Medicine found:\n");
    printf("Medicine ID: %s\n", current->data->id);
    printf("Medicine Name: %s\n", current->data->name);
    printf("Manufacturer: %s\n", current->data->manufacturer);
    printf("Registration Number: %s\n", current->data->registrationNumber);
    printf("Batch Number: %s\n\n", current->data->batchNumber);

    char confirm;
    printf("Do you want to remove this medicine? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        if (prev == NULL) {
            hashTable[index] = current->next;
        } else {
            prev->next = current->next;
        }
        free(current->data);
        free(current);
        printf("Medicine removed successfully!\n");
    } else if (confirm == 'n' || confirm == 'N') {
        printf("Operation canceled.\n");
    } else {
        printf("Invalid input. Operation canceled.\n");
    }
}

// Free allocated memory of the hash table
void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *current = hashTable[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        }
    }
}

// Convert string to uppercase
void toUpperCase(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

// Check if ID is unique
int isUniqueID(const char *id) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *current = hashTable[i];
        while (current != NULL) {
            if (strcmp(current->data->id, id) == 0) {
                return 0;
            }
            current = current->next;
        }
    }
    return 1;
}

// Check if string is numeric
int isNumeric(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

// Validate manufacturer name
int isValidManufacturer(const char *str) {
    int length = strlen(str);
    return (length >= 4 && length <= 28 && strcmp(str + length - 4, "Ltd.") == 0);
}

// Validate batch number
int isValidBatch(const char *str) {
    return strlen(str) >= MIN_BATCH_LENGTH;
}

// Strip newline character from a string
void stripNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}
