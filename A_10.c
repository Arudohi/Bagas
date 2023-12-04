#include <stdio.h>

int main()
{
    int N,M;
    scanf("%d %d", &N, &M);
    int angka[N];
    int hilang;
    int cok;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &angka[i]);
    }
    for (int i = 0; i < M; i++)
    {
        scanf("%d" , &hilang);
        for (int j = 0; j < N; j++)
        {
            if(hilang == angka[j])
            {
                angka[j] = 0;
            }
        }
    }
    
    cok = 0;
    for (int i = 0; i < N; i++)
    {
        if(cok < angka[i])
        {
            cok = angka[i];
        }
    }
    if(cok != 0) printf("Maximum number is %d\n", cok);
    else printf("Maximum number is -1\n");
}