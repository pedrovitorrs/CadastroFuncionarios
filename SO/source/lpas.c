#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Interpreta programas em LPAS. A linguagem LPAS utiliza um único registrador do processador para executar as instruções sobre números inteiros.


/*
Estrutura de dados para guardar a instrução LPAS e o argumento da instrução LPAS 
*/
typedef struct{
    char instrucaoLPAS[50]; //instrucaoLPAS: READ..
    char argumentoInstrucaoLPAS[50]; //argumentoInstrucaoLPAS: X
}TInstrucao;

/*
Estrutura de dados para guardar variaveis do registrador
*/
typedef struct{
    int valorVariavel; //valorVariavel: 13
    char variavel[5]; //variavel: X
}TRegistrador;

/*
Aloca dinamicamente 50 posicoes para guardar instrucoes no vetor de estrutura de instrucoes
e retorna um ponteiro para a estrutura 
*/
TInstrucao* alocaDinamicamenteVetor(){
    int N = 50;
    return (TInstrucao*) malloc(N*sizeof(TInstrucao));
}

/*
Aloca dinamicamente N posicoes para guardar instrucoes no vetor de estrutura de registrador
e retorna um ponteiro para a estrutura 
*/
TRegistrador* alocaDinamicamenteVetorRegistrador(int quantidadeAlocar){
    return (TRegistrador*) malloc((quantidadeAlocar+1)*sizeof(TRegistrador));
}

/*
Libera uma regiao de memoria previamente alocada
*/
void liberaVetorInstrucao(TInstrucao *vetorInstrucao){
    free(vetorInstrucao);
}

/*
Libera uma regiao de memoria previamente alocada
*/
void liberaVetorRegistrador(TRegistrador *vetorRegistrador){
    free(vetorRegistrador);
}

/*
Essa função recebe como parâmetro um ponteiro para char
E verifica se contém somente numeros.
Retorna 0, caso a variável tiver recebido alguma letra
Retorna 1 caso a variavel conter somente numeros
*/
int verificaNum(char *string){
    int i;
    for(i=0;i<strlen(string);i++){
        if(isalpha(string[i])!=0){
            return 0;
        }
    }
    return 1;
}

/*
Essa função recebe como parâmetro um ponteiro para char
E verifica há caracteres ou esta vazio.
Retorna 0, caso a variável conter espaços ou estiver vazio
Retorna 1 caso a variavel caracteres
*/
int verificaString(char *vetor){
    int i=0;
    if(vetor[i] == '\0' || vetor[i] == ' ' || strlen(vetor)==0)
        return 0;
    return 1;
}

/*
Funcao que recebe por parametro um ponteiro para char
limpa uma string inserindo o o delimitador
final de caracter nas posicao correta
*/
void cleanString(char* ref) {
    int i = 0;
    while(ref[i] != '\n')
        i++;
    ref[i] = '\0';
}

/*
Funcao que recebe como parametro um ponteiro para char, um inteiro e 
um char constante, mostra na tela uma mensagem e entao recebe
por input de teclado uma string  
*/
void readString(char* ref, int length, const char message[]){
    printf("%s", message);
    setbuf(stdin, NULL);
    fgets(ref, length, stdin);
    setbuf(stdin, NULL);
    cleanString(ref);
}

/*
Funcao que recebe um ponteiro para char como parametro
e retorna este char como um numero inteiro 
*/
int castInteiro(char *args){
    return strtol(args, NULL, 10);
}


/*
Recebe como parametro um ponteiro para char e um ponteiro
para um matriz de char, percorre o primeiro ponteiro para char
e divide os seus caractere por um delimitadores (que no caso é o Espaco)
adicionando assim cada string quebrada na matriz de char 
*/
void splitString(char *str, char strings[][50]){
    int i = 0;
    char *ponteiroChar = strtok(str, " "); //quebra uma string por um delimitador Espaco
    
    while (ponteiroChar != NULL){
        strcpy(strings[i++], ponteiroChar); //copiar cada string para a posição correta
        ponteiroChar = strtok (NULL, " ");
    }
} 


/*
Recebe como parametro um vetor de TRegistrador, um ponteiro para char e um inteiro
percorre as posicoes do vetor de registrador e compara se os argumentos da instrucao sao semelhantes naquele vetor.
Retorna a posicao do vetor caso encontrar as informacoes semelhantes.
Retorna -1 caso não encontrar informacoes semelhantes no vetor de registrador.
*/
int pesquisaVariavel(TRegistrador* vetorRegistrador,char *argsInstrucao,int tamanho){
    int i,posicao=0;
    for(i=0;i<=tamanho;i++){
        if(strcmp(vetorRegistrador[i].variavel,argsInstrucao)==0)
            return posicao;
        else
            posicao++;
    }
    return -1;
}

/*
Funcao que recebe um ponteiro para char como parametro
e retorna este char como um numero inteiro 
*/
int loadNumero(char *args){
    return castInteiro(args);
}


/*
Recebe como parametro um vetor de TRegistrador, um ponteiro para char e um inteiro,
percorre as posicoes do vetor de registrador e caso encontrar as informacoes semelhantes
no vetor, retorna o valor da variavel 
*/
int loadVariavel(TRegistrador *vetorRegistrador,char *argsInstrucao, int tamanhoVetorRegistrador){
    int posicaoVariavel;
    posicaoVariavel = pesquisaVariavel(vetorRegistrador,argsInstrucao,tamanhoVetorRegistrador);
    if(posicaoVariavel!=-1)
        return vetorRegistrador[posicaoVariavel].valorVariavel;
    return -1;
}


/*
Recebe como parametro um vetor de TRegistrador, um ponteiro para char e um inteiro,
le um valor input do teclado e adiciona aquele valor em uma posicao do vetor de registrador
*/
void readVariavel(TRegistrador *vetorRegistrador,char *nomeVariavel, int *auxiliaTamanhoVetorRegistrador){
    printf(".");
    scanf("%d",&vetorRegistrador[*auxiliaTamanhoVetorRegistrador].valorVariavel);
    strcpy(vetorRegistrador[*auxiliaTamanhoVetorRegistrador].variavel,nomeVariavel);
    (*auxiliaTamanhoVetorRegistrador)++;
}


/*
Recebe como parametro um vetor de TRegistrador, um ponteiro para char e um inteiro,
mostra na tela o valor de uma determinada variavel, caso ela ja tenha sido declarada 
*/
void writeVariavel(TRegistrador *vetorRegistrador,char *argsInstrucao, int tamanhoVetorRegistrador){
    int posicaoVariavel;
    posicaoVariavel = pesquisaVariavel(vetorRegistrador,argsInstrucao,tamanhoVetorRegistrador);
    if(posicaoVariavel!=-1)
        printf("%d", vetorRegistrador[posicaoVariavel].valorVariavel);
}

/*
Recebe como parametro um vetor de TRegistrador, um ponteiro para char e um inteiro,
caso a variavel passada por parametro ja tenha sido declarada e esteja armazenada no vetor
de registrador, ele adiciona o valor do registrador nesta posicao do vetor de registrador
*/
void storeVariavel(TRegistrador *vetorRegistrador,char *argsInstrucao, int tamanhoVetorRegistrador, int registrador){
    int posicaoVariavel;
    posicaoVariavel = pesquisaVariavel(vetorRegistrador,argsInstrucao,tamanhoVetorRegistrador);
    if(posicaoVariavel!=-1) // Se tiver encontrado o valor no vetor de registrador 
        vetorRegistrador[posicaoVariavel].valorVariavel = registrador;
    else{ // Se nao tiver encontrado o valor no vetor de registrador
        // E util para funcao store pois o argumento desta instrucao nem sempre estará 
        // previamente declarada no vetor de registrador, por isso é necessario fazer aqui a adicao do valor
        strcpy(vetorRegistrador[tamanhoVetorRegistrador].variavel,argsInstrucao);
        vetorRegistrador[tamanhoVetorRegistrador].valorVariavel = registrador;
    }
}

/*
Recebe como parametro um vetor de TInstrucao e um inteiro,
percorre o vetor de instrucao e caso encontrar uma palavra especifica no vetor,
no caso a palavra é "READ" retorna a quantidade de vezes que a palavra apareceu
*/
int contaInstrucaoRead(TInstrucao *vetorInstrucao,int contadorInstrucao){
    int contadorRead=0,i;
    for(i=0;i<contadorInstrucao;i++){
        if(strcmp(vetorInstrucao[i].instrucaoLPAS,"READ")==0){
            contadorRead++;
        }
    }
    return contadorRead;
}

/*
Recebe como parametro um vetor de TInstrucao, um ponteiro para char e um inteiro,
funcao que recebe as instrucoes do programa LPAS e adiciona no vetor de instrucao,
caso estas instrucoes esteja vazia a funcao e encerrada
*/
void editarProgramaLPAS(TInstrucao *vetorInstrucao, int *contadorInstrucao){
    int contadorInput=0;
    char copiaInstrucaoLPAS[50], stringQuebrada[1][50];

    printf("\n\tMaquina de Execucao LPAS [Editar Programa]\n");
    printf("\nPara finalizar tecle ENTER em uma linha em branco. \n");
    printf("\n---------------\n");
    
    do{
        printf("%d",contadorInput);
        readString(copiaInstrucaoLPAS, 50, ". ");
        
        if(verificaString(copiaInstrucaoLPAS)==1){
            splitString(copiaInstrucaoLPAS,stringQuebrada);
            strncpy(vetorInstrucao[*contadorInstrucao].instrucaoLPAS,stringQuebrada[0],50);
            strncpy(vetorInstrucao[*contadorInstrucao].argumentoInstrucaoLPAS,stringQuebrada[1],50);
            (*contadorInstrucao)++;
        }

        contadorInput++;
    }while(verificaString(copiaInstrucaoLPAS)!=0);
    printf("\n");
}

/*
Recebe como parametro um vetor de TInstrucao, um ponteiro para char e um inteiro,
percorre o vetor de instrucoes e mostra na tela do usuario as intrucoes que foram inseridas
na funcao de editar programa LPAS
*/
void exibirProgramaLPAS(TInstrucao *vetorInstrucao, int contadorInstrucao){
    int i;
    printf("\n\tMaquina de Execucao LPAS [Exibir Programa]\n\n");
    for(i=0;i<contadorInstrucao;i++)
        printf("%s %s\n",vetorInstrucao[i].instrucaoLPAS, vetorInstrucao[i].argumentoInstrucaoLPAS);
}

/*
Recebe como parametro um vetor de TInstrucao, um ponteiro para char e um inteiro,
percorre o vetor de instrucoes executando assim as instrucoes de acordo com as funcoes
pre estabelecidade, o programa e interrompido caso uma isntrucao esteja sem argumento e caso
no final da instrucoes nao sejam inseridas a instrucao HALT que encerra o programa
*/
void executarProgramaLPAS(TInstrucao *vetorInstrucao, int contadorInstrucao){
    TRegistrador *vetorRegistrador;
    int i, contadorInstrucaoRead=0,auxiliaContadorRegistrador=0;
    int registrador;

    contadorInstrucaoRead = contaInstrucaoRead(vetorInstrucao,contadorInstrucao);
    vetorRegistrador = alocaDinamicamenteVetorRegistrador(contadorInstrucaoRead);
    
    printf("\n\tMaquina de Execucao LPAS [Executar Programa]\n\n");
    if(strcmp(vetorInstrucao[contadorInstrucao-1].instrucaoLPAS,"HALT")==0){
        // Percorre ate a ultima posicao, pois a ultima posicao ser ao HALT
        for(i=0;i<contadorInstrucao-1;i++){
            //Se o argumento da instrucao nao for vazio, realiza a instrucao
            if(verificaString(vetorInstrucao[i].argumentoInstrucaoLPAS)){
                if(strcmp(vetorInstrucao[i].instrucaoLPAS,"LOAD")==0){
                    //Caso o argumento da instrucao seja um numero -> Fazer o load caso seja uma variavel
                    if(verificaNum(vetorInstrucao[i].argumentoInstrucaoLPAS))
                        registrador = loadNumero(vetorInstrucao[i].argumentoInstrucaoLPAS);
                    //Caso o argumento da instrucao seja uma letra/palavra
                    if(!verificaNum(vetorInstrucao[i].argumentoInstrucaoLPAS))
                        registrador = loadVariavel(vetorRegistrador,vetorInstrucao[i].argumentoInstrucaoLPAS,contadorInstrucaoRead);
                }

                if(strcmp(vetorInstrucao[i].instrucaoLPAS,"READ")==0)
                    readVariavel(vetorRegistrador,vetorInstrucao[i].argumentoInstrucaoLPAS,&auxiliaContadorRegistrador);
                
                if(strcmp(vetorInstrucao[i].instrucaoLPAS,"WRITE")==0)
                    writeVariavel(vetorRegistrador,vetorInstrucao[i].argumentoInstrucaoLPAS,contadorInstrucaoRead);
                
                if(strcmp(vetorInstrucao[i].instrucaoLPAS,"STORE")==0)
                    storeVariavel(vetorRegistrador,vetorInstrucao[i].argumentoInstrucaoLPAS,contadorInstrucaoRead, registrador);
            
                if(strcmp(vetorInstrucao[i].instrucaoLPAS,"ADD")==0){
                    //Caso o argumento da instrucao seja um numero 
                    if(verificaNum(vetorInstrucao[i].argumentoInstrucaoLPAS))
                        registrador += loadNumero(vetorInstrucao[i].argumentoInstrucaoLPAS);
                    //Caso o argumento da instrucao seja um caractere
                    if(!verificaNum(vetorInstrucao[i].argumentoInstrucaoLPAS))
                        registrador += loadVariavel(vetorRegistrador,vetorInstrucao[i].argumentoInstrucaoLPAS,contadorInstrucaoRead);
                }

                if(strcmp(vetorInstrucao[i].instrucaoLPAS,"SUB")==0){
                    //Caso o argumento da instrucao seja um numero 
                    if(verificaNum(vetorInstrucao[i].argumentoInstrucaoLPAS))
                        registrador -= loadNumero(vetorInstrucao[i].argumentoInstrucaoLPAS);
                    //Caso o argumento da instrucao seja um caractere
                    if(!verificaNum(vetorInstrucao[i].argumentoInstrucaoLPAS))
                        registrador -= loadVariavel(vetorRegistrador,vetorInstrucao[i].argumentoInstrucaoLPAS,contadorInstrucaoRead);
                }

                if(strcmp(vetorInstrucao[i].instrucaoLPAS,"MUL")==0){
                    //Caso o argumento da instrucao seja um numero 
                    if(verificaNum(vetorInstrucao[i].argumentoInstrucaoLPAS))
                        registrador *= loadNumero(vetorInstrucao[i].argumentoInstrucaoLPAS);
                    //Caso o argumento da instrucao seja um caractere
                    if(!verificaNum(vetorInstrucao[i].argumentoInstrucaoLPAS))
                        registrador *= loadVariavel(vetorRegistrador,vetorInstrucao[i].argumentoInstrucaoLPAS,contadorInstrucaoRead);
                }

                if(strcmp(vetorInstrucao[i].instrucaoLPAS,"DIV")==0){
                    //Caso o argumento da instrucao seja um numero -> Fazer o load caso seja uma variavel
                    if(verificaNum(vetorInstrucao[i].argumentoInstrucaoLPAS))
                        registrador /= loadNumero(vetorInstrucao[i].argumentoInstrucaoLPAS);
                    //Caso o argumento da instrucao seja um caractere
                    if(!verificaNum(vetorInstrucao[i].argumentoInstrucaoLPAS))
                        registrador /= loadVariavel(vetorRegistrador,vetorInstrucao[i].argumentoInstrucaoLPAS,contadorInstrucaoRead);
                }
            }
        }
    }
    liberaVetorRegistrador(vetorRegistrador);
    printf("\n");
}

//Função que inicia a Maquina de execucao
void iniciaMaquinaExecucao(){
    int opcao, contadorInstrucao=0;
    TInstrucao *vetorInstrucao;
    
    vetorInstrucao = alocaDinamicamenteVetor();

    do{
        printf("\nMaquina de Execucao LPAS\n");
        printf("\n1. Editar Programa\n2. Exibir Programa\n3. Executar Programa\n4. Sair Programa\n");
        printf("\nEscolha: ");
        scanf("%d",&opcao);

        switch(opcao){
        case 1:
            editarProgramaLPAS(vetorInstrucao, &contadorInstrucao);
            break;
        case 2:
            exibirProgramaLPAS(vetorInstrucao, contadorInstrucao);
            break;
        case 3:
            executarProgramaLPAS(vetorInstrucao,contadorInstrucao);
            break;
        }
    }while(opcao!=4);

    liberaVetorInstrucao(vetorInstrucao);
}

int main(){
    iniciaMaquinaExecucao();
    return 0;
}
