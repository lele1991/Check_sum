#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int arquivo_t(arqui_t *registro, char nome[]){

    int i = 0, j = 0, k=0, caso=0;
    char buffer[100];
    unsigned char calc = 0;

    FILE *fp;//cria variavel - auxiliar pra mexer no arquivo
    fp = fopen(nome, "r");

    if(fp==NULL){
        printf("erro");
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer,sizeof (buffer), fp)!= NULL){
       // puts(buffer);
        registro[i].doispontos = buffer[0];
        sscanf(buffer+1, "%2x %4x %2x",  (unsigned int *)&registro[i].tamanho,
                                         (unsigned int *)&registro[i].endereco,
                                         (unsigned int *)&registro[i].tipo);
        //int ret = sscanf...  - verificacao
        int tam = strlen(buffer);
        sscanf(buffer+tam-3, "%2x", (unsigned int *)&registro[i].checksum);
       // printf("\t%d\n", ret);
        for(k=0, j=9; k<registro[i].tamanho; k++, j=j+2){
            sscanf(buffer+j, " %2x", (unsigned int *)&registro[i].data[k]);
        }
        if (registro[i].tamanho!=0 || registro[i].endereco!=0 || registro[i].tipo!=1 || registro[i].checksum!=0xFF){
        /*    printf("%c %x %x %x %x %x %x\n", registro[i].doispontos,
                                             registro[i].tamanho,
                                             registro[i].endereco,
                                             registro[i].tipo,
                                             registro[i].data[0],
                                             registro[i].data[1],
                                             registro[i].checksum);*/
        }


        calc = check(&registro[i]);
        if(calc!=registro[i].checksum){
            printf("O cheksum da linha %d nao corresponde ao calculado", i);
            break;
        }
        i++;

       // break;
    }
    printf("Escolha o modo como o dado serah mostrado:\n(1)decimal com sinal\n(2)decimal sem sinal\n"
                                               "(3)hexadecimal\n(4)octal\n(5)binario\n");
    scanf("%d", &caso);
    escolha(caso, registro, i);

    fclose(fp);

    return 0;
    //NAO PODE APARECER FF NO ULTIMO
}

unsigned char check(arqui_t *reg){
    unsigned int soma = 0, i=0;
    unsigned char inv = 0;

    soma =  (unsigned int)reg->tamanho +
            (unsigned int)reg->endereco/256 +
            (unsigned int)reg->endereco%256 +
            (unsigned int)reg->tipo;
    for(i=0; i<reg->tamanho; i++){
       soma += (unsigned int)reg->data[i];
    }
    //endereco/256.. pego o byte + sig    ... endereco%256.. pego o byte - sig
    inv = (~(unsigned char)soma%256) +1; // extrai o byte - sig
   // printf("%x\n", inv);

    return inv;
}

void escolha(int casos, arqui_t*registro, int reg){
    int i, k, j;
    unsigned char temp=0;

    switch (casos){
        case 1:
            for(i=0; i<reg; i++){
                for(k=0; k<registro[i].tamanho; k++){
                    printf("%d ", (char)registro[i].data[k]);
                }
                printf("\n");
            }
            break;

        case 2:
            for(i=0; i<reg; i++){
                for(k=0; k<registro[i].tamanho; k++){
                    printf("%u ", (unsigned char)registro[i].data[k]);
                }
                printf("\n");
            }
            break;

        case 3:
            for(i=0; i<reg; i++){
                for(k=0; k<registro[i].tamanho; k++){
                    printf("%x ", (unsigned char)registro[i].data[k]);
                }
                printf("\n");
            }
            break;

        case 4:
            for(i=0; i<reg; i++){
                for(k=0; k<registro[i].tamanho; k++){
                    printf("%o ", (unsigned char)registro[i].data[k]);
                }
                printf("\n");
            }
            break;

        case 5:
            for(i=0; i<reg; i++){
                for(k=0; k<registro[i].tamanho; k++){
                    temp = registro[i].data[k];
                    for(j=0; j<8; j++){//8 bits
                        if(temp & 0b10000000){
                            printf("1");
                        }
                        else{
                            printf("0");
                        }
                       // printf("%u", temp%2);//primeiro bit -  mais à direita
                        temp = temp*2;//elimino o primeiro bit e vai pro lugar do primeiro
                    }
                printf(" ");
                }
                printf("\n");
            }
            break;
    }
}





