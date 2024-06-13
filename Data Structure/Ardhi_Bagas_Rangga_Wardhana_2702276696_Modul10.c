#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100

int heap[MAX_SIZE];
int heap_size = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap_size && heap[left] > heap[largest]) {
        largest = left;
    }
    if (right < heap_size && heap[right] > heap[largest]) {
        largest = right;
    }
    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        max_heapify(largest);
    }
}

void insert(int value) {
    if (heap_size == MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }

    heap[heap_size] = value;
    int current = heap_size;
    heap_size++;

    while (current != 0 && heap[(current - 1) / 2] < heap[current]) {
        swap(&heap[(current - 1) / 2], &heap[current]);
        current = (current - 1) / 2;
    }

    printf("Insert Success\n");
}

void print_spaces(float count) {
    for (int i = 0; i < (int)count; i++) {
        printf(" ");
    }
}

void view() {
    if (heap_size == 0) {
        printf("Heap is empty!\n");
        return;
    }

    int levels = 5;
    int max_index = (1 << levels) - 2;
    int level = 0;
    int nodes_in_level = 1;
    int index = 0;

    while (level < levels) {
        float spaces_between = (float)(1 << (levels - level + 1)) - 1.5;
        float spaces_before = spaces_between / 2.0;

        print_spaces(spaces_before);
        for (int i = 0; i < nodes_in_level; i++) {
            if (index < heap_size) {
                printf("%d", heap[index]);
            } else {
                printf("NL");
            }
            index++;
            if (i < nodes_in_level - 1) {
                print_spaces(spaces_between);
            }
        }
        printf("\n");

        level++;
        nodes_in_level *= 2;
        printf("\n");
    }

    // Adding extra spacing for the last level
    float last_level_spaces = (float)(1 << (levels + 1)) - 1;
    print_spaces(last_level_spaces);
    printf("\n");
}
void pop() {
    if (heap_size == 0) {
        printf("There is no data.\n");
        return;
    }

    printf("Removed element: %d\n", heap[0]);
    heap[0] = heap[heap_size - 1];
    heap[heap_size - 1] = -1; 
    heap_size--;
    max_heapify(0);
}

void clear_heap() {
    heap_size = 0;
}
void enter(){
	printf("\nPress Enter to continue... ");
    getchar();
    system("cls");
}
int main() {
    int choice;
    int value;

    while (1) {
        printf("MAX HEAP TREE\n");
        printf("=============\n");
        printf("1. Insert\n");
        printf("2. View\n");
        printf("3. Pop\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
         while(getchar() != '\n');
        switch (choice) {
            case 1:
			    printf("Input your data [1-100]: ");
			    if (scanf("%d", &value) != 1) {
			        printf("Invalid input! Please enter a number.\n");
			        while(getchar() != '\n');
			        enter();
			        break;
			    } else if (value < 1 || value > 100) {
			        printf("Invalid input! Please enter a number between 1 and 100.\n");
			    } else {
			        insert(value);
			    }
			    printf("\nPress Enter to continue... ");
			    getchar();
			    getchar();
			    system("cls");
			    break;

                printf("\nPress Enter to continue... ");
				getchar();
			    getchar();
			    system("cls");
                break;
            case 2:
            	printf("Only 5 levels shown\n");
                view();
                enter();
                break;
            case 3:
                pop();
                enter();
                break;
            case 4:
                printf("Exiting the program\n");
				clear_heap();
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
                enter();
        }
    }

    return 0;
}

