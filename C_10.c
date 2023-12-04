#include <stdio.h>

int main()
{
    int T, N, MMR;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        scanf("%d", &N);
        int angka[N];
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &angka[j]);
        }

        for (int j = 0; j < (N - 1); j++)
        {
            for (int k = 0; k < (N - 1); k++)
            {
                if (angka[k] > angka[k + 1])
                {
                    int blok = angka[k];
                    angka[k] = angka[k + 1];
                    angka[k + 1] = blok;
                }
            }
        }
        scanf("%d", &MMR);

        int ajg = 0;

        for (int j = 0; j < N; j++)
        {
            if (MMR == angka[N - 1])
            {
                printf("CASE #%d: %d %d\n", i + 1, angka[N - 2], MMR);
                ajg = 1;
                break;
            }
            else if (MMR == angka[j])
            {
                printf("CASE #%d: %d %d\n", i + 1, MMR, angka[j + 1]);
                ajg = 1;
                break;
            }
        }

        if(!ajg) printf("CASE #%d: -1 -1\n", i + 1);
    }
}