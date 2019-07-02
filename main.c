#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"


int main()
{
    arqui_t arquivo[2048]; // salvo as declaraçoes
    char nomearq[256];


    printf("Entre com o nome do arquivo:\n");
    scanf("%s", nomearq);

    arquivo_t(arquivo ,nomearq); //(guardo declaracoes, string)

    return 0;
}
