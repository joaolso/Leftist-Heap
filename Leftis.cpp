#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Turma EDPA 2018.2 - Um agradecimento especial a todos envolvidos nesse projeto         //
// Discentes: Divino 			|	Orientadora: Prof(a) Dr(a) Marcia Rodrigues Cappelle  //
//			  Joao Lucas
//			  Naiane
//			  Paulo Henrique

// - Leftist Heap //


// Variaveis Globais //
					
int opf=0;
double total_t=0;

// Funcoes  //
struct node * merge(struct node*, struct node*);

// Estrutura do No/Arvore //
struct node {													// Contrucao da estrutura dos NOS
	int key, ccn;
	struct node *right, *left;
}


*temp, *root;

struct node * deletar(struct node *root){
		root=merge(root->right,root->left);
}

int altura (struct node *root){									// Funcao pra calcular a altura da arvore
	int u=0,v=0;
	if (root == NULL)
		return -1;
	
	u = altura(root->left);
	v = altura(root->right);
	
	if (u > v) 
		return u+1;
	else
		return v+1; 
}

int visualiza(struct node *ra){									// funcao que imprime em in-Ordem
	if(ra!=NULL){												// verifica a condicao de NULL (folha da raiz)
		visualiza(ra->left);									// recurssao filho da esquerda
		printf(" |%d| ",ra->key);								// imprime na tela
		visualiza(ra->right);									// recurssao filho da direita
	}
}

int distance(struct node *m){									// Calcula o CCN
	if(m==NULL)
		return(-1);
	else
	return(m->ccn);
}

struct node * merge (struct node *root, struct node *newnode){
	if (root==NULL)												// condicoes de parada da recurssao
		return newnode; 										// retorna novo NO
	if (newnode==NULL) 											// condicoes de para da recurssao
		return root;											// retorna RAIZ
	if (newnode->key < root->key){								// verifica se o novo NO e menor que a RAIZ
		temp=root;												// operacao de troca de NO
		root=newnode;										
		newnode=temp;
	}
	
	root->right = merge(root->right, newnode);					// recurssao
																// A magica comeca aqui
	if (distance(root->right) > distance(root->left)){			// Chama a funcao pra calcular o CNN
		opf++;													// incrementa o contador de operacoes troca de filho
		temp=root->right;										// faz a troca do filho da esquerda com o da direita
		root->right=root->left;									//*
		root->left=temp;	
	}
	if (root->right==NULL)										// verifica se o filho da direita e NULL pra mudar o CNN pra 0
		root->ccn=0;
	else
		root->ccn = 1+(root->right->ccn);						// como o da direita e o filho mais proximo, ele incrementa a raiz 			
	return (root);							
}														
												
struct node * inserir (int valor) {
	if (root->key==0){											// Verifica se a primeira vez, logo eh preciso atribuir valor a raiz
		root->key=valor;
	}else{														// Funcao inseri novo no, tabalha juntamente da funcao merge						
		struct node *newnode;									// Constroi o pronteiro
		newnode=(struct node *)malloc(sizeof(struct node));		// Aloca espaco na memoria
		newnode->right=NULL;									// default inicilizacao e garantia de nao coleta de lixo	
		newnode->left=NULL;										// *
		newnode->ccn=0;											// *
		newnode->key = valor;									// *
		root=merge(root, newnode);								// *
	}
	return (root);
}

struct node * inserirAle (int qtd) {
	clock_t start_t = clock();

	for (int i=0;i<=qtd;i++){
	int valor = ( rand() % qtd );	
	if (root->key==0)												// Verifica se a primeira vez, logo eh preciso atribuir valor a raiz
		root->key=valor;
		else{														// Funcao inseri novo no, tabalha juntamente da funcao merge						
			struct node *newnode;									// Constroi o pronteiro
			newnode=(struct node *)malloc(sizeof(struct node));		// Aloca espaco na memoria
			newnode->right=NULL;									// default inicilizacao e garantia de nao coleta de lixo	
			newnode->left=NULL;										// *
			newnode->ccn=0;											// *
			newnode->key = valor;									// *
			root=merge(root, newnode);								// *
		}
	}
	clock_t end_t = clock();
	total_t = ((double)(end_t - start_t)/(CLOCKS_PER_SEC/1000));
	return (root);
}

void ins () {
	while(1){
	printf("\n 1.Manual  2.Automatico  3.Sair\n");
	int valor,opc=0;
	int paratudo=0;
	printf(" :");
	scanf("%d",&opc);
		switch(opc){
		case 1:
			opf=0;
			system("cls");
			printf("Informe o valor: ");
			scanf("%d",&valor);
			inserir(valor);
			return;
			break;
		case 2:
			system("cls");
			printf("Informe o total de insercoes: ");
			scanf("%d",&valor);
			inserirAle(valor);
			if (root!=NULL){
				printf("\n \n Raiz: %d\n",root->key);
				printf(" # Altura da Arvore: %d\n",altura(root));
				printf(" # CCN Raiz: %d\n",root->ccn);
				printf(" # Qtd de rotacoes(filhos): %d\n", opf);
				printf(" # Tempo (ms): %f \n", total_t);
			}
			return;
			break;
		case 4:
			return;
		default:
			break;
		}
		if(paratudo==1)
		break;
	}
}

int main(){

	root=(struct node *)malloc(sizeof(struct node));		//Constoi a raiz ao iniciar o programa
	root->right=NULL;
	root->left=NULL;
	root->key=0;
	root->ccn=0;
	
	while(1){
		printf("\n Menu: Leftist Heap \n 1.Inserir 2.Visualizar 3.Deletar(Min) 4.Sair\n");
		int valor,opc=0;
		int paratudo=0;
		int ex=0;
		printf(" :");
		scanf("%d",&opc);
			switch(opc){
			case 1:
				ins ();
				break;
			case 2:
				opf=0;
				visualiza(root);
				if (root!=NULL){
					printf("\n \n Raiz: %d\n",root->key);
					printf(" # Altura da Arvore: %d\n",altura(root));
					printf(" # CCN Raiz: %d\n",root->ccn);
					printf(" # Qtd de rotacoes(filhos): %d\n", opf);
					printf(" # Tempo (ms): %f \n", total_t);
				}
				break;
			case 3: {
				opf=0;
				printf("Qtd de Exclusoes: ");
				scanf("%d", &ex);
				
				clock_t start = clock();
				for (int i=0;i<ex;i++){
					root=deletar(root);
				}
				clock_t end = clock();
				total_t = ((double)(end - start)/(CLOCKS_PER_SEC/1000));
				printf(" # Tempo (ms): %f \n", total_t);
				printf(" # Qtd de rotacoes(filhos): %d\n", opf);		
				if (root!=NULL){
					printf("\n \n Raiz: %d\n",root->key);
					printf(" # Altura da Arvore: %d\n",altura(root));
					printf(" # CCN Raiz: %d\n",root->ccn);
					printf(" # Qtd de rotacoes(filhos): %d\n", opf);
					printf(" # Tempo (ms): %f \n", total_t);	
				}	
				break;
				}
			case 4:
				paratudo=1;
				break;
			default:
				break;
			}
			if(paratudo==1)
			break;
	}
}

