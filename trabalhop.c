//Eduardo Henrique Fernandes Marques -23.2.4010

//Incluindo as bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_RESET            "\x1b[0m"
#define ANSI_COLOR_CYAN       "\x1b[36m"

//Estrutura para ler o cabeçalho
typedef struct{
    int tam;
    int *num;
    int posicao;
}Cabecalho;

//Função que retorna 1 se o comando for dado em letra minuscula e 0 se for em maiuscula 
int retornaCaps(char comando[]){
    
        if(comando[2]>=97)
            return 1;
        else
            return 0;
    
    
}
//Função para criar a matriz
char **criaMatriz(int m,int n){
    char **matriz = malloc(m*sizeof(char*));
    for (int i = 0; i < m; i++)
    {
        matriz[i]=malloc(n*sizeof(char));
    }
    
    return matriz;
}

//Função para liberar a matriz
void liberaMatriz(char **A,int m){
    for (int i = 0; i < m; i++)
    {
        free(A[i]);
    }
    free(A);
}

//Função para preencher com x a posição desejada
char preencheX(){
    char x = 'x';
    return x;
}

//Função para preencher com - a posição desejada
char preencheTraco(){
    char t = '-';
    return t;
}

//Função para preencher com . a posição desejada
char preenchePonto(){
    char p = '.';
    return p;
}

//Função para salvar as modificações no nonograma
void salvar(int argc, char *argv[],char **matriz,int n, int m,Cabecalho *lins, Cabecalho *cols){
    //Criando um arquivo para escrever
    FILE *arquivoB;
    char nome[20];

    printf("Insira o nome do arquivo para salvar: ");
    scanf("%s",nome);
    int tam = strlen(nome);

    if(tam>=5)
        arquivoB = fopen(nome,"w+");
    else
        arquivoB = fopen(argv[argc-1],"w");

    //Escrevendo o tamanho da matriz
    fprintf(arquivoB,"%d %d\n",n,m);

    //Escrevendo os valores dos cabeçalhos
    for (int i = 0; i < n; i++)
    {   
        fprintf(arquivoB,"\n");
        fprintf(arquivoB,"%d ",lins[i].tam);

        for (int j = 0; j < lins[i].tam; j++)
        {
            fprintf(arquivoB,"%d ",lins[i].num[j]);
        }
        
    }

    for (int i = 0; i < m; i++)
    {   
        fprintf(arquivoB,"\n");
        fprintf(arquivoB,"%d ",cols[i].tam);

        for (int j = 0; j < cols[i].tam; j++)
        {
            fprintf(arquivoB,"%d ",cols[i].num[j]);
        }
        
    }

    //Escrevendo o nonograma
    for (int i = 0; i < n; i++)
    {
        fprintf(arquivoB,"\n");
        for (int j = 0; j < m; j++)
        {
            fprintf(arquivoB,"%c ",matriz[i][j]);
        }
        
    }
    
    fclose(arquivoB);

}

//Função para impedir o usuario de ultrapassar o número de marcações indicado pelas coordenadas do jogo
int impede(char **matriz,int n, int m, Cabecalho *lins, Cabecalho *cols){
    //Criando 2 contadores
    int *cont;
    int *cont2;
    

    //Criando variaveis para receber os valores das coordenadas em cada linha e coluna
    int *resultadoL = malloc(n*sizeof(int));
    int *resultadoC = malloc(m*sizeof(int));
    
    for (int i = 0; i < n; i++)
    {
        resultadoL[i]=0;
    }

    for (int i = 0; i < m; i++)
    {
        resultadoC[i]=0;
    }

    //Alocando os contadores que vao receber o número de x por linha/coluna do arquivo
    cont = malloc(n*sizeof(int));

    cont2 = malloc(m*sizeof(int));

    //Zerando as posições do contador
    for (int i = 0; i < n; i++)
    {
        cont[i]=0;
    }

    for (int i = 0; i < m; i++)
    {
        cont2[i]=0;
    }

    //Verificando quantas marcações cada linha do nonograma possui
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if(matriz[i][j]=='x')
                cont[i]++;
        }
        
    }

    //Verificando quantas marcações cada coluna do nonograma possui
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(matriz[j][i]=='x')
                cont2[i]++;
        } 
    }

    //Armazenando o numero de marcações cada linha/coluna deve ter
    for (int i = 0; i < n; i++)
    {
    
        for (int j = 0; j < lins[i].tam; j++)
        {
            resultadoL[i] += lins[i].num[j];
        }
        
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < cols[i].tam; j++)
        {
            resultadoC[i] += cols[i].num[j];
        }
        
    }

    //Se o numero de marcações de linha/coluna for maior que as coordenadas passadas ira retornar 1
    for (int i = 0; i < n; i++)
    {
        if(cont[i]>resultadoL[i])
            return 1;
    }

    for (int i = 0; i < m; i++)
    {
        if(cont2[i]>resultadoC[i])
            return 1;
    }
    
    //Liberando os contadores
    free(cont);
    free(cont2);
    free(resultadoC);
    free(resultadoL);

    return 0;

}


//Função que verifica se o jogador concluiu o jogo
int verificaFuncao(char **matriz,int n,int m,Cabecalho *lins, Cabecalho *cols){
    //Criando 4 contadores
    int *cont;
    int *cont2;
    int k=0,v=0;

    //Criando variaveis para receber o numero de elementos em cada linha e coluna
    int resultadoL = 0;
    int resultadoC = 0;
    
    //Alocando o contador que vai receber o número de linhas do arquivo
    cont = malloc(n*sizeof(int));

    cont2 = malloc(m*sizeof(int));

    //Zerando as posições do contador
    for (int i = 0; i < n; i++)
    {
        cont[i]=0;
    }

    for (int i = 0; i < m; i++)
    {
        cont2[i]=0;
    }
    
    //Verificando quantas marcações cada linha do nonograma possui
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if(matriz[i][j]=='x')
                cont[i]++;
        }

    }

    //Verificando quantas marcações cada coluna do nonograma possui
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if(matriz[i][j]=='x')
                cont2[j]++;
        }
        
    }
    

    //Verificando se o número de marcações do contador é igual ao número de marcações correto do nonograma
    for (int i = 0; i < n; i++)
    {
        k++;
        resultadoL = 0;
        

        for (int j = 0; j < lins[i].tam; j++)
        {
            resultadoL+=lins[i].num[j];
        }
        
        //Se o numero de x indicado pelo jogo for igual ao numero de marcacoes, V incrementa
        if(cont[i]==resultadoL)
            v++;
    }

    for (int i = 0; i < m; i++)
    {
        k++;
        resultadoC = 0;

        for (int j = 0; j < cols[i].tam; j++)
        {
            resultadoC+=cols[i].num[j];
        }

        if(cont2[i]==resultadoC)
            v++;
    }
    
    
    free(cont);
    free(cont2);

    //K e incrementado em toda iteracao, porem V so é incrementado se o numero de x for igual ao informado pelo jogo
    //Entao se K for igual a V, a função retorna 1, caso contrario, retorna 0
    if(k==v)
        return 1;
    else
        return 0;
    
}

void imprimir(char **matriz,int n, int m, Cabecalho *lins, Cabecalho *cols){
    int maiorl,maiorc;
    maiorl = lins[0].tam;
    maiorc = cols[0].tam;
    
    //calcula o maior numero de elementos linha
    for (int i = 1; i < n; i++)
    {
        if(lins[i].tam>maiorl){
            maiorl = lins[i].tam;
            }
    }
    
    //calcula o maior numero de elementos coluna
    for (int i = 1; i < m; i++)
    {
        if(cols[i].tam>maiorc){
            maiorc = cols[i].tam;
            }
    }    
    
    //Zerando a variavel de posicao que percorre os elementos
    for (int i = 0; i < n; i++)
    {
        lins[i].posicao=0;
    }

    for (int i = 0; i < m; i++)
    {
        cols[i].posicao=0;
    }
    
    
    //Dividir a impressao em 2 partes: cabeçalho superior, e matriz e cabeçalho lateral
    
    for (int i = maiorc; i >= 0; i--)
    {
        
        for (int j = 0; j < maiorl+1+m  ; j++)
        {
            
            if(maiorl + 1 - j > 0 ) {
            //printa os espacos referentes aos coeficientes da coluna
                printf("   ");
            }
            else if(i == 0){
                printf("%c  ", 'A' + j - maiorl - 1);
            }
            //Quando a quantidade de numeros das colunas for maior ou igual a i, ira printar na linha o cabeçalho
            else if(cols[j-maiorl-1].tam >= i){
                
                    printf("%d  ",cols[j-maiorl-1].num[cols[j-maiorl-1].posicao]);
                    cols[j-maiorl-1].posicao++;
            }
            else printf("   ");
        }

        printf("\n");   
        
    }

    //Variavel pra receber o numero de linhas
    int tamAux=0;

    //Printando o cabeçalho lateral
    for (int i = 0; i < n ; i++)
    {
        tamAux = lins[i].tam;
        for (int j = 0; j < maiorl - tamAux; j++)
        {
            printf("   ");
        }
        
        for (int j = 0; j < tamAux; j++)
        {
            if(lins[i].num[j]>9)
                printf("%d ",lins[i].num[j]);
            else
                printf("%d  ",lins[i].num[j]);
        }



        printf("%c  ", 'A' + i);
        for (int j = 0; j < m; j++)
        {
            if(matriz[i][j]=='x' || matriz[i][j]=='X')
                printf(ANSI_COLOR_RED"%c  "ANSI_RESET,matriz[i][j]);
            else
                printf("%c  ",matriz[i][j]);
        }
        printf("\n");
    }
    

}

//Criando função main já passando os argumentos como parâmetro
int main(int argc, char *argv[]){
    
    //Declarando as variáveis
    Cabecalho *lins,*cols;
    int n,m;
    char **matriz;
    char comando[16];
    int sz;
    int x,y,mascMin;
    int verifica;
    int imp;

    //Criando o arquivo que irá ser utilizado
    FILE *arquivo;
    //Abrindo o arquivo
    arquivo = fopen(argv[argc-1],"r");
    if(arquivo==NULL){
        printf("Falha na abertura");
        return 0;
    }
    //Lendo o tamanho do nonograma
    fscanf(arquivo,"%d%d",&n,&m);

    //Verificando se alguma coordenada do tamanho da matriz e superior a 26
    if(n>26 || m>26){
        printf("Arquivo invalido!");
        fclose(arquivo);
        return 0;
    }


    lins = malloc(n*(sizeof(Cabecalho)));
    cols = malloc(m*(sizeof(Cabecalho)));
    //Alocando a matriz
    matriz = criaMatriz(n,m);

    //Alocando e lendo o cabeçalho das linhas
    for (int i = 0; i < n; i++)
    {
        fscanf(arquivo,"%d",&lins[i].tam);
        lins[i].posicao=0;
        lins[i].num=malloc(lins[i].tam*sizeof(int));
        for (int j = 0; j < lins[i].tam; j++)
        {
            fscanf(arquivo,"%d",&lins[i].num[j]);
            
        }
        
    }

    //Alocando e lendo o cabeçalho das colunas
    for (int i = 0; i < m; i++)
    {
        fscanf(arquivo,"%d",&cols[i].tam);
        cols[i].posicao=0;
        cols[i].num=malloc(cols[i].tam*sizeof(int));
        for (int j = 0; j < cols[i].tam; j++)
        {
            fscanf(arquivo,"%d",&cols[i].num[j]);
            
        }
        
    }
    
    //Lendo os elementos da matriz
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fscanf(arquivo," %c",&matriz[i][j]);
            
        }
        
    }

    //Fechando o arquivo
    fclose(arquivo);
    //Imprimindo o nonograma
    imprimir(matriz,n,m,lins,cols);
    
    printf("\nBem vindo ao Nonograma!");
    //Criando uma repetição para ler os comandos
    do{
        //Inserindo o comando com o fgets
        printf("\nDigite um comando: ");
        fflush(stdin);
        fgets(comando,15,stdin);

        printf("\n");
        //Retirando o \n do comando
        sz=strlen(comando);
        comando[sz-1]='\0';

        //Verificando qual o comando e caso seja um comando de preenchimento é feito a converção das letras para valores de posição do nonograma
        if(comando[0]=='x' || comando[0]=='X'){
            mascMin = retornaCaps(comando);
            if(mascMin==1){
                x = comando[2]-97;
                y = comando[3]-97;
            }
            else if(mascMin==0){
                x = comando[2]-65;
                y = comando[3]-65;
            }
            matriz[x][y]=preencheX();
            //Chamando a função impede para impedir que o jogador marque uma posição que ultrapasse os valores dados pelas coordenadas
            imp = impede(matriz,n,m,lins,cols);
            
            //Se retornar 1 ele impede o jogador de marcar x na posição desejada e o avisa
            if(imp==1){
                matriz[x][y] = preenchePonto();
                printf("\nJogada invalida!\n");
            }
        }

        else if(comando[0]=='-'){
            mascMin = retornaCaps(comando);
            if(mascMin==1){
                x = comando[2]-97;
                y = comando[3]-97;
            }
            else if(mascMin==0){
                x = comando[2]-65;
                y = comando[3]-65;
            }
            matriz[x][y]=preencheTraco();
        }

        else if(comando[0]=='.'){
            mascMin = retornaCaps(comando);
            if(mascMin==1){
                x = comando[2]-97;
                y = comando[3]-97;
            }
            else if(mascMin==0){
                x = comando[2]-65;
                y = comando[3]-65;
            }
            matriz[x][y]=preenchePonto();
        }

        else if(strcasecmp(comando,"salvar")==0){
            salvar(argc,argv,matriz,n,m,lins,cols);
        }
        
        else if(strcasecmp(comando,"sair")==0){

            return 0;
        }
        
        //Imprimindo o nonograma
        imprimir(matriz,n,m,lins,cols);

        //Verificando se o jogador concluiu o jogo usando a função verificaFuncao
        verifica = verificaFuncao(matriz,n,m,lins,cols);
        
        if(verifica==1)
            printf("\nParabéns Jogador, você concluiu o jogo com sucesso!");
    }while(strcasecmp(comando,"sair")!=0);
    
    //Fazendo a liberação da matriz e dos cabeçalhos
    liberaMatriz(matriz,n);
    free(cols);
    free(lins);

    return 0;
}