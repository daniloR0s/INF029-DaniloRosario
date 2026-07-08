#include <stdio.h>
#include <stdlib.h>
#define TAM 10
#include "trabalho2.h"


void ordenar(int vet[], int tam){
    int temp = 0;
    for(int i = 0; i<tam - 1; i++){
        for(int j = 0; j<tam - i - 1; j++){
            if(vet[j] > vet[j + 1]){
                temp = vet[j];
                vet[j] = vet [j + 1];
                vet[j + 1] = temp;
            }
        }
    }
}
typedef struct node{
    int key;
    struct node *proximo;
    struct node *anterior;
}node;
typedef struct{
    node *cabeca;
    int qtd;
    int tam;
}lista;
lista *vetor[10];
int getQtdElementos(lista *vetor[10]){
    int cont = 0;
    for(int i = 0; i<10; i++){
        if(vetor[i] !=NULL){
            cont += vetor[i]->qtd;
        }            
    }
    return cont;
}
node *criarNode(int key){
    node *novo = malloc(sizeof(node));
    novo->key = key;
    novo->proximo = NULL;
    novo->anterior = NULL;
    return novo;
}
lista *criarLista(int tam){
    lista *l = malloc(sizeof(lista));
    if(l == NULL){
        return NULL;
    }
    l->cabeca = NULL;
    l->tam = tam;
    l->qtd = 0;
    return l;
}
node *procura(lista *l, int key){
    node *x = l->cabeca;
    while(x!=NULL && x->key != key){
        x = x->proximo;
    }
    return x;
}
void insert(node *no, lista *l){
    if(l->qtd < l->tam){
        if(l->cabeca == NULL){
            l->cabeca = no;
            l->cabeca->anterior = NULL;
            l->cabeca->proximo = NULL;
            l->qtd +=1;
            return;
        }
        node *x = l->cabeca;
        while(x->proximo!= NULL){
            x = x->proximo;
        }
        x->proximo = no;
        x->proximo->proximo = NULL;
        x->proximo->anterior = x;
        l->qtd +=1;
        return;
    }
}
void remover(lista *l, int key){
    node *x = procura(l, key);
    if(x == NULL){
        return;
    }
    else if(x!=NULL){
        if(x->anterior == NULL){
            l->cabeca = l->cabeca->proximo;
            if(l->cabeca != NULL){
                l->cabeca->anterior = NULL;
            }
        }
        else if(x->proximo == NULL){
            x->anterior->proximo = NULL;
        }
        else{
            x->proximo->anterior = x ->anterior;
            x->anterior->proximo = x -> proximo;
        }
        l->qtd = l->qtd - 1;
    }
    free(x);
}
void removerNoFinal(lista *l){
    node *x = l->cabeca;
    if(x == NULL){
        return;
    }
    while(x->proximo!=NULL){
        x=x->proximo;
    }
    if(x->anterior == NULL){
        l->cabeca = NULL;
    }else{
        x->anterior->proximo = NULL;
    }
    l->qtd--;
    free(x);
}
void aumentarTamanho(lista *l, int tamNov){
    l->tam += tamNov;
}
void ListarElementosDeTodasEstruturas(lista *vetor[10]){
    for(int i = 0; i<10; i++){
        if(vetor[i] !=NULL){
            node *x = vetor[i]->cabeca;
            printf("estrutura %i", i);
            printf("%i", vetor[i]->tam);
            printf("%i", vetor[i]->qtd);
            for(int j = 0; j<vetor[i]->qtd; j++){
                printf("%i", x->key);
                x= x->proximo;
            }
        }
    }
}
lista *montarListaEncadeadaComCabecote1(lista *vetor[]){
    lista *c = criarLista(50000);
    for(int i = 0; i<10; i++){
        if(vetor[i] !=NULL){
            node *x = vetor[i]->cabeca;
            for(int j = 0; j<vetor[i]->qtd; j++){
                node *a = criarNode(x->key);
                insert(a, c);
                x= x->proximo;
            }
        }
    }
    return c;
} 
void listarNumerosOrdenados(int vet[], lista *vetor[10]){
    int cont = getQtdElementos(vetor);
    lista *p = montarListaEncadeadaComCabecote1(vetor);
    node *x = p->cabeca;
    for(int i = 0; i<cont; i++){
        vet[i] = x->key;
        x = x->proximo;
    }
    ordenar(vet, cont);
    for(int i = 0; i<cont; i++){
        printf("%i\t", vet[i]);
    }
}
void listarNumerosOrdenadosPorEstrutura(int pos, int vetorAux[], lista *vetor[]){
    int cont = vetor[pos - 1]->qtd;
    node *x = vetor[pos - 1]->cabeca;
    for(int i = 0; i<cont; i++){
        vetorAux[i] = x->key;
        x = x->proximo;
    }
    ordenar(vetorAux, cont);
    for(int i = 0; i<cont; i++){
        printf("%i\t", vetorAux[i]);
    }
}
void inicializar(){
    for(int i = 0; i<10; i++){
        vetor[i] = NULL;
    }
}
void finalizar(){
    for(int i = 0; i<10; i++){
        if(vetor[i] == NULL)
            continue;
        node *x = vetor[i]->cabeca;
        int tam = vetor[i]->qtd;
        for(int j = 0; j<tam; j++){
            node *next = x->proximo;
            free(x);
            x = next;
        }
        free(vetor[i]);
        vetor[i] = NULL;
    }
}
int criarEstruturaAuxiliar(int posicao, int tamanho){
    int retorno = 0;
    retorno = SUCESSO;
    // a posicao pode já existir estrutura auxiliar
    if(posicao < 1 || posicao > 10 ){
        // se posição é um valor válido {entre 1 e 10}
        retorno = POSICAO_INVALIDA;        
    }else if(vetor[posicao - 1] != NULL){
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    }
    else if(tamanho<1){
        // o tamanho nao pode ser menor que 1
        retorno = TAMANHO_INVALIDO;
    }else{
        lista *l = criarLista(tamanho);
        if(l == NULL){
            // o tamanho ser muito grande
            retorno = SEM_ESPACO_DE_MEMORIA;
        }else{
            vetor[posicao - 1] = l; 
        }
    }
    
    // deu tudo certo, crie

    return retorno;
}
int inserirNumeroEmEstrutura(int posicao, int valor){
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;
    retorno = SUCESSO;
    if(posicao < 1 || posicao > 10 ){
        // se posição é um valor válido {entre 1 e 10}
        posicao_invalida = 1;     
        return POSICAO_INVALIDA;   
    }
    if(vetor[posicao - 1] == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    if(vetor[posicao - 1] != NULL){
        existeEstruturaAuxiliar = 1;
        if(vetor[posicao - 1] ->qtd < vetor[posicao - 1]->tam){
            temEspaco = 1;
        }
    }

    if (posicao_invalida)
        retorno = POSICAO_INVALIDA;
    else
    {
        // testar se existe a estrutura auxiliar
        if (existeEstruturaAuxiliar)
        {
            if (temEspaco)
            {
                node *x = criarNode(valor);
                insert(x, vetor[posicao - 1]);
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}
int excluirNumeroDoFinaldaEstrutura(int posicao){
    int retorno = SUCESSO;
    if(posicao<1 || posicao>10){
        retorno = POSICAO_INVALIDA;
    }
    else if(vetor[posicao - 1] ==NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else if(vetor[posicao - 1] ->cabeca == NULL){
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    }else{
        removerNoFinal(vetor[posicao - 1]);
    }    
    return retorno;
}
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor){
    int retorno = SUCESSO;
    if(posicao<1 || posicao>10){
        retorno = POSICAO_INVALIDA;
        return retorno;
    }else if(vetor[posicao - 1] ==NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
        return retorno;
    }
    node *x = procura(vetor[posicao - 1], valor);
    if(vetor[posicao - 1] ->cabeca == NULL){
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
        return retorno;
    }else if(x == NULL){
        retorno = NUMERO_INEXISTENTE;
        return retorno;
    }else{
        remover(vetor[posicao - 1], valor);
    }
    return retorno;

}
int ehPosicaoValida(int posicao){
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    int retorno = SUCESSO;
    if(posicao<1 || posicao>10){
        retorno = POSICAO_INVALIDA;
        return retorno;
    }
    if(vetor[posicao - 1] ==NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
        return retorno;
    }
    int cont = vetor[posicao - 1]->qtd;   
    if(cont > vetor[posicao-1]->tam)
        cont = vetor[posicao-1]->tam; 
    node *x = vetor[posicao - 1]->cabeca;
    for(int i = 0; i<cont; i++){
        vetorAux[i] = x->key;
        x = x->proximo;
    }

    return retorno;
}
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    int retorno = 0;
    retorno = SUCESSO;
    if(posicao<1 || posicao > 10){
        retorno = POSICAO_INVALIDA;
        return retorno;
    }else if(vetor[posicao - 1] == NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
        return retorno;
    }
    int cont = vetor[posicao - 1]->qtd;
    if(cont > vetor[posicao-1]->tam)
        cont = vetor[posicao-1]->tam;
    lista *c = criarLista(50000);
    node *x = vetor[posicao - 1]->cabeca;
    for(int j = 0; j<vetor[posicao - 1]->qtd; j++){
        node *a = criarNode(x->key);
        insert(a, c);
        x= x->proximo;
    }
    x = c->cabeca;
    for(int i = 0; i<cont; i++){
        vetorAux[i] = x->key;
        x = x->proximo;
    }
    ordenar(vetorAux, cont);
    return retorno;
}
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    int retorno = 0;
    retorno = SUCESSO;
    int cont = getQtdElementos(vetor);
    if(cont == 0){
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
        return retorno;
    }
    lista *p = montarListaEncadeadaComCabecote1(vetor);
    node *x = p->cabeca;
    for(int i = 0; i<cont; i++){
        vetorAux[i] = x->key;
        x = x->proximo;
    }
    return retorno;
}
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){

    int retorno = 0;
    retorno = SUCESSO;
    int cont = getQtdElementos(vetor);
    if(cont == 0){
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
        return retorno;
    }
    lista *p = montarListaEncadeadaComCabecote1(vetor);
    node *x = p->cabeca;
    for(int i = 0; i<cont; i++){
        vetorAux[i] = x->key;
        x = x->proximo;
    }
    ordenar(vetorAux, cont);
    return retorno;
}
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){
    if(posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;

    if(vetor[posicao-1] == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    int novoTam = vetor[posicao-1]->tam + novoTamanho;

    if(novoTam < 1)
        return NOVO_TAMANHO_INVALIDO;

    while(vetor[posicao-1]->qtd > novoTam)
    {
        removerNoFinal(vetor[posicao-1]);
    }

    vetor[posicao-1]->tam = novoTam;

    return SUCESSO;
}
int getQuantidadeElementosEstruturaAuxiliar(int posicao){

    int retorno = 0;
    if(posicao<1 || posicao>10){
        retorno = POSICAO_INVALIDA;
    }else if(vetor[posicao - 1] ==NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }else if(vetor[posicao - 1] ->cabeca == NULL){
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    }else{
        return vetor[posicao - 1]->qtd;
    }
    return retorno;
}
No *montarListaEncadeadaComCabecote(){
    No *inicio = NULL;
    No *fim = NULL;

    for(int i = 0; i < 10; i++)
    {
        if(vetor[i] != NULL)
        {
            node *x = vetor[i]->cabeca;

            while(x != NULL)
            {
                No *novo = malloc(sizeof(No));

                if(novo == NULL)
                {
                    destruirListaEncadeadaComCabecote(&inicio);
                    return NULL;
                }

                novo->conteudo = x->key;
                novo->prox = NULL;

                if(inicio == NULL)
                {
                    inicio = novo;
                    fim = novo;
                }
                else
                {
                    fim->prox = novo;
                    fim = novo;
                }

                x = x->proximo;
            }
        }
    }

    return inicio;
}
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
    int i = 0;

    while(inicio != NULL)
    {
        vetorAux[i++] = inicio->conteudo;
        inicio = inicio->prox;
    }
}
void destruirListaEncadeadaComCabecote(No **inicio){
    No *aux;

    while(*inicio != NULL)
    {
        aux = *inicio;
        *inicio = (*inicio)->prox;
        free(aux);
    }

    *inicio = NULL;
}


