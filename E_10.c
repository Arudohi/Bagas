#include <stdio.h>

long long max(long long a, long long b)
{
    return a > b ? a : b;
}

int main()
{
    int T, N;
    long long M;
    scanf("%d", &T);

    for (int i = 0; i < T; i++)
    {
        scanf("%d %lld", &N, &M);

        long long A[N];
        for (int j = 0; j < N; j++)
        {
            scanf("%lld", &A[j]);
        }

        long long hasil = 0;
        int arrA = 0, arrB = 0, maxPanjang = 0;

        while (arrA < N)
        {
            hasil += A[arrA];
            while (hasil > M)
            {
                hasil -= A[arrB];
                arrB++;
            }

            int panjang = arrA - arrB + 1;
            maxPanjang = max(maxPanjang, panjang);
            arrA++;
        }

        if (maxPanjang == 0)
        {
            printf("Case #%d: -1\n", i + 1);
        }
        else
        {
            printf("Case #%d: %d\n", i + 1, maxPanjang);
        }
    }

    return 0;
}