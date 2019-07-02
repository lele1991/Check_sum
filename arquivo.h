#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

struct arqui{
    char doispontos;
	unsigned char  tamanho;
	short int endereco;
	unsigned char tipo;
	unsigned char data[255]; //maximo que cabe no 'tamanho'
	unsigned char checksum; //verificacao de erros
};

typedef struct arqui arqui_t;

int arquivo_t(arqui_t*registro, char nome[]);
unsigned char check(arqui_t *reg);
void escolha(int casos, arqui_t*registro, int reg);

#endif // ARQUIVO_H_INCLUDED
