#include <stdio.h>
#include <string.h>

struct data {
    char nama[100];
    int rank;
};

int main() {
    struct data data1[100];
    int T;
    printf("Enter the number of data: ");
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        printf("Enter name %d: ", i + 1);
        scanf(" %[^\n]", data1[i].nama);
        printf("Enter Rank %d: ", i+1);
        scanf("%d",&data1[i].rank);
    }

    
    for (int j = 0; j < T - 1; j++) {
        for (int k = 0; k < T - j - 1; k++) {
            if (data1[k].rank > data1[k + 1].rank ||
                (data1[k].rank == data1[k + 1].rank && strcmp(data1[k].nama, data1[k + 1].nama) > 0)) {
                // Swap ranks
                int tempRank = data1[k].rank;
                data1[k].rank = data1[k + 1].rank;
                data1[k + 1].rank = tempRank;

                // Swap names
                char tempName[100];
                strcpy(tempName, data1[k].nama);
                strcpy(data1[k].nama, data1[k + 1].nama);
                strcpy(data1[k + 1].nama, tempName);
            }
        }
    }

    printf("Sorted data based on rank:\n");
    for (int i = 0; i < T; i++) {
        printf("%s , %d\n", data1[i].nama, data1[i].rank);
    }

    return 0;
}