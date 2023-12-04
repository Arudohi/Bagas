#include <stdio.h>

int main() {
    int N, Q;

    scanf("%d", &N);

    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    scanf("%d", &Q);

    for (int caseNum = 1; caseNum <= Q; caseNum++) {
        long long Mi;
        scanf("%lld", &Mi);

        long long currentSum = 0;
        int maxLength = 0;
        int leftPointer = 0;

        for (int rightPointer = 0; rightPointer < N; rightPointer++) {
            currentSum += A[rightPointer];

            while (currentSum > Mi && leftPointer <= rightPointer) {
                currentSum -= A[leftPointer];
                leftPointer++;
            }

            if (rightPointer - leftPointer + 1 > maxLength) {
                maxLength = rightPointer - leftPointer + 1;
            }
        }

        if (currentSum <= Mi) {
            printf("Case #%d: %d\n", caseNum, maxLength);
        } else {
            printf("Case #%d: -1\n", caseNum);
        }
    }

    return 0;
}
