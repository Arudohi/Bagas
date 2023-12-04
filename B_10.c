#include <stdio.h>
#include <string.h>

struct mhs
{
    char name[11];
    int nilai;
};

int main()
{
    int T, N;
    char nama[11];
    int cok;
    struct mhs blok;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        cok = 1;
        scanf("%d", &N);
        struct mhs orang[N];
        for (int j = 0; j < N; j++)
        {
            scanf(" %[^#]#%d", orang[j].name, &orang[j].nilai);
        }
        scanf(" %[^\n]", nama);

        for (int j = 0; j < (N - 1); j++)
        {
            for (int k = 0; k < (N - 1); k++)
            {
                if (orang[k].nilai < orang[k + 1].nilai)
                {
                    blok = orang[k];
                    orang[k] = orang[k + 1];
                    orang[k + 1] = blok;
                }
            }
        }

        for (int j = 0; j < (N - 1); j++)
        {
            for (int k = 0; k < (N - 1); k++)
            {
                if (orang[k].nilai == orang[k + 1].nilai)
                {
                    if (strcmp(orang[k].name, orang[k + 1].name) > 0)
                    {
                        blok = orang[k];
                        orang[k] = orang[k + 1];
                        orang[k + 1] = blok;
                    }
                }
            }
        }

        for (int j = 0; j < N; j++)
        {
            // printf("%s %d", orang[j].name, orang[j].nilai);
            if(strcmp(nama, orang[j].name) == 0) cok = cok + j;
        }
        printf("Case #%d: %d\n", i + 1, cok);
    }
}