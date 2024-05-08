#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient {
    char name[26];
    char id[6];
    int age;
    char description[200];
    char code[10];
    struct patient* next;
};

struct patient* head = NULL;

void insert() {
    struct patient* newPatient;

    do {
        newPatient = (struct patient*)malloc(sizeof(struct patient));
        printf("Input patient name[4-25]: ");
        scanf(" %[^\n]", newPatient->name);
    } while (strlen(newPatient->name) < 4 || strlen(newPatient->name) > 25);

    do {
        printf("Input patient age[>= 0]: ");
        scanf("%d", &newPatient->age);
    } while (newPatient->age < 0);

    do {
        printf("Input patient ID[5]: ");
        scanf(" %s", newPatient->id);
    } while (strlen(newPatient->id) != 5);

    struct patient* current = head;
    while (current != NULL) {
        if (strcmp(current->id, newPatient->id) == 0) {
            printf("ID already exists!\n");
            return;
        }
        current = current->next;
    }

    do {
        printf("Input description[>= 6 Characters]: ");
        scanf(" %[^\n]", newPatient->description);
    } while (strlen(newPatient->description) < 6);

    do {
        printf("Input code[Red|Yellow|Green]: ");
        scanf(" %s", newPatient->code);
    } while (strcmp(newPatient->code, "Red") != 0 && strcmp(newPatient->code, "Yellow") != 0 && strcmp(newPatient->code, "Green") != 0);

    newPatient->next = NULL;

    if (head == NULL || strcmp(newPatient->code, head->code) > 0) {
        newPatient->next = head;
        head = newPatient;
    } else {
        struct patient* temp = head;
        while (temp->next != NULL && strcmp(newPatient->code, temp->next->code) <= 0) {
            temp = temp->next;
        }
        newPatient->next = temp->next;
        temp->next = newPatient;
    }

    printf("\nInsert Success !\n");
    printf("Press any key to continue. . . ");
    getchar();
    getchar();
    system("cls");
}

void view() {
    if (head == NULL) {
        printf("There is no queue yet!\n");
        printf("Press any key to continue. . . ");
        getchar();
        getchar();
        system("cls");
        return;
    }

    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("| No | Name                     | ID    | AGE  | Description                                       | Code   |\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    struct patient* current = head;
    int counter = 1;

    while (current != NULL) {
        if (strcmp(current->code, "Red") == 0) {
            printf("| %-3d| %-25s| %-6s| %-5d| %-50s| %-7s|\n", counter, current->name, current->id, current->age, current->description, current->code);
            counter++;
        }
        current = current->next;
    }

    current = head;

    while (current != NULL) {
        if (strcmp(current->code, "Yellow") == 0) {
            printf("| %-3d| %-25s| %-6s| %-5d| %-50s| %-7s|\n", counter, current->name, current->id, current->age, current->description, current->code);
            counter++;
        }
        current = current->next;
    }

    current = head;

    while (current != NULL) {
        if (strcmp(current->code, "Green") == 0) {
            printf("| %-3d| %-25s| %-6s| %-5d| %-50s| %-7s|\n", counter, current->name, current->id, current->age, current->description, current->code);
            counter++;
        }
        current = current->next;
    }
    printf("-------------------------------------------------------------------------------------------------------------\n");

    printf("Press any key to continue. . . ");
    getchar();
    getchar();
    system("cls");
}

void queue() {
    if (head == NULL) {
        printf("There is no queue yet!\n");
        printf("Press any key to continue. . . ");
        getchar();
        getchar();
        system("cls");
        return;
    }

    struct patient* removed = NULL;
    struct patient* current = head;

    while (current != NULL) {
        if (strcmp(current->code, "Red") == 0) {
            removed = current;
            break;
        }
        current = current->next;
    }

    if (removed == NULL) {
        current = head;

        while (current != NULL) {
            if (strcmp(current->code, "Yellow") == 0) {
                removed = current;
                break;
            }
            current = current->next;
        }
    }

    if (removed == NULL) {
        current = head;

        while (current != NULL) {
            if (strcmp(current->code, "Green") == 0) {
                removed = current;
                break;
            }
            current = current->next;
        }
    }

    if (removed != NULL) {
        printf("The next patient is:\n");
        printf("Name\t\t: %s\n", removed->name);
        printf("ID\t\t: %s\n", removed->id);
        printf("AGE\t\t: %d\n", removed->age);
        printf("Description\t: %s\n", removed->description);
        printf("Code\t\t: %s\n", removed->code);

        if (removed == head) {
            head = head->next;
        } else {
            current = head;
            while (current->next != NULL && current->next != removed) {
                current = current->next;
            }
            if (current->next != NULL) {
                current->next = removed->next;
            }
        }

        free(removed);
    } else {
        printf("No patients in the queue.\n");
    }

    printf("Press any key to continue. . . ");
    getchar();
    getchar();
    system("cls");
}

int main() {
    int menu;

    do {
        printf("Sunib Patient Entry\n");
        printf("====================\n");
        printf("[1] Insert Patient\n");
        printf("[2] View List\n");
        printf("[3] Next Queue\n");
        printf("[4] Exit\n");
        printf(">>> ");
        scanf("%d", &menu);
        system("cls");
        switch (menu) {
            case 1:
                insert();
                break;
            case 2:
                view();
                break;
            case 3:
                queue();
                break;
            case 4:
                while (head != NULL) {
                    struct patient* temp = head;
                    head = head->next;
                    free(temp);
                }
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (1);

    return 0;
}
